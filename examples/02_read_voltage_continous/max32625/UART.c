#include <string.h>
#include "mxc_config.h"
#include "mxc_sys.h"

#include "UART.h"

void DebugUART_Init() {
	int status;

	gpio_cfg_t gpio;
	gpio.func = GPIO_FUNC_GPIO;
	gpio.pad = GPIO_PAD_NORMAL;
	gpio.port = PORT_0;
	gpio.mask = PIN_1;
	SYS_IOMAN_UseVDDIOH(&gpio);

	uart_cfg_t cfg;
	cfg.parity = UART_PARITY_DISABLE;
	cfg.size = UART_DATA_SIZE_8_BITS;
	cfg.extra_stop = 0;
	cfg.cts = 0;
	cfg.rts = 0;
	cfg.baud = 115200;

	sys_cfg_uart_t sys_cfg;
	sys_cfg.clk_scale = CLKMAN_SCALE_AUTO;
	sys_cfg.io_cfg = (ioman_cfg_t)IOMAN_UART(0, IOMAN_MAP_A, IOMAN_MAP_A, IOMAN_MAP_A, 1, 1, 1);

	status = UART_Init(MXC_UART0, &cfg, &sys_cfg);
	if(status) {
		__BKPT(0);
		while(1) { __WFI(); }
	}
}

void DebugUART_PrintString(char* string) {
	int len = strlen(string);
	int status = UART_Write(MXC_UART0, (uint8_t*)string, len);
	if (status != len) {
		__BKPT(0);
		while(1) { __WFI(); }
	}
}
