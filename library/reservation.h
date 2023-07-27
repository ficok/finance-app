#ifndef RESERVATION_H
#define RESERVATION_H

typedef struct
{
  char name[100];
  int goal;
  int current_fund;
} reservation_t;

extern int log_reserve(reservation_t reservation);
extern int reserve();

extern int new_reservation();
extern int update_reservation();
extern int check_reservation();

#endif