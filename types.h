#ifndef _WWTERM_TYPES_H_
#define _WWTERM_TYPES_H_

#include <sys/text.h>

#ifdef _WONX_
#include "wonx/wonx.h"
#endif

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
#define HEIGHT (TEXT_SCREEN_HEIGHT - 6)

/* キーボードの表示位置 */
#define KEYBOARD_X 0
#define KEYBOARD_Y (HEIGHT + 1)

/* キーボードのモード数 */
#define KEYBOARD_MODE_NUM 3

/* キーボードのサイズ */
#define KEYBOARD_WIDTH 28
#define KEYBOARD_HEIGHT 3

#define KEYINFO_WIDTH  28
#define KEYINFO_HEIGHT  2

/* XON, XOFF */
#define XON  0x11
#define XOFF 0x13

/* 改行コード */
#define NEWLINE_CODE '\n'

/* エスケープ文字 */
#define ESCAPE_CODE 0x1b

/* ログの出力用ファイル名 */
#ifdef _WONX_
#define LOG_FILE "log%d"
#else
#define LOG_FILE "/ram0/log%d"
#endif

#ifdef _WONX_ /* WonX用 */
#define wonx_lcddraw_level_down() wonx_lcddraw_level_down()
#define wonx_lcddraw_level_up()   wonx_lcddraw_level_up()
#else
#define wonx_lcddraw_level_down() do { /* None */ } while (0)
#define wonx_lcddraw_level_up()   do { /* None */ } while (0)
#endif

#endif /* _WWTERM_TYPES_H_ */

/* End of Program  */
