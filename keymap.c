#include "keymap.h"

/* キーボードのマッピング */
keymap keyboard[KEYBOARD_MODE_NUM][KEYBOARD_HEIGHT][KEYBOARD_WIDTH] = {
  {
    {{'a',0,0},{'b',0,0},{'c',0,0},{'d',0,0},{'e',0,0},{'f',0,0},{'g',0,0},{0},
     {'h',0,0},{'i',0,0},{'j',0,0},{'k',0,0},{'l',0,0},{'m',0,0},{'n',0,0},{0},
     {'0',0,0},{'1',0,0},{'2',0,0},{'3',0,0},{'4',0,0},{0},
     {',',0,0},{'.',0,0},{'+',0,0},{'-',0,0},{'<',0,0},{'>',0,0}},
    {{'o',0,0},{'p',0,0},{'q',0,0},{'r',0,0},{'s',0,0},{'t',0,0},{'u',0,0},{0},
     {'v',0,0},{'w',0,0},{'x',0,0},{'y',0,0},{'z',0,0},{'(',0,0},{')',0,0},{0},
     {'5',0,0},{'6',0,0},{'7',0,0},{'8',0,0},{'9',0,0},{0},
     {':',0,0},{';',0,0},{'*',0,0},{'/',0,0},{'=',0,0},{0}},
    {{' ' ,"Spc"  ,"Space"    }, {KEY_SL},{KEY_SL},{0},
     {0x0d,"Enter","Enter"    }, {KEY_SL},{KEY_SL},{KEY_SL},{KEY_SL},{0},
     {0x1b,"Esc"  ,"Escape"   }, {KEY_SL},{KEY_SL},{0},
     {0x08,"BS"   ,"BackSpace"}, {KEY_SL},{0},
     {0x7f,"Del"  ,"Delete"   }, {KEY_SL},{KEY_SL},{0},
     {0x09,"Tab"  ,"Tab"      }, {KEY_SL},{KEY_SL},{0},
     {0x0c,"Clr"  ,"Clear"    }, {KEY_SL},{KEY_SL}}
  },
  {
    {{'A',0,0},{'B',0,0},{'C',0,0},{'D',0,0},{'E',0,0},{'F',0,0},{'G',0,0},{0},
     {'H',0,0},{'I',0,0},{'J',0,0},{'K',0,0},{'L',0,0},{'M',0,0},{'N',0,0},{0},
     {'!',0,0},{'\"',0,0},{'#',0,0},{'$',0,0},{'%',0,0},{'&',0,0},{'\'',0,0},
     {'~',0,0},{'^',0,0},{0},
     {KEY_CURSOR_UP  ,"\x18","Cursor Up"},
     {KEY_CURSOR_DOWN,"\x19","Cursor Down"}},
    {{'O',0,0},{'P',0,0},{'Q',0,0},{'R',0,0},{'S',0,0},{'T',0,0},{'U',0,0},{0},
     {'V',0,0},{'W',0,0},{'X',0,0},{'Y',0,0},{'Z',0,0},{'{',0,0},{'}',0,0},{0},
     {'[',0,0},{']',0,0},{'|',0,0},{'\\',0,0},{'@',0,0},{'`',0,0},
     {'?',0,0},{'_',0,0},{0},{0},
     {KEY_CURSOR_LEFT,"\x1b","Cursor Left"},
     {KEY_CURSOR_RIGHT,"\x1a","Cursor Right"}},
    {{0x0a, "NL"  , "NewLine"}, {KEY_SL},{0},
     {0x07, "Bel" , "Bell"   }, {KEY_SL},{KEY_SL},{0},
     {KEY_F1,"F1",0},{KEY_SL},{KEY_F2,"F2",0},{KEY_SL},
     {KEY_F3,"F3",0},{KEY_SL},{KEY_F4,"F4",0},{KEY_SL},
     {KEY_F5,"F5",0},{KEY_SL},{KEY_F6,"F6",0},{KEY_SL},
     {KEY_F7,"F7",0},{KEY_SL},{KEY_F8,"F8",0},{KEY_SL},
     {KEY_F9,"F9",0},{KEY_SL},{KEY_F10,"F10",0},{KEY_SL},{KEY_SL}}
  },
  {
    {{0x01,"cA","Ctrl-A"},{KEY_SL}, {0x02,"cB","Ctrl-B"},{KEY_SL},
     {0x03,"cC","Ctrl-C"},{KEY_SL}, {0x04,"cD","Ctrl-D"},{KEY_SL},
     {0x05,"cE","Ctrl-E"},{KEY_SL}, {0x06,"cF","Ctrl-F"},{KEY_SL},
     {0x07,"cG","Ctrl-G"},{KEY_SL}, {0x08,"cH","Ctrl-H"},{KEY_SL},
     {0x09,"cI","Ctrl-I"},{KEY_SL}, {0x0a,"cJ","Ctrl-J"},{KEY_SL},
     {0x0b,"cK","Ctrl-K"},{KEY_SL}, {0x0c,"cL","Ctrl-L"},{KEY_SL},
     {0x0d,"cM","Ctrl-M"},{KEY_SL}, {0x0e,"cN","Ctrl-N"},{KEY_SL}},
    {{0x0f,"cO","Ctrl-O"},{KEY_SL}, {0x10,"cP","Ctrl-P"},{KEY_SL},
     {0x11,"cQ","Ctrl-Q"},{KEY_SL}, {0x12,"cR","Ctrl-R"},{KEY_SL},
     {0x13,"cS","Ctrl-S"},{KEY_SL}, {0x14,"cT","Ctrl-T"},{KEY_SL},
     {0x15,"cU","Ctrl-U"},{KEY_SL}, {0x16,"cV","Ctrl-V"},{KEY_SL},
     {0x17,"cW","Ctrl-W"},{KEY_SL}, {0x18,"cX","Ctrl-X"},{KEY_SL},
     {0x19,"cY","Ctrl-Y"},{KEY_SL}, {0x1a,"cZ","Ctrl-Z"},{KEY_SL},
     {0},{0},{0},{0}},
    {{KEY_COM_CONNECT, "Connect", "Serial Connect ON/OFF"},
     {KEY_SL},{KEY_SL},{KEY_SL},{KEY_SL},{KEY_SL},{KEY_SL},{0},
     {KEY_COM_SPEED  , "Speed"  , "Serial Speed 9600/38400"},
     {KEY_SL},{KEY_SL},{KEY_SL},{KEY_SL},{0},
     {KEY_CLEAN_SCREEN, "Clean"  , "Clean Screen"},
     {KEY_SL},{KEY_SL},{KEY_SL},{KEY_SL},{0},
     {KEY_CHANGE_MODE, "Mode", "Change Screen Mode"},
     {KEY_SL},{KEY_SL},{KEY_SL},{0},
     {KEY_LOG_SWITCH, "Log", "Log ON/OFF"},{KEY_SL},{KEY_SL}}
  }
};

