# MAX40080 Library
This project contains library for controlling MAX40080 Current Sense Amplifier digital sensor from Maxim Integrated (now Analog Devices). Library is written in C and is designed as multiplatform.

Originally I created this Library as part of [Element14 Experimenting with Current Sense Amplifiers Design Challenge](https://community.element14.com/challenges-projects/design-challenges/experimenting-with-current-sense-amplifier/).

## Features
- Written in C. Can be used in both C and C++ projects.
- Minimal RAM usage. No dynamic memory allocation.
- Library core depends on stdint.h (for uint8_t, uint16_t, int16_t and uint32_t types) and stddef.h (for size_t type).
- Platform specific ports depends on vendor SDK (see section Supported platfroms and porting below).
- Support for reading both current and voltage.
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
- Tested with [MikroElektronika MicroE Current 6 Click Board](https://www.mikroe.com/current-6-click)

## Getting started
1. Go to [Release page](https://github.com/misaz/MAX40080-Library/releases) and download ZIP file targetting your Platform or ZIP targeting Generic platform if your platform is not supported.
2. Unzip downloaded file and copy all files to folder of your project or IDE
3. Add `#include "MAX40080.h"` at the begining of your source code file.
4. Call `MAX40080_Init()` function at the begining of your program.
5. If you use different setup than 10mOhm shunt resistor (10mOhm is used at MikroE Click board, MAX40080EVKIT use 50mOhm). and 100kOhm address resistor (100kOhm is used by both MikroE Click Board and MAX40080EVKIT) then open `MAX40080.h` file and edit `MAX40080_I2C_7BIT_ADDRESS` and `MAX40080_SHUNT_RESISOTR_VALUE` constants.
6. Use functions starting with `MAX40080_` as needed.

## Functions
Library contains following functions (you can find this listing in MAX40080.h file):

```
MAX40080_Status MAX40080_Init();
MAX40080_Status MAX40080_Deinit();

MAX40080_Status MAX40080_GetDefaultConfiguration(MAX40080_Configuration* config);
MAX40080_Status MAX40080_GetConfiguration(MAX40080_Configuration* config);
MAX40080_Status MAX40080_SetConfiguration(MAX40080_Configuration* config);

MAX40080_Status MAX40080_EnableInterrupts(MAX40080_Interrupt interrupts);
MAX40080_Status MAX40080_GetPendingInterrupts(MAX40080_Interrupt* interrupts);
MAX40080_Status MAX40080_ClearPendingInterrupts(MAX40080_Interrupt interrupts);

MAX40080_Status MAX40080_GetRawOverCurrentTreshold(uint8_t* treshold);
MAX40080_Status MAX40080_SetRawOverCurrentTreshold(uint8_t treshold);
MAX40080_Status MAX40080_GetRawOverVoltageTreshold(uint8_t* treshold);
MAX40080_Status MAX40080_SetRawOverVoltageTreshold(uint8_t treshold);
MAX40080_Status MAX40080_GetRawUnderVoltageTreshold(uint8_t* treshold);
MAX40080_Status MAX40080_SetRawUnderVoltageTreshold(uint8_t treshold);
MAX40080_Status MAX40080_GetRawWakeUpCurrent(uint8_t* wakeUpCurrent);
MAX40080_Status MAX40080_SetRawWakeUpCurrent(uint8_t wakeUpCurrent);
MAX40080_Status MAX40080_GetRawMaxPeakCurrent(uint16_t* maxPeakCurrent);

MAX40080_Status MAX40080_GetFifoDefaultConfiguration(MAX40080_FifoConfiguration* fifoConfig);
MAX40080_Status MAX40080_GetFifoConfiguration(MAX40080_FifoConfiguration* fifoConfig);
MAX40080_Status MAX40080_SetFifoConfiguration(MAX40080_FifoConfiguration* fifoConfig);
MAX40080_Status MAX40080_GetAvailableFifoDataCount(uint8_t* fifoDataCount);
MAX40080_Status MAX40080_FlushFifo();

MAX40080_Status MAX40080_ReadRawCurrent(int16_t* current);
MAX40080_Status MAX40080_ReadRawVoltage(int16_t* voltage);
MAX40080_Status MAX40080_ReadRawCurrentAndVoltage(int16_t* current, int16_t* voltage);

MAX40080_Status MAX40080_ReadCurrent(float* current);
MAX40080_Status MAX40080_ReadVoltage(float* voltage);
MAX40080_Status MAX40080_ReadCurrentAndVoltage(float* current, float* voltage);
```

## Supported platfroms and porting
Library is currently supported on following platforms:

- **Maxim Integrated MAX32625**: Implementation use MAX32625 StdPeriph driver from Maxim SDK to control I2C bus. Library was tested on MAX32625PICO board.
- **Renesas RA6M4**: Implementation use Renesas IIC FSP. Library was tested on EK-RA6M4 board.
- **Linux**: Implementation use `/dev/i2c-x` devices and ioctl access enabling running library in userspace on Linux computers like Raspberry Pi SBC.

Library is designed as platform independent and you can port it to whatever platform you want. If you want to port it, just implement `src/MAX40080_PlatformSpecific.c` files and remove files with suffixed names related to other platforms. In `src/MAX40080_PlatformSpecific.c` you need to implement 4 functions responsible for initialization, deinitialization and two I2C transactions. Implement them using I2C driver available on your platform. `src/MAX40080_PlatformSpecific.c` contains comments describing what you should do in each function.

## Implemented examples
There are 14 examples. Every example is implemented on some platforms but not at all. Following matrix contains information which examples are implemented on which platform. All examples contains README page with platform-independent description and code example showing how to use specific feature of library. You can use this platform-independent description in case when example is not implemented as a project for your target platform.

| Example                                                            | MAX32625 | RA6M4 | Linux |
|--------------------------------------------------------------------|----------|-------|-------|
| 01_read_current_continous [description](01_read_current_continous) | [link](01_read_current_continous/max32625) | | |

## Feedback
Any feedback (including negative) is welcome. If you found any bug kindly create issue. You can also create issue for asking questions about library or just providing feedback.