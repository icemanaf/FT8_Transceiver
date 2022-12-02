# ***A Simple FT8 Transceiver***
---
## Introduction
Described here is a simple FT8 transceiver built for the 20m band using the Microchip dsPic 30F3012 and the ubiquitous SI5351.
The dspic was chosen over the traditional Arduino and ESP32/8266 route due to the flexibilty around it's input capture modules.
Simply put, the transceiver samples the audio stream from WSJT-X , works out the frequency of the audio tone at a given instant , 
and "moves" one of the SI5351's output which is set as the transmit VFO. This method seems to work rather well. This was inspired 
by the approach taken by Hans Summers in the QDX transceiver design.