#include "keymap.h"

/* キーボードのマッピング */
keymap keyboard[KEYBOARD_HEIGHT][KEYBOARD_WIDTH] = {
  {{0x61,0,0},{0x62,0,0},{0x63,0,0},{0x64,0,0},{0x65,0,0},
   {0x66,0,0},{0x67,0,0}, {0x20,0,"SPACE"},
   {0x41,0,0},{0x42,0,0},{0x43,0,0},{0x44,0,0},{0x45,0,0},
   {0x46,0,0},{0x47,0,0}, {0x20,0,"SPACE"},
   {0x37,0,0},{0x38,0,0},{0x39,0,0},{0x2b,0,0},{0x2d,0,0}, {0x20,0,"SPACE"},
   {0x20,0,"SPACE"},{0x21,0,0},{0x22,0,0},{0x23,0,0},{0x24,0,0}},
  {{0x68,0,0},{0x69,0,0},{0x6a,0,0},{0x6b,0,0},{0x6c,0,0},
   {0x6d,0,0},{0x6e,0,0}, {0x20,0,"SPACE"},
   {0x48,0,0},{0x49,0,0},{0x4a,0,0},{0x4b,0,0},{0x4c,0,0},
   {0x4d,0,0},{0x4e,0,0}, {0x20,0,"SPACE"},
   {0x34,0,0},{0x35,0,0},{0x36,0,0},{0x2a,0,0},{0x2f,0,0}, {0x20,0,"SPACE"},
   {0x25,0,0},{0x26,0,0},{0x27,0,0},{0x40,0,0},{0x5e,0,0}},
  {{0x6f,0,0},{0x70,0,0},{0x71,0,0},{0x72,0,0},{0x73,0,0},
   {0x74,0,0},{0x75,0,0}, {0x20,0,"SPACE"},
   {0x4f,0,0},{0x50,0,0},{0x51,0,0},{0x52,0,0},{0x53,0,0},
   {0x54,0,0},{0x55,0,0}, {0x20,0,"SPACE"},
   {0x31,0,0},{0x32,0,0},{0x33,0,0},{0x3c,0,0},{0x3e,0,0}, {0x20,0,"SPACE"},
   {0x5b,0,0},{0x5d,0,0},{0x5c,0,0},{0x5f,0,0},{0x60,0,0}},
  {{0x76,0,0},{0x77,0,0},{0x78,0,0},{0x79,0,0},{0x7a,0,0},
   {0x28,0,0},{0x29,0,0}, {0x20,0,"SPACE"},
   {0x56,0,0},{0x57,0,0},{0x58,0,0},{0x59,0,0},{0x5a,0,0},
   {0x3a,0,0},{0x3b,0,0}, {0x20,0,"SPACE"},
   {0x30,0,0},{0x2c,0,0},{0x2e,0,0},{0x3d,0,0},{0x3f,0,0}, {0x20,0,"SPACE"},
   {0x7b,0,0},{0x7d,0,0},{0x7c,0,0},{0x7e,0,0},{0x7f,0,0}},
  /* 以下は特殊文字用 */
  {{KEY_COM_CONNECT,  'C', "COMCnct/NC"}, /* シリアル接続/非接続 */
   {KEY_COM_SPEED,    'S', "COMSpeed"  }, /* シリアル速度変更    */
   {KEY_CLEAR_SCREEN, 'L', "ClearSCRN" }, /* スクリーンクリア    */
   {0, ' ', "-"},
   {0x1b, 'E', "Escape"   }, {0x0a, 'N', "NewLine"}, {0x0d, 'R', "Return"},
   {0x08, 'B', "BackSPACE"}, {0x7f, 'D', "Delete" }, {0x0c, 'C', "Clear" },
   {0x09, 'T', "TAB"      }, {0x07, 'A', "Bell"   }, {0x0b, 'V', "VTAB"  },
   {0, ' ', "-"},
   {0, '-', 0}, {0, '-', 0}, {0, '-', 0}, {0, '-', 0},
   {0, '-', 0}, {0, '-', 0}, {0, '-', 0}, {0, '-', 0}, {0, '-', 0},
   {0, '-', 0}, {0, '-', 0}, {0, '-', 0}, {0, '-', 0}}
};

/* End of Program  */
