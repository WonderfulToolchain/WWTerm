/*
 * WWTerm - Terminal for WonderWitch
 *
 * WonderWitch 用 ターミナルアプリケーション
 * 2000/12/16(土) 坂井弘亮
 *
 * FAQ.
 *
 * Q.通信ができない．
 * A.接続されてません．Y2ボタンで connect 状態にしてください．
 *
 * Q.文字列の受信時に，xという文字列ばかりが出てくる．
 * A.シリアルのスピードがあっていません．Y1ボタンで速度を変更してください．
 *
 * Q.文字列の受信時に，おかしな文字列ばかりが出てくる．
 * A.シリアルのスピードがあっていません．Y1ボタンで速度を変更してください．
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/text.h>
#include <sys/key.h>
#include <sys/comm.h>
#include <sys/system.h>

/* デフォルトの通信速度 */
#define DEFAULT_COM_SPEED COMM_SPEED_9600

/* 受信時に XON/XOFF のフロー制御を行う */
/* #define FLOW_CONTROL */

/* 文字列表示時に XON/XOFF のフロー制御により，受信を一時停止する */
#define COM_PAUSE_IN_PRINTING

/* バッファがいっぱいのときはフラッシュする */
#define FLUSH_IN_BUFFER_OVER

/* 受信バッファサイズ(あまり大きくしないように注意すること) */
#define BUFFER_SIZE 1024

/* 受信バッファ */
#define FIRST_STRING "WWTerm(C)2000 SAKAI Hiroaki.\nPush Y1 to change the speed\nof the serial port.\nPush Y2 to connect to the\nserial port.\n\n\n"
static char com_receive_buffer[BUFFER_SIZE] = FIRST_STRING;
static int com_receive_start = 0;
static int com_receive_end   = sizeof(FIRST_STRING) - 1;

/* ターミナルのスクリーンサイズ */
#define WIDTH  (TEXT_SCREEN_WIDTH)
#define HEIGHT (TEXT_SCREEN_HEIGHT - 9)

/* ターミナルのスクリーン */
static char screen[HEIGHT][WIDTH];

/* カーソルの位置 */
static int cursol_x = 0, cursol_y = 0;

/* キーボードの表示位置 */
#define KEYBOARD_X 1
#define KEYBOARD_Y (HEIGHT + 1)

/* キーボードのサイズ */
#define KEYBOARD_WIDTH 27
#define KEYBOARD_HEIGHT 4

/* 接続状態 0.非接続 1.接続 */
static int com_is_connected = 0;

/* 停止状態 0.通信中 1.停止中 */
static int com_is_paused = 0;

/* XON, XOFF */
#define XON  0x11
#define XOFF 0x13

/* 改行コード */
#define NEWLINE_CODE '\n'

/* キーボードのカーソル座標 */
static int keyboard_cursol_x = 0;
static int keyboard_cursol_y = 0;

/* 終了のフラグ */
static int end_flag = 0;

/* キーボードのマッピング */
static unsigned char keyboard[KEYBOARD_HEIGHT][KEYBOARD_WIDTH] = {
  {0x61,0x62,0x63,0x64,0x65,0x66,0x67, 0x20,
   0x41,0x42,0x43,0x44,0x45,0x46,0x47, 0x20,
   0x37,0x38,0x39,0x2b,0x2d, 0x20,
   0x20,0x21,0x22,0x23,0x24},
  {0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e, 0x20,
   0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e, 0x20,
   0x34,0x35,0x36,0x2a,0x2f, 0x20,
   0x25,0x26,0x27,0x40,0x5e},
  {0x6f,0x70,0x71,0x72,0x73,0x74,0x75, 0x20,
   0x4f,0x50,0x51,0x52,0x53,0x54,0x55, 0x20,
   0x31,0x32,0x33,0x3c,0x3e, 0x20,
   0x5b,0x5d,0x5c,0x5f,0x60},
  {0x76,0x77,0x78,0x79,0x7a,0x28,0x29, 0x20,
   0x56,0x57,0x58,0x59,0x5a,0x3a,0x3b, 0x20,
   0x30,0x2c,0x2e,0x3d,0x3f, 0x20,
   0x7b,0x7d,0x7c,0x7e,0x7f}
};

void line_clear(int line)
{
  int i;
  for (i = 0; i < WIDTH; i++) screen[line][i] = ' ';
}

void screen_clear(void)
{
  int i;
  for (i = 0; i < HEIGHT; i++) line_clear(i);
}

void clear_keycursol(int x, int y)
{
  text_put_char(KEYBOARD_X - 1, KEYBOARD_Y + y, ' ');
  text_put_char(KEYBOARD_X + x, KEYBOARD_Y - 1, '-');
}

void print_keycursol(int x, int y)
{
  text_put_char(KEYBOARD_X - 1, KEYBOARD_Y + y, 0x10);
  text_put_char(KEYBOARD_X + x, KEYBOARD_Y - 1, 0x1f);
  text_put_char(KEYBOARD_X - 1, KEYBOARD_Y - 1, keyboard[y][x]);
  cursor_set_location(KEYBOARD_X + x, KEYBOARD_Y + y, 1, 1);
}

void make_keyboard()
{
  int x, y;

  for (y = 0; y < KEYBOARD_HEIGHT; y++) {
    for (x = 0; x < KEYBOARD_WIDTH; x++) {
      text_put_char(KEYBOARD_X + x, KEYBOARD_Y + y, keyboard[y][x]);
    }
  }

  text_put_string(0, KEYBOARD_Y - 1,
		  "----------------------------");
  text_put_string(0, KEYBOARD_Y + KEYBOARD_HEIGHT,
		  "----------------------------");

  text_put_string(0, KEYBOARD_Y + KEYBOARD_HEIGHT + 1,
		  "X1234)Select A)Input B)Enter");
  text_put_string(0, KEYBOARD_Y + KEYBOARD_HEIGHT + 2,
		  "Y1)Speed Y2)Connect");
  text_put_string(0, KEYBOARD_Y + KEYBOARD_HEIGHT + 3,
		  "Y3)Clear START)Quit");

  print_keycursol(0, 0);
}

