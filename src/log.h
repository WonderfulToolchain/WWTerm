#ifndef _WWTERM_LOG_H_
#define _WWTERM_LOG_H_

#include "types.h"

int is_log_on();
char * log_switch();
void log_close();
void log_putc(int c);
void log_puts(char * s);
void log_putb(void * p, int len);

#endif /* _WWTERM_LOG_H_ */

/* End of Program  */
