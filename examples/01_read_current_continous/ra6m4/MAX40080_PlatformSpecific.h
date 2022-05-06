#ifndef __MAX40080_PLATFORM_SPECIFIC_H
#define __MAX40080_PLATFORM_SPECIFIC_H

#include "MAX40080.h"

#include <stdint.h>
#include "hal_data.h"

#define MAX40080_IIC_MASTER_INSTANCE                    g_i2c_master0

MAX40080_Status MAX40080_PlatformSpecific_Init();
MAX40080_Status MAX40080_PlatformSpecific_Deinit();
MAX40080_Status MAX40080_PlatformSpecific_Read(uint8_t registerAddress, uint8_t* buffer, size_t bufferSize);
MAX40080_Status MAX40080_PlatformSpecific_Write(uint8_t registerAddress, uint8_t* buffer, size_t bufferSize);
MAX40080_Status MAX40080_PlatformSpecific_QuickCommand();
MAX40080_Status MAX40080_PlatformSpecific_SetI2CSpeed(MAX40080_I2CSpeed speed);

#endif
