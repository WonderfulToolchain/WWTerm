#ifndef _WWTERM_SCREEN_H_
#define _WWTERM_SCREEN_H_

#include "types.h"

/* ターミナルのスクリーン */
extern char screen[HEIGHT][WIDTH];

/* カーソルの位置 */
extern int cursol_x;
extern int cursol_y;

void cursol_up(int add);
void cursol_down(int add);
void cursol_left(int add);
void cursol_right(int add);
void cursol_set_x(int x);
void cursol_set_y(int y);
void cursol_set(int x, int y);
void font_normal(int x, int y);
void font_reverse(int x, int y);
void line_clear(int line);
void screen_init(void);
void screen_clear(void);
void print_com_speed(int com_speed);
void print_com_connect();
void refresh(void);

/* ターミナルスクリーンへの文字表示 */
void print_character(char c);

#endif /* _WWTERM_SCREEN_H_ */

/* End of Program  */
