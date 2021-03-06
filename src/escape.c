#include <stdio.h>
#include <stdlib.h>
#include <sys/comm.h>

#include "escape.h"
#include "esclib.h"
#include "screen.h"

/* エスケープシーケンスの処理用バッファ */
int escseq_length = 0;
char escseq_buffer[20] = "\0";

int cursor_send_mode = 0; /* DEC専用モードのアプリケーションモード */

/* 引数 */
int escape_args[20];

/* エスケープシーケンスの処理 */
void parse_escseq()
{
  int tmp1, tmp2;
  int dec_mode = 0; /* DEC専用モード */
  char command;

  if (escseq_length < 3) return;
  if (escseq_buffer[0] != ESCAPE_CODE) return;
  if (escseq_buffer[1] != '[') return;
  if (escseq_buffer[2] == '?') dec_mode = 1;

  command = make_args();

  tmp1 = escape_args[0];
  tmp2 = escape_args[1];

  switch (command) {

  case 'n': /* ESC[n カーソル座標を通知 */
    escape_send_stat(tmp1);
    break;

  case 'A': /* ESC[A カーソルを上に移動 */
    if (tmp1 < 0) tmp1 = 1;
    cursor_up(tmp1);
    break;

  case 'B': /* ESC[B カーソルを下に移動 */
  case 'e': /* ESC[e カーソルを下に移動 */
    if (tmp1 < 0) tmp1 = 1;
    cursor_down(tmp1);
    break;

  case 'C': /* ESC[C カーソルを右に移動 */
  case 'a': /* ESC[a カーソルを右に移動 */
    if (tmp1 < 0) tmp1 = 1;
    cursor_right(tmp1);
    break;

  case 'D': /* ESC[D カーソルを左に移動 */
    if (tmp1 < 0) tmp1 = 1;
    cursor_left(tmp1);
    break;

  case 'G': /* ESC[G カーソルのx座標を設定 */
    tmp1--;
    if (tmp1 < 0) tmp1 = 0;
    cursor_set_x(tmp1);
    break;

  case 'd': /* ESC[d カーソルのy座標を設定 */
    tmp1--;
    if (tmp1 < 0) tmp1 = 0;
    cursor_set_y(tmp1);
    break;

  case 'E': /* ESC[E カーソルをpar1行下の先頭に移動する */
    if (tmp1 < 0) tmp1 = 1;
    cursor_down(tmp1);
    cursor_set_x(0);
    break;

  case 'F': /* ESC[F カーソルをpar1行上の先頭に移動する */
    if (tmp1 < 0) tmp1 = 1;
    cursor_up(tmp1);
    cursor_set_x(0);
    break;

  case 'H': /* ESC[<row>;<col>H カーソルを指定した座標に移動 */
    tmp1--;
    tmp2--;
    if (tmp1 < 0) tmp1 = 0;
    if (tmp2 < 0) tmp2 = 0;
    cursor_set(tmp2, tmp1);
    break;

  case 'J': /* ESC[J クリア */
    if (tmp1 < 0) tmp1 = 0;
    escape_screen_clear(tmp1);
    break;

  case 'K': /* ESC[K クリア */
    if (tmp1 < 0) tmp1 = 0;
    escape_line_clear(tmp1);
    break;

  case 'L': /* ESC[L 行の挿入 */
  case 'M': /* ESC[M 行の削除 */
    if (tmp1 < 0) tmp1 = 1;
    escape_ins_del(command, tmp1);
    break;

  case 'h': /* ESC[?h DEC専用モード設定 */
  case 'l': /* ESC[?l DEC専用モードクリア */
    if (!dec_mode) break;
    parse_dec_escseq(command, escape_args[1]);
    break;
  }
}

/* End of Program  */
