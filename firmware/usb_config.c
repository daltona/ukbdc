#include "usb_config.h"
#include <avr/pgmspace.h>

struct endpoint_config PROGMEM endpoint_configs[NUM_ENDPOINTS] = {
	{.num = 0,
		.type = EP_TYPE_CONTROL,
		.config = EP_SIZE_32 | EP_SINGLE_BUFFER,
		_BV(RXSTPE)},
	{.num = KEYBOARD_ENDPOINT,
		.type = EP_TYPE_INTERRUPT_IN,
		.config = EP_SIZE_32 | EP_DOUBLE_BUFFER,
		.int_flags = 0x00},
	{.num = RAWHID_TX_ENDPOINT,
		.type = EP_TYPE_INTERRUPT_IN,
		.config = EP_SIZE_64 | EP_DOUBLE_BUFFER,
		.int_flags = 0x00},
	{.num = RAWHID_RX_ENDPOINT,
		.type = EP_TYPE_INTERRUPT_OUT,
		.config = EP_SIZE_64 | EP_DOUBLE_BUFFER,
		.int_flags = 0x00}
};

#include "hid.h"
#include "rawhid.h"
#include "main.h"
struct interface_request_handler
iface_req_handlers[NUM_INTERFACE_REQUEST_HANDLERS] = {
	{.iface_num = KEYBOARD_INTERFACE,
		.f = &HID_handle_control_request},
	{.iface_num = RAWHID_INTERFACE,
		.f = &RAWHID_handle_control_request}
};
struct endpoint_interrupt_handler PROGMEM
endpoint_int_handlers[NUM_ENDPOINT_INTERRUPT_HANDLERS] = {
};
struct sof_handler
sof_handlers[NUM_SOF_HANDLERS] = {
	{.f = &HID_handle_sof},
	{.f = &MAIN_handle_sof},
};
