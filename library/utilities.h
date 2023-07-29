#ifndef UTILITIES_H
#define UTILITIES_H

#include "reservation.h"

#define MESSAGE_LEN 1040

extern char DIVIDER[];
extern char *create_current_date(void);
extern void flush_input_buffer(void);
extern void shave_newline(char *line);

extern int search_for_reservation(char *input);
extern void print_reservation(reservation_t);

extern void binary_search_ret_interval(reservation_t*, char*, int*, int*);
extern int binary_search_ret_left(reservation_t*, char*);
extern int binary_search_ret_right(reservation_t*, char*);
extern int sort_reservation_search_list_file(void);

#endif