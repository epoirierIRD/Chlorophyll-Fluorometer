# Assembly Guide for Chlorophyll-Fluorometer

This guide provides detailed instructions on how to assemble the Chlorophyll-Fluorometer device.

## Prerequisites

Before starting the assembly process, ensure you have the following tools and components ready:

- Arduino IDE installed on your computer
- All electronic components listed in the [Components List](hardware/components.md)
- 3D printer for printing support structures
- Soldering equipment for assembling electronic circuits
- Basic hand tools (screwdrivers, pliers, etc.)

## Step 1: Clone the Repository

To get started, clone the project repository to your local machine:

```bash
git clone https://github.com/EnssatPhotonicsProjects/Chlorophyll-Fluorometer.git
```

## Step 2: Assemble the Electronic Components

### Using a Breadboard

If you are prototyping or prefer not to use a PCB, you can assemble the circuit on a breadboard. Refer to the [Circuit-diagram.pdf](hardware/Circuit-diagram.pdf) for detailed connections.

### Using a PCB

1. Download the PCB design file from the repository: [PCB File](hardware/Fluorometer_PCB/).
2. Order the PCB from a manufacturer or print it if you have the necessary equipment. For example, go to [JLCPCB](https://jlcpcb.com/), and in the field "Add gerber files" drop a zip of the folder /CAMoutputs situated at [this location](hardware/Fluorometer_PCB/).
You will receive a quality pro PCB and you can even choose the color.
3. Solder the components onto the PCB following the schematic diagram. 
Tip: As you will solder with you PCB upside down, start with the thin components (resistors,...) and finish with the thick ones (headers, capacitor, ...).

## Step 3: Assemble the Support Structures

Use the provided STL file to 3D print the necessary support structures with black PLA filament, and a filling density of 50%. Printing takes about 7 hours : 

- [LED and Photodiode Support](hardware/3D_ready_to_print_LED-Photodiode-Support.stl)

Assemble the parts according to the instructions provided in the [Assembly Manual](structure_assembly_guide.md).

## Step 4: Upload the Arduino Code

1. Open the `.ino` file in the Arduino IDE.
2. Connect your Arduino board to the computer.
3. Select the correct board and port in the Arduino IDE.
4. Upload the code to the Arduino board.

## Step 5: Calibration

Follow the calibration protocol described in the [Calibration Guide](calibration.md) to ensure accurate measurements:

1. Prepare the calibration standards.
2. Adjust the device settings according to the calibration data.
3. Verify the calibration by testing with known samples.

## Troubleshooting

If you encounter any issues during the assembly or operation of the device, open an issue in the repository.
