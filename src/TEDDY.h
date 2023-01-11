/*
 TEDDY.h
 
 Transducer Electronic Datasheet Decryption Yielder - An arduino library to read and decode TEDS from acceleration sensors.
 
 */

#ifndef TEDDY_h
#define TEDDY_h

#include <Arduino.h>
#include <OneWire.h>
#include <String.h>
#include <ManufacturerIDs.h>

class TEDDY {
private:
  byte TEDSROM[8];
  byte TEDSData[32];
  int busPin;
  byte offset;
  byte ROMDeviceType;
  byte SensorDirection;
  int ModelNumber;
  char ModelVersion;
  byte ModelVersionNumber;
  String TransducerType;
  TEDSManID TEDSManIDArray[150];

public:
  TEDDY(int busPin);
  ~TEDDY();
  void POPULATETEDDYMANID();
  uint8_t read();
  char* getROMDeviceType();
  unsigned long int getSerialNumber();
  char getSensorDirection();
  float getSensitivity();
  String getTransducerType();
  String getManufacturer();
  unsigned int getCalibrationDate();
};

#endif
