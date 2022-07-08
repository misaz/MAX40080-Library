#include "MAX40080_PlatformSpecific.h"
#include "hal_data.h"
#include "r_iic_master.h"

MAX40080_Status MAX40080_PlatformSpecific_Init() {
	fsp_err_t fStatus;

	fStatus = R_IIC_MASTER_Open(MAX40080_IIC_MASTER_INSTANCE.p_ctrl, MAX40080_IIC_MASTER_INSTANCE.p_cfg);
	if (fStatus) {
		return MAX40080_Status_I2CError;
	}

	return MAX40080_Status_Ok;
}

MAX40080_Status MAX40080_PlatformSpecific_Deinit() {
	fsp_err_t fStatus;

	fStatus = R_IIC_MASTER_Close(MAX40080_IIC_MASTER_INSTANCE.p_ctrl);
	if (fStatus) {
		return MAX40080_Status_I2CError;
	}

	return MAX40080_Status_Ok;
}

static i2c_master_event_t i2cEvent = 0;

static void MAX40080_PlatformSpecific_I2C_Callback(i2c_master_callback_args_t* p_args) {
	i2cEvent = p_args->event;
}

static MAX40080_Status MAX40080_PlatformSpecific_WaitForCompletion(i2c_master_event_t expectedEvent) {
	uint32_t timeout = 1000;
	while (i2cEvent == 0 && timeout--) {
		R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MICROSECONDS);
		//__WFI();
	}

	if (i2cEvent == 0) {
		return MAX40080_Status_I2CTimeout;
	} else if (i2cEvent != expectedEvent) {
		R_IIC_MASTER_Abort(MAX40080_IIC_MASTER_INSTANCE.p_ctrl);
		return MAX40080_Status_I2CError;
	}

	return MAX40080_Status_Ok;
}

MAX40080_Status MAX40080_PlatformSpecific_Read(uint8_t registerAddress, uint8_t* buffer, size_t bufferSize) {
	fsp_err_t fStatus;
	MAX40080_Status status;

	fStatus = R_IIC_MASTER_SlaveAddressSet(MAX40080_IIC_MASTER_INSTANCE.p_ctrl, MAX40080_I2C_7BIT_ADDRESS, I2C_MASTER_ADDR_MODE_7BIT);
	if (fStatus) {
		return MAX40080_Status_I2CError;
	}

	fStatus = R_IIC_MASTER_CallbackSet(MAX40080_IIC_MASTER_INSTANCE.p_ctrl, MAX40080_PlatformSpecific_I2C_Callback, NULL, NULL);
	if (fStatus) {
		return MAX40080_Status_I2CError;
	}

	i2cEvent = 0;
	fStatus = R_IIC_MASTER_Write(MAX40080_IIC_MASTER_INSTANCE.p_ctrl, &registerAddress, 1, 1);
	if (fStatus) {
		R_IIC_MASTER_Abort(MAX40080_IIC_MASTER_INSTANCE.p_ctrl);
		return MAX40080_Status_I2CError;
	}
	status = MAX40080_PlatformSpecific_WaitForCompletion(I2C_MASTER_EVENT_TX_COMPLETE);
	if (status) {
		return status;
	}

	i2cEvent = 0;
	fStatus = R_IIC_MASTER_Read(MAX40080_IIC_MASTER_INSTANCE.p_ctrl, buffer, bufferSize, 0);
	if (fStatus) {
		R_IIC_MASTER_Abort(MAX40080_IIC_MASTER_INSTANCE.p_ctrl);
		return MAX40080_Status_I2CError;
	}
	status = MAX40080_PlatformSpecific_WaitForCompletion(I2C_MASTER_EVENT_RX_COMPLETE);
	if (status) {
		return status;
	}

	return MAX40080_Status_Ok;
}

MAX40080_Status MAX40080_PlatformSpecific_Write(uint8_t registerAddress, uint8_t* buffer, size_t bufferSize) {
	fsp_err_t fStatus;
	MAX40080_Status status;

	if (bufferSize > 6) {
		return MAX40080_Status_NotImplemented;
	}

	uint8_t bufferToTransmit[7];
	bufferToTransmit[0] = registerAddress;

	for (size_t i = 0; i < bufferSize; i++) {
		bufferToTransmit[i + 1] = buffer[i];
	}

	fStatus = R_IIC_MASTER_SlaveAddressSet(MAX40080_IIC_MASTER_INSTANCE.p_ctrl, MAX40080_I2C_7BIT_ADDRESS, I2C_MASTER_ADDR_MODE_7BIT);
	if (fStatus) {
		return MAX40080_Status_I2CError;
	}

	fStatus = R_IIC_MASTER_CallbackSet(MAX40080_IIC_MASTER_INSTANCE.p_ctrl, MAX40080_PlatformSpecific_I2C_Callback, NULL, NULL);
	if (fStatus) {
		return MAX40080_Status_I2CError;
	}

	i2cEvent = 0;
	fStatus = R_IIC_MASTER_Write(MAX40080_IIC_MASTER_INSTANCE.p_ctrl, bufferToTransmit, bufferSize + 1, 0);
	if (fStatus) {
		R_IIC_MASTER_Abort(MAX40080_IIC_MASTER_INSTANCE.p_ctrl);
		return MAX40080_Status_I2CError;
	}
	status = MAX40080_PlatformSpecific_WaitForCompletion(I2C_MASTER_EVENT_TX_COMPLETE);
	if (status) {
		return status;
	}

	return MAX40080_Status_Ok;
}

MAX40080_Status MAX40080_PlatformSpecific_QuickCommand() {
	fsp_err_t fStatus;
	MAX40080_Status status;

	fStatus = R_IIC_MASTER_SlaveAddressSet(MAX40080_IIC_MASTER_INSTANCE.p_ctrl, MAX40080_I2C_7BIT_ADDRESS, I2C_MASTER_ADDR_MODE_7BIT);
	if (fStatus) {
		return MAX40080_Status_I2CError;
	}

	fStatus = R_IIC_MASTER_CallbackSet(MAX40080_IIC_MASTER_INSTANCE.p_ctrl, MAX40080_PlatformSpecific_I2C_Callback, NULL, NULL);
	if (fStatus) {
		return MAX40080_Status_I2CError;
	}

	i2cEvent = 0;
	fStatus = R_IIC_MASTER_Write(MAX40080_IIC_MASTER_INSTANCE.p_ctrl, NULL, 0, 0);
	if (fStatus) {
		R_IIC_MASTER_Abort(MAX40080_IIC_MASTER_INSTANCE.p_ctrl);
		return MAX40080_Status_I2CError;
	}
	status = MAX40080_PlatformSpecific_WaitForCompletion(I2C_MASTER_EVENT_TX_COMPLETE);
	if (status) {
		return status;
	}

	return MAX40080_Status_Ok;
}

MAX40080_Status MAX40080_PlatformSpecific_SetI2CSpeed(MAX40080_I2CSpeed speed) {
	fsp_err_t fStatus;

	fStatus = R_IIC_MASTER_Close(MAX40080_IIC_MASTER_INSTANCE.p_ctrl);
	if (fStatus) {
		return MAX40080_Status_I2CError;
	}

	i2c_master_cfg_t clonedConfig;
	memcpy(&clonedConfig, MAX40080_IIC_MASTER_INSTANCE.p_cfg, sizeof(i2c_master_cfg_t));

	if (speed == MAX40080_I2CSpeed_100_kHz) {
		clonedConfig.rate = I2C_MASTER_RATE_STANDARD;

	} else if (speed == MAX40080_I2CSpeed_400_kHz) {
		clonedConfig.rate = I2C_MASTER_RATE_FAST;

	} else if (speed == MAX40080_I2CSpeed_1_MHz) {
		clonedConfig.rate = I2C_MASTER_RATE_FASTPLUS;

	} else {
		return MAX40080_Status_NotSupported;
	}

	fStatus = R_IIC_MASTER_Open(MAX40080_IIC_MASTER_INSTANCE.p_ctrl, &clonedConfig);
	if (fStatus) {
		return MAX40080_Status_I2CError;
	}

	return MAX40080_Status_Ok;
}