char * keyinfo[KEYBOARD_MODE_NUM][KEYINFO_HEIGHT] = {
  {"X1234)Select A)Input B)Shift",
   "Y1234)Cursor START)Quit"},
  {"X1234)Select A)Input B)Shift",
   "Y1234)Screen START)Quit"},
  {"X1234)Select A)Input B)Shift",
   "Y1234)Fn1234 START)Quit"}
};

int y1234map[KEYBOARD_MODE_NUM][4] = {
  { KEY_CURSOR_UP, KEY_CURSOR_RIGHT, KEY_CURSOR_DOWN, KEY_CURSOR_LEFT },
  { KEY_SCREEN_UP, KEY_SCREEN_RIGHT, KEY_SCREEN_DOWN, KEY_SCREEN_LEFT },
  { KEY_F1, KEY_F2, KEY_F3, KEY_F4 }
};

char * default_function_key[FUNCTION_KEY_NUMBER] = {
  "ls \0\0\0\0\0\0\0\0\0\0\0\0\0", /* F1 */
  "cd \0\0\0\0\0\0\0\0\0\0\0\0\0", /* F2 */
  "cat \0\0\0\0\0\0\0\0\0\0\0\0", /* F3 */
  "eval `resize`\n\0\0", /* F4 */
  "pwd\n\0\0\0\0\0\0\0\0\0\0\0\0", /* F5 */
  "more \0\0\0\0\0\0\0\0\0\0\0", /* F6 */
  "less \0\0\0\0\0\0\0\0\0\0\0", /* F7 */
  "vi \0\0\0\0\0\0\0\0\0\0\0\0\0", /* F8 */
  "emacs \0\0\0\0\0\0\0\0\0\0", /* F9 */
  "mnews -m\n\0\0\0\0\0\0\0", /* F10 */
};

/* End of Program  */
