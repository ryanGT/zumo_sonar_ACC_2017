Overview
==============

This repository presents several Arduino sketches for using a
low-cost, sonar-based robotic vehicle for introducing dynamic systems
and control.  The vehicle can be built by attaching a sonar sensor
(such as the HC-SR04) to the Pololu Zumo shield for Arduino chassis.

Arduino Sketches
====================

`sonar_print_only.ino` does not command the robot to move at all; it
only prints the sonar output to the serial monitor.  This allows a
piece of masking tape to be place at the desired stopping distance for
demonstration purposes.


`zumo_sonar_simple.ino` uses a simple on/off control that will coast
past the desired stopping point.  This example is used to initiate a
discussion of the question "What is a dynamic system?".

`zumo_kp_cases.ino` uses proportional control and allows multiple
tests to be run while varying `Kp`.