#include "arduino.h"

//#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>
Adafruit_NFCShield_I2C nfc(2);  //IRQ

boolean success;
uint8_t uid[7] = {
  0, 0, 0, 0, 0, 0, 0
};  // Buffer to store the returned UID
uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

boolean nfc_begin()
{
  nfc.begin();
  delay(100);

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.println("Didn't find PN53x board");
    while (1)
    {
      nfc.begin();
      delay(100);
      versiondata = nfc.getFirmwareVersion();
      if (versiondata)
        break;
    } // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5");
  Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware ver. ");
  Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.');
  Serial.println((versiondata >> 8) & 0xFF, DEC);
  // configure board to read RFID tags
  nfc.SAMConfig();
  nfc.Refresh(PN532_MIFARE_ISO14443A);
  Serial.println("Waiting for an ISO14443A Card ...");
  return true;
}

void nfc_Refresh() {
  nfc.Refresh(PN532_MIFARE_ISO14443A);
}

uint32_t nfc_Scan() {
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  if (success && uidLength == 4)  {
    delay(200);
    // Display some basic information about the card
    Serial.println("Found an ISO14443A card");
    Serial.print("UID Length: ");
    Serial.print(uidLength, DEC);
    Serial.println(" bytes");
    Serial.print("UID Value: ");
    nfc.PrintHex(uid, uidLength);
    Serial.println("---------------");
    return get_data(uid);
  }
  else
    return 0;
}
