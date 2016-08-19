# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# TMD2671
# This code is designed to work with the TMD2671_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/products

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# TMD2671 address, 0x39(57)
# Select enable register register, 0x00(00), with command register 0x80(128)
#		0x0F(15)	Power on, Wait enabled, Proximity enabled
i2c.writeByte(0x39, 0x00 | 0x80, 0x0F)
# TMD2671 address, 0x39(57)
# Select proximity time control register, 0x02(02), with command register 0x80(128)
#		0xFF(255)	Time = 2.72 ms
i2c.writeByte(0x39, 0x02 | 0x80, 0xFF)
# TMD2671 address, 0x39(57)
# Select wait time register 0x03(03), with command register, 0x80(128)
#		0xFF(255)	Time - 2.72ms
i2c.writeByte(0x39, 0x03 | 0x80, 0xFF)
# TMD2671 address, 0x39(57)
# Select pulse count register, 0x0E(14), with command register 0x80(128)
#		0x20(32)	Pulse count = 32
i2c.writeByte(0x39, 0x0E | 0x80, 0x20)
# TMD2671 address, 0x39(57)
# Select control register, 0x0F(15), with command register 0x80(128)
#		0x20(32)	Proximity uses CH1 diode
i2c.writeByte(0x39, 0x0F | 0x80, 0x20)

time.sleep(0.8)

# TMD2671 address, 0x39(57)
# Read data back from 0x18(24) with command register 0x80(128), 2 bytes
# proximity lsb, proximity msb
data = i2c.readBytes(0x39, 0x18 | 0x80, 2)

# Convert the data
proximity = data[1] * 256 + data[0]

# Output data to screen
print "Proximity of the Device : %d" %proximity
