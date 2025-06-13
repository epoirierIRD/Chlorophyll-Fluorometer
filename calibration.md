# Calibration Guide for Chlorophyll-Fluorometer

This guide provides detailed instructions on how to calibrate the Chlorophyll-Fluorometer device.

## Prerequisites

Before starting the calibration process, ensure you have the following tools and components ready:

- The fluorometer completely closed and waterproof
- Various chlorophyll solutions of known concentration (minimum four solutions to ensure quality calibration)
- A container in which you can dip the fluorometer

## Step 1: Threshold in the dark

1. Put the fluorometer in a completely dark room, you can also use a black screen to hide completely the photodide.
2. Read the current value on the screen or via Bluetooth.

This value is the noise of the complete device.

## Step 2: Minimum value

1. Put clear water, if possible distilled water, in your container.
2. Dip the fluorometer in the water, make sure that there is no air between the window of the fluorometer and the surface of the water.
3. Read the current value.

This value is the minimum value that you should read, corresponding to a chlorophyll concentration of 0 µg/L. It will be the origin of your calibration line.

## Step 3: Calibration with chlorophyll solutions

1. Remove water from container, then put the first chlorophyll solution (with the smaller concentration) in the container.
2. As above, dip the fluorometer in the solution, check for air bubbles.
3. Read the current value.

This value corresponds to the concentration you tested. 

4. Repeat this process for all the solutions you have, increasing the concentration.

## Step 4: Draw the calibration line

1. Draw your measures in a data analysis and visualization program. On the x-axis put the concentration, on the y-axis put the current.
2. Fit the points with a linear model. You can adjust the ordinate at origin with the value you read in **Step 2**.

For concentrations between 0.5 and 100 µg/L, you should get a line similar to the figure below :

<p align="center">
  <img src="images/calibration.png" alt="calibration_line" width="700"/>
</p>

Your fluorometer is now calibrated.
