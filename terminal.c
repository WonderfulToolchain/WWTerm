/*
 * WWTerm - Terminal for WonderWitch
 *
 * WonderWitch 用 ターミナルアプリケーション
 * 2000/12/16(土) 坂井弘亮
 *
 * FAQ.
 *
 * Q.通信ができない．
 * A.接続されてません．画面上の「仮想キーボード」の左下にある 'C' を使って，
 *   connect 状態にしてください．
 *
 * Q.文字列の受信時に，xという文字列ばかりが出てくる．
 * A.シリアルのスピードがあっていません．画面上の「仮想キーボード」の
 *   左下にある 'S' を使って，速度を変更してください．
 *
 * Q.文字列の受信時に，おかしな文字列ばかりが出てくる．
 * A.シリアルのスピードがあっていません．画面上の「仮想キーボード」の
 *   左下にある 'S' を使って，速度を変更してください．
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/text.h>
#include <sys/key.h>
#include <sys/comm.h>
#include <sys/system.h>

#include "types.h"
#include "lib.h"
#include "termlib.h"
#include "keyboard.h"
#include "keymap.h"
#include "com.h"
#include "screen.h"

/* 終了のフラグ */
static int end_flag = 0;

/* 文字入力 */
int input_character()
{
  int ch;
  int key;

  key = key_press_check();
  ch = '\0';

  if (key & (KEY_X1 | KEY_X2 | KEY_X3 | KEY_X4)) {
    ch = key_X1234_action(key);
  }
  if (key & (KEY_Y1 | KEY_Y2 | KEY_Y3 | KEY_Y4)) {
    ch = key_Y1234_action(key);
  }

  if (key & KEY_A    ) { ch = key_A_action(key); }
  if (key & KEY_B    ) { ch = key_B_action(key); }
  if (key & KEY_START) { ch = key_START_action(key); }

  if (!com_is_connected) {
    print_character(ch);
  }

  return (ch);
}

/* キー入力の割り込みハンドラ */
void far key_handler()
{
  int ch;

  /* 送信 */
  ch = input_character();

  if (ch == -1) {
    end_flag = 1;
  }

  if (com_is_connected && (ch != 0)) comm_send_char(ch);
}

/* シリアル受信の割り込みハンドラ */
void far com_handler()
{
#ifdef FLOW_CONTROL
  com_pause();
#endif

  /* シリアル受信 */
  com_receive();

  /* バッファのフラッシュ */
#if 0 /* ハンドラ内でフラッシュすると，文字落ちを起こすので */
  com_flush();
#endif

#ifdef FLOW_CONTROL
  com_unpause();
#endif
}

/* 初期化 */
void init(void)
{
  text_screen_init();
  screen_init();
  screen_clear();
  refresh();

  print_com_speed(DEFAULT_COM_SPEED);
  print_com_connect();
  make_keyboard();
  cursor_display(1);
}

static intvector_t key_intvector;
static intvector_t key_last_intvector;
static intvector_t com_intvector;
static intvector_t com_last_intvector;

/* メイン */
void main()
{
  init();

  comm_set_timeout(0, 75 * 5); /* 受信のタイムアウトは0/75秒，送信のは75/75秒*/
  comm_open();

  key_intvector.callback = (void (near *)())FP_OFF(key_handler);
  com_intvector.callback = (void (near *)())FP_OFF(com_handler);
#if 0
  key_intvector.cs = FP_SEG(com_handler);
  key_intvector.ds = FP_SEG(&com_receive_start);
  com_intvector.cs = FP_SEG(com_handler);
  com_intvector.ds = FP_SEG(&com_receive_start);
#else
  key_intvector.cs = _asm_inline("\tmov\tax,cs");
  key_intvector.ds = _asm_inline("\tmov\tax,ds");
  com_intvector.cs = _asm_inline("\tmov\tax,cs");
  com_intvector.ds = _asm_inline("\tmov\tax,ds");
#endif

  sys_interrupt_set_hook(SYS_INT_KEY,
			 &key_intvector, &key_last_intvector);
  sys_interrupt_set_hook(SYS_INT_RECEIVEREADY,
			 &com_intvector, &com_last_intvector);

  while (!end_flag) {
    com_flush();
    sys_wait(7); /* ウエイトを 1/75秒単位で指定する */
  }

  sys_interrupt_reset_hook(SYS_INT_KEY, &key_last_intvector);
  sys_interrupt_reset_hook(SYS_INT_RECEIVEREADY, &com_last_intvector);

  comm_close();

  bios_exit();
}

/* End of Program  */
