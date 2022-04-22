# MAX40080 Library
This project contains library for controlling MAX40080 Current Sense Amplifier digital sensor from Maxim Integrated (now Analog Devices). Library is written in C and is designed as multiplatform.

Originally I created this Library as part of [Element14 Experimenting with Current Sense Amplifiers Design Challenge](https://community.element14.com/challenges-projects/design-challenges/experimenting-with-current-sense-amplifier/).

## Features
- Written in C. Can be used in both C and C++ projects.
- Minimal RAM usage. No dynamic memory allocation.
- Library core depends on stdint.h (for uint8_t, uint16_t, int16_t and uint32_t types) and stddef.h (for size_t type).
- Platform specific ports depends on vendor SDK (see section Supported platfroms and porting below).
- Support for reading both current and voltage.
- Support for converting measured values to amps and volts.
- Support for reading RAW values of current and voltage from sensor. 
- Support for all operating modes:
	- Single-Measurement Mode
	- Active Mode
	- Selected Active Mode
	- Low-Power Mode
	- Standby Mode
- Support for both 10mV and 50mV input ranges.
- Support for ADC sample rates ranging from 15 ksps to 1 Msps.
- Support for digital filtering measauring samples ranging from no-everaging to averaging among 128 samples.
- Support for enabling and disabling packet error checking. Library computes and check CRC when this feature is enabled.
- Support for configuring alert response time.
- Support for going into standby mode when I2C is inactivite for a minute.
- Support for overcurrent, overvoltage and undervoltage detections
- Support for configurable FIFO level warning
- Support for reading Max Peak Current
- Support for interrupts.
- Support for high-speed i2c mode.
- Tested with [MikroElektronika MicroE Current 6 Click Board](https://www.mikroe.com/current-6-click)

## Getting started
1. Go to [Release page](https://github.com/misaz/MAX40080-Library/releases) and download ZIP file targetting your Platform or ZIP targeting Generic platform if your platform is not supported.
2. Unzip downloaded file and copy all files to folder of your project or IDE
3. Add `#include "MAX40080.h"` at the begining of your source code file.
4. Call `MAX40080_Init()` function at the begining of your program.
5. Update `MAX40080_I2C_7BIT_ADDRESS` and `MAX40080_SHUNT_RESISOTR_VALUE` constants in `MAX40080.h` file.
	- If you use MikroE Current 6 Click you do not need to modify anything. Default values matches this board.
	- If you use MAX40080EVKIT, you need to update `MAX40080_SHUNT_RESISOTR_VALUE` to `0.050`
	- If you use other or custom board you need to update both constant according to your configuration.
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
- **Linux**: Implementation use `/dev/i2c-x` devices and ioctl access enabling running library in userspace on Linux computers like Raspberry Pi SBC.

Library is designed as platform independent and you can port it to whatever platform you want. If you want to port it, just implement `src/MAX40080_PlatformSpecific.c` files and remove files with suffixed names related to other platforms. In `src/MAX40080_PlatformSpecific.c` you need to implement 4 functions responsible for initialization, deinitialization and two I2C transactions. Implement them using I2C driver available on your platform. `src/MAX40080_PlatformSpecific.c` contains comments describing what you should do in each function.

## Implemented examples
Every example is implemented on some platforms but not at all. Following matrix contains information which examples are implemented on which platform. All examples contains README page with platform-independent description and code example showing how to use specific feature of library. You can use this platform-independent description in case when example is not implemented as a project for your target platform.

| Example                                                            | MAX32625 | Linux |
|--------------------------------------------------------------------|----------|-------|
| 01_read_current_continous [description](examples/01_read_current_continous) | [Eclipse porject](examples/01_read_current_continous/max32625) | |

## Feedback
Any feedback (including negative) is welcome. If you found any bug kindly create issue. You can also create issue for asking questions about library or just providing feedback.