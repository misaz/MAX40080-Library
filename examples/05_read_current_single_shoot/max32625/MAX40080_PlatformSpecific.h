#ifndef __MAX40080_PLATFORM_SPECIFIC_H
#define __MAX40080_PLATFORM_SPECIFIC_H

#include "MAX40080.h"
#include "mxc_config.h"
#include "i2cm.h"

#include <stdint.h>
#include <stddef.h>

#define MAX40080_I2C_DRIVER		MXC_I2CM0
#define MAX40080_I2C_DRIVER_ID	0
#define MAX40080_I2C_SDA_PORT	PORT_1
#define MAX40080_I2C_SDA_PIN	PIN_6
#define MAX40080_I2C_SCL_PORT	PORT_1
#define MAX40080_I2C_SCL_PIN	PIN_7


MAX40080_Status MAX40080_PlatformSpecific_Init();
MAX40080_Status MAX40080_PlatformSpecific_Deinit();
MAX40080_Status MAX40080_PlatformSpecific_Read(uint8_t registerAddress, uint8_t* buffer, size_t bufferSize);
MAX40080_Status MAX40080_PlatformSpecific_Write(uint8_t registerAddress, uint8_t* buffer, size_t bufferSize);
MAX40080_Status MAX40080_PlatformSpecific_QuickCommand();
MAX40080_Status MAX40080_PlatformSpecific_SetI2CSpeed(MAX40080_I2CSpeed speed);

#endif
