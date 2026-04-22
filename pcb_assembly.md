# How to assemble the Fluorometer PCB

This guide provides detailed instructions on how to solder the different components
on PCB shiel A. Courtay version.

## Prerequisites

Before starting the assembly process, ensure you have the following tools and components ready:

- All electronic components listed in the [Components List](hardware/components.md)
- Soldering equipment for assembling electronic circuits
- Basic hand tools (screwdrivers, pliers, etc.)

## Step 1: order the PCB

There is very little chance that you will manufacture the PCB yourself. Better choose
a PCB manufacturer (ex: JLCPCB in China, Beta Layout EU). Got the the website and just drop the
 folder: [CAMOutputs](hardware/Fluorometer_PCB/CAMOutputs) as GERBER files. Don't forget to zip the 
 CAMOutputs folder before uploading it to the website.
 
 This is what you should see on the pcb manufacturer website:
 <p align="center">
  <img src="hardware/Fluorometer_PCB/acourtay_pcb_recto.png" width="400" />
  <img src="hardware/Fluorometer_PCB/acourtay_pcb_verso.png" width="400" />
</p>

## Step 2: Soldering the components step by step in good order

A key rule for this operation is to first solder flat components such as resistors and then thicker components such as capacitors. You will work with your components looking downwards. Your desk will pusk on them to keep them in position. The tricky thing is to have them soldered close to the board.

In fact, on this project we only use THT (*Through Hole Technology*) components. This means that we will often turn the PCB upside down to do the soldering. It would be diffrent with SMD (*Surface-Mount Device*), smaller components used in modern electronics that are mounted directly on the pcb surface.

### Open a PCB drawing showing the postion of the components

To know where to place each component, you need a precise plan. Use the document [Fluorometer_routing.pdf](hardware/Fluorometer_PCB/Fluorometer_routing.pdf).
Below is a detailed picture of the document.
<p align="center">
  <img src="images/PCB_assembly/fluorometer_routing.png" width="800" />
</p>

NB: The bridges showed in red have benn implemented in the PCB you have.

### Start soldering the 3 resistors: 4.75 Ω, 273 Ω (can be 270 Ω), 100 kΩ

No worries standard resistors don't have polarity. They can be connected in either direction in a circuit.

**⚠️** : Place the resistors close to the board. Turn your pcb upside down with the resistors aginst the desk to keep them in position. Immobilize the pcb with clamps. You need your two hands to solder.

<p align="center">
  <img src="images/PCB_assembly/resistors_soldered.jpg" width="400" />
</p>

### Solder 8 contacts sockets (x2) and then the transistor PN2222A (lower left corner)

**⚠️** : The NPN transistor is polarized and must be connected in the correct orientation. The position of the flat face of the components shows you the proper orientation.

<p align="center">
  <img src="images/PCB_assembly/8sockets_soldered.jpg" width="300" />
  <img src="images/PCB_assembly/transitor_soldered.jpg" width="400" />
</p>

### Solder x3 wire-to-board terminal blocks (green, bottom)

<p align="center">
  <img src="images/PCB_assembly/wire_to_board.jpg" width="400" />
</p>

🔥 A nice alignment of the blocks is not easy to achieve!

### Solder x1 DC Power connector (left side of the picture below)

**⚠️** : The soldering holes are big, you will need a good amount of tin for soldering the 3 pins of the DC power connector. It must be robust. However the ideal would be to have a flat solder joint to avoid any contact with the DC connector top of the arduino UNO. See that in the next step.

<p align="center">
  <img src="images/PCB_assembly/DC_power_soldered.jpg" width="400" />
</p>

### Solder male headers connectors HE14 2.54mm to purple PCB board (4 pc)

