## ECE595-Midterm-Project
Midterm Project for ECE 595 at IUPUI, Spring 2020


This program was written in C for the NXP FRDM-K64F. It utilizes several libraries from mbed's online compiler and the main.c file was written by me. 
The program is a simple home security system that sound an alarm when an intruder is detected (motion sensor) or the temperature rises/falls to an unsafe temperature. 


![Security System](https://i.imgur.com/6DMBR64.jpg?1)


The system communicates with the user via a 16x2 LCD whenever an event is triggered. The user can also press an on-board push button to get a display of the current temperature and humidity readings on the LCD. The relative temperature is also displayed on a 10-digit LED bar, with one bar signaling a dangerously low temperature and all ten bars signaling a dangerously high temperature. 


If motion is detected, there is a warning displayed for 10 seconds before the alarm sounds to give the user the chance to turn off the alarm if set off by accident. The system can be enabled/disabled via an on-board switch; when disabled, the alarm will not sound when motion or an unsafe temperature is detected. If the system is enabled and the alarm sounds due to motion, it can be disabled by pressing the attached push button. If the alarm sounds due to temperature, it will not be disabled until the temperature reaches a safe level again.


The project was intended to be boxed up and presentable, but progress was interrupted by the COVID-19 pandemic in Spring 2020 and that idea was discarded. The image below shows the final hardware setup.


## Images

System disabled message and instructions to enable:

![System Disabled](https://i.imgur.com/MEtsg51m.jpg?1)

Temp and humidity readings displayed after pressing push button:

![T/H Display](https://i.imgur.com/4ESK6Tam.jpg)

Motion detection warning (10 seconds to alarm):

![Motion Display](https://i.imgur.com/gejwe8Jm.jpg?1)

Display when alarm sounds due to motion detection:

![Intruder Alert](https://i.imgur.com/MwEdHaVm.jpg)

High temperature alarm display:

![High Temp Warning](https://i.imgur.com/6rC6SOSm.jpg?1)
