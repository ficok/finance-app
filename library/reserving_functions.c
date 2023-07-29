#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"
#include "reservation.h"
#include "app.h"
#include "error_codes.h"
#include "utility_codes.h"
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
  
  num_of_reservations++;
  reservation->id = num_of_reservations;
  
  log_reservation(reservation, NEW_RESERVATION);
  
  reserved += goal;
  
  FILE *number_of_reservations_file = fopen("account_data/number_of_reservations","w");
  if(number_of_reservations_file == NULL)
  {
    fprintf(stderr, "unable to open number of reservations file.\n");
    return CANT_OPEN_FILE;
  }
  
  fprintf(number_of_reservations_file, "%d", reserved);
  
  fclose(number_of_reservations_file);
  
  sort_reservations_file();
  
  free(reservation);
  
  return OK;
}

extern int check_reservation()
{
  printf("enter name or keyword: ");
  char name[MESSAGE_LEN];
  flush_input_buffer();
  fgets(name, MESSAGE_LEN, stdin);
  flush_input_buffer();
  
  search_for_reservation(name);

  return OK;
}

extern int update_reservation()
{
  /** when logging, log only */
  return OK;
}