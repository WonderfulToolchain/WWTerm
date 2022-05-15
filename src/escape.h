#ifndef _WWTERM_ESCAPE_H_
#define _WWTERM_ESCAPE_H_

/* エスケープシーケンスの処理用バッファ */
extern int escseq_length;
extern char escseq_buffer[];

extern int cursor_send_mode;

/* 引数 */
extern int escape_args[];

/* エスケープシーケンスの処理 */
void parse_escseq();

#endif /* _WWTERM_ESCAPE_H_ */

/* End of Program  */
