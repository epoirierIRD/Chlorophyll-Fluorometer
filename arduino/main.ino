#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include "U8glib.h"
#include "SPI.h"
#include "SD.h"

// === Display Setup ===
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

// === ADC ===
Adafruit_ADS1115 ads;

// === Sampling & LED ===
const int ledPin = 3;
volatile bool sampleNow = false;
volatile bool inSamplingWindow = false;

bool ledState = false;
unsigned long lastWindowStart = 0;
unsigned long interruptCount = 0;

// === Signal Processing ===
float lowSample = 0;
bool lowSampleReady = false;
const int MA_WINDOW = 8;
float maBuffer[MA_WINDOW];
int maIndex = 0;
int maCount = 0;
float filteredSum = 0;
int filteredCount = 0;
const int maxFiltered = 200;

// === SD Card Shield ===
File currents;
const int chipSelect = 4;  

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

   Serial.begin(115200); // Optional debug

// === Display Init ===
  u8g.firstPage();
  do {
    u8g.setColorIndex(1); // 1 for white text on black background
    u8g.setFont(u8g_font_7x14); // simple font
    u8g.drawStr(0,12,"Starting...");
  } while (u8g.nextPage());
  delay(1000);

  // === ADC Init ===
  ads.begin();
  ads.setGain(GAIN_ONE);
  ads.setDataRate(128);

  // === Timer2 for ~128Hz ===
  cli();
  TCCR2A = (1 << WGM21);
  TCCR2B = (1 << CS22); // 64 prescaler
  OCR2A = 249;          // ~128Hz
  TIMSK2 |= (1 << OCIE2A);
  sei();

  // === SD Card Shield Init ===
  pinMode(SS, OUTPUT);
  if (!SD.begin(SPI_HALF_SPEED, chipSelect)) { 
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_7x14);
      u8g.setPrintPos(1, 12);
      u8g.print("SD initialization");
      u8g.setPrintPos(1, 24);
      u8g.print("failed");
    } while (u8g.nextPage());
    delay(10000);}

  currents = SD.open("currents.txt", FILE_WRITE);
  if (currents) {
    currents.println("Time (ms) Current (nA)");
    currents.close();
  } else {
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_7x14);
      u8g.setPrintPos(1, 12);
      u8g.print("error opening");
      u8g.setPrintPos(1, 24);
      u8g.print("currents.txt");
    } while (u8g.nextPage());
    delay(10000);}
  
  lastWindowStart = millis();
}

void loop() {
  unsigned long now = millis();

  // === Start Sampling Window ===
  if (!inSamplingWindow && (now - lastWindowStart >= 3000)) {
    inSamplingWindow = true;
    lastWindowStart = now;
    filteredSum = 0;
    filteredCount = 0;
    maIndex = 0;
    maCount = 0;
    lowSampleReady = false;
    u8g.firstPage();
    do {
    u8g.setPrintPos(1, 14);
    u8g.setFont(u8g_font_helvR14);
    u8g.print("Sampling...");
    } while (u8g.nextPage());
    delay(500);
  }

  // === End Sampling Window ===
  if (inSamplingWindow && (now - lastWindowStart >= 1000)) {
    inSamplingWindow = false;
    PORTD &= ~(1 << PORTD3);  // LED OFF
    ledState = false;

    if (filteredCount > 0) {
      //float avg = filteredSum / filteredCount; // voltage value
      float avg = (filteredSum / filteredCount)*10000;
      u8g.firstPage();
      do {
      u8g.setPrintPos(1, 14);
      u8g.setFont(u8g_font_helvR14);
      //u8g.println("Avg V : "); //print voltage value
      u8g.println("Avg nA : ");
      u8g.setPrintPos(1, 35);
      u8g.print(avg);
      } while (u8g.nextPage());
      currents = SD.open("currents.txt", FILE_WRITE);
      currents.print(now);
      currents.print(" ");
      currents.println(avg);
      currents.close();
    } else {

      u8g.firstPage();
      do {
        u8g.setPrintPos(1, 14);
        u8g.setFont(u8g_font_helvR14); 
        u8g.print("No data");
      } while (u8g.nextPage());
    }
    delay(1000);
  }

  // === Sampling Logic ===
  if (sampleNow && inSamplingWindow) {
    sampleNow = false;

    ledState = !ledState;
    if (ledState)
      PORTD |= (1 << PORTD3);
    else
      PORTD &= ~(1 << PORTD3);

    int16_t adc = ads.readADC_SingleEnded(0);
    float voltage = calculateVoltage(adc);

    // Adjust gain only on HIGH state
    if (ledState) adjustGain(voltage);

    if (!ledState) {
      lowSample = voltage;
      lowSampleReady = true;
    } else if (lowSampleReady && filteredCount < maxFiltered) {
      float signal = abs(voltage - lowSample);
      lowSampleReady = false;

      maBuffer[maIndex] = signal;
      maIndex = (maIndex + 1) % MA_WINDOW;
      if (maCount < MA_WINDOW) maCount++;

      float maSum = 0;
      for (int i = 0; i < maCount; i++) maSum += maBuffer[i];
      float smoothed = maSum / maCount;

      filteredSum += smoothed;
      filteredCount++;
    }
  }
}

// === ISR: 128 Hz Sampling ===
ISR(TIMER2_COMPA_vect) {
  sampleNow = true;
  interruptCount++;
}

// === Gain Compensation Voltage Calculation ===
float calculateVoltage(int16_t adc) {
  switch (ads.getGain()) {
    case GAIN_SIXTEEN: return adc * 0.256 / 32768.0;
    case GAIN_EIGHT:   return adc * 0.512 / 32768.0;
    case GAIN_FOUR:    return adc * 1.024 / 32768.0;
    case GAIN_TWO:     return adc * 2.048 / 32768.0;
    case GAIN_ONE:     return adc * 4.096 / 32768.0;
    default:           return adc * 4.096 / 32768.0;
  }
}

// === Auto Gain Adjustment on HIGH Samples Only ===
void adjustGain(float voltage) {
  if (voltage < 0.2)
    ads.setGain(GAIN_SIXTEEN);
  else if (voltage < 1.0)
    ads.setGain(GAIN_FOUR);
  else if (voltage < 2.0)
    ads.setGain(GAIN_TWO);
  else
    ads.setGain(GAIN_ONE);
}
