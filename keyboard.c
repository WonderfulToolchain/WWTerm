#include <string.h>

#include "types.h"
#include "keyboard.h"
#include "keymap.h"
#include "screen.h"
#include "lib.h"

static void get_keymap();
static char * get_symbol();
static char * get_string();

/* キーボードのモード(Shiftで変更) */
static int keyboard_mode = 0;

/* キーボードのカーソル座標 */
static int keyboard_cursor_x = 0;
static int keyboard_cursor_y = 0;

/* 現在フォーカスしているキーマップ */
static int keymap_x = 0;
static int keymap_y = 0;
static keymap * keymap_key = &(keyboard[0][0][0]);

/* ファンクションキー */
static char * function_key[FUNCTION_KEY_NUMBER];

void keycursor_up()
{
  clear_keycursor();
  keyboard_cursor_y--;
  if (keyboard_cursor_y < 0) keyboard_cursor_y = KEYBOARD_HEIGHT - 1;
  get_keymap();
  print_keycursor();
}

void keycursor_down()
{
  clear_keycursor();
  keyboard_cursor_y++;
  if (keyboard_cursor_y > KEYBOARD_HEIGHT - 1) keyboard_cursor_y = 0;
  get_keymap();
  print_keycursor();
}

void keycursor_left()
{
  clear_keycursor();
  get_keymap();
  keyboard_cursor_x = keymap_x;
  keyboard_cursor_y = keymap_y;
  keyboard_cursor_x--;
  if (keyboard_cursor_x < 0) keyboard_cursor_x = KEYBOARD_WIDTH - 1;
  get_keymap();
  keyboard_cursor_x = keymap_x;
  keyboard_cursor_y = keymap_y;
  get_keymap();
  print_keycursor();
}

void keycursor_right()
{
  clear_keycursor();
  get_keymap();
  keyboard_cursor_x = keymap_x;
  keyboard_cursor_y = keymap_y;
  keyboard_cursor_x++;
  if (keyboard_cursor_x > KEYBOARD_WIDTH - 1) keyboard_cursor_x = 0;
  while (1) {
    keymap_key =
      &(keyboard[keyboard_mode][keyboard_cursor_y][keyboard_cursor_x]);
    if (keymap_key->key != KEY_SL) break;
    keyboard_cursor_x++;
    if (keyboard_cursor_x > KEYBOARD_WIDTH - 1) keyboard_cursor_x = 0;
  }
  while (1) {
    keymap_key =
      &(keyboard[keyboard_mode][keyboard_cursor_y][keyboard_cursor_x]);
    if ((keymap_key->key != KEY_SL) && (keymap_key->key != 0)) break;
    keyboard_cursor_x++;
    if (keyboard_cursor_x > KEYBOARD_WIDTH - 1) keyboard_cursor_x = 0;
  }
  get_keymap();
  keyboard_cursor_x = keymap_x;
  keyboard_cursor_y = keymap_y;
  get_keymap();
  print_keycursor();
}

void mode_change()
{
  clear_keycursor();
  get_keymap();
  keyboard_mode++;
  if (keyboard_mode > KEYBOARD_MODE_NUM - 1)
    keyboard_mode = 0;
  make_keyboard();
}

static void get_keymap()
{
  keymap_x = keyboard_cursor_x;
  keymap_y = keyboard_cursor_y;

  while (1) {
    keymap_key = &(keyboard[keyboard_mode][keymap_y][keymap_x]);
    if ((keymap_key->key != 0) && (keymap_key->key != KEY_SL)) break;
    /* キーが存在しない場合は，すぐ左のキーが有効になる */
    keymap_x--; if (keymap_x < 0) keymap_x = KEYBOARD_WIDTH - 1;
    /* １周してしまった場合は，すぐ上のキーが有効になる */
    if (keymap_x == keyboard_cursor_x) {
      keymap_y--; if (keymap_y < 0) keymap_y = KEYBOARD_HEIGHT - 1;
      if (keymap_y == keyboard_cursor_y) {
	/* 全周してしまうことはいくらなんでもありえないだろう */
	error_exit("no keymap");
      }
    }
  }
}

void clear_keycursor()
{
  int i, len;
  len = strlen(get_symbol());
  wonx_lcddraw_level_down();
  for (i = 0; i < len; i++) {
    font_normal(KEYBOARD_X + keymap_x + i, KEYBOARD_Y + keymap_y);
  }
  wonx_lcddraw_level_up();
}

void print_keycursor()
{
  char c;
  int i, len;
  char * string;

  string = get_string();
  len = strlen(string);
  wonx_lcddraw_level_down();
  for (i = 0; i < KEY_STRING_MAX_LENGTH; i++) {
    c = (i < KEY_STRING_MAX_LENGTH - len) ? '-' : string[i - KEY_STRING_MAX_LENGTH + len];
    if (c == 0x0a)
      c = 0x19;
    else if ((c < 0x20) || (c > 0x7e))
      c = ' ';
    text_put_char(i, KEYBOARD_Y - 1, c);
  }

  string = get_symbol();
  len = strlen(string);
  for (i = 0; i < len; i++) {
    font_reverse(KEYBOARD_X + keymap_x + i, KEYBOARD_Y + keymap_y);
  }
  wonx_lcddraw_level_up();
}

void make_keyboard()
{
  int key, i;
  char * string;
  char * p;
  int x, y;

  wonx_lcddraw_level_down();
  for (y = 0; y < KEYBOARD_HEIGHT; y++) {
    for (x = 0; x < KEYBOARD_WIDTH; x++) {
      keymap_key = &(keyboard[keyboard_mode][y][x]);
      key = keyboard_get_key();
      if (key == 0) {
	text_put_char(KEYBOARD_X + x, KEYBOARD_Y + y, ' ');
      } else if (key == KEY_SL) {
	/* NOP */
      } else {
	string = get_symbol();
	text_put_string(KEYBOARD_X + x, KEYBOARD_Y + y, string);
      }
    }
  }

  text_put_string(0, KEYBOARD_Y - 1, "----------------------------");

  for (i = 0; i < KEYINFO_HEIGHT; i++) {
    p = keyinfo[keyboard_mode][i];
    text_put_string(0, KEYBOARD_Y + KEYBOARD_HEIGHT + i, p);
  }
  wonx_lcddraw_level_up();

  get_keymap();
  print_keycursor();
}

int keyboard_get_key()
{
  return (keymap_key->key);
}

static char * get_symbol()
{
  static char buffer[2];
  char * symbol;
  int key;

  symbol = keymap_key->symbol;
  if (symbol == NULL) {
    key = keyboard_get_key();
    if (key <= 0) key = 'E';
    buffer[0] = key;
    buffer[1] = '\0';
    symbol = buffer;
  }
  return (symbol);
}

static char * get_string()
{
  int key;
  char * string;

  key = keyboard_get_key();
  if ((key <= KEY_F1) && (key >= KEY_F1 - FUNCTION_KEY_NUMBER + 1)) {
    return (get_function_key(KEY_F1 - key));
  }

  string = keymap_key->string;
  if (string == NULL) {
    string = get_symbol();
  }
  return (string);
}

void keyboard_change_string(char * string)
{
  keymap_key->string = string;
}

int keyboard_get_y1234map(int y)
{
  return (y1234map[keyboard_mode][y]);
}

void init_function_key()
{
  int i;
  for (i = 0; i < FUNCTION_KEY_NUMBER; i++) {
    function_key[i] = default_function_key[i];
  }
}

char * get_function_key(int n)
{
  return (function_key[n]);
}

/* End of Program  */
