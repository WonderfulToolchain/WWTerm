#include <stdio.h>
#include <stdlib.h>
#include <sys/comm.h>

#include "esclib.h"
#include "escape.h"
#include "screen.h"
#include "lib.h"

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
      cursol_send_mode = 1;
      break;
    }
    break;

  case 'l': /* ESC[?l DEC専用モードクリア */
    switch (command2) {
    case 1: /* アプリケーションモードをクリアする */
      cursol_send_mode = 0;
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
    comm_send_char(ESCAPE_CODE);
    comm_send_string("[0n");
    break;
  case 6:
    buffer[0] = ESCAPE_CODE;
    sprintf(buffer + 1, "[%d;%dR", cursol_y + 1, cursol_x + 1);
    comm_send_string(buffer);
    break;
  }
}

/* 画面のクリア */
void escape_screen_clear(char command)
{
  int i;
  switch (command) {
  case 0: /* カーソル位置から画面の終りまでをクリア */
    for (i = cursol_x; i < WIDTH; i++) { screen[cursol_y][i] = ' '; }
    for (i = cursol_y + 1; i < HEIGHT; i++) { line_clear(i); }
    refresh();
    break;
  case 1: /* 基点からカーソル位置までをクリア */
    for (i = 0; i < cursol_x + 1; i++) { screen[cursol_y][i] = ' '; }
    for (i = 0; i < cursol_y; i++) { line_clear(i); }
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
    for (i = cursol_x; i < WIDTH; i++) { screen[cursol_y][i] = ' '; }
    refresh();
    break;
  case 1: /* 行の先頭からカーソル位置までをクリア */
    for (i = 0; i < cursol_x + 1; i++) { screen[cursol_y][i] = ' '; }
    refresh();
    break;
  case 2: /* 行をすべてクリア */
    line_clear(cursol_y);
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
    for (i = HEIGHT - 1; i > cursol_y + parameter - 1; i--) {
      memcpy(screen[i], screen[i - parameter], sizeof(screen[0][0]) * WIDTH);
    }
    for (i = cursol_y; i < cursol_y + parameter; i++) {
      line_clear(i);
    }
    break;

  case 'M': /* ESC[M 行の削除 */
    for (i = cursol_y; i < HEIGHT - parameter; i++) {
      memcpy(screen[i], screen[i + parameter], sizeof(screen[0][0]) * WIDTH);
    }
    for (i = HEIGHT - 1; i > HEIGHT - 1 - parameter; i--) {
      line_clear(i);
    }
    break;
  }
}

/* End of Program  */
