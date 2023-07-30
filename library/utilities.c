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

int update_available()
{
  printf("entering: update_available\n");
  FILE *available_file = fopen("account_data/available","w");
  // check error
  
  available -= reserved;
  
  fprintf(available_file, "%d", available);
  
  fclose(available_file);
  
  printf("leaving: update_available\n");
  return OK;
}

int update_reserved(int goal)
{
  printf("entering: update_reserved\n");
  FILE *reserved_file = fopen("account_data/reserved", "w");
  // check error
  
  reserved += goal;

  fprintf(reserved_file, "%d", reserved);
  
  fclose(reserved_file);
  
  update_available();
  
  load_data();
  printf("leaving: update_reserved\n");
  return OK;
}

int update_number_of_reservations()
{
  FILE *num_of_reservations_file = fopen("account_data/number_of_reservations", "w");
  // check error
  
  num_of_reservations++;
  
  fprintf(num_of_reservations_file, "%d", num_of_reservations);
  
  fclose(num_of_reservations_file);
  
  load_data();
  
  return OK;
}

interval_t search_for_reservation(reservation_t *reservation_list, char *target)
{
  /**
   * 1. load the reservations
   * 2. pass it to binary search along with the name/keyword
   * 3. it returns the ends of the interval that has the target name(s)
   * 4. print the information from the structure list
  */
  
  /** binary search */
  int left_end, right_end;
  binary_search_ret_interval(reservation_list, target, &left_end, &right_end);
  
  interval_t interval = {
    left_end,
    right_end,
    FOUND
  };
  
  if(left_end == NOT_FOUND || right_end == NOT_FOUND)
    interval.found_flag = NOT_FOUND;
  /** binary search done; interval acquired */

  return interval;
}

int rename_reservation(reservation_t *reservation)
{
  char name[MESSAGE_LEN];
  printf("enter new name: ");
  // flush_input_buffer();
  fgets(name, MESSAGE_LEN, stdin);
  shave_newline(name);
  
  strcpy(reservation->name, name);
  // flush_input_buffer();
  return OK;
}

int update_funding(reservation_t *reservation)
{
  int current_funding;
  printf("add funding: ");
  // flush_input_buffer();
  scanf("%d", &current_funding); getchar();
  
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
  printf("entering: binary_search\n");
  *left_end = lower_bound(reservation_list, target);
  *right_end = upper_bound(reservation_list, target);
  printf("leaving: binary_search\n");
  return;
}

int lower_bound(reservation_t* reservation_list, char* target)
{
  printf("entering: lower_bound\n");
  int l = 0, d = num_of_reservations - 1;
  int s;
  while(l < d)
  {
    s = l + (d-l)/2;
    if(strstr(reservation_list[s].name, target) != NULL)
      d = s;
    else if (strcmp(reservation_list[s].name, target) < 0)
      l = ++s;
    else
      d = --s;
  }
  printf("leaving: lower_bound\n");
  if (l < num_of_reservations)
    return l;
  else
    return NOT_FOUND;
}

int upper_bound(reservation_t *reservation_list, char* target)
{
  printf("entering: upper bound\n");
  int l = 0, d = num_of_reservations - 1;
  int s, iter = 0;
  while(l < d)
  {
    printf("upper bound iter: %d\n", iter);
    iter++;
    if(iter == 2*num_of_reservations)
      break;
    s = l + (d-l)/2+1;
    printf("s is: %d\nl is: %d and d is: %d\n", s,l,d);
    printf("is %s a substring of %s? ", target, reservation_list[s].name);
    if(strstr(reservation_list[s].name, target) != NULL)
    {
      printf("it is\n");
      l = s;
    }
    else if(strcmp(reservation_list[s].name, target) < 0)
    {
      printf("it is\n");
      l = s+1;
    }
    else
      d = s-1;
  }
  printf("leaving: upper bound\n");
  if (d > 0 && d < num_of_reservations)
    return d;
  else
    return NOT_FOUND;
}

int swap_reservations(reservation_t *reservation1, reservation_t *reservation2, int iteration)
{
  // printf("entering %d: swap_reservations\n", iteration);
  reservation_t *temp = malloc(sizeof(reservation_t));
// printf("swap 1\n");
  *temp = *reservation1;
// printf("swap 2\n");
  *reservation1 = *reservation2;
// printf("swap 3\n");
  *reservation2 = *temp;
// printf("swap 4\n");
  // printf("leaving %d: swap_reservations\n", iteration);
  return OK;
}

int partition(reservation_t *reservation_list, int left, int right)
{
  // printf("entering: partition\n");
  char *pivot = reservation_list[right].name;
// printf("partition 1\n");
  int i = (left - 1);
  int j;
  for(j = left; j < right; j++)
  {
    // printf("partition %d loop enter\n", j);
    if(strcmp(reservation_list[j].name, pivot) < 0)
    {
      i++;
      // printf("partition 2\n");
      swap_reservations(&reservation_list[i], &reservation_list[j], j);
      // printf("partition 3\n");
    }
    // printf("partition %d loop leave\n", j);
  }
  
  int pivot_index = (i + 1);
  // printf("partition 4\n");
  swap_reservations(&reservation_list[pivot_index], &reservation_list[right],j);
  // printf("leaving: partition\n");
  return pivot_index;
}

int quick_sort_reservation_list(reservation_t *reservation_list, int left, int right)
{
// printf("entering: quick_sort_resrvation_list\n");
  if(left < right)
  {
    int pivot = partition(reservation_list, left, right);
    quick_sort_reservation_list(reservation_list, left, (pivot - 1));
    quick_sort_reservation_list(reservation_list, (pivot + 1), right);
  }

// printf("leaving: quick_sort_reservation_list\n");
  return OK;
}

int sort_reservations_file_with_loading(void)
{
  // printf("entering: sort_reservations_file_with_loading\n");
  reservation_t *reservation_list = malloc(num_of_reservations * sizeof(reservation_t));
  // check for error
  
  load_reservations(reservation_list);
  
  quick_sort_reservation_list(reservation_list, 0, (num_of_reservations - 1));
  
  FILE *reservations_file = fopen("account_data/reservations","w");
  // check for error
  
  for (int i = 0; i < num_of_reservations; i++)
  {
    fprintf(reservations_file, "%s,%d,%d\n",
            reservation_list[i].name,
            reservation_list[i].goal, reservation_list[i].current_fund);
  }
  
  fclose(reservations_file);
  
  free(reservation_list);
  
  // printf("leaving: sort_reservations_file_with_loading\n");
  
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
    fprintf(reservations_file, "%s,%d,%d\n",
            reservation_list[i].name,
            reservation_list[i].goal, reservation_list[i].current_fund);
  }
  
  fclose(reservations_file);
  
  return OK;
}

void print_reservation(reservation_t reservation)
{
  printf("reservation name: %s\nreservation goal: %d\nreservation funds: %d\n\n",
  reservation.name, reservation.goal, reservation.current_fund);
  
  return;
}