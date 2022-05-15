# Arduino-PN532-Mifare-Dumper
This code allows you to dump Mifare Classic 1k and Mifare Ultralight tags.

Demo : https://i.imgur.com/IYuxYaA.mp4

![alt text](https://github.com/rrifi/Arduino-PN532-Mifare-Dumper/blob/main/pn532_output.PNG)

-------------------------------------------------------------------
USAGE : 

For use this you will need the Elechouse's PN532 and PN532_I2C libraries 

They can be downloaded here -> https://github.com/elechouse/PN532
OR you can download it direcly through Arduino IDE by clicking : Sketch > Include Library > Manage Libraries > Search "PN532" and you will find them both.

Dot not forget to put your PN532 on I2C mode :

![alt text](https://github.com/rrifi/Arduino-PN532-Mifare-Dumper/blob/main/IC2_mode.PNG)

Here is schema you should make :

Connect SDA pin to SDA pin
Connect SCL pin to SCL pin
Connect VCC to 5V
Connect Ground to Grounc

![alt text](https://github.com/rrifi/Arduino-PN532-Mifare-Dumper/blob/main/pn532_i2c_scheme.PNG)

Dont forget to open the serial console on 115200 baud
