#ifndef ARRAY_H
#define ARRAY_H
#include <string>
#include <iostream>
#include <iomanip>
#include "../!includes/constants.h"

bool sort_need_swap(bool ascending, int a, int b);
ERRORS shuffle(ITEM_TYPE a[], int num_used);
ERRORS sort(ITEM_TYPE a[],
            int & num_used,
            bool ascending);                                 //sort a[] in ascending or descending order
void swap(ITEM_TYPE & a, ITEM_TYPE & b);                     //swap values of a and b
ERRORS delete_repeats(ITEM_TYPE a[],                         //remove all repeated items (save only one)
                      int & num_used);
ERRORS reverse(ITEM_TYPE a[], int num_used);                 //reverse the order of elements in a[ ]
void display_menu();
void display_array_info(int cursor, int num_used);
void display_array_nav(ITEM_TYPE a[], int num_used, int cursor, ERRORS & error);
void arr_fill_up(int arr[], int size);
int GetNext(int lo, int hi);
std::string error_description(ERRORS code);
ERRORS shift_left(ITEM_TYPE a[],
                  int & numUsed,
                  int mark);
ERRORS shift_right(ITEM_TYPE a[],
                   int & num_used,
                   int mark);
ERRORS remove(ITEM_TYPE a[],
              int & num_used,
              int mark);
ERRORS insert_before(ITEM_TYPE a[],
                     int & num_used,
                     ITEM_TYPE item,
                     int mark);
ERRORS insert_after(ITEM_TYPE a[],
                    int & num_used,
                    ITEM_TYPE item,
                    int mark);
int search(ITEM_TYPE a[],
           int num_used,
           ITEM_TYPE key);
ERRORS append(ITEM_TYPE a[],
              int & num_used,
              ITEM_TYPE item);
int get_int(std::string prompt);


#endif // ARRAY_H
