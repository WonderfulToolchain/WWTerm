#include <sys/key.h>
#include "types.h"
#include "lib.h"

/* isdigit() と同じ */
int is_digit(char c) { return (('0' <= c) && (c <= '9')); }
/* isupper() と同じ */
int is_upper(char c) { return (('A' <= c) && (c <= 'Z')); }
/* islower() と同じ */
int is_lower(char c) { return (('a' <= c) && (c <= 'z')); }
/* isalpha() と同じ */
int is_alpha(char c) { return (is_upper(c) || is_lower(c)); }

/* atoi() と同じようなことをする関数 */
int asc2int(char * s)
{
  int value = -1;
  while (is_digit(*s)) {
    if (value < 0) value = 0;
    value *= 10;
    value += (*s - '0'); /* カッコを外さないように注意! */
    s++;
  }
  return (value);
}

/* sprintf(buffer, "%d", x); と同じようなことをする関数 */
void int2asc(int d, char * buffer)
{
  int dd = 1;

  while (dd <= d) dd *= 10;
  dd /= 10;
  while (dd > 0) {
    *buffer = (d / dd) + '0';
    d = d % dd;
    dd /= 10;
    buffer++;
  }
  *buffer = '\0';
}

/* 文字列中から文字を探して，位置を返す */
char * search_char(char c, char * s)
{
  while (*s != c) {
    s++;
  }
  return (s);
}

/* エラーメッセージを表示して終了 */
void error_exit(char * message)
{
  int key;
  text_put_string(0, KEYBOARD_Y - 1, message);

  while (1) {
    key = key_press_check();
    if (key & KEY_START) break;
  }

  bios_exit();
}

/* End of Program  */
