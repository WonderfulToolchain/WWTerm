#include "com.h"
#include "screen.h"

/* 受信バッファ */
char com_receive_buffer[BUFFER_SIZE] = FIRST_STRING;
int com_receive_start = 0;
int com_receive_end   = sizeof(FIRST_STRING) - 1;

/* 接続状態 0.非接続 1.接続 */
int com_is_connected = 0;

/* 停止状態 0.通信中 1.停止中 */
int com_is_paused = 0;

void com_pause()
{
  com_is_paused++;
  if (com_is_connected && (com_is_paused == 1)) comm_send_char(XOFF);
}

void com_unpause()
{
  com_is_paused--;
  if (com_is_connected && (com_is_paused == 0)) comm_send_char(XON);
}

void com_flush()
{
  if (com_receive_start == com_receive_end) return;

#ifdef COM_PAUSE_IN_PRINTING
  com_pause();
#endif
  while (com_receive_start != com_receive_end) {
    print_character(com_receive_buffer[com_receive_start]);
    com_receive_start = (com_receive_start + 1) % BUFFER_SIZE;
  }
#ifdef COM_PAUSE_IN_PRINTING
  com_unpause();
#endif
}

void com_receive()
{
  int c;
  int e;

  c = comm_receive_char();

  if (!com_is_connected) { return; }

  if (c == ERR_SIO_TIMEOUT) { return; }
  if (c == ERR_SIO_CANCEL ) { return; }
  if (c == ERR_SIO_OVERRUN) { return; }

  e = (com_receive_end + 1) % BUFFER_SIZE;

  if (com_receive_start == e) {
#ifdef FLUSH_IN_BUFFER_OVER
    com_flush(); /* バッファがいっぱいのときはフラッシュする */
    e = (com_receive_end + 1) % BUFFER_SIZE;
#else
    return; /* バッファがいっぱいのときは廃棄 */
#endif
  }

  com_receive_buffer[com_receive_end] = c;
  com_receive_end = e;
}

/* End of Program  */
