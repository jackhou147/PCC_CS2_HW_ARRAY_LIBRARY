//File Name: main.cpp
//Author: Jack Hou
//Email Address: jackhou147@yahoo.com
//Assignment: Array Navigation Application
//Description: Program for array processing.
//Last Changed: Oct 17, 2017
#include <iostream>
#include <time.h>
#include "../../!includes/array.h"


using namespace std;

//PROTOTYPES
void main_output(bool menu, int arr[], int num_used, int cursor, ERRORS error);     //help main function output
void main_process(char command, int arr[],                                          //help main function process array
                  int & cursor, int & num_used,
                  bool & print_menu, ERRORS & error);

int main() {
    srand(time(0));
    //variables...
    int cursor = 0;                                          //cursor position to be passed down
    int num_used = 6;                                        //number of interesting elements in array
    bool print_menu = true;                                  //if true, print menu on screen
    char command;
    int arr[CAPACITY] = {10,15,36,9,36,18};
    ERRORS error = NO_ERROR;                                 //default value

    //output...
    main_output(print_menu,arr,num_used,cursor, error);
    do{
        //input...
        cin>>command;
        command = toupper(command);

        //process...
        main_process(command,arr,cursor,num_used,print_menu, error);

        //output...
        main_output(print_menu,arr,num_used,cursor, error);
    }while(command != 'X');                                  //repeat until user exits
    return 0;
}

//DEFINITIONS
void main_output(bool menu, int arr[], int num_used, int cursor, ERRORS error) {
    /* Purpose: output everything main needs to output.
     * Pre-condition: arguments have been given valid values.
     * Post-condition: print num_used, cursor position and
     * array on the screen; also print menu if needed.
     * Dependency: display_menu(), display_array_nav()
     * TESTED: OCT 11, 2017
     */

    /*-------------process--------------*/
    //1. output menu if needed
    if (menu) display_menu();
    cout << endl;
    //2. output cursor position, last index, num_used
    display_array_info(cursor, num_used);
    cout<<setw(3);
    //3. output list of the numbers in the array.
    display_array_nav(arr, num_used, cursor, error);
    cout << endl;
}

void main_process(char command, int arr[],
                  int & cursor, int & num_used,
                  bool & print_menu, ERRORS & error) {
    /* Purpose: process array and cursor on behalf of main function.
     * Pre-condition: arguments are given valid values.
     * Post-condition: array or cursor position has been modified, or
     * print_menu is set to true/false.
     * Note:
     *   1. this function is not reusable.
     *   2. this function can do input, because
     *      it is the same level as main.
     * Dependency: append(), insert_before(), insert_after(),
     *  remove(), search(), <cstdlib>
     * TESTED: OCT 14, 2017
     */

    /*-------------DEBUG STATEMENT----------------*/
    const bool DEBUG = false;
    if (DEBUG)
        cout << endl << "-------------main_process---------------" << endl;

    /*-----------variables------------*/
    print_menu = false;                                      //default value, until changed
    error = NO_ERROR;                                        //default value, until changed
    int key;                                                 //key to search for
    int search_result;                                       //index of key in array, -1 if not found.
    string prompt = ">> ";

    /*-----------process-------------*/
    switch (command) {
        //append
        case 'A':
            //1.input an element
            key = get_int(prompt);
            //2.put it to the end of array
            error = append(arr, num_used, key);
            if (error == NO_ERROR)
                cursor = num_used - 1;
            break;
        //before
        case 'B':
            //1.input an element
            key = get_int(prompt);
            //2.insert it before current cursor position
            error = insert_before(arr, num_used, key, cursor);
            break;
        //after
        case 'F':
            //1.input an element
            key = get_int(prompt);
            //2.insert it after current cursor position
            error = insert_after(arr, num_used, key, cursor);
            if (error == NO_ERROR)
                cursor++;
            break;
        //random
        case 'R':
            //1. insert a random number after current cursor position
            error = insert_after(arr, num_used, GetNext(10, 99), cursor);
            //2. update cursor position
            if (error == NO_ERROR)
                cursor++;
            break;
        //delete
        case 'D':
            //1. delete element at current cursor position
            error = remove(arr, num_used, cursor);
            //2. update cursor position
            if (cursor >= num_used) //if out of range
                cursor--;
            break;
        //search
        case 'S':
            //1. input an element
            key = get_int(prompt);
            //2. search for it in array
            search_result = search(arr, num_used, key);
            //3. update cursor position if found
            if (search_result != -1)
                cursor = search_result;
            break;
        //unique
        case 'U':
            error = delete_repeats(arr, num_used);
            if (cursor > 0)
                cursor = 0;
            break;
        //reverse
        case 'V':
            error = reverse(arr, num_used);
            if (cursor > 0)
                cursor = 0;
            break;
        //shuffle
        case 'H':
            error = shuffle(arr, num_used);
            if (cursor > 0)
                cursor = 0;
            break;
        //ascending
        case '>':
            error = sort(arr, num_used, true);
            if (cursor > 0)
                cursor = 0;
            break;
        //descending
        case '<':
            error = sort(arr, num_used, false);
            if (cursor > 0)
                cursor = 0;
            break;
        //menu
        case '?':
            print_menu = true;
            break;
        //cursor next
        case 'N':
            if ((cursor + 1) < num_used)
                cursor++; //move cursor 1 element right
            break;
        //cursor previous
        case 'P':
            if ((cursor - 1) >= 0)
                cursor--; //move cursor 1 element left
            break;
        //exit
        case 'X':
            break;
        //default
        default:
            cout << endl << "invalid choice.";
            break;
    }

    /*-------------DEBUG STATEMENT----------------*/
    if (DEBUG)
        cout << endl << "-------------/main_process---------------" << endl;
}


