#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

/* ログの ON/OFF */
static int log_flag = 0;

int is_log_on() { return (log_flag); }

static FILE far * fp;

char * log_switch()
{
  static char buffer[sizeof(LOG_FILE) + 15];
  static int file_number = 0;

  if (log_flag) { /* ログの取得中 */
    fclose(fp);
    strcpy(buffer, "logfile open");
  } else {
    while (1) { /* ファイルが存在する場合はスキップする */
      sprintf(buffer, LOG_FILE, file_number);
      fp = fopen(buffer, FOPEN_FOR_RB);
      if (fp == NULL) break;
      fclose(fp);
      file_number++;
    }
    fp = fopen(buffer, FOPEN_FOR_WB);
    strcat(buffer, " close");
  }
  log_flag = !log_flag;
  return (buffer);
}

void log_close()
{
  if (log_flag) {
    fflush(fp);
    fclose(fp);
  }
}

void log_putc(int c)
{
  if (!log_flag) return;
  if ((c >= 0) && (c <= 255)) {
    fputc(c, fp);
    fflush(fp);
  }
  return;
}

void log_puts(char * s)
{
  if (!log_flag) return;
  for (; *s != '\0'; s++)
    log_putc(*s);
  return;
}

void log_putb(void * p, int len)
{
  char * s;
  if (!log_flag) return;
  for (s = p; len > 0; len--,s++)
    log_putc(*s);
  return;
}

/* End of Program  */
