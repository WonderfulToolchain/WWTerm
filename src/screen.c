#include <stdlib.h>
#include <string.h>
#include <sys/disp.h>

#include "screen.h"
#include "com.h"
#include "lib.h"
#include "escape.h"
#include "log.h"

/* ターミナルのスクリーン */
char screen[HEIGHT][WIDTH];

/* カーソルの位置 */
int cursor_x = 0;
int cursor_y = 0;

void refresh(void)
{
  int y;

  wonx_lcddraw_level_down();
  for (y = 0; y < HEIGHT; y++) {
    text_put_substring(0, y, screen[y], WIDTH);
  }
  wonx_lcddraw_level_up();
}

static void cursor_check()
{
  int i;

  while (cursor_x < 0) {
    cursor_x += WIDTH;
    cursor_y--;
  }

  while (cursor_x > WIDTH - 1) {
    cursor_x -= WIDTH;
    cursor_y++;
  }

  if (cursor_y < 0) cursor_y = 0;

  if (cursor_y >= HEIGHT) {
    while (cursor_y >= HEIGHT) {
      for (i = 0; i < HEIGHT - 1; i++) {
	memcpy(screen[i], screen[i + 1], sizeof(screen[0][0]) * WIDTH);
      }
      line_clear(i);
      cursor_y--;
    }
    refresh();
  }

  cursor_set_location(cursor_x, cursor_y, 1, 1);
}

void cursor_up(int add)
{
  cursor_y -= add;
  cursor_check();
}

void cursor_down(int add)
{
  cursor_y += add;
  cursor_check();
}

void cursor_left(int add)
{
  cursor_x -= add;
  cursor_check();
}

void cursor_right(int add)
{
  cursor_x += add;
  cursor_check();
}

void cursor_set_x(int x)
{
  if (x < 0         ) x = 0;
  if (x > WIDTH  - 1) x = WIDTH  - 1;
  cursor_x = x;
  cursor_check();
}

void cursor_set_y(int y)
{
  if (y < 0         ) y = 0;
  if (y > HEIGHT - 1) y = HEIGHT - 1;
  cursor_y = y;
  cursor_check();
}

void cursor_set(int x, int y)
{
  cursor_set_x(x);
  cursor_set_y(y);
}

void font_normal(int x, int y)
{
  screen_fill_attr(text_get_screen(), x, y, 1, 1,
		   text_get_palette() << 9,
		   0xe1ff); /* 1110 0001 1111 1111 */
}

void font_reverse(int x, int y)
{
  screen_fill_attr(text_get_screen(), x, y, 1, 1,
		   (cursor_get_type() & 0xffff) << 9,
		   0xe1ff); /* 1110 0001 1111 1111 */
}

void line_clear(int line)
{
  int i;
  for (i = 0; i < WIDTH; i++) screen[line][i] = ' ';
}

void screen_init()
{
  lcd_set_color(0xfff0, 0xffff);
  palette_set_color(0, 0xfff0);
  palette_set_color(1, 0x000f);
}

void screen_clear(void)
{
  int i;

  wonx_lcddraw_level_down();
  for (i = 0; i < HEIGHT; i++) line_clear(i);
  wonx_lcddraw_level_up();
}

void print_com_speed(int com_speed)
{
  text_put_string(23, KEYBOARD_Y + KEYBOARD_HEIGHT + 1,
		  (com_speed == COMM_SPEED_9600) ? " 96" : "384");
  comm_set_baudrate(com_speed);
}

void print_log_on()
{
  text_put_string(26, KEYBOARD_Y + KEYBOARD_HEIGHT + 1,
		  is_log_on() ? "L" : "N");
}

void print_com_connect()
{
  text_put_string(27, KEYBOARD_Y + KEYBOARD_HEIGHT + 1,
		  com_is_connected ? "C" : "N");
}

/* ターミナルスクリーンへの文字表示 */
void print_character(char c)
{
  static char last = '\0'; /* \r\n を \n にするため */

  wonx_lcddraw_level_down();

  /* ログの出力 */
  log_putc(c);

  /* エスケープシーケンスの処理 */
  if ((c == ESCAPE_CODE) || (escseq_length > 0)) {
    escseq_buffer[escseq_length] = c;
    escseq_length++;
    escseq_buffer[escseq_length] = '\0';
    if (is_alpha(c)) {
      parse_escseq();
      escseq_length = 0;
      escseq_buffer[0] = '\0';
    }
    goto ret1;
  }

  if (c == '\0') {
    goto ret1;
  } else if (c == '\r') {
    if (last == '\n') { goto ret2; } /* \n\r を \n にする */
    cursor_set_x(0);
    cursor_down(1);
  } else if (c == '\n') {
    if (last == '\r') { goto ret2; } /* \r\n を \r にする */
    cursor_set_x(0);
    cursor_down(1);
  } else if (c == 0x08) { /* バックスペース */
    cursor_left(1);
  } else if (c == 0x7f) { /* DEL */
    /* とりあえず，なにもしない */
  } else if ( (0x20 <= c) && (c <= 0x7e) ) {
    text_put_char(cursor_x, cursor_y, c);
    screen[cursor_y][cursor_x] = c;
    cursor_right(1);
  }

ret1:
  last = c;
ret2:
  wonx_lcddraw_level_up();
  return;
}

void print_string(char * s)
{
  wonx_lcddraw_level_down();
  while (*s != '\0') {
    print_character(*s);
    s++;
  }
  wonx_lcddraw_level_up();
}

/* End of Program  */
