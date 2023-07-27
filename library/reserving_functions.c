#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"
#include "reservation.h"
#include "app.h"
#include "error_codes.h"
#include "logging.h"

extern int new_reservation()
{
  reservation_t *reservation = malloc(sizeof(reservation_t));
  
  printf("what is the name of your reservation: ");
  char name_buffer[100];
  flush_input_buffer();
  fgets(name_buffer, 100, stdin);
  shave_newline(name_buffer);
  strcpy(reservation->name, name_buffer);
  
  printf("what is the fund goal of %s: ", reservation->name);
  int goal;
  scanf("%d", &goal);
  reservation->goal = goal;
  
  printf("initialise the funding (enter 0 if no funding): ");
  int current_fund;
  scanf("%d", &current_fund);
  reservation->current_fund = current_fund;
  
  log_new_reservation(reservation);
  
  free(reservation);
  
  return OK;
}

extern int check_reservation()
{
  return OK;
}

extern int update_reservation()
{
  return OK;
}