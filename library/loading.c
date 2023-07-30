#include <stdio.h>
#include <stdlib.h>

#include "app.h"
#include "utilities.h"
#include "loading.h"
#include "reservation.h"
#include "error_codes.h"

extern int load_data()
{
  /** loading available funds */
  FILE *available_file = fopen("account_data/available", "r");
  if(available_file == NULL)
  {
    fprintf(stderr, "unable to open available file.\n");
    return CANT_OPEN_FILE;
  }
  fscanf(available_file, "%d", &available);
  
  fclose(available_file);
  
  /** loading reserved funds */
  
  FILE *reserved_file = fopen("account_data/reserved", "r");
  if(reserved_file == NULL)
  {
    fprintf(stderr, "unable to open reserved file.\n");
    return CANT_OPEN_FILE;
  }
  
  fscanf(reserved_file, "%d", &reserved);
  
  fclose(reserved_file);
  
  /** loading number of reservations */
  FILE *number_of_reservations_file = fopen("account_data/number_of_reservations","r");
  if(number_of_reservations_file == NULL)
  {
    fprintf(stderr, "unable to open number of reservations file.\n");
    return CANT_OPEN_FILE;
  }
  fscanf(number_of_reservations_file, "%d", num_of_reservations);
  
  return OK;
}

int load_reservations(reservation_t *reservation_list)
{
  FILE *reservations_file = fopen("account_data/reservations","r");
  if(reservations_file == NULL)
  {
    fprintf(stderr, "unable to open reservations file.\n");
  }
  
  int iterator = 0;
  char *buffer[MESSAGE_LEN];
  while(fgets(buffer, MESSAGE_LEN, reservations_file) != NULL)
  {
    char *token = NULL;
    token = strtok(buffer, ",");
    reservation_list[iterator].id = atoi(token);
    
    token = strtok(NULL, ",");
    shave_newline(token);

    strcpy(reservation_list[iterator].name, token);
    
    token = strtok(NULL, ",");
    reservation_list[iterator].goal = atoi(token);
    
    token = strtok(NULL, ",");
    reservation_list[iterator].current_fund = atoi(token);

    iterator++;
  }
  if (!feof(reservations_file))
  {
    fprintf(stderr, "unable to read reservation search list file.\n");
  }
  fclose(reservations_file);
  
  return OK;
}

int reload_reservations_file(reservation_t *reservation_list)
{
  sort_reservations_file(reservation_list);
  load_data();
}