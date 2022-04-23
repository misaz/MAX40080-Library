#include <stdint.h>
#include <stdio.h>
#include "mxc_config.h"
#include "tmr_utils.h"

#include "MAX40080.h"
#include "UART.h"
#include "MAX32625PICO.h"


int main(void) {
	MAX40080_Status status;
	int iStatus;

	iStatus = MAX32625PICO_VDDIOH_Init();
	if (iStatus) {
		__BKPT(0); // Software breakpoint. Error occurs only in case of SW bug.
	}

	DebugUART_Init();
	DebugUART_PrintString("\r\nUART initialization completed.\r\n");

	status = MAX40080_Init();
	if (status) {
		DebugUART_PrintString("MAX40080 Initialization failed.\r\n");
		while (1) {
			__WFI();
		}
	}

	MAX40080_Configuration config;
	MAX40080_GetDefaultConfiguration(&config);
	config.adcSampleRate = MAX40080_AdcSampleRate_Both_at_0_5_ksps;
	config.inputRange = MAX40080_InputRange_50mV;
	config.operatingMode = MAX40080_OperationMode_Active;

	status = MAX40080_SetConfiguration(&config);
	if (status) {
		DebugUART_PrintString("Error while configuring MAX40080.\r\n");
		while (1) {
			__WFI();
		}
	}

	MAX40080_FifoConfiguration fifoConfig;
	MAX40080_GetFifoDefaultConfiguration(&fifoConfig);
	fifoConfig.storingMode = MAX40080_FifoStoringMode_CurrentAndVoltage;

	status = MAX40080_SetFifoConfiguration(&fifoConfig);
	if (status) {
		DebugUART_PrintString("Error while configuring MAX40080 FIFO.\r\n");
		while (1) {
			__WFI();
		}
	}

	while (1) {
		float current;
		float voltage;

		status = MAX40080_ReadCurrentAndVoltage(&current, &voltage);
		if (status && status != MAX40080_Status_FifoIsEmpty) {
			DebugUART_PrintString("Error while receiving sample from MAX40080.\r\n");
			continue;
		}

		if (status == MAX40080_Status_FifoIsEmpty) {
			TMR_Delay(MXC_TMR0, (USEC(100)));
			continue;
		}

		char message[128];
		iStatus = snprintf(message, sizeof(message), "Voltage: %.2fV, Current: %.2fmA\r\n", voltage, current * 1000);
		if (iStatus < 0 || iStatus >= sizeof(message)) {
			__BKPT(0); // Software breakpoint. Error occurs only in case of SW bug.
			continue;
		}

		DebugUART_PrintString(message);
	}

}
