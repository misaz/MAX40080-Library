#include "hal_data.h"
#include "SEGGER_RTT/SEGGER_RTT.h"
#include <stdio.h>

#include "MAX40080.h"

void hal_entry(void) {
	MAX40080_Status status;
	int iStatus;
	fsp_err_t fStatus;

	fStatus = R_IOPORT_Open(&g_ioport_ctrl, g_ioport.p_cfg);
	if (fStatus) {
		__BKPT(0); // Software breakpoint. Error occurs only in case of SW bug.
	}

	// waint until Current 6 Click LDO power up and I2C pullups become working before initializing I2C driver.
    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

	SEGGER_RTT_WriteString(0, "RTT Initialization completed.\r\n");

	status = MAX40080_Init();
	if (status) {
		SEGGER_RTT_WriteString(0, "MAX40080 Initialization failed.\r\n");
		while (1) {
			__WFI();
		}
	}

	MAX40080_Configuration config;
	MAX40080_GetDefaultConfiguration(&config);
	config.operatingMode = MAX40080_OperationMode_Active;

	status = MAX40080_SetConfiguration(&config);
	if (status) {
		SEGGER_RTT_WriteString(0, "Error while configuring MAX40080.\r\n");
		while (1) {
			__WFI();
		}
	}

	while (1) {
		float current;

		status = MAX40080_ReadCurrent(&current);
		if (status && status != MAX40080_Status_FifoIsEmpty) {
			SEGGER_RTT_WriteString(0, "Error while receiving sample from MAX40080.\r\n");
			continue;
		}

		if (status == MAX40080_Status_FifoIsEmpty) {
			continue;
		}

		char message[128];
		float currentMiliAmps = current * 1000;
		iStatus = snprintf(message, sizeof(message), "Current: %d.%02d mA\r\n", (int)(currentMiliAmps), (int)(currentMiliAmps * 1000) % 1000);
		if (iStatus < 0 || iStatus >= (int)sizeof(message)) {
			__BKPT(0); // Software breakpoint. Error occurs only in case of SW bug.
			continue;
		}

		SEGGER_RTT_WriteString(0, message);
	}
}

