#include <sys/key.h>

#include "termlib.h"
#include "com.h"
#include "types.h"
#include "lib.h"
#include "keyboard.h"
#include "keymap.h"
#include "screen.h"
#include "escape.h"

int key_X1234_action(int key)
{
  clear_keycursol();

  if (key & KEY_X1) keyboard_cursol_y--;
  if (key & KEY_X2) keyboard_cursol_x++;
  if (key & KEY_X3) keyboard_cursol_y++;
  if (key & KEY_X4) keyboard_cursol_x--;
  keyboard_cursol_x =
    (keyboard_cursol_x + KEYBOARD_WIDTH ) % KEYBOARD_WIDTH;
  keyboard_cursol_y =
    (keyboard_cursol_y + KEYBOARD_HEIGHT) % KEYBOARD_HEIGHT;
  
  print_keycursol();

  return (0);
}

int key_Y1234_action(int key)
{
  if (key & KEY_Y1) { /* Up */
    if (com_is_connected) {
      comm_send_char(ESCAPE_CODE);
      comm_send_char(cursol_send_mode ? 'O' : '[');
      comm_send_char('A');
    } else {
      cursol_up(1);
      refresh();
    }
  }
  if (key & KEY_Y3) { /* Down */
    if (com_is_connected) {
      comm_send_char(ESCAPE_CODE);
      comm_send_char(cursol_send_mode ? 'O' : '[');
      comm_send_char('B');
    } else {
      cursol_down(1);
      refresh();
    }
  }
  if (key & KEY_Y2) { /* Right */
    if (com_is_connected) {
      comm_send_char(ESCAPE_CODE);
      comm_send_char(cursol_send_mode ? 'O' : '[');
      comm_send_char('C');
    } else {
      cursol_right(1);
      refresh();
    }
  }
  if (key & KEY_Y4) { /* Left */
    if (com_is_connected) {
      comm_send_char(ESCAPE_CODE);
      comm_send_char(cursol_send_mode ? 'O' : '[');
      comm_send_char('D');
    } else {
      cursol_left(1);
      refresh();
    }
  }
  return (0);
}

int key_A_action(int key)
{
  int ch;
  int com_speed;

  ch = keyboard_get_key();
  switch (ch) {
  case KEY_COM_CONNECT:
    com_is_connected = !com_is_connected;
    keyboard_change_string(com_is_connected ? "Disconnect" : "Connect");
    print_com_connect();
    print_keycursol();
    ch = '\0';
    break;
  case KEY_COM_SPEED:
    com_speed = comm_get_baudrate();
    if      (com_speed == COMM_SPEED_9600 ) com_speed = COMM_SPEED_38400;
    else if (com_speed == COMM_SPEED_38400) com_speed = COMM_SPEED_9600;
    keyboard_change_string((com_speed == COMM_SPEED_9600)
			   ? "38400bps" : "9600bps");
    print_com_speed(com_speed);
    print_keycursol();
    ch = '\0';
    break;
  case KEY_CLEAR_SCREEN:
    cursol_x = 0;
    cursol_y = 0;
    screen_clear();
    refresh();
    ch = '\0';
    break;
  }
  return (ch);
}

int key_B_action(int key)
{
  return (NEWLINE_CODE);
}

int key_START_action(int key)
{
  return (-1);
}

/* End of Program  */
