#ifndef _WWTERM_TYPES_H_
#define _WWTERM_TYPES_H_

#include <sys/text.h>

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

/* 最初に表示する文字列 */
#define FIRST_STRING "WWTerm(C)2000 SAKAI Hiroaki.\nPush S at left-below of the\nvirtual keyboard to change\nthe serial port speed.\nPush C at left-below of the\nvirtual keyboard to connect\nthe serial port.\n"

/* ターミナルのスクリーンサイズ */
#define WIDTH  (TEXT_SCREEN_WIDTH)
#define HEIGHT (TEXT_SCREEN_HEIGHT - 8)

/* キーボードの表示位置 */
#define KEYBOARD_X 1
#define KEYBOARD_Y (HEIGHT + 1)

/* キーボードのサイズ */
#define KEYBOARD_WIDTH 27
#define KEYBOARD_HEIGHT 5

/* XON, XOFF */
#define XON  0x11
#define XOFF 0x13

/* 改行コード */
#define NEWLINE_CODE '\n'

/* エスケープ文字 */
#define ESCAPE_CODE 0x1b

#endif /* _WWTERM_TYPES_H_ */

/* End of Program  */
