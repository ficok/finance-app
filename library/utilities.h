#ifndef UTILITIES_H
#define UTILITIES_H

#include "reservation.h"

#define MESSAGE_LEN 1040

typedef struct
{
  int left;
  int right;
  int found_flag;
} interval_t;

extern char DIVIDER[];
extern char *create_current_date(void);
extern void flush_input_buffer(void);
extern void shave_newline(char *line);

extern int update_available(int);
extern int update_reserved(int);
extern int update_number_of_reservations(void);

extern interval_t search_for_reservation(reservation_t *reservation_list, char *input);
extern int rename_reservation(reservation_t*);
extern int update_funding(reservation_t*);
extern void print_reservation(reservation_t);

extern void binary_search_ret_interval(reservation_t*, char*, int*, int*);
extern int lower_bound(reservation_t*, char*);
extern int upper_bound(reservation_t*, char*);
extern int sort_reservations_file(reservation_t*);
extern int sort_reservations_file_with_loading(void);
extern int quick_sort_reservation_list(reservation_t*, int, int);

extern int swap_reservations(reservation_t*, reservation_t*);
extern int partition(reservation_t *reservation_list, int left, int right);

#endif