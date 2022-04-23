#include "MAX32625PICO.h"

#include "mxc_config.h"
#include "mxc_sys.h"

int MAX32625PICO_VDDIOH_Init() {
	int status;

	// conifguration:
	// P3_6 = 1
	// P2_2 = 0
	// P2_3 = 0

	// results to:
	// SWD_HDR = AIN
	// DIP_HDR = AIN
	// VDDIOH = 3V3


	gpio_cfg_t gpio;
	gpio.func = GPIO_FUNC_GPIO;
	gpio.pad = GPIO_PAD_NORMAL;

	// powering config
	gpio.port = PORT_3;
	gpio.mask = PIN_6;
	status = GPIO_Config(&gpio);
	if (status) {
		return 1;
	}
	GPIO_OutSet(&gpio);

	// powering config
	gpio.port = PORT_2;
	gpio.mask = PIN_2;
	status = GPIO_Config(&gpio);
	if (status) {
		return 1;
	}
	GPIO_OutClr(&gpio);

	// powering config
	gpio.port = PORT_2;
	gpio.mask = PIN_3;
	status = GPIO_Config(&gpio);
	if (status) {
		return 1;
	}
	GPIO_OutClr(&gpio);

	return 0;
}
