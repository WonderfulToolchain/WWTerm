#include <stdlib.h>
#include <sys/disp.h>

#include "screen.h"
#include "com.h"
#include "lib.h"
#include "escape.h"

/* ターミナルのスクリーン */
char screen[HEIGHT][WIDTH];

/* カーソルの位置 */
int cursol_x = 0;
int cursol_y = 0;

void refresh(void)
{
  int y;

  for (y = 0; y < HEIGHT; y++) {
    text_put_substring(0, y, screen[y], WIDTH);
  }
}

static void cursol_check()
{
  int i;

  while (cursol_x < 0) {
    cursol_x += WIDTH;
    cursol_y--;
  }

  while (cursol_x > WIDTH - 1) {
    cursol_x -= WIDTH;
    cursol_y++;
  }

  if (cursol_y < 0) cursol_y = 0;

  if (cursol_y >= HEIGHT) {
    while (cursol_y >= HEIGHT) {
      for (i = 0; i < HEIGHT - 1; i++) {
	memcpy(screen[i], screen[i + 1], sizeof(screen[0][0]) * WIDTH);
      }
      line_clear(i);
      cursol_y--;
    }
    refresh();
  }

  cursor_set_location(cursol_x, cursol_y, 1, 1);
}

void cursol_up(int add)
{
  cursol_y -= add;
  cursol_check();
}

void cursol_down(int add)
{
  cursol_y += add;
  cursol_check();
}

void cursol_left(int add)
{
  cursol_x -= add;
  cursol_check();
}

void cursol_right(int add)
{
  cursol_x += add;
  cursol_check();
}

void cursol_set_x(int x)
{
  if (x < 0         ) x = 0;
  if (x > WIDTH  - 1) x = WIDTH  - 1;
  cursol_x = x;
  cursol_check();
}

void cursol_set_y(int y)
{
  if (y < 0         ) y = 0;
  if (y > HEIGHT - 1) y = HEIGHT - 1;
  cursol_y = y;
  cursol_check();
}

void cursol_set(int x, int y)
{
  cursol_set_x(x);
  cursol_set_y(y);
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
  for (i = 0; i < HEIGHT; i++) line_clear(i);
}

void print_com_speed(int com_speed)
{
  char * s = "ERR";

  if      (com_speed == COMM_SPEED_9600 ) { s = " 96"; }
  else if (com_speed == COMM_SPEED_38400) { s = "384"; }

  text_put_string(22, KEYBOARD_Y + KEYBOARD_HEIGHT + 1, s);

  comm_set_baudrate(com_speed);
}

void print_com_connect()
{
  char * s;

  if (com_is_connected) s = "Cn";
  else                  s = "NC";

  text_put_string(26, KEYBOARD_Y + KEYBOARD_HEIGHT + 1, s);
}

/* ターミナルスクリーンへの文字表示 */
void print_character(char c)
{
  static char last = '\0'; /* \r\n を \n にするため */

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
    last = c;
    return;
  }

  if (c == '\0') {
    last = c;
    return;
  } else if (c == '\r') {
    if (last == '\n') { return; } /* \n\r を \n にする */
    cursol_set_x(0);
    cursol_down(1);
  } else if (c == '\n') {
    if (last == '\r') { return; } /* \r\n を \r にする */
    cursol_set_x(0);
    cursol_down(1);
  } else if (c == 0x08) { /* バックスペース */
    cursol_left(1);
  } else if (c == 0x7f) { /* DEL */
    /* とりあえず，なにもしない */
  } else if ( (0x20 <= c) && (c <= 0x7e) ) {
    text_put_char(cursol_x, cursol_y, c);
    screen[cursol_y][cursol_x] = c;
    cursol_right(1);
  }

  last = c;
}

/* End of Program  */
