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
