#ifndef _WWTERM_COM_H_
#define _WWTERM_COM_H_

#include <sys/comm.h>

#include "types.h"

/* 受信バッファ */
extern char com_receive_buffer[BUFFER_SIZE];
extern int com_receive_start;
extern int com_receive_end;

/* 接続状態 0.非接続 1.接続 */
extern int com_is_connected;

/* 停止状態 0.通信中 1.停止中 */
extern int com_is_paused;

void com_pause();
void com_unpause();
void com_flush();
void com_receive();
int com_putc(unsigned char c);
int com_puts(char * string);
int com_putb(void * buffer, int size);

#endif /* _WWTERM_COM_H_ */

/* End of Program  */