void print_com_speed(int com_speed)
{
  char * s = "Unknown ";

  if      (com_speed == COMM_SPEED_9600 ) s = " 9600bps";
  else if (com_speed == COMM_SPEED_38400) s = "38400bps";

  text_put_string(20, KEYBOARD_Y + KEYBOARD_HEIGHT + 2, s);

  comm_set_baudrate(com_speed);
}

void print_com_connect()
{
  char * s;

  if (com_is_connected) s = " Connect";
  else                  s = " Discon.";

  text_put_string(20, KEYBOARD_Y + KEYBOARD_HEIGHT + 3, s);
}

void refresh(void)
{
  int y;

  for (y = 0; y < HEIGHT; y++) {
    text_put_substring(0, y, screen[y], WIDTH);
  }

  text_put_char(cursol_x, cursol_y, '_');
}

/* ターミナルスクリーンへの文字表示 */
void print_character(char c)
{
  int i;
  static char last = '\0'; /* \r\n を \n にするため */

  if (c == '\0') {
    last = c;
    return;
  } else if (c == '\r') {
    if (last == '\n') { return; } /* \n\r を \n にする */
    text_put_char(cursol_x, cursol_y, ' ');
    cursol_x = 0;
    cursol_y++;
  } else if (c == '\n') {
    if (last == '\r') { return; } /* \r\n を \r にする */
    text_put_char(cursol_x, cursol_y, ' ');
    cursol_x = 0;
    cursol_y++;
  } else if ( (0x20 <= c) && (c <= 0x7f) ) {
    text_put_char(cursol_x, cursol_y, c);
    screen[cursol_y][cursol_x] = c;
    cursol_x++;

    if (cursol_x >= WIDTH) {
      cursol_x = 0;
      cursol_y++;
    }
  } else {
    last = c;
    return;
  }

  last = c;

  while (cursol_y >= HEIGHT) {
    for (i = 0; i < HEIGHT - 1; i++) {
      memcpy(screen[i], screen[i + 1], sizeof(screen[0][0]) * WIDTH);
    }
    line_clear(i);
    cursol_y--;

    refresh();
  }

  text_put_char(cursol_x, cursol_y, '_');
}

void com_pause()
{
  com_is_paused++;
  if (com_is_connected && (com_is_paused == 1)) comm_send_char(XOFF);
}

void com_unpause()
{
  com_is_paused--;
  if (com_is_connected && (com_is_paused == 0)) comm_send_char(XON);
}

void com_flush()
{
#ifdef COM_PAUSE_IN_PRINTING
  com_pause();
#endif
  while (com_receive_start != com_receive_end) {
    print_character(com_receive_buffer[com_receive_start]);
    com_receive_start = (com_receive_start + 1) % BUFFER_SIZE;
  }
#ifdef COM_PAUSE_IN_PRINTING
  com_unpause();
#endif
}

void com_receive()
{
  int c;
  int e;

  c = comm_receive_char();

  if (!com_is_connected) { return; }

  if (c == ERR_SIO_TIMEOUT) { return; }
  if (c == ERR_SIO_CANCEL ) { return; }
  if (c == ERR_SIO_OVERRUN) { return; }

  e = (com_receive_end + 1) % BUFFER_SIZE;

  if (com_receive_start == e) {
#ifdef FLUSH_IN_BUFFER_OVER
    com_flush(); /* バッファがいっぱいのときはフラッシュする */
    e = (com_receive_end + 1) % BUFFER_SIZE;
#else
    return; /* バッファがいっぱいのときは廃棄 */
#endif
  }

  com_receive_buffer[com_receive_end] = c;
  com_receive_end = e;
}

/* 文字入力 */
int input_character()
{
  int ch;
  int key;
  int com_speed;

  key = key_press_check();
  ch = '\0';

  if (key & (KEY_X1 | KEY_X2 | KEY_X3 | KEY_X4)) {

    clear_keycursol(keyboard_cursol_x, keyboard_cursol_y);

    if (key & KEY_X1) keyboard_cursol_y--;
    if (key & KEY_X2) keyboard_cursol_x++;
    if (key & KEY_X3) keyboard_cursol_y++;
    if (key & KEY_X4) keyboard_cursol_x--;
    keyboard_cursol_x =
      (keyboard_cursol_x + KEYBOARD_WIDTH ) % KEYBOARD_WIDTH;
    keyboard_cursol_y =
      (keyboard_cursol_y + KEYBOARD_HEIGHT) % KEYBOARD_HEIGHT;

    print_keycursol(keyboard_cursol_x, keyboard_cursol_y);
  }

  if (key & KEY_A    ) { ch = keyboard[keyboard_cursol_y][keyboard_cursol_x]; }
  if (key & KEY_B    ) { ch = NEWLINE_CODE; }
  if (key & KEY_START) { ch = -1; }

  if (key & KEY_Y1) {
    com_speed = comm_get_baudrate();
    if      (com_speed == COMM_SPEED_9600 ) com_speed = COMM_SPEED_38400;
    else if (com_speed == COMM_SPEED_38400) com_speed = COMM_SPEED_9600;
    print_com_speed(com_speed);
  }

  if (key & KEY_Y2) {
    com_is_connected = !com_is_connected;
    print_com_connect();
  }

  if (key & KEY_Y3) {
    cursol_x = 0;
    cursol_y = 0;
    screen_clear();
    refresh();
  }

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
