#ifndef _WWTERM_LIB_H_
#define _WWTERM_LIB_H_

/* isdigit() と同じ */
int is_digit(char c);
/* isupper() と同じ */
int is_upper(char c);
/* islower() と同じ */
int is_lower(char c);
/* isalpha() と同じ */
int is_alpha(char c);

/* atoi() と同じようなことをする関数 */
int asc2int(char * s);

/* sprintf(buffer, "%d", x); と同じようなことをする関数 */
void int2asc(int d, char * buffer);

/* 文字列中から文字を探して，位置を返す */
char * search_char(char c, char * s);

#endif /* _WWTERM_LIB_H_ */

/* End of Program  */
