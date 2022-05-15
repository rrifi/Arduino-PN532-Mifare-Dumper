# Arduino-PN532-Mifare-Dumper
This code allows you to dump Mifare Classic 1k and Mifare Ultralight tags.

![alt text](https://github.com/rrifi/Arduino-PN532-Mifare-Dumper/blob/main/pn532_output.PNG)

-------------------------------------------------------------------
USAGE : 

For use this you will need Elehouse PN532 and PN532_I2C libraries 

You can download here -> https://github.com/elechouse/PN532
OR you can download it direcly through Arduino IDE by clicking : Sketch > Include Library > Manage Libraries > Search "PN532" and you will find them both.

Dot not forget to put your PN532 on I2C mode :

![alt text](https://github.com/rrifi/Arduino-PN532-Mifare-Dumper/blob/main/IC2_mode.PNG)

Here is schema you should make :

![alt text](https://github.com/rrifi/Arduino-PN532-Mifare-Dumper/blob/main/pn532_i2c_scheme.PNG)

Dont forget to open the serial console on 115200 baud
