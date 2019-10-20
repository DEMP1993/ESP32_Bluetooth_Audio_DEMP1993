# **ESP32 Car Audio Connector**
This project connects your Bluetooth Source to the ESP32

You need:
-The DEMP1993 ESP32 Audio Devolopment Board
-NODE MCU with ESP 32
-Working ESP-IDF

![Alt-Text](/pictures/DSC_0002.jpg)

Features:
-Burr-Brown DAC Chip
-Sampling frequency up to 384kHz
-Resolution up to 32 Bit
-Low noise Power Supply with low ESR Capacitors

How it works:
-Download this project and add it to the ESP IDF
-Write this Code to the ESP 32 NODE MCU
-Plug in the Audio Devolopment Board
-Connect a Bluetooth device and enjoy 

PINOUT:
-XSMT (Mute)    -> D17
-LRCK           -> D5
-DOUT           -> D18
-BCK            -> D19

Planned features:
-AVRCP Comands (Play/Pause/Volume...)
-Buttons with AVRCP functions
-extended 6 Pin Header with AVRCP functions
