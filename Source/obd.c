#include "stm32f10x.h"
#include "obd.h"
#include "can.h"

u8 obd_mode = 0xff;
u8 obd_pid = 0xff;

void obd_cmd_parse(u8 mode, u8 pid){
	switch (mode){
		case 0x01:			//OBD_MODE = 0x01
			switch (pid){
				case 0x00:
					//can1_transmit_buf((u8 *)obd_mode, 1);
					//can1_transmit_buf((u8 *)obd_pid, 1);
				break;
				case 0x01:
					//can1_transmit_buf((u8 *)obd_mode, 1);
					//can1_transmit_buf((u8 *)obd_pid, 1);
				break;
			}
			break;
	}
	obd_mode = 0xff;
	obd_pid = 0xff;
}


