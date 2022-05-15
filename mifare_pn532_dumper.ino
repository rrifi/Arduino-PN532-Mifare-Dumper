
  #include <Wire.h>
  #include <PN532_I2C.h>
  #include <PN532.h>
  PN532_I2C pn532i2c(Wire);
  PN532 nfc(pn532i2c);  



void setup(void) {
  Serial.begin(115200);
  Serial.println("Hello!");

  
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  
  // configure board to read RFID tags
  nfc.SAMConfig();
  
  Serial.println("Waiting for an ISO14443A Card ...");
}


void loop(void) {
  
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
    
  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  // Serial.println("Waiting for an NFC tag");
  
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  
  if (success) {
    // Display some basic information about the card
    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    Serial.print("  UID Value: ");
    nfc.PrintHex(uid, uidLength);
    Serial.println("");
    
    if (uidLength == 4)
    
    {
      // We probably have a Mifare Classic card ... 
      Serial.println("Seems to be a Mifare Classic card (4 byte UID)");
    
      // Now we need to try to authenticate it for read/write access
      // Try with the factory default KeyA: 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF
      Serial.println("Trying to authenticate block 4 with default KEYA value");
      uint8_t keya[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    
    // Start with block 4 (the first block of sector 1) since sector 0
    // contains the manufacturer data and it's probably better just
    // to leave it alone unless you know what you're doing
    
    //***********************************************************************************
    //***********************************************************************************
    
    int numblock = 0 ;
    int sectorAccess = 0 ;
    

    long int t1 = millis();
  
    for (int numsector = 0 ; numsector <= 15 ; numsector++ ){
        
    success = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, sectorAccess, 0, keya);

    
    

    
    
    uint8_t data[16];
    
    if (success){
    
      for(int blockIteration = 0 ; blockIteration < 4 ; blockIteration++ ){
            
        success = nfc.mifareclassic_ReadDataBlock(numblock, data);
        
        if (success) {
        
          Serial.print("Block " );
          if (numblock < 10) Serial.print("0");
          Serial.print(numblock);
          Serial.print(" : ");
          
          nfc.PrintHexChar(data, 16);


          /////////************** rajout*/ 

          //for (int p = 0 ; p <= 15 ; p++) {

            //aaaaa = data[p];
            
            //Serial.print(aaaaa, HEX);
            
            
          //}
          
          





          ///////////***********fin rajout
          //Serial.println("");
          
          
      
          // Wait a bit before reading the card again
          //delay(1000);
        }
        else {
          
          Serial.print("Ooops ... unable to read the block ");
          Serial.print(numblock);
          Serial.print(" of sector ");
          Serial.println(numsector);
          
          }
        
        
        numblock ++ ;
            
            
      }
      sectorAccess += 4 ;
      
    }
    else{
      Serial.println("Ooops ... authentication failed: Try another key?");
      }

    }

    long int t2 = millis();
    Serial.print("Read duration : ") ; Serial.print(t2-t1);  Serial.println(" ms") ;
    
    
    Serial.println();
    Serial.println("Please wait...");
    Serial.println("......3.......");
    delay(1000);
    Serial.println("......2.......");
    delay(1000);
    Serial.println("......1.......");
    delay(1000);
    Serial.println("");
    
    Serial.println("You can now scan another NFC TAG....");

    

    

    
    }

    //***********************************************************************************
    //***********************************************************************************

    
    if (uidLength == 7)
    {
      // We probably have a Mifare Ultralight card ...
      Serial.println("Seems to be a Mifare Ultralight tag (7 byte UID)");
    
      // Try to read the first general-purpose user page (#4)
      Serial.println("Reading page 4");
      uint8_t data[32];

      long int t1 = millis();


      for (int iter = 0 ; iter < 100 ; iter++) {

        success = nfc.mifareultralight_ReadPage (iter, data);
        if (success)
        {
          // Data seems to have been read ... spit it out
          nfc.PrintHexChar(data, 4);
          //Serial.println("");
    
          // Wait a bit before reading the card again
          //delay(1000);
        }
        else
        {
        break ;
        }

        

        
      }

      long int t2 = millis();
      Serial.print("Read duration : ") ; Serial.print(t2-t1);  Serial.println(" ms") ;

      Serial.println();
      Serial.println("Please wait...");
      Serial.println("......3.......");
      delay(1000);
      Serial.println("......2.......");
      delay(1000);
      Serial.println("......1.......");
      delay(1000);
      Serial.println("");
    
      Serial.println("You can now scan another NFC TAG....");
      /*
      success = nfc.mifareultralight_ReadPage (5, data);
      if (success)
      {
        // Data seems to have been read ... spit it out
        nfc.PrintHexChar(data, 4);
        Serial.println("");
    
        // Wait a bit before reading the card again
        delay(1000);
      }
      else
      {
        Serial.println("Ooops ... unable to read the requested page!?");
      }
      */


      
    }
  }
}
