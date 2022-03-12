# MAX40080 Library
This project contains library for controlling MAX40080 Current Sense Amplifier digital sensor from Maxim Integrated (now Analog Devices). Library is written in C and is designed as multiplatform.

## Features
- Support for reading both current and voltage 
- Support for converting measured values to amps and volts (see example 1).
- Support for reading RAW values of current and voltage from sensor (see example 2). 
- Support for all operating modes:
	- Single-Measurement Mode (see example 1)
	- Active Mode (see example 3 and 4)
	- Selected Active Mode (see example 6)
	- Low-Power Mode (see example 10)
	- Standby Mode (see example 14)
- Support for both 10mV and 50mV input ranges.
- Support for ADC sample rates ranging from 15 ksps to 1 Msps.
- Support for digital filtering measauring samples ranging from no-everaging to averaging among 128 samples.
- Support for enabling and disabling packet error checking. Library computes and check CRC when this feature is enabled.
- Support for configuring alert response time.
- Support for going into standby mode when I2C is inactivite for a minute.
- Support for overcurrent (see example 7), overvoltage and undervoltage (see example 8) detections
- Support for configurable FIFO level warning (see example 9)
- Support for reading Max Peak Current (see example 11)
- Support for interrupts (see example 11).
- Support for high-speed i2c mode (see example 13).

## Supported platfroms and porting
Library is currently supported on following platforms:

- **Maxim Integrated MAX32625**: Implementation use MAX32625 StdPeriph driver from Maxim SDK to control I2C bus. Library was tested on MAX32625PICO board.
- **Renesas RA6M4**: Implementation use Renesas IIC FSP. Library was tested on EK-RA6M4 board.
- **Linux**: Implementation use `/dev/i2c-x` devices and ioctl access enabling running library in userspace on Linux computers like Raspberry Pi SBC.

Library is designed as platform independent and you can port it to whatever platform you want. If you want to port it, just implement `src/MAX40080_PlatformSpecific.c` files and remove files with suffixed names related to other platforms. In `src/MAX40080_PlatformSpecific.c` you need to implement 4 functions responsible for initialization, deinitialization and two I2C transactions. Implement them using I2C driver available on your platform. `src/MAX40080_PlatformSpecific.c` contains commends describing what you should do in each function.

## Implemented examples
There are 14 examples. Every example is implemented on some platforms but not at all. Following matrix contains informatio which examples are implemented on which platform. All examples contains README page with platform-independent description and code example showing how to use specific feature of library. You can use this platform-independent description in case when example is not implemented as a project for your target platform.

| Example                                     | MAX32625 | RA6M4 | Linux |
|---------------------------------------------|----------|-------|-------|
| 01_read_voltage_and_current_singleshoot     |          |       |       |
| 02_read_raw_voltage_and_current_singleshoot |          |       |       |
| 03_read_current_continuous				  |          |       |       |
| 04_read_voltage_continuous				  |          |       |       |
| 05_read_current_and_voltage_continuous	  |          |       |       |
| 06_selected_active_mode					  |          |       |       |
| 07_overcurrent							  |          |       |       |
| 08_overvoltage_and_undervoltage			  |          |       |       |
| 09_fifo_warning							  |          |       |       |
| 10_low_power_wake_up_current				  |          |       |       |
| 11_max_peek_current						  |          |       |       |
| 12_interrupt								  |          |       |       |
| 13_high_speed_i2c							  |          |       |       |
| 14_standby								  |          |       |       |
