#include "stm32f10x.h"
#include "obd.h"

u8 obd_mode = 0xff;
u8 obd_pid = 0xff;

void obd_cmd_parse(u8 mode, u8 pid){
	switch (mode){
		case 0x01:			//OBD_MODE = 0x01
			switch (pid){
				case 0x00:
					printf("01 00");
				break;
				case 0x01:
					printf("01 01");
				break;
			}
			break;
		
	
	}
	obd_mode = 0xff;
	obd_pid = 0xff;
}


