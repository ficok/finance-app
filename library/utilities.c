#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "app.h"
#include "utilities.h"
#include "error_codes.h"
#include "utility_codes.h"
#include "loading.h"

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

interval_t search_for_reservation(reservation_t *reservation_list, char *target)
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

  /** binary search */
  int left_end, right_end;
  binary_search_ret_interval(reservation_list, target, &left_end, &right_end);
  
  interval_t interval = {
    left_end,
    right_end
  };
  
  if(left_end == NOT_FOUND || right_end == NOT_FOUND)
    interval.found_flag = NOT_FOUND;
  else
    interval.found_flag = FOUND;
  /** binary search done; interval acquired */

  return interval;
}

int rename_reservation(reservation_t *reservation)
{
  char name[MESSAGE_LEN];
  printf("enter new name: ");
  flush_input_buffer();
  fgets(name, MESSAGE_LEN, stdin);
  flush_input_buffer();
  
  strcpy(reservation->name, name);
  
  return OK;
}

int update_funding(reservation_t *reservation)
{
  int current_funding;
  printf("add funding: ");
  flush_input_buffer();
  scanf("%d", &current_funding);
  flush_input_buffer();
  
  reservation->current_fund = current_funding;
  
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

int swap_reservations(reservation_t *reservation1, reservation_t *reservation2)
{
  reservation_t *temp;
  *temp = *reservation1;
  *reservation1 = *reservation2;
  *reservation2 = *temp;
  
  return OK;
}

int partition(reservation_t *reservation_list, int left, int right)
{
  char *pivot = reservation_list[right].name;
  
  int i = (left - 1);
  
  for(int j = left; j < right; j++)
  {
    if(strcmp(reservation_list[j].name, pivot) < 0)
    {
      i++;
      swap_reservations(&reservation_list[i], &reservation_list[j]);
    }
  }
  
  int pivot_index = (i + 1);
  swap_reservations(&reservation_list[pivot_index], &reservation_list[right]);
  
  return pivot;
}

int quick_sort_reservation_list(reservation_t *reservation_list, int left, int right)
{
  if(left < right)
  {
    char *pivot = partition(reservation_list, 0, (num_of_reservations - 1));
    quick_sort_reservation_list(reservation_list, left, (pivot - 1));
    quick_sort_reservation_list(reservation_list, (pivot + 1), right);
  }

  return OK;
}

int sort_reservations_file_with_loading(void)
{
  reservation_t *reservation_list = malloc(num_of_reservations * sizeof(reservation_t));
  // check for error
  
  load_reservations(reservation_list);
  
  quick_sort_reservation_list(reservation_list, 0, (num_of_reservations - 1));
  
  FILE *reservations_file = fopen("account_data/reservations","w");
  // check for error
  
  for (int i = 0; i < num_of_reservations; i++)
  {
    fprintf(reservations_file, "%d,%s,%d,%d\n",
            reservation_list[i].id, reservation_list[i].name,
            reservation_list[i].goal, reservation_list[i].current_fund);
  }
  
  fclose(reservations_file);
  
  return OK;
}

int sort_reservations_file(reservation_t *reservation_list)
{
  /**
   * 1. sort reservation list with quick_sort_reservation_list
   * 2. write the reservation_list to file
  */
 
  quick_sort_reservation_list(reservation_list, 0, (num_of_reservations - 1));
  
  FILE *reservations_file = fopen("account_data/reservations","w");
  // check for error
  
  for (int i = 0; i < num_of_reservations; i++)
  {
    fprintf(reservations_file, "%d,%s,%d,%d\n",
            reservation_list[i].id, reservation_list[i].name,
            reservation_list[i].goal, reservation_list[i].current_fund);
  }
  
  fclose(reservations_file);
  
  return OK;
}