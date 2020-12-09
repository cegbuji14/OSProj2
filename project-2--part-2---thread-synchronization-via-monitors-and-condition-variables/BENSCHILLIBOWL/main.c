#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "BENSCHILLIBOWL.h"

// Feel free to play with these numbers! This is a great way to
// test your implementation.
#define BENSCHILLIBOWL_SIZE 100
#define NUM_CUSTOMERS 90
#define NUM_COOKS 10
#define ORDERS_PER_CUSTOMER 3
#define EXPECTED_NUM_ORDERS NUM_CUSTOMERS * ORDERS_PER_CUSTOMER

// Global variable for the restaurant.
BENSCHILLIBOWL *bcb;

/**
 * Thread funtion that represents a customer. A customer should:
 *  - allocate space (memory) for an order.
 *  - select a menu item.
 *  - populate the order with their menu item and their customer ID.
 *  - add their order to the restaurant.
 */
void* BENSCHILLIBOWLCustomer(void* tid) {
  int customer_id = (int)(long) tid;
  int i;
  for (i = 0; i < ORDERS_PER_CUSTOMER; i++){
    Order *cust_order = (Order*)malloc(sizeof(Order));
    MenuItem item = PickRandomMenuItem();
    cust_order->customer_id = customer_id;
    cust_order->menu_item = item;
    cust_order->next=NULL;
    int x = AddOrder(bcb,cust_order);//Add Order 
    }
}

/**
 * Thread function that represents a cook in the restaurant. A cook should:
 *  - get an order from the restaurant.
 *  - if the order is valid, it should fulfill the order, and then
 *    free the space taken by the order.
 * The cook should take orders from the restaurants until it does not
 * receive an order.
 */
void* BENSCHILLIBOWLCook(void* tid) {
  int cook_id = (int)(long) tid;
	int done_orders = 0;
  Order *order;
  order = GetOrder(bcb);
  while(order != NULL){
    free(order);
    done_orders++;
    order = GetOrder(bcb);
  }
	printf("Cook #%d fulfilled %d orders\n", cook_id, done_orders);
}

/**
 * Runs when the program begins executing. This program should:
 *  - open the restaurant
 *  - create customers and cooks
 *  - wait for all customers and cooks to be done
 *  - close the restaurant.
 */
int main() {
    int i,j;
    j = 1;
  
    int customer[NUM_CUSTOMERS];
    int cook[NUM_COOKS];
  
    bcb = OpenRestaurant(BENSCHILLIBOWL_SIZE, EXPECTED_NUM_ORDERS);

    pthread_t bcb_customers[NUM_CUSTOMERS];
    pthread_t bcb_cooks[NUM_COOKS];

    for (i = 0; i < NUM_CUSTOMERS; i++){
      customer[i] = j;
      pthread_create(&(bcb_customers[i]), NULL, BENSCHILLIBOWLCustomer, &(customer[i]));
      j++;
    }
  
    for (i = 0; i < NUM_COOKS; i++){
      cook[i] = j;
      pthread_create(&(bcb_cooks[i]), NULL, BENSCHILLIBOWLCook, &(cook[i]));
      j++;
    }
  
    for (i = 0; i < NUM_CUSTOMERS; i++){
      pthread_join(bcb_customers[i], NULL);
    }
  
    for (i = 0; i < NUM_COOKS; i++){
      pthread_join(bcb_cooks[i], NULL);
    }

    //CloseRestaurant(bcb);
    return 0;
}