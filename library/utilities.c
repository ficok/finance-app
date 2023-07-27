#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utilities.h"

char DIVIDER[] = "-------------------\n\n";

char *create_current_date(void)
{
  time_t now; time(&now);
  struct tm *local_time = localtime(&now);
  char *date = malloc(10*sizeof(char));
  int day = local_time->tm_mday;
  int month = local_time->tm_mon + 1;
  int year = local_time->tm_year + 1900;
  sprintf(date, "%d/%d/%d", day, month, year);
  /**
   * DON'T FORGET TO FREE DATE AFTER USE
  */
  return date;
}