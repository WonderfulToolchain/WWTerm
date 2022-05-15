#ifndef _WWTERM_KEYMAP_H_
#define _WWTERM_KEYMAP_H_

#include "types.h"

#define KEY_SL            (-1) /* Same as Left */
#define KEY_COM_CONNECT   (-2)
#define KEY_COM_SPEED     (-3)
#define KEY_CLEAN_SCREEN  (-4)
#define KEY_CHANGE_MODE   (-5)
#define KEY_LOG_SWITCH    (-6)
#define KEY_SEND_RESIZE   (-7)

#define KEY_CURSOR_UP     (-11)
#define KEY_CURSOR_DOWN   (-12)
#define KEY_CURSOR_LEFT   (-13)
#define KEY_CURSOR_RIGHT  (-14)
#define KEY_SCREEN_UP     (-15)
#define KEY_SCREEN_DOWN   (-16)
#define KEY_SCREEN_LEFT   (-17)
#define KEY_SCREEN_RIGHT  (-18)

#define KEY_F1            (-21)
#define KEY_F2            (-22)
#define KEY_F3            (-23)
#define KEY_F4            (-24)
#define KEY_F5            (-25)
#define KEY_F6            (-26)
#define KEY_F7            (-27)
#define KEY_F8            (-28)
#define KEY_F9            (-29)
#define KEY_F10           (-30)

#define FUNCTION_KEY_NUMBER 10

#define KEY_STRING_MAX_LENGTH KEYBOARD_WIDTH

typedef struct _keymap {
  int key;       /* 送信する文字 */
  char * symbol; /* キーボードに表示する文字列(NULLの場合は送信文字と同じ) */
  char * string; /* メッセージに表示する文字列 */
} keymap;

extern keymap keyboard[KEYBOARD_MODE_NUM][KEYBOARD_HEIGHT][KEYBOARD_WIDTH];
extern char * keyinfo[KEYBOARD_MODE_NUM][KEYINFO_HEIGHT];
extern int y1234map[KEYBOARD_MODE_NUM][4];
extern char * default_function_key[FUNCTION_KEY_NUMBER];

#endif /* _WWTERM_KEYMAP_H_ */

/* End of Program  */
