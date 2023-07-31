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
  // flush_input_buffer();
  fgets(name_buffer, 100, stdin);
  shave_newline(name_buffer);
  strcpy(reservation->name, name_buffer);
  
  printf("what is the fund goal of %s: ", reservation->name);
  int goal;
  scanf("%d", &goal); getchar();
  reservation->goal = goal;
  
  printf("initialise the funding (enter 0 if no funding): ");
  int current_fund;
  scanf("%d", &current_fund); getchar();
  reservation->current_fund = current_fund;
  
  update_number_of_reservations();
  reservation->id = num_of_reservations;
  
  log_reservation(reservation, NEW_RESERVATION);
  
  update_reserved(goal);
  update_available(goal);
  
  sort_reservations_file_with_loading();
  
  free(reservation);
  
  return OK;
}

extern int check_reservation()
{
  printf("enter name or keyword: ");
  char name[MESSAGE_LEN];
  // flush_input_buffer();
  fgets(name, MESSAGE_LEN, stdin);
  shave_newline(name);
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
  
  printf("found: %d reservation(s) containing %s.\n\n", (interval.right - interval.left + 1), name);
  
  for(int i = interval.left; i < (interval.right + 1); i++)
    print_reservation(reservation_list[i]);
  
  free(reservation_list);
  return OK;
}

extern int update_reservation()
{
  printf("enter name or keyword: ");
  char name[MESSAGE_LEN];
  // flush_input_buffer();
  fgets(name, MESSAGE_LEN, stdin);
  shave_newline(name);
  
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
  
  int index;
  if ((interval.right - interval.left) != 0)
  {
    printf("multiple reservations found. pick one:\n");
    for(int i = interval.left; i < (interval.right + 1); i++)
      printf("  [%d] %s\n", i, reservation_list[i].name);
    
    printf("your choice: ");
    // flush_input_buffer();
    scanf("%d", &index); getchar();
    printf("\n");
  }
  else
    index = interval.right;
  
  printf("reservation you searched for: \n\n");
  print_reservation(reservation_list[index]);
  
  bool exit_flag = false;
  while (!exit_flag)
  {
    printf("options:\n  [1] rename\n  [2] update funding\n  [3] go back\nyour choice: ");
    char choice;
    // flush_input_buffer();
    scanf("%c", &choice); getchar();
    
    switch(choice)
    {
      case '1':
        printf("- rename\n%s", DIVIDER);
        rename_reservation(&reservation_list[index]);
        printf("%s", DIVIDER);
        break;
      case '2':
        printf("- update funding\n%s", DIVIDER);
        update_funding(&reservation_list[index]);
        printf("%s", DIVIDER);
        break;
      case '3':
        exit_flag = true;
        printf("- going back\n");
        break;
      default:
        printf("incorrect input.\n");
        flush_input_buffer();
        printf("%s", DIVIDER);
        break;
    }
  }
  
  reload_reservations_file(reservation_list, NULL, NULL);
  
  log_reservation(&reservation_list[index], UPDATE_RESERVATION);
  
  free(reservation_list);
  return OK;
}