#ifndef _WWTERM_ESCLIB_H_
#define _WWTERM_ESCLIB_H_

char make_args();
void parse_dec_escseq(char command1, int command2);
void escape_send_stat(char command);
void escape_screen_clear(char command);
void escape_line_clear(char command);
void escape_ins_del(char command, int parameter);

#endif /* _WWTERM_ESCLIB_H_ */

/* End of Program  */
