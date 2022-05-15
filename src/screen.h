#ifndef _WWTERM_SCREEN_H_
#define _WWTERM_SCREEN_H_

#include "types.h"

/* ターミナルのスクリーン */
extern char screen[HEIGHT][WIDTH];

/* カーソルの位置 */
extern int cursor_x;
extern int cursor_y;

void cursor_up(int add);
void cursor_down(int add);
void cursor_left(int add);
void cursor_right(int add);
void cursor_set_x(int x);
void cursor_set_y(int y);
void cursor_set(int x, int y);
void font_normal(int x, int y);
void font_reverse(int x, int y);
void line_clear(int line);
void screen_init(void);
void screen_clear(void);
void print_com_speed(int com_speed);
void print_log_on();
void print_com_connect();
void refresh(void);

/* ターミナルスクリーンへの文字表示 */
void print_character(char c);
void print_string(char * s);

#endif /* _WWTERM_SCREEN_H_ */

/* End of Program  */
