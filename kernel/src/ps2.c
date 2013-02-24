#include <kraken/ps2.h>

#define command(C) outb (PS2_REG, C)
#define status() inb (PS2_REG)
#define write(C) outb (PS2_DATA, C)
#define read() inb (PS2_DATA)

bool ps2_dual_channel = false;

static bool
buf_wait (bool inbuf, bool desired)
{
	ps2_status_t s;
	int limit = 10000;

	s.data = status ();

	while (limit--)
		{
			s.data = status ();
			if (inbuf)
				{
					if (s.inbuf == desired)
						return true;
				}
			else
				{
					if (s.outbuf == desired)
						return true;
				}
		}
	return false;
}

bool
ps2_device_send (uint8_t dev, uint8_t data)
{
	if (buf_wait (true, false))
		{
			if (dev == PS2_MOUSE)
				command (0xd4); // send to second ps2 port
			write (data);
			return true;
		}
	return false;
}

bool
ps2_device_read (uint8_t * c)
{
	if (!buf_wait (false, true))
		return false;
	*c = read ();
	return true;
}

bool
ps2_controller_init (void)
{
	ps2_config_t c;

	// disable ps/2 ports
	command (0xad);
	command (0xa7);

	// clear buffer
	inb (PS2_REG);

	// read/write configuration byte
	command (0x20);
	c.data = read ();
	if (c.port2_clock)
		ps2_dual_channel = true;
	// c.port1_int = c.port2_int = c.port1_trans = false;
	c.port1_int = true;
	c.port1_trans = false;
	command (0x60);
	write (c.data);

	command (0xaa);
	if (read () != 0x55)
		return false;
	return true;
}

void
ps2_test_ports (bool * kbd, bool * mouse)
{
	*kbd = true;
	*mouse = false;
	command (0xab);
	buf_wait (true, false);
	if (read () != 0x00)
		*kbd = false;
	if (!ps2_dual_channel)
		return;
	command (0xa9);
	buf_wait (true, false);
	if (read () == 0x00)
		*mouse = true;
	return;
}

void
ps2_set_ports (bool kbd, bool mouse)
{
	if (kbd)
		command (0xae);
	if (mouse)
		command (0xa8);
	return;
}

bool
ps2_reset_device (uint8_t dev)
{
	ps2_device_send (dev, 0xff);
	buf_wait (false, true);
	if (read () == 0xfa && read () == 0xaa) // no idea, conflicting docs
		return true;
	return false;
}
