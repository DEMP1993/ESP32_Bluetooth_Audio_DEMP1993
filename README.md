# **ESP32 Audio Connector**
This project connects your Bluetooth Audio Source to your Speaker  

You need:  
-The ESP32 Audio Devolopment Board  
-NODE MCU with ESP 32 (e.g. ESP 32 DEVKIT V1 DOIT)  
-Working ESP-IDF  

![Alt-Text](/pictures/DSC_0002.jpg)
![Alt-Text](/pictures/DSC_0001.jpg)

Features:  
-Burr-Brown DAC Chip  
-Sampling frequency up to 384kHz  
-Resolution up to 32 Bit  
-Low noise Power Supply with low ESR Capacitors  
-Two tactile switches  
-6 pin header with GPIOs and ground  

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
-3D printed case for ESP32 Audio Devolopment Board and NODE MCU
