#ifndef _WWTERM_KEYBOARD_H_
#define _WWTERM_KEYBOARD_H_

#include <sys/text.h>

#include "types.h"

/* キーボードのカーソル座標 */
void keycursor_up();
void keycursor_down();
void keycursor_left();
void keycursor_right();

void mode_change();

void clear_keycursor();
void print_keycursor();
void init_keyboard();
int keyboard_get_key();
void keyboard_change_string(char * string);
int keyboard_get_y1234map(int y);
char * get_function_key(int n);

#endif /* _WWTERM_KEYBOARD_H_ */

/* End of Program  */
