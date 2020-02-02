# MakeHarvard2020

## Project Purpose

Many of the older apartments and dorms still use radiatiors to heat the room. The issue is that these units will cause the room to be too hot and the occupant will have to either shut the radiator off or open a window. The latter is a waste of energy. This project attempts to automate the switching proccess so that upon reaching a certain temp the Radiator switch is turned on or off. This might not work if your radiator does not have an accessible switch. 
## Materials List

* Arduino Uno
* Groove Base Shield
* Groove RGB-LCD display
* Groove Temperature Sensor
* Groove Button x 2
* Fixed Servo Motor
* 80/20 T slot profiles x 4
* Sheet of Wood

## Assembly Instructions

1. Connect the base shield to the arduino
2. Connect Servo motor signal to port 4 and 5V power and GND cables
3. Connect Temp sensor to A0 on base shield 
4. Connect Increase button to D2 and Decrease button to D3 on the base shield
5. Connect LCD to I2C on base shield
6. Cut 4 5x3.5" pieces of the wood sheet and 2 3.5x3.5 pieces for the box and the holes indicated in the diagram. Attach sides together except top.
7. Connect 2 sliders on the top side of each horizontal T-Profile
8. Connect 2 sliders to the inside of each horizontal T-Profie these will slide into the verticle T-profiles
8. Connect the 4 T slot profiles in a rectangle and the 2 horizontal bars should sit in between the 2 verticle T-Profiles
9. Mount Arduino And servo into box 
10 Put components in to their respective cutout (see diagram)
11. Mount box to Horizontal T-Profile Sliders

## Project Code Description

The code should be compiled and run on the Arduino Uno. It will display desired and current room temperature on the LCD. If the current temp is above or below the desired temperature by 20 degrees Farenheit or if it exceeds either the upper or lower threshold the servo will move and switch the radiator off or on. The occupant can adjust the desired Temp value by using the Up and Down buttons.
