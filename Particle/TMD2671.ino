// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// TMD2671
// This code is designed to work with the TMD2671_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <application.h>
#include <spark_wiring_i2c.h>

// TMD2671 I2C address is 0x39(57)
#define Addr 0x39

int proximity = 0;

void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "TMD2671");
  Particle.variable("proximity", proximity);

  // Initialise I2C communication as Master
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select proximity time register OR with control register
  Wire.write(0x02 | 0x80);
  // Ptime = 2.72 ms
  Wire.write(0xFF);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select wait time register OR with command register
  Wire.write(0x03 | 0x80);
  // Wtime = 2.72 ms
  Wire.write(0xFF);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select pulse count register OR with command register
  Wire.write(0x0E | 0x80);
  // Pulse count = 32
  Wire.write(0x20);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register OR with command register
  Wire.write(0x0F | 0x80);
  // 100 mA LED strength, proximtiy uses CH1 diode, 1x PGAIN, 1x AGAIN
  Wire.write(0x20);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select enable register OR with command register
  Wire.write(0x00 | 0x80);
  // Set power on, proximity and wait enabled
  Wire.write(0x0F);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(800);
}

void loop()
{
  unsigned int data[0];

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register OR with command register
  Wire.write(0x18 | 0x80);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // proximity lsb, proximity msb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data
  proximity = data[1] * 256 + data[0];

  // Output data to dashboard
  Particle.publish("Proximity Of The Device : ", String(proximity));
  delay(1000);
}
