#include <string.h>

#include "types.h"
#include "keyboard.h"
#include "keymap.h"
#include "screen.h"

/* キーボードのカーソル座標 */
int keyboard_cursol_x = 0;
int keyboard_cursol_y = 0;

void clear_keycursol()
{
  text_put_char(KEYBOARD_X - 1, KEYBOARD_Y + keyboard_cursol_y, ' ');
  text_put_char(KEYBOARD_X + keyboard_cursol_x, KEYBOARD_Y - 1, '-');
  font_normal(KEYBOARD_X + keyboard_cursol_x, KEYBOARD_Y + keyboard_cursol_y);
}

void print_keycursol()
{
  static char string[10];
  int i, len;

  keyboard_copy_string(string);
  len = strlen(string);
  for (i = len; i < KEY_STRING_MAX_LENGTH; i++) {
    string[i] = '-';
  }
  string[KEY_STRING_MAX_LENGTH] = '\0';

  text_put_char(KEYBOARD_X - 1, KEYBOARD_Y + keyboard_cursol_y, 0x10);
  text_put_char(KEYBOARD_X + keyboard_cursol_x, KEYBOARD_Y - 1, 0x1f);
  text_put_string(KEYBOARD_X + KEYBOARD_WIDTH  - KEY_STRING_MAX_LENGTH,
		  KEYBOARD_Y + KEYBOARD_HEIGHT - 1, string);
  font_reverse(KEYBOARD_X + keyboard_cursol_x, KEYBOARD_Y + keyboard_cursol_y);
#if 0
  cursor_set_location(KEYBOARD_X + keyboard_cursol_x,
		      KEYBOARD_Y + keyboard_cursol_y, 1, 1);
#endif
}

void make_keyboard()
{
  for (keyboard_cursol_y = 0;
       keyboard_cursol_y < KEYBOARD_HEIGHT;
       keyboard_cursol_y++) {
    for (keyboard_cursol_x = 0;
	 keyboard_cursol_x < KEYBOARD_WIDTH;
	 keyboard_cursol_x++) {
      text_put_char(KEYBOARD_X + keyboard_cursol_x,
		    KEYBOARD_Y + keyboard_cursol_y, keyboard_get_symbol());
    }
  }

  text_put_string(0, KEYBOARD_Y - 1, "----------------------------");

  text_put_string(0, KEYBOARD_Y + KEYBOARD_HEIGHT + 0,
		  "X1234)Select A)Input B)Enter");
  text_put_string(0, KEYBOARD_Y + KEYBOARD_HEIGHT + 1,
		  "Y1234)Move START)Quit");

  keyboard_cursol_x = 0;
  keyboard_cursol_y = 0;

  print_keycursol();
}

int keyboard_get_key()
{
  return (keyboard[keyboard_cursol_y][keyboard_cursol_x].key);
}

unsigned char keyboard_get_symbol()
{
  unsigned char symbol;
  symbol = keyboard[keyboard_cursol_y][keyboard_cursol_x].symbol;
  if (symbol == '\0') symbol = keyboard_get_key();
  return (symbol);
}

void keyboard_copy_string(char * buffer)
{
  char * string;
  string = keyboard[keyboard_cursol_y][keyboard_cursol_x].string;
  if (string == NULL) {
    buffer[0] = keyboard_get_symbol();
    buffer[1] = '\0';
  } else {
    strcpy(buffer, string);
  }
}

void keyboard_change_string(char * string)
{
  keyboard[keyboard_cursol_y][keyboard_cursol_x].string = string;
}

/* End of Program  */
