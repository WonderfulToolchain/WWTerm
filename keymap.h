#ifndef _WWTERM_KEYMAP_H_
#define _WWTERM_KEYMAP_H_

#include "types.h"

#define KEY_COM_CONNECT  (-1)
#define KEY_COM_SPEED    (-2)
#define KEY_CLEAR_SCREEN (-3)

#define KEY_STRING_MAX_LENGTH 10

typedef struct _keymap {
  int key;    /* 送信する文字 */
  unsigned char symbol; /* キーボードに表示する文字 */
  char * string;        /* キーボードの右下に表示する文字列 */
} keymap;

extern keymap keyboard[KEYBOARD_HEIGHT][KEYBOARD_WIDTH];

#endif /* _WWTERM_KEYMAP_H_ */

/* End of Program  */
