#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "app.h"
#include "utilities.h"
#include "error_codes.h"
#include "utility_codes.h"

/**
 * used for searching through the reservation search list file
*/
typedef struct
{
  int index;
  int id;
  char *name;
} reservation_triplet_t;

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

void flush_input_buffer(void)
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
  
  return;
}

void shave_newline(char *line)
{
  int line_len = strlen(line);
  if(line_len > 0 && line[line_len - 1] == '\n')
    line[line_len - 1] = '\0';

  return;
}

int search_for_reservation(char *target)
{
  /**
   * 1. load the reservations
   * 2. pass it to binary search along with the name/keyword
   * 3. it returns the ends of the interval that has the target name(s)
   * 4. print the information from the structure list
  */
  
  /** loading data from reservation search list file */
  FILE *reservations_file = fopen("account_data/reservations","r");
  if(reservations_file == NULL)
  {
    fprintf(stderr, "unable to open reservations file.\n");
  }
  
  reservation_t *reservation_list = malloc(num_of_reservations * sizeof(reservation_t));
  if(reservation_list == NULL)
  {
    fprintf(stderr, "unable to allocate memory for reservation triplet for searching.\n");
    free(reservation_list);
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
  /** loading done */
  
  /** binary search */
  int left_end, right_end;
  binary_search_ret_interval(reservation_list, target, &left_end, &right_end);
  /** binary search done; interval acquired */
  
  /** printing the interval */
  if(left_end == NOT_FOUND || right_end == NOT_FOUND)
  {
    printf("reservation with %s name or keyword not found.\n", target);
    free(reservation_list);
    return OK;
  }

  for (int i = left_end; i < (right_end + 1); i++)
  {
    print_reservation(reservation_list[i]);
  }
  /** printing done */
  
  /** deallocating */
  free(reservation_list);
  
  return OK;
}

void binary_search_ret_interval(reservation_t *reservation_list, char *target, int *left_end, int *right_end)
{
  /**
   * 1. binary search to return the index of the first target
   * 2. binary search to return the index of the last target
   * 3. put left and right index to corresponding arguments
  */
  
  *left_end = lower_bound(reservation_list, target);
  *right_end = upper_bound(reservation_list, target);

  return;
}

int lower_bound(reservation_t* reservation_list, char* target)
{
  int l = 0, d = num_of_reservations - 1;
  int s;
  while(l < d)
  {
    if(strstr(reservation_list[s].name, target) != NULL)
      d = s;
    else if (strcmp(reservation_list[s].name, target) < 0)
      l = ++s;
    else
      d = --s;
  }
  
  if (l < num_of_reservations)
    return l;
  else
    return NOT_FOUND;
}

int upper_bound(reservation_t *reservation_list, char* target)
{
  int l = 0, d = num_of_reservations - 1;
  int s;
  while(l < d)
  {
    if (strstr(reservation_list[s].name, target) != NULL)
      l = s;
    else if (strcmp(reservation_list[s].name, target) < 0)
      l = ++s;
    else
      d = --s;
  }
  
  if (d >= 0)
    return d;
  else
    return NOT_FOUND;
}

int sort_reservations_file(void)
{
  return OK;
}