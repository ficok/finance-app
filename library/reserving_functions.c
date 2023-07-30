#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "utilities.h"
#include "reservation.h"
#include "app.h"
#include "error_codes.h"
#include "utility_codes.h"
#include "logging.h"
#include "loading.h"

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
  
  sort_reservations_file_with_loading();
  
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
  
  /**
   * 1. load the reservations
   * 2. search for reservations
   * 3. use acquired interval to print
  */
  
  reservation_t *reservation_list = malloc(num_of_reservations * sizeof(reservation_t));
  // check for error
  load_reservations(reservation_list);
  
  interval_t interval = search_for_reservation(reservation_list, name);

  if (interval.found_flag == NOT_FOUND)
  {
    // deallocation
    printf("reservation containing %s not found.\n", name);
    return NOT_FOUND;
  }
  
  for(int i = interval.left; i < (interval.right + 1); i++)
    print_reservation(reservation_list[i]);
  
  free(reservation_list);
  return OK;
}

extern int update_reservation()
{
  printf("enter name or keyword: ");
  char name[MESSAGE_LEN];
  flush_input_buffer();
  fgets(name, MESSAGE_LEN, stdin);
  flush_input_buffer();
  
  reservation_t *reservation_list = malloc(num_of_reservations * sizeof(reservation_t));
  // check for error
  load_reservations(reservation_list);
  
  interval_t interval = search_for_reservation(reservation_list, name);
  if (interval.found_flag == NOT_FOUND)
  {
    // deallocation
    printf("reservation containing %s not found.\n", name);
    return NOT_FOUND;
  }
  
  if ((interval.right - interval.left) != 0)
  {
    printf("multiple reservations found. pick one:\n");
    for(int i = interval.left; i < (interval.right + 1); i++)
      printf("  [%d] %s\n", i, reservation_list[i].name);
  }
  printf("your choice: ");
  int index;
  scanf("%d", &index);
  flush_input_buffer();
  printf("\n\n");
  
  printf("reservation you searched for: \n");
  print_reservation(reservation_list[index]);
  
  bool exit_flag = false;
  while (!exit_flag)
  {
    printf("  [1] rename\n  [2] update funding\n  [3] go back\nyour choice: ");
    char choice;
    scanf("%c", &choice);
    
    switch(choice)
    {
      case '1':
        rename_reservation(&reservation_list[index]);
        printf("%s", DIVIDER);
        break;
      case '2':
        update_funding(&reservation_list[index]);
        printf("%s", DIVIDER);
        break;
      case '3':
        exit_flag = true;
        printf("%s", DIVIDER);
        break;
      default:
        printf("incorrect input.\n");
        printf("%s", DIVIDER);
        break;
    }
    flush_input_buffer();
  }
  
  reload_reservations_file(reservation_list);
  
  return OK;
}