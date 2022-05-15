#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/comm.h>

#include "esclib.h"
#include "escape.h"
#include "screen.h"
#include "lib.h"
#include "com.h"

#if 1
static unsigned char resize_begin[] = "\neval `resize`";
static unsigned char resize_end[] = "\n";
#else
static unsigned char resize_begin[] = {
  0xff, 0xfe, 0x01, 0xff, 0xfa, 0x22, 0x01, 0x07,
  0xff, 0xf0, 0xff, 0xfa, 0x22, 0x03, 0x05, 0x82,
  0x14, 0x08, 0x82, 0x04, 0x09, 0xc2, 0x1a, 0x0c,
  0x82, 0x17, 0x0d, 0x82, 0x12, 0x0e, 0x82, 0x16,
  0xff, 0xf0, 0xff, 0xfa, 0x22, 0x01, 0x06, 0xff,
  0xf0, 0xff, 0xfa, 0x22, 0x03, 0x05, 0x80, 0xff,
  0xff, 0x08, 0x80, 0xff, 0xff, 0x09, 0x80, 0xff,
  0xff, 0x0c, 0x80, 0xff, 0xff, 0x0d, 0x80, 0xff,
  0xff, 0x0e, 0x80, 0xff, 0xff, 0xff, 0xf0, 0xff,
  0xfd, 0x01, 0xff, 0xfa, 0x1f
};
static unsigned char resize_end[] = { 0xff, 0xf0 };
#endif

char make_args()
{
  int i, argc;
  char * p;

  for (i = 0; i < 20; i++) {
    escape_args[i] = -1;
  }

  argc = 0;
  p = escseq_buffer + 2;
  while (!is_alpha(*p)) {
    escape_args[argc] = asc2int(p);
    argc++;
    while (is_digit(*p)) { p++; }
    if (!is_alpha(*p)) p++;
  }
  return (*p);
}

void parse_dec_escseq(char command1, int command2)
{
  switch (command1) {
  case 'h': /* ESC[?h DEC専用モード設定 */
    switch (command2) {
    case 1: /* カーソルキーをアプリケーションモードにする */
      cursor_send_mode = 1;
      break;
    }
    break;

  case 'l': /* ESC[?l DEC専用モードクリア */
    switch (command2) {
    case 1: /* アプリケーションモードをクリアする */
      cursor_send_mode = 0;
      break;
    }
    break;
  }
}

/* 状態を通知 */
void escape_send_stat(char command)
{
  static char buffer[30];
  switch (command) {
  case 5:
    com_putc(ESCAPE_CODE);
    com_puts("[0n");
    break;
  case 6:
    buffer[0] = ESCAPE_CODE;
    sprintf(buffer + 1, "[%d;%dR", cursor_y + 1, cursor_x + 1);
    com_puts(buffer);
    break;
  }
}

/* 画面のクリア */
void escape_screen_clear(char command)
{
  int i;
  switch (command) {
  case 0: /* カーソル位置から画面の終りまでをクリア */
    for (i = cursor_x; i < WIDTH; i++) { screen[cursor_y][i] = ' '; }
    for (i = cursor_y + 1; i < HEIGHT; i++) { line_clear(i); }
    refresh();
    break;
  case 1: /* 基点からカーソル位置までをクリア */
    for (i = 0; i < cursor_x + 1; i++) { screen[cursor_y][i] = ' '; }
    for (i = 0; i < cursor_y; i++) { line_clear(i); }
    refresh();
    break;
  case 2: /* 画面をすべてクリア */
    screen_clear();
    refresh();
    break;
  }
}

/* 行のクリア */
void escape_line_clear(char command)
{
  int i;
  switch (command) {
  case 0: /* カーソル位置から行の終りまでをクリア */
    for (i = cursor_x; i < WIDTH; i++) { screen[cursor_y][i] = ' '; }
    refresh();
    break;
  case 1: /* 行の先頭からカーソル位置までをクリア */
    for (i = 0; i < cursor_x + 1; i++) { screen[cursor_y][i] = ' '; }
    refresh();
    break;
  case 2: /* 行をすべてクリア */
    line_clear(cursor_y);
    refresh();
    break;
  }
}

/* 行の挿入/削除 */
void escape_ins_del(char command, int parameter)
{
  int i;

  switch (command) {

  case 'L': /* ESC[L 行の挿入 */
    for (i = HEIGHT - 1; i > cursor_y + parameter - 1; i--) {
      memcpy(screen[i], screen[i - parameter], sizeof(screen[0][0]) * WIDTH);
    }
    for (i = cursor_y; i < cursor_y + parameter; i++) {
      line_clear(i);
    }
    break;

  case 'M': /* ESC[M 行の削除 */
    for (i = cursor_y; i < HEIGHT - parameter; i++) {
      memcpy(screen[i], screen[i + parameter], sizeof(screen[0][0]) * WIDTH);
    }
    for (i = HEIGHT - 1; i > HEIGHT - 1 - parameter; i--) {
      line_clear(i);
    }
    break;
  }
}

void send_resize()
{
  if (com_is_connected) {
#if 1
    com_puts(resize_begin);
    com_puts(resize_end);
#else
    com_putb(resize_begin, sizeof(resize_begin));
    com_putc(0x00);
    com_putc(WIDTH);
    com_putc(0x00);
    com_putc(HEIGHT);
    com_putb(resize_end, sizeof(resize_end));
#endif
  } else {
    print_string(resize_begin);
    print_string(resize_end);
  }
}

/* End of Program  */
