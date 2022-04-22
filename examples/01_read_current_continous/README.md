# Exmaple 01: Simple Current Measurements
This example shows basic usage of MAX40080 CSA sensor. It uses almost standard configuration of MAX40080 sensor. Only change is that change mode from Standby to Active.

Code does following tasks:

1. Init the library
2. Configure sensor
3. Read current samles in infinite loop
4. Print samples over UART

## Initializing library
Library initialization is simple. Library can be initalized using following code snippet:

```
status = MAX40080_Init();
if (status) {
	// handle error
}
```

## Configure sensor
Sensor is configured using `MAX40080_SetConfiguration` function. This functions requires pointer to the `MAX40080_Configuration`. You can fill the structure manualy or you can use `MAX40080_GetDefaultConfiguration` function for preparing structure and then you can just modify it partially.

Example code use default values and modifies only `operatingMode` field of structure.

```
MAX40080_Configuration config;
MAX40080_GetDefaultConfiguration(&config);
config.operatingMode = MAX40080_OperationMode_Active;
```

Equaivalent code with manualy filling whole structure is:

```
MAX40080_Configuration config;
config->operatingMode = MAX40080_OperationMode_Active;
config->i2cTimeoutSettings = MAX40080_I2CTimeoutSettings_Enabled;
config->alertResponseTime = MAX40080_AlertResponseTime_Unfiltered;
config->packetErrorChecking = MAX40080_PacketErrorChecking_Enabled;
config->inputRange = MAX40080_InputRange_10mV;
config->stayHsMode = MAX40080_StayHsMode_ExitAtStop;
config->adcSampleRate = MAX40080_AdcSampleRate_Either_at_15_ksps;
config->digitalFilter = MAX40080_DigitalFilter_NoAverage;
```

After you have prepared configuration structure, you can pass it to the `MAX40080_SetConfiguration` function:

```
status = MAX40080_SetConfiguration(&config);
if (status) {
	// handle error
}
```

## Reading samples from sensor

Reading measured sample can be done using `MAX40080_ReadCurrent`. If you call the function before the collection is complete, then function returns status code `MAX40080_Status_FifoIsEmpty`. For retrieving number of samples in the FIFO you can use function `MAX40080_GetAvailableFifoDataCount` but because sensor is fast, another transaction caused by `MAX40080_GetAvailableFifoDataCount` can reduce the overal performance. Usualy is better to just try read the sample and discard them in case of detecting empty FIFO.

```
while (1) {
	float current;

	status = MAX40080_ReadCurrent(&current);
	if (status && status != MAX40080_Status_FifoIsEmpty) {
		// handle error
		continue;
	}

	if (status == MAX40080_Status_FifoIsEmpty) {
		continue;
	}

	// print current over UART
}
```

# Configurable constans
Library and this example assumes using with MikroE Current 6 Click board. If you use other or custom board, for correct operation you need to edit `MAX40080_I2C_7BIT_ADDRESS` and `MAX40080_SHUNT_RESISOTR_VALUE` constants in `MAX40080.h` file. I2C address depends on value of resistor connected to A0 pin. Consult I2C Slave Addresses table in datasheet for getting address number coresponding to your resistor. Both MikroE Current 6 Click Board and MAX40080EVKIT uses 100kOhm resisotr which coresponds to address 0x21. Similarly you need to change values of shunt resistor as a float value in ohms. MikroeE Current 6 Click Board uses 10mOhm (0.010 ohms) and this value is by default in source code. MAX40080EVKIT uses shunt resistor of value 0.050 ohms and if you use this board you need to update `MAX40080_SHUNT_RESISOTR_VALUE` constant to this value.

# MAX32625 port
This example is implemented for MAX32625 MCU targetting MAX32625PICO board and MikroE Current 6 Click Board containing MAX40080 sensor. Folder (max32625)[max32625] contains Eclipse project created using `MAX32625PeriphDriver` from [Low Power Microcontroller SDK](https://www.maximintegrated.com/en/design/software-description.html/swpart=SFW0001500A).

> :warning: Implementation use 3.3V voltage level. MikroE Current 6 Click Board has onboard level shifter. If you use different board like MAX40080EVKIT, then you need to modify the `MAX40080_PlatformSpecific.c` file and remove TWO `SYS_IOMAN_UseVDDIOH(&gpio);` lines from `MAX40080_PlatformSpecific_Init`.

For deploying and debugging directly from Eclipse you will need to define Launch configuration. Use the same Launch configuration which you use for launching examples from MAX32625 SDK. For debugging use `GDB OpenOCD Debugging`, C/C++ Application set to `build\max32625.elf`. At `Debugger` tab set Executable to `C:\Maxim\Toolchain\bin\openocd.exe`, GDB port 3333, telnet port 4444 and config options set to:

```
-s C:\Maxim\Toolchain\share\openocd\scripts -f "interface/{name_of_script_file_related_to_your_debug_probe}.cfg" -f target\max32625.cfg
```

For example:

![Configuration of Eclipse launch profile](readme_assets/max32625_debug_cfg.png)
