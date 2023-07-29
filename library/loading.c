#include <stdio.h>
#include <stdlib.h>

#include "app.h"
#include "loading.h"
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
