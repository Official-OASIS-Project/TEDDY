/*
 TEDDY.cpp
 
 Transducer Electronic Datasheet Decryption Yielder - An arduino library to read and decode TEDS from acceleration sensors.
 
 */

#include "TEDDY.h"

TEDDY::TEDDY(int busPinInit){
	busPin = busPinInit;
	POPULATETEDDYMANID();
}

TEDDY::~TEDDY(){
   
}

uint8_t TEDDY::read(){
	
	int ReadFailed = 1;
	
	// Read the TEDS ROM to determine the EEPROM device type
	OneWire SensorBus(busPin);
	SensorBus.reset();
	SensorBus.write(0x33); // Read ROM command
	
	for(int i = 0; i < 8; i++) {
		TEDSROM[i] = SensorBus.read();
		if(TEDSROM[i]!=0xFF){
			ReadFailed = 0;
		}
	}
	
	// Assign ROM device type
	ROMDeviceType = TEDSROM[0];
	
	// No TEDS device attached (line was not pulled low -> all bits are 1)
	if(ReadFailed){
		return ReadFailed;
	}
	
	ReadFailed = 1;
	
	// Read the TEDS EEPROM content
	
	// For Kistler 8688A50T (TEDS v.0.9 Legacy - Template Id 0)
	if(ROMDeviceType==0x14 || ROMDeviceType==0x2D){

		SensorBus.reset();
		SensorBus.write(0xCC); // SKIP ROM command
		SensorBus.write(0xF0); // READ MEMORY command
		SensorBus.write(0x00); // STARTING ADDRESS? command
		SensorBus.write(0x00); // STARTING ADDRESS? command
	
		for (int i = 0; i < 32; i++) {
			TEDSData[i] = SensorBus.read();
			if(TEDSData[i]!=0xFF){
				ReadFailed = 0;
			}
		}
	}
	
	// No TEDS device attached (line was not pulled low -> all bits are 1)
	if(ReadFailed){
		return ReadFailed;
	}
	
	// Legacy v.0.9 Template Id 0 - DS2430A (0x14)
	if(ROMDeviceType==0x14){
		offset = 0;
	}
	
	// Legacy v.0.9 Template Id 0 - DS2431 (0x2D)
	if(ROMDeviceType==0x2D){
		offset = 1;
	}
	
	return 0;
}

char* TEDDY::getROMDeviceType(){
	
	if(ROMDeviceType==0x14){
		return "DS2430A (0x14)";
	}
	
	if(ROMDeviceType==0x2D){
		return "DS2431 (0x2D)";
	}
	
	if(ROMDeviceType==0xFF){
		return "TEDS read error (0xFF)";
	}
	
	return "Unknown device";
}

unsigned long int TEDDY::getSerialNumber(){
	
	// Communication error, return 0
	if(ROMDeviceType==0xFF){
		return 0;
	}
	
	return (((TEDSData[7+offset]<<16) + (TEDSData[6+offset]<<8) + TEDSData[5+offset])<<1) + (TEDSData[4+offset]>>7);
}

char TEDDY::getSensorDirection(){
	
	// Communication error, return E
	if(ROMDeviceType==0xFF){
		return 'E';
	}
	
	SensorDirection = ((TEDSData[16+offset]<<7)>>6) + (TEDSData[15+offset]>>7);
	
	if(SensorDirection==0){
		return 'X';
	}
	
	if(SensorDirection==1){
		return 'Y';
	}
	
	if(SensorDirection==2){
		return 'Z';
	}
	
	return 'E';
}

float TEDDY::getSensitivity(){
	
	byte ByteTemp;
	
	// Communication error, return 0
	if(ROMDeviceType==0xFF){
		return 0;
	}
	
	ByteTemp = TEDSData[13+offset]<<6;
	ByteTemp = ByteTemp>>6;
	
	return 0.0001 * pow(1.0002, (ByteTemp<<14) + (TEDSData[12+offset]<<6) + (TEDSData[11+offset]>>2));
}

String TEDDY::getTransducerType(){
	
	// Communication error, return error
	if(ROMDeviceType==0xFF){
		return "TEDS read error (0xFF)";
	}
	
	byte ByteTemp = TEDSData[3+offset]<<4;
	byte MNByte = ByteTemp>>4;
	ByteTemp = TEDSData[4+offset]<<7;
	byte MVByte = ByteTemp>>3;
	byte MVNByte = TEDSData[4+offset]<<1;
	
	ModelNumber = (MNByte<<12) + (TEDSData[2+offset]<<4) + (TEDSData[1+offset]>>4);
	TransducerType = ModelNumber;
	
	ModelVersion = (MVByte + (TEDSData[3+offset]>>4));
	if(ModelVersion>0 && ModelVersion<27){
		ModelVersion += 64; //Offset to C char table
	}
	else{
		return "Error: Unimplemented chr5 value!";
	}
	TransducerType += ModelVersion;
	
	ModelVersionNumber = MVNByte>>2;
	TransducerType += ModelVersionNumber;
	
	return TransducerType;	
}

String TEDDY::getManufacturer(){
	
	// Communication error, return error
	if(ROMDeviceType==0xFF){
		return "TEDS read error (0xFF)";
	}

	byte ByteTemp = TEDSData[1+offset]<<4;
	int ManufacturerID = (ByteTemp<<4) + (TEDSData[0+offset]);
	int i = 0;
	
	while(TEDSManIDArray[i].ManID!=ManufacturerID){
		i++;
	}
	
	return TEDSManIDArray[i].ManName;
}

unsigned int TEDDY::getCalibrationDate(){
	
	// Communication error, return 0
	if(ROMDeviceType==0xFF){
		return 0;
	}
	
	byte ByteTemp = TEDSData[11+offset]<<6;
	
	return (ByteTemp<<10) + (TEDSData[10+offset]<<6) + (TEDSData[9+offset]>>2);
}