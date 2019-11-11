# **ESP32 Audio Connector**
This project connects your Audio Source over Bluetooth to the ESP32
  
### **What it is:**  
You want a wireless audio connection from you bluetooth device to your Speaker or Headphone? 
This project connects you bluetooth device to the ESP32 (Over Bluetooth A2DP and AVRCP). With the Audio Development Board and this code you can get a clear sound for you Speaker or Headphone.
![Alt-Text](/pictures/overview.jpg)
  
### **You need:**  
-The ESP32 Audio Development Board  
-NODE MCU with ESP 32 (e.g. ESP 32 DEVKIT V1 DOIT)  
-Working ESP-IDF  
-A device which can send A2DP over Bluetooth (e.g. every new smartphone)  
-A speaker or headphone  
-USB Powersupply or a  free PC USB-Port
  
There are more than one Version of the ESP 32 NODE MCU on the market. They have different pinouts. Use a ESP 32 NODE MCU with the ESP 32 DEVKIT V1 DOIT Pinout.

ESP 32 DEVKIT V1 DOIT Pinout: https://docs.zerynth.com/latest/official/board.zerynth.doit_esp32/docs/index.html

![Alt-Text](/pictures/DSC_0002.jpg)
  
### **Features:**  
-Burr-Brown DAC Chip  
-Sampling frequency up to 384kHz  
-Resolution up to 32 Bit  
-Low noise Power Supply with low ESR Capacitors  
-Two tactile switches  
-6 pin header with GPIOs and ground  
  
### **How it works:**  
-Download this project and add it to the ESP IDF  
-Connect the Micro USB Connector from the ESP 32 to your PC  
-Write this Code to the ESP 32 NODE MCU  
-Plug in the Audio Development Board  
-Connect headphone or speaker to the ESP32 Audio Development Board   
-Connect a Bluetooth device to the ESP32  
-Enjoy

### **Conection to DAC:**  
-XSMT (Mute)    -> D17  
-LRCK           -> D5  
-DOUT           -> D18  
-BCK            -> D19  
  
### **Planned features:**  
-AVRCP Comands (Play/Pause/Volume...)  
-Buttons with AVRCP functions  
-extended 6 Pin Header with AVRCP functions  
-3D printed case for ESP32 Audio Development Board and NODE MCU
  
  <a href="https://www.tindie.com/stores/demp_1993/?ref=offsite_badges&utm_source=sellers_DEMP_1993&utm_medium=badges&utm_campaign=badge_small"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-smalls.png" alt="I sell on Tindie" width="200" height="55"></a>
