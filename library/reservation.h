#ifndef RESERVATION_H
#define RESERVATION_H

typedef struct
{
  int id;
  char name[100];
  int goal;
  int current_fund;
} reservation_t;

extern int reserve();

extern int new_reservation();
extern int update_reservation();
extern int check_reservation();

#endif