#include <sys/key.h>

#include "termlib.h"
#include "com.h"
#include "types.h"
#include "lib.h"
#include "keyboard.h"
#include "keymap.h"
#include "screen.h"
#include "escape.h"
#include "esclib.h"
#include "log.h"

void push_function_key(int ch)
{
  char * s;
  s = get_function_key(KEY_F1 - ch);
  if (com_is_connected) {
    com_puts(s);
  } else {
    print_string(s);
  }
}

int key_X1234_action(int key)
{
  wonx_lcddraw_level_down();
  if (key & KEY_X1) keycursor_up();
  if (key & KEY_X2) keycursor_right();
  if (key & KEY_X3) keycursor_down();
  if (key & KEY_X4) keycursor_left();
  wonx_lcddraw_level_up();
  return (0);
}

static void com_put_escseq(char c) {
  com_putc(ESCAPE_CODE);
  com_putc(cursor_send_mode ? 'O' : '[');
  com_putc(c);
}

static int special_key_action(int ch)
{
  int com_speed;
  char * p;

  switch (ch) {
  case KEY_COM_CONNECT:
    com_is_connected = !com_is_connected;
    keyboard_change_string(com_is_connected ? "Disconnect" : "Connect");
    print_com_connect();
    break;
  case KEY_COM_SPEED:
    com_speed = (comm_get_baudrate() == COMM_SPEED_9600)
      ? COMM_SPEED_38400 : COMM_SPEED_9600;
    keyboard_change_string((com_speed == COMM_SPEED_9600)
			   ? "38400bps" : "9600bps");
    print_com_speed(com_speed);
    break;
  case KEY_CLEAN_SCREEN:
    cursor_set(0, 0);
    screen_clear();
    refresh();
    break;
  case KEY_CHANGE_MODE:
    /* None */
    break;
  case KEY_LOG_SWITCH:
    p = log_switch();
    keyboard_change_string(p);
    print_log_on();
    break;
  case KEY_SEND_RESIZE:
    send_resize();
    refresh();
    break;
  case KEY_CURSOR_UP: /* Up */
    if (com_is_connected) com_put_escseq('A');
    else cursor_up(1);
    break;
  case KEY_CURSOR_RIGHT: /* Right */
    if (com_is_connected) com_put_escseq('C');
    else cursor_right(1);
    break;
  case KEY_CURSOR_DOWN: /* Down */
    if (com_is_connected) com_put_escseq('B');
    else cursor_down(1);
    break;
  case KEY_CURSOR_LEFT: /* Left */
    if (com_is_connected) com_put_escseq('D');
    else cursor_left(1);
    break;
  case KEY_SCREEN_UP:
  case KEY_SCREEN_RIGHT:
  case KEY_SCREEN_DOWN:
  case KEY_SCREEN_LEFT:
    /* None */
    break;
  case KEY_F1:
  case KEY_F2:
  case KEY_F3:
  case KEY_F4:
  case KEY_F5:
  case KEY_F6:
  case KEY_F7:
  case KEY_F8:
  case KEY_F9:
  case KEY_F10:
    push_function_key(ch);
    break;
  default:
    return (ch);
  }

  print_keycursor();
  return (0);
}

int key_Y1234_action(int key)
{
  int ch = 0;

  if (key & KEY_Y1) { ch = keyboard_get_y1234map(0); } /* Up    */
  if (key & KEY_Y2) { ch = keyboard_get_y1234map(1); } /* Right */
  if (key & KEY_Y3) { ch = keyboard_get_y1234map(2); } /* Down  */
  if (key & KEY_Y4) { ch = keyboard_get_y1234map(3); } /* Left  */

  return (special_key_action(ch));
}

int key_A_action(int key)
{
  int ch;

  ch = keyboard_get_key();
  return (special_key_action(ch));
}

int key_B_action(int key)
{
  mode_change();
  return (0);
}

int key_START_action(int key)
{
  return (-1);
}

/* End of Program  */
