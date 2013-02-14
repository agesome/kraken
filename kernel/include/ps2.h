#ifndef PS2_H
#define PS2_H

#include <portio.h>
#include <stdbool.h>

#define PS2_DATA 0x60
#define PS2_REG 0x64

#define PS2_KBD 1
#define PS2_MOUSE 0

extern bool ps2_dual_channel;

typedef union {
	struct {
		bool outbuf : 1; // data coming FROM the device! (to be read by sofware)
		bool inbuf : 1; // data going to the device
		bool sysflag : 1;
		bool dc : 1; // 0 -- data for the device; 1 -- for the controller
		bool unused : 1;
		bool unused_ : 1;
		bool timeout : 1;
		bool parity : 1;
	};
	uint8_t data;
} ps2_status_t;

typedef union {
	struct {
		bool port1_int : 1;
		bool port2_int : 1;
		bool sysflag : 1;
		bool zero : 1;
		bool port1_clock : 1; // inverse!
		bool port2_clock : 1;
		bool port1_trans : 1;
		bool zero_ : 1;
	};
	uint8_t data;
} ps2_config_t;

bool ps2_controller_init (void);
void ps2_test_ports (bool *, bool *);
void ps2_set_ports (bool, bool);
bool ps2_reset_device (uint8_t);
bool ps2_device_read (uint8_t *);
#endif // PS2_H
