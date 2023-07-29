#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utilities.h"
#include "logging.h"
#include "error_codes.h"
#include "utility_codes.h"
#include "reservation.h"



extern int write_log(char *message)
{
  FILE *log_file = fopen("account_data/log","a");
  if(log_file == NULL)
  {
    fprintf(stderr, "unable to open the log file.\n");
    return CANT_OPEN_FILE;
  }
  
  char *date = create_current_date();
  char final_message[MESSAGE_LEN];
  strcpy(final_message, date);
  strcat(final_message, ",");
  strcat(final_message, message);
  
  fprintf(log_file, "%s\n", final_message);
  fclose(log_file);
  /**
   * date VARIABLE WAS MALLOC-ED IN THE create_current_date FUNCTION, BUT WASN'T FREED THERE
   * YOU MUST FREE IT HERE
  */
  free(date);
  
  return OK;
}

extern int print_log(void)
{
  FILE *log_file = fopen("account_data/log", "r");
  if(log_file == NULL)
  {
    fprintf(stderr, "unable to open the log file.\n");
    return CANT_OPEN_FILE;
  }
  
  char buffer[MESSAGE_LEN];
  printf("transaction log file:\n~~~~~~~~~~~~~~~~~~~~~\n");
  while(fgets(buffer, MESSAGE_LEN, log_file) != NULL)
  {
    printf("%s", buffer);
  }
  
  fclose(log_file);
  return OK;
}

extern int log_reservation(reservation_t *reservation, int type)
{
  if(type == NEW_RESERVATION)
  { /** new reservation log */
    log_reservation_helper(reservation, "new reservation");

    FILE *reservations_file = fopen("account_data/reservations", "a");
    if(reservations_file == NULL)
    {
      fprintf(stderr, "unable to open reservation names file.\n");
      return CANT_OPEN_FILE;
    }
    
    char message[MESSAGE_LEN];
    sprintf(message, "%d,%s,%d,%d\n", reservation->id, reservation->name, reservation->current_fund, reservation->goal);
    
    fclose(reservations_file);
  }
  else if(type == UPDATE_RESERVATION)
  { /** reservation update log */
    
  }
  else /** type == DELETE_RESERVATION */
  { /** reservation deletion log */

  }

  return OK;
}

extern int print_reservation_log()
{
  FILE *reservation_log_file = fopen("account_data/reservation_log", "r");
  if(reservation_log_file == NULL)
  {
    fprintf(stderr, "unable to open reservation log file.\n");
    return CANT_OPEN_FILE;
  }
  
  char buffer[MESSAGE_LEN];
  printf("reservation log file:\n~~~~~~~~~~~~~~~~~~~~~\n");
  while(fgets(buffer, MESSAGE_LEN, reservation_log_file) != NULL)
  {
    printf("%s", buffer);
  }
  if (!feof(reservation_log_file))
  {
    fclose(reservation_log_file);
    return CANT_READ_FILE;
  }
  
  fclose(reservation_log_file);
  
  return OK;
}

int log_reservation_helper(reservation_t *reservation, char *type)
{
  FILE *reservation_log_file = fopen("account_data/reservation_log", "a");
  if(reservation_log_file == NULL)
  {
    fprintf(stderr, "unable to open reservation log file.\n");
    return CANT_OPEN_FILE;
  }
  
  char *date = create_current_date();
  char final_message[MESSAGE_LEN];
  char message[1024];
    
  sprintf(message, "%d,%s,%d,%d,%s\n", reservation->id, reservation->name, reservation->current_fund, reservation->goal, type);
    
  strcpy(final_message, date);
  strcat(final_message, ",");
  strcat(final_message, message);
    
  fprintf(reservation_log_file, "%s", final_message);

  fclose(reservation_log_file);
  
  return OK;
}