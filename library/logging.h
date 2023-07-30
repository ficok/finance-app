#ifndef LOGGING_H
#define LOGGING_H

#include "reservation.h"

extern int write_log(char *message);
extern int print_log(void);

extern int log_new_reservation(reservation_t *reservation);
extern int log_reservation(reservation_t *reservation, int type);
extern int log_reservation_helper(reservation_t*, char*);
extern int print_reservation_log();

#endif