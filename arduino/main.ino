#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// === Display Setup ===
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Serial.begin(115200); // Optional debug

  // === Display Init ===
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("Starting...");
  display.display();
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
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Sampling...");
    display.display();
    delay(500);
  }

  // === End Sampling Window ===
  if (inSamplingWindow && (now - lastWindowStart >= 1000)) {
    inSamplingWindow = false;
    PORTD &= ~(1 << PORTD3);  // LED OFF
    ledState = false;

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    if (filteredCount > 0) {
      float avg = filteredSum / filteredCount;
      display.print("Avg V:");
      display.setCursor(0, 30);
      display.print(avg, 5);
    } else {
      display.print("No data");
    }
    display.display();
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
