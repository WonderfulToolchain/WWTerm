#ifndef _WWTERM_KEYBOARD_H_
#define _WWTERM_KEYBOARD_H_

#include <sys/text.h>

#include "types.h"

/* キーボードのカーソル座標 */
extern int keyboard_cursol_x;
extern int keyboard_cursol_y;

void clear_keycursol();
void print_keycursol();
void make_keyboard();
int keyboard_get_key();
unsigned char keyboard_get_symbol();
void keyboard_copy_string(char * buffer);
void keyboard_change_string(char * string);

#endif /* _WWTERM_KEYBOARD_H_ */

/* End of Program  */
