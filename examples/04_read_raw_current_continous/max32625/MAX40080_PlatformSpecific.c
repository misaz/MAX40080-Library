#include "MAX40080_PlatformSpecific.h"
#include "mxc_config.h"
#include "i2cm.h"
#include "mxc_config.h"
#include "i2cm.h"

MAX40080_Status MAX40080_PlatformSpecific_Init() {
	gpio_cfg_t gpio;
	gpio.func = GPIO_FUNC_GPIO;
	gpio.pad = GPIO_PAD_NORMAL;

	gpio.port = MAX40080_I2C_SDA_PORT;
	gpio.mask = MAX40080_I2C_SDA_PIN;
	SYS_IOMAN_UseVDDIOH(&gpio);
	GPIO_Config(&gpio);
	GPIO_OutSet(&gpio);

	gpio.port = MAX40080_I2C_SCL_PORT;
	gpio.mask = MAX40080_I2C_SCL_PIN;
	SYS_IOMAN_UseVDDIOH(&gpio);
	GPIO_Config(&gpio);
	GPIO_OutSet(&gpio);


	for (int i = 0; i < 9; i++) {
		GPIO_OutClr(&gpio);
		for (volatile int i = 0; i < 10000; i++) {}
		GPIO_OutSet(&gpio);
		for (volatile int i = 0; i < 10000; i++) {}
	}


	sys_cfg_i2cm_t i2cm_sys_cfg;
	ioman_cfg_t io_cfg = IOMAN_I2CM(MAX40080_I2C_DRIVER_ID, 1, 0);
	i2cm_sys_cfg.clk_scale = CLKMAN_SCALE_DIV_1;
	i2cm_sys_cfg.io_cfg = io_cfg;
	I2CM_Init(MAX40080_I2C_DRIVER, &i2cm_sys_cfg, I2CM_SPEED_100KHZ);

	return MAX40080_Status_Ok;
}

MAX40080_Status MAX40080_PlatformSpecific_Deinit() {
	I2CM_Shutdown(MAX40080_I2C_DRIVER);

	return MAX40080_Status_Ok;
}

MAX40080_Status MAX40080_PlatformSpecific_Read(uint8_t registerAddress, uint8_t* buffer, size_t bufferSize) {
	int error;

	error = I2CM_Read(MAX40080_I2C_DRIVER, MAX40080_I2C_7BIT_ADDRESS, &registerAddress, 1, buffer, bufferSize);
	if (error != bufferSize) {
		return MAX40080_Status_I2CError;
	}

	return MAX40080_Status_Ok;
}

MAX40080_Status MAX40080_PlatformSpecific_Write(uint8_t registerAddress, uint8_t* buffer, size_t bufferSize) {
	int error;

	if (bufferSize > 6) {
		return MAX40080_Status_NotImplemented;
	}

	uint8_t bufferToTransmit[7];
	bufferToTransmit[0] = registerAddress;

	for (size_t i = 0; i < bufferSize; i++) {
		bufferToTransmit[i + 1] = buffer[i];
	}

	error = I2CM_Write(MAX40080_I2C_DRIVER, MAX40080_I2C_7BIT_ADDRESS, NULL, 0, bufferToTransmit, bufferSize + 1);
	if (error != bufferSize + 1) {
		return MAX40080_Status_I2CError;
	}

	return MAX40080_Status_Ok;
}

MAX40080_Status MAX40080_PlatformSpecific_QuickCommand() {
	int error;

	error = I2CM_Write(MAX40080_I2C_DRIVER, MAX40080_I2C_7BIT_ADDRESS, NULL, 0, NULL, 0);
	if (error != 0) {
		return MAX40080_Status_I2CError;
	}

	return MAX40080_Status_Ok;
}

MAX40080_Status MAX40080_PlatformSpecific_SetI2CSpeed(MAX40080_I2CSpeed speed) {
	uint32_t inputClock = SYS_I2CM_GetFreq(MAX40080_I2C_DRIVER);

	if (inputClock != 96000000) {
		return MAX40080_Status_NotSupported;
	}

	if (speed == MAX40080_I2CSpeed_100_kHz) {
		MAX40080_I2C_DRIVER->fs_clk_div = (
			(48 << MXC_F_I2CM_FS_CLK_DIV_FS_FILTER_CLK_DIV_POS) |
			(164 << MXC_F_I2CM_FS_CLK_DIV_FS_SCL_HI_CNT_POS) |
			(576 << MXC_F_I2CM_FS_CLK_DIV_FS_SCL_LO_CNT_POS));
	} else if (speed == MAX40080_I2CSpeed_400_kHz) {
		MAX40080_I2C_DRIVER->fs_clk_div = (
			(12 << MXC_F_I2CM_FS_CLK_DIV_FS_FILTER_CLK_DIV_POS) |
			(33 << MXC_F_I2CM_FS_CLK_DIV_FS_SCL_HI_CNT_POS) |
			(144 << MXC_F_I2CM_FS_CLK_DIV_FS_SCL_LO_CNT_POS));
	} else if (speed == MAX40080_I2CSpeed_1_MHz) {
		MAX40080_I2C_DRIVER->fs_clk_div = (
			(5 << MXC_F_I2CM_FS_CLK_DIV_FS_FILTER_CLK_DIV_POS) |
			(11 << MXC_F_I2CM_FS_CLK_DIV_FS_SCL_HI_CNT_POS) |
			(57 << MXC_F_I2CM_FS_CLK_DIV_FS_SCL_LO_CNT_POS));
	} else {
		return MAX40080_Status_NotSupported;
	}

	return MAX40080_Status_Ok;
}
