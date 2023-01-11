#include <U8g2lib.h>
#include <Wire.h>
#include <TEDDY.h>

// Display Setup
#define SDA 33
#define SCL 32

// Pins
#define TEDDYPin 21
#define BUTTON 25

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

void u8g2_prepare() {
u8g2.setFont(u8g2_font_6x10_tf);
u8g2.setFontRefHeightExtendedText();
u8g2.setDrawColor(1);
u8g2.setFontPosTop();
u8g2.setFontDirection(0);
}

// Variables
TEDDY teddy(TEDDYPin);

void setup() {
  u8g2.begin();
  u8g2_prepare();

  pinMode(BUTTON, INPUT);
  Serial.begin(115200);
  u8g2.drawStr(0, 0, "TEDS Readout Dev Tool");
  u8g2.drawStr(0, 12, "Press Button to read");
  u8g2.sendBuffer();
}

void loop() {

  if(digitalRead(BUTTON)){
    
    // Read the ROM of the TEDS chip
    Serial.print("TEDS read status: ");
    Serial.println(teddy.read());
    Serial.print("ROM device type: ");
    Serial.println(teddy.getROMDeviceType());
    Serial.print("Transducer manufacturer: ");
    Serial.println(teddy.getManufacturer());
    Serial.print("Transducer type: ");
    Serial.println(teddy.getTransducerType());
    Serial.print("Serial number: ");
    unsigned long int SerialNum = teddy.getSerialNumber();
    Serial.println(SerialNum);
    Serial.print("Sensor direction: ");
    Serial.println(teddy.getSensorDirection());
    Serial.print("Sensor sensitivity [V/(m/s^2)]: ");
    Serial.printf("%.8f", teddy.getSensitivity());
    Serial.println();
    Serial.print("Sensor sensitivity [mV/g]: ");
    Serial.printf("%.8f",teddy.getSensitivity()*9806.65);
    Serial.println();
    Serial.print("Calibration date (days since January 1st, 1998): ");
    Serial.println(teddy.getCalibrationDate());
    Serial.println();

    u8g2.clear();
    u8g2.drawStr(0, 0, "Trans. Type:");
    u8g2.setCursor(76,0);
    u8g2.print(teddy.getTransducerType());
    u8g2.drawStr(0, 12, "Serial #:");
    u8g2.setCursor(60,12);
    u8g2.print(SerialNum);
    u8g2.drawStr(0, 24, "Sensor direction:");
    u8g2.setCursor(110,24);
    u8g2.print(teddy.getSensorDirection());
    u8g2.drawStr(0, 36, "Sens. [V/(m/s^2)|g]:");
    u8g2.setCursor(0,48);
    u8g2.printf("%.8f",teddy.getSensitivity());
    u8g2.drawStr(64, 48, "|");
    u8g2.setCursor(74,48);
    u8g2.printf("%.4f",teddy.getSensitivity()*9806.65);
    u8g2.sendBuffer();
    
    delay(1000);
  }
}
