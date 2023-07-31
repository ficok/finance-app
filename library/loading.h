#ifndef LOADING_H
#define LOADING_H

extern int load_data(void);
extern int load_reservations(reservation_t *reservation_list);
extern int reload_reservations_file(reservation_t *reservation_list, char*, int*);

#endif