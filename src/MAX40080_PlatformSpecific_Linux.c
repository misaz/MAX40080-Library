#include "MAX40080_PlatformSpecific.h"

#include <stdio.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>

static int fd = -1;
static int controllerNumber = 1;

MAX40080_Status MAX40080_PlatformSpecific_Init() {
	int status;
	char path[32];
	
	status = snprintf(path, sizeof(path), "/dev/i2c-%d", controllerNumber);
	// 10 is length of minimal output "/dev/i2c-0". If we get string 
	// less than 10 characters something went wrong and stdlib is buggy.
	// Function also returns negative number on error. This is handled by 
	// the same condition.
	if (status < 10 || status >= sizeof(path)) {
		return MAX40080_Status_InvalidOperation;
	}
	
	fd = open(path, O_RDWR);
	if (fd < 0) {
		return MAX40080_Status_I2CError;
	}
	
	status = ioctl(fd, I2C_SLAVE, MAX40080_I2C_7BIT_ADDRESS);
	if (status < 0) {
		return MAX40080_Status_I2CError;
	}
	
	return MAX40080_Status_Ok;
}

MAX40080_Status MAX40080_PlatformSpecific_Deinit() {
	close(fd);
	fd = -1;
	return MAX40080_Status_Ok;
}

MAX40080_Status MAX40080_PlatformSpecific_Read(uint8_t registerAddress, uint8_t* buffer, size_t bufferSize) {
	int status;
	struct i2c_msg messages[2];
	struct i2c_rdwr_ioctl_data data;
	
	messages[0].addr = MAX40080_I2C_7BIT_ADDRESS;
	messages[0].flags = 0;
	messages[0].buf = &registerAddress;
	messages[0].len = 1;
	
	messages[1].addr = MAX40080_I2C_7BIT_ADDRESS;
	messages[1].flags = I2C_M_RD;
	messages[1].buf = buffer;
	messages[1].len = bufferSize;
	
	data.msgs = messages;
	data.nmsgs = 2;
	
	status = ioctl(fd, I2C_RDWR, &data);
	if (status < 0) {
		if (status == ENXIO) {
			return MAX40080_Status_I2CNack;
		} else if (status == ETIMEDOUT) {
			return MAX40080_Status_I2CTimeout;
		} else {
			return MAX40080_Status_I2CError;
		}
	}
	
	return MAX40080_Status_Ok;
}

MAX40080_Status MAX40080_PlatformSpecific_Write(uint8_t registerAddress, uint8_t* buffer, size_t bufferSize) {
	uint8_t bufferToTransmit[7];
	int status;
	
	if (bufferSize > 6) {
		return MAX40080_Status_NotImplemented;
	}

	bufferToTransmit[0] = registerAddress;

	for (size_t i = 0; i < bufferSize; i++) {
		bufferToTransmit[i + 1] = buffer[i];
	}
	
	status = write(fd, bufferToTransmit, bufferSize + 1);
	if (status != bufferSize + 1) {
		int e = errno;
		if (e == ENXIO) {
			return MAX40080_Status_I2CNack;
		} else if (e == ETIMEDOUT) {
			return MAX40080_Status_I2CTimeout;
		} else {
			return MAX40080_Status_I2CError;
		}
	}
	
	return MAX40080_Status_Ok;
}

MAX40080_Status MAX40080_PlatformSpecific_QuickCommand() {
	// this function must generate following on the I2C bus:
	//
	// 1) Generate STRAT condition.
	// 2) Transmit MAX40080_I2C_WRITE_ADDRESS. If you are using platform (library) which 
	//    requires non-shifted 7bit address use MAX40080_I2C_7BIT_ADDRESS constant and 
	//    write direction.
	// 3) Check that device ACKed transaction. Otherwise generate STOP sequence and 
	//    return MAX40080_Status_I2CNack.
	// 4) generate STOP sequence and return MAX40080_Status_Ok.
	//
	// In all steps check for errors like arbitration lost error. Use return code 
	// MAX40080_Status_I2CNack for errors related to NACKing and MAX40080_Status_I2CError 
	// for other I2C errors. 
	//
	// Before returning any status code remember to generate STOP sequence.
	//
	// Prevent using loops which may end up in inifinete loop in case of unpredictable 
	// behaviour of I2C peripheral. Try implement platform specific timeout detection
	// and return MAX40080_Status_I2CTimeout when timeout occur. In case of timeout 
	// also generate STOP sequence and turn platform specific driver to the state that 
	// it can be reused for further communication again. (In the other words any I2C 
	// error should not make library stuck in error-generating state forever).

	return MAX40080_Status_NotImplemented;
}

MAX40080_Status MAX40080_PlatformSpecific_SetI2CSpeed(MAX40080_I2CSpeed speed) {
	// this function must reconfigure the I2C driver for target speed specified by 
	// argument. It should not generate any transaction to the MAX40080 device.

	// You can implement in multiple manner. While param is enum, it value is 
	// encoded as frequncy in kHz unit. If your underlaying I2C driver support 
	// configuring any speed you can support any speed and you are not restricted 
	// to support only enum values. You are not required to supoirt all values 
	// from enum. If your platform do not support all speeds, you can supoort just 
	// few. You need to check user param and in case of request to set unsupported 
	// speed you need to return MAX40080_Status_NotSupported status code. If your 
	// platform support only one speed, you do not need to immplemnt this function
	// and just let this function return MAX40080_Status_NotImplemented status code.

	return MAX40080_Status_NotImplemented;
}