The purple custom PCB board is called a shield because it comes above the arduino UNO. 
The arduino UNO comes with female pin headers 2.54 mm (0.1") pitch.
Therefore the PCB must me fitted with male pin headers 2.54mm to fit together with the arduino UNO.

1. Cut the male pin headers as per the PCB board: x6 (1 pc), x8 (2 pcs), x10 (1 pc)
2. Insert the short end of the male pin headers in the PCB board. Beware of the board side
3. **⚠️** :Solder only 2 ends of the male headers
4. Make sure your arduino uno is note powered. Assemble your pcb with the arduino and check for correct alignement of the pins. Just like the above picture.
5. Once you are happy with the position of the shield on the arduino, kepp them joined and solder the rest of the male pins headers on the PCB board.
6. This is what you get at the end once you have unplugged the pcb from the arduino UNO.
<p align="center">
  <img src="images/PCB_assembly/dc_power_contact.jpg" width="300" />
  <img src="images/PCB_assembly/dc_connector_issue.jpg" width="400" />
</p>

🔥 At the stage, you may have noticed an issue (pic above). If the solder joints of the DC connector are too big, they block on the top of the arduino UNO DC connector preveting the PCB male header to be fully inserted in the arduino UNO female headers. 
However don't worry, it will work. You may trim off the solder joints to avoid that.

### Keep going with soldering the x6 female headers that will hold the ADS1115 (yellow below)

To do that proceed just as above using component ADS1115 to make sure that the alignment of the female headers will be correct once soldered on your PCB.

<p align="center">
  <img src="images/PCB_assembly/ads1115 alignment.jpg" width="350" />
  <img src="images/PCB_assembly/female_headers_ADS1115.jpg" width="400" />
</p>

### Solder the 2 capacitors 150 μF, ⚠️ beware of the polarity

- **Identifying capacitor polarities:**

Usually, electrolytic/tantalum capacitors do have a + and − pin.

On an electrolytic capacitor:

    + (positive) = usually the longer leg
    − (negative) = usually the shorter leg
The body also has a marking: A stripe with “− − −” indicates the negative side

So:

👉 Striped side = negative (−)

👉 Opposite side = positive (+)


<p align="center">
  <img src="images/PCB_assembly/capacitor_150uF_polarity-.jpg" width="450" />
  <img src="images/PCB_assembly/Capacitor_150uF_polarity+.jpg" width="400" />
</p>

The position of the + pin of the capacitor is indicated on the PCB. Refer to that in order to orientate your capacitor before soldering.
- **Soldering the capacitors**

Insert the capacitors in the holes, turn your PCB upside down. Immobilize it and solder.

<p align="center">
  <img src="images/PCB_assembly/placing_capacitors.jpg" width="350" />
  <img src="images/PCB_assembly/capacitors_mounted.jpg" width="400" />
</p>


### Solder the SD card 8 pin connector NSK254-8 on the PCB


This part will be about soldering the connector on the PCB board that will enable the connection with the SD card module GT126.
At this stage you have few options depending on the components you have with you. 

*A possible alternative would be to solder a x8 female header instead and use DuPont wires.*

We rather like to use a 8 wires ribbon for a better durability. That's why in this example we choose to solder a NSK254-8 connector because we have them in stock together with a ribbon made with the female NSK254-8F + 20 cm wires.

<p align="center">
  <img src="images/PCB_assembly/NSK254-8_male.png" width="200" />
  <img src="images/PCB_assembly/8wires_ribbon_NSK254-8F.png" width="200" />
</p>

<p align="center">
  <em>NSK254-8 male header and 8-wire ribbon cable (female connector NSK254-8F)</em>
</p>

- **Solder the NSK254-8 male connector on the PCB board. Beware of the orientation.**

Don't forget to cut the rest of the legs once the solder joint is good. Do that after each soldering step.

<p align="center">
  <img src="images/PCB_assembly/SD_card_connector_pcb.jpg" width="400" />
  <img src="images/PCB_assembly/plier_use_cut_wires.jpg" width="250" />
  <img src="images/PCB_assembly/SD_card_ribbon_connector_on.jpg" width="300" />
</p>

### Adapt the 8 wires ribbon

The [8 wires ribbon](https://www.gotronic.fr/art-connecteur-nsk254-8f-15369.htm) we purchased from Gotronics France (Connector NSK254-8F female 8 pins + wires 20 cm, Code : 48670) comes with an unterlinated end.
The task is to solder the same NSK254-8F at the other end. Solder and use heat-shrink tubing to cover the joints.

⚠️: Beware of the colors: don't mix them.


<p align="center">
  <img src="images/PCB_assembly/8wires_ribbon_modified.jpg" width="300" />
</p>

### Place the components : MAX660CPA+ voltage converter, TL081 Operational amplifier, ADS115 16bit ADC

⚠️: **Orientation of the components is crucial at this step**. Please refer to the picture below.
You can see keying features on Max660 and TL081. For the ADC, match the pins of the component with the labels of the PCB board.

<p align="center">
  <img src="images/PCB_assembly/placing_max_tl081.jpg" width="400" />
</p>

### Solder the OLED screen 128x64 DFR0650 with care

You are almost there 😀. Last step is to solder the OLED screen to the PCB board.
Align the OLED pins with the labels on the PCB. Watch for the orientation and the alignment of the screen with the PCB for a nice looking.

<p align="center">
  <img src="images/PCB_assembly/oled_screen_done.jpg" width="300" />
  <img src="images/PCB_assembly/oled_screen_closeup.jpg" width="300" />
</p>
kfkfkfkf




- 😀 Smile
- 😎 Cool
- 🚀 Rocket

- ⚙️ Settings
- 🧠 Brain

