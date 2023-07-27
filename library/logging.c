#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "logging.h"
#include "error_codes.h"
#include "reservation.h"

#define MESSAGE_LEN 1040

extern int write_log(char *message)
{
  FILE *log_file = fopen("account_data/log","a");
  if(log_file == NULL)
  {
    fprintf(stderr, "unable to open the log file.\n");
    return CANT_OPEN_FILE;
  }
  
  time_t now; time(&now);
  struct tm *local_time = localtime(&now);
  char date[10];
  int day = local_time->tm_mday;
  int month = local_time->tm_mon + 1;
  int year = local_time->tm_year + 1900;
  sprintf(date, "%d/%d/%d", day, month, year);
  char final_message[MESSAGE_LEN];
  strcpy(final_message, date);
  strcat(final_message, ",");
  strcat(final_message, message);
  
  fprintf(log_file, "%s\n", final_message);
  fclose(log_file);
  
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
  while(fgets(buffer, MESSAGE_LEN, log_file) != NULL)
  {
    printf("%s", buffer);
  }
  
  fclose(log_file);
  return OK;
}

extern int log_new_reservation(reservation_t reservation)
{
  FILE *reservation_log_file = fopen("account_data/reservation_log", "a");
  if(reservation_log_file == NULL)
  {
    fprintf(stderr, "unable to open reservation log file.\n");
    return CANT_OPEN_FILE;
  }
  
  /* DODAJ DATUM U LOG */
  
  // ako pravi dva newline, onda obrisi newline iz formata ispod
  fprintf(reservation_log_file, "name,%s,current fund,%d,goal,%\nd", reservation.name, reservation.current_fund, reservation.goal);
  fclose(reservation_log_file);

  return OK;
}

extern int print_reservation_logs()
{
  return OK;
}