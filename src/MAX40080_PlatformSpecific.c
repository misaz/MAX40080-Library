#include "MAX40080_PlatformSpecific.h"

MAX40080_Status MAX40080_PlatformSpecific_Init() {
	// this function must initialize I2C bus driver. It should not generate any 
	// transaction to the MAX40080 device. It is recommended to generate 9 clock  
	// cycles when SDA line is asserted as low and then generate stop sequence.

	return MAX40080_Status_NotImplemented;
}

MAX40080_Status MAX40080_PlatformSpecific_Deinit() {
	// this function must deinitialize I2C bus driver. It should not generate any 
	// transaction to the MAX40080 device.

	return MAX40080_Status_NotImplemented;
}

MAX40080_Status MAX40080_PlatformSpecific_Read(uint8_t registerAddress, uint8_t* buffer, size_t bufferSize) {
	// this function must generate following on the I2C bus:
	//
	// 1) Generate STRAT condition.
	// 2) Transmit MAX40080_I2C_WRITE_ADDRESS. If you are using platform (library) which 
	//    requires non-shifted 7bit address use MAX40080_I2C_7BIT_ADDRESS constant and 
	//    write direction.
	// 3) Check that device ACKed transaction. Otherwise generate STOP sequence and 
	//    return MAX40080_Status_I2CNack.
	// 4) Transmit registerAddress byte.
	// 5) Check that device ACKed transaction. Otherwise generate STOP sequence and
	//    return MAX40080_Status_I2CNack.
	// 6) Generate REPEATED START sequence
	// 7) Transmit MAX40080_I2C_READ_ADDRESS. If you are using platform (library) which 
	//    requires non-shifted 7bit address use MAX40080_I2C_7BIT_ADDRESS constant and 
	//    read direction.
	// 8) Read buffer of size bufferSize. After receiving every byte except the last byte 
	//    ACK the transaction. Generate NACK instead of ACK after receiving last byte.
	// 7) Generate STOP sequence and return MAX40080_Status_Ok.
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

MAX40080_Status MAX40080_PlatformSpecific_Write(uint8_t registerAddress, uint8_t* buffer, size_t bufferSize) {
	// this function must generate following on the I2C bus:
	//
	// 1) Generate STRAT condition.
	// 2) Transmit MAX40080_I2C_WRITE_ADDRESS. If you are using platform (library) which 
	//    requires non-shifted 7bit address use MAX40080_I2C_7BIT_ADDRESS constant and 
	//    write direction.
	// 3) Check that device ACKed transaction. Otherwise generate STOP sequence and 
	//    return MAX40080_Status_I2CNack.
	// 4) transmit registerAddress byte.
	// 5) check that device ACKed transaction. Otherwise generate STOP sequence and
	//    return MAX40080_Status_I2CNack.
	// 6) transmit buffer of size bufferSize. After transmiting every byte check that 
	//    device ACKed transaction. Otherwise generate STOP sequence and return
	//    MAX40080_Status_I2CNack.
	// 7) generate STOP sequence and return MAX40080_Status_Ok.
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