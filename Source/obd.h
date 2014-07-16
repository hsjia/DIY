#ifndef __OBD_H
#define __OBD_H

extern u8 obd_mode;
extern u8 obd_pid;

void obd_cmd_parse(u8 mode, u8 pid);

#endif
