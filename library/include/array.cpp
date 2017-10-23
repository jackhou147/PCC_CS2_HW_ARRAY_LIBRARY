#include "array.h"
#include<string>
using namespace std;

//DEFINITIONS
void display_menu()
{
    /* Purpose: print menu to the screen.
   * Pre-condition: none.
   * Post-condition: none.
   * TESTED: OCT 14, 2017
   */

    /*-------------DEBUG STATEMENT----------------*/
    const bool DEBUG = false;
    if (DEBUG)
        cout << endl
             << "-------------display_menu---------------" << endl;

    /*-------------process--------------*/
    cout << endl
         << "------------------------------------------------------------------------" << endl
         << " [A]ppend [B]efore a[F]ter [R]andom [D]elete [S]earch" << endl
         << "re[V]erse [U]nique [<]Descending [>]Ascending s[H]uffle" << endl
         << ".   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   ." << endl
         << "         [?]menu    [N]ext   [P]rev    e[X]it" << endl
         << "------------------------------------------------------------------------" << endl;
}
void display_array_info(int cursor, int num_used)
{
    /* Purpose: print "| CURSOR_POSITION/ LAST_INDEX: NUM_USED|"
   * Pre-condition: valid argument values are given.
   * Post-condition: none.
   * TESTED: OCT 14, 2017
   */

    /*-------------DEBUG STATEMENT--------------*/
    const bool DEBUG = false;
    if (DEBUG)
        cout << endl
             << "-------------display_array_info---------------" << endl;

    /*-----------process-----------*/
    cout << "|";
    if (cursor < 10)
        cout << " ";
    cout << cursor;
    cout << "/";
    if ((num_used - 1) < 10)
        cout << " ";
    cout << (num_used - 1);
    cout << ":";
    if (num_used < 10)
        cout << " ";
    cout << num_used;
    cout << "|";
}
string error_description(ERRORS code)
{
    /* Purpose: describe array error code.
   * Pre-condition: code is given valid
   * value. enum ERRORS has to be in scope.
   * Post-condition: description string is returned.
   * Dependency: enum ERRORS{}
   * TESTED: OCT 14,2017
   */

    /*-------------DEBUG STATEMENT----------------*/
    const bool DEBUG = false;
    if (DEBUG)
        cout << endl
             << "-------------error_description---------------" << endl;

    //variables...
    string description = "";

    //process...
    switch (code) {
    case FULL_ARRAY:
        description = "FULL ARRAY";
        break;
    case EMPTY_ARRAY:
        description = "EMPTY ARRAY";
        break;
    case INSERT_ON_EMPTY_ARRAY:
        description = "INSERT ON EMPTY ARRAY";
        break;
    case BAD_SHIFT_POS:
        description = "BAD SHIFT POS";
        break;
    case END_OF_LIST:
        description = "END OF LIST";
        break;
    case START_OF_LIST:
        description = "START OF LIST";
        break;
    case NO_ERROR:
    default:
        break;
    }

    //output...
    return description;
}
void display_array_nav(ITEM_TYPE a[], int num_used, int cursor, ERRORS& error)
{
    /* Purpose: displays the array with the cursor
   * and error description, if any.
   * Pre-condition: valid argument values are given.
   * Post-condition: none.
   * Note: 1. cursor is current cursor position and is zero-based.
   *       2. prints on the SAME line, no endl, no spaces.
   * Dependency: error_description(), enum ERRORS{}
   * TESTED: OCT 14,2017
   */

    /*-------------DEBUG STATEMENT----------------*/
    const bool DEBUG = false;
    if (DEBUG)
        cout << endl
             << "-------------display_array_nav---------------" << endl
             << "error: " << error << "; " << error_description(error) << endl;

    /*-----------process-----------*/
    //1. output opening brace
    cout << "{";
    //2. output each number in array
    for (int i = 0; i < num_used; i++) {
        if (i == cursor) {
            cout << "[" << setw(2) << a[i] << "]";
        }
        else {
            cout << " " << setw(2) << a[i] << " ";
        }
    };
    //3. output closing brace.
    cout << "} " << error_description(error);
}
ERRORS shift_right(ITEM_TYPE a[],
    int& num_used,
    int mark)
{
    /* Purpose: starting from current mark position,
   * shift array elements 1 element to the right.
   * Pre-condition:
   *   1. mark < numUsed
   *   2. num_used+1 <= array capacity
   *   3. 0 <= num_used
   * Post-condition:
   *   1. starting from mark, array elements
   *   are shifted 1 element to the right.
   *   2. mark is not changed.
   *   3. num_used is incremented by 1.
   * Dependency: enum ERRORS{}, int CAPACITY
   * Notes: ex: {a,[b],c,d} -> {a,[b],b,c,d}
   * TESTED: OCT 14, 2017
   */

    /*-------------DEBUG STATEMENT--------------*/
    const bool DEBUG = false;
    if (DEBUG)
        cout << endl
             << "-------------shift_right---------------" << endl
             << "num_used: " << num_used << "; mark: " << mark << endl;

    /*-------------process--------------*/
    //1. bad shift position
    if (mark < 0 || mark >= num_used)
        return BAD_SHIFT_POS;
    //2. full array
    if (num_used == CAPACITY)
        return FULL_ARRAY;
    //3. empty array
    if (num_used <= 0)
        return EMPTY_ARRAY;
    //4. safe to proceed
    for (int i = num_used; i > mark; i--) {
        a[i] = a[i - 1];
    };
    num_used++;
    return NO_ERROR;
}
ERRORS shift_left(ITEM_TYPE a[],
    int& numUsed,
    int mark)
{
    /* Purpose: shift array elements left, starting from mark.
   * Pre-condition:
   *   1. num_used >= 0
   *   2. mark < num_used
   * Post-condition:
   *   1.array elements are shifted one element to the left,
   *     starting from mark
   *   2.mark is NOT modified.
   * Note: ex: {a,b,c,[d],e} --> {a,b,d,[d],e} --> {a,b,d,[e],e}
   *       bad shift position when mark <= 0 or mark >= numUsed
   * Dependency: enum ERRORS{}, int CAPACITY
   * TESTED: OCT 14, 2017
   *
   */

    /*-------------DEBUG STATEMENT--------------*/
    const bool DEBUG = false;
    if (DEBUG)
        cout << endl
             << "-------------shift_left---------------" << endl;

    /*----------process-----------*/
    //1. bad shift position
    if (mark <= 0 || mark >= numUsed)
        return BAD_SHIFT_POS;
    //2. safe to proceed
    for (int i = mark; i < numUsed; i++) {
        if ((i - 1) >= 0) {
            a[i - 1] = a[i];
        }
    }
    numUsed--;
    return NO_ERROR;
}

ERRORS insert_before(ITEM_TYPE a[],
    int& num_used,
    ITEM_TYPE item,
    int mark)
{
    /* Purpose: insert an element before current mark position.
   * Pre-condition:
   *      -1 < mark < num_used < array capacity
   * Post-condition:
   *   1. item has been inserted before mark element
   *   2. num_used has been incremented by 1
   * Dependency: shift_right()
   * Note:
   *   1. mark is the index to insert the number before.
   *   2. do NOT use this function in an empty array.
   * Extra note: errors: empty array, full array
   * TESTED: OCT 14, 2017
   */

    /*-------------DEBUG STATEMENT--------------*/
    const bool DEBUG = false;
    if (DEBUG)
        cout << endl
             << "-------------insert_before---------------" << endl
             << "num_used: " << num_used << "; mark:" << mark << endl;

    /*-----------process-----------*/
    //1. if empty array
    if (num_used == 0)
        return EMPTY_ARRAY;
    //2. if full array
    else if (num_used == CAPACITY)
        return FULL_ARRAY;
    //3. safe to proceed
    shift_right(a, num_used, mark);
    a[mark] = item;
    return NO_ERROR;
}
ERRORS insert_after(ITEM_TYPE a[],
    int& num_used,
    ITEM_TYPE item,
    int mark)
{
    /* Purpose: insert an element after current mark position.
   * Pre-condition:  -1 <= mark < num_used < array capacity
   * Post-condition:
   *   1. item has been inserted after mark
   *   2. num_used has been incremented by 1
   * Dependency: shift_right();
   * Note: do not pass a mark argument that's out of range.
   * TESTED: OCT 14, 2017
   */

    /*-------------DEBUG STATEMENT----------------*/
    const bool DEBUG = false;
    if (DEBUG)
        cout << endl
             << "-------------insert_after---------------" << endl;

    /*-----------process-----------*/
    //1. if empty array
    if (num_used <= 0)
        return EMPTY_ARRAY;
    //2. if full array
    else if ((num_used + 1) > CAPACITY)
        return FULL_ARRAY;
    //3. safe to proceed
    if ((mark + 1) < num_used) //if marked element is not the last one in array,
        shift_right(a, num_used, mark + 1); //move right side neighbor elements to the right
    else
        num_used++; //manually update num_used because shift_right not called
    a[mark + 1] = item;
    return NO_ERROR;
}
int search(ITEM_TYPE a[],
    int num_used,
    ITEM_TYPE key)
{
    /* Purpose: search for key in array.
   * Pre-condition: valid argument values are given.
   * Post-condition: return first index of key,
   *   or -1 if key not found.
   * TESTED: OCT 14, 2017
   */

    /*-------------DEBUG STATEMENT--------------*/
    const bool DEBUG = false;
    if (DEBUG)
        cout << endl
             << "-------------arr_search---------------" << endl;

    /*----------variable-----------*/
    int index = -1; //index of key, -1 if key not found.

    /*-----------process-----------*/
    for (int i = 0; i < num_used; i++) {
        if (a[i] == key) {
            index = i;
            break;
        }
    }

    /*------------output-----------*/
    return index;
}
ERRORS append(ITEM_TYPE a[],
    int& num_used,
    ITEM_TYPE item)
{
    /* Purpose: append a given element to the end
   * of the interesting part of array.
   * Pre-condition: -1 < num_used < array capacity
   * Post-condition:
   *   1. item becomes the last interesting
   *      element of array.
   *   2. num_used is incremented by 1.
   * TESTED: OCT 14, 2017
   */

    /*-------------DEBUG STATEMENT----------------*/
    const bool DEBUG = false;
    if (DEBUG)
        cout << endl
             << "-------------arr_append---------------" << endl;

    //process...
    if (num_used < CAPACITY) {
        a[num_used] = item;
        num_used++;
        return NO_ERROR;
    }
    return FULL_ARRAY;
}
int get_int(string prompt)
{
    /* Purpose: to input a number from user.
   * Precondition: appropriate prompt is provided.
   * Postcondition: return the user input.
   * Note: no range requirement so integer overflow is possible.
   * TESTED: OCT 14 ,2017
   */

    //variable declarations...
    int number;

    //input...
    cout << prompt;
    cin >> number;

    //output...
    return number;
}
ERRORS remove(ITEM_TYPE a[],
    int& num_used,
    int mark)
{
    /* Purpose: remove element at mark.
   * Pre-condition: valid mark position.
   * Post-condition:
   *   1.element at mark has been removed,
   *   2.num_used has been decremented by 1.
   *   3.mark index is NOT changed
   * Dependency: shift_left()
   * Note: this function does NOT decrement num_used.
   *   num_used is decremented by shift_left function.
   * TESTED: OCT 14, 2017
   */

    /*-------------DEBUG STATEMENT----------------*/
    const bool DEBUG = false;
    if (DEBUG)
        cout << endl
             << "-------------arr_remove---------------" << endl
             << "num_used: " << num_used << "; mark: " << mark << endl;

    /*----------process-----------*/
    //1. if empty array
    if (num_used <= 0)
        return EMPTY_ARRAY;
    //2. safe to proceed
    if ((mark + 1) < num_used) //if marked element is not the last one in array,
        shift_left(a, num_used, mark + 1); //overwrite it by shifting its right side neighbors
    else
        num_used--;
    return NO_ERROR;
}

int GetNext(int lo, int hi)
{
    /* Purpose: get a random number within range.
   * Pre-condition: lo < hi
   * Post-condition: a random number between lo
   * and hi are generated and returned.
   */

    //process...
    int r = rand() % (hi - lo + 1) + lo;
    //output...
    return r;
}

void swap(ITEM_TYPE& a, ITEM_TYPE& b)
{
    /* Purpose: swap values of a and b
   * Pre-condition: valid a and b values.
   * Post-condition: a's value is set to
   * b, b's value is set to a.
   * TESTED: OCT 17, 2017
   */

    //variables...
    ITEM_TYPE temp = a;

    //process...
    a = b;
    b = temp;
}

bool sort_need_swap(bool ascending, int cell, int neighbor_right)
{
    /* Purpose: help sort function determine
   * if swap function needs to be called.
   * Pre-condition: valid argument values are given.
   * Post-condition: a boolean is returned.
   * Dependency: sort()
   * Note: USE THIS FUNCTION AND SORT TOGETHER.
   */

    //variables...
    bool result;

    //process...
    //1. if ascending, each cell has to be smaller than its right side neighbor
    if (ascending)
        result = (cell > neighbor_right) ? true : false;
    //2. if descending, each cell has to be bigger than its right side neighbor
    else
        result = (cell < neighbor_right) ? true : false;

    //output...
    return result;
}

ERRORS sort(
    ITEM_TYPE a[],
    int& num_used,
    bool ascending)
{
    /* Purpose: sort a[] in ascending or descending order
   * Pre-condition: valid argument values.
   * Post-condition: a[] has been sorted in ascending or
   * descending order.
   * Dependency: swap(), sort_need_swap()
   * Note: bubble sort algorithm. The algorithm keeps track
   * of number of swaps in each iteration, and stops only
   * when no more swaps are needed.
   * TESTED: OCT 17, 2017
   */

    //variables...
    int swap_count = 0; //how many times swap has been called

    //process...
    if (num_used <= 0) //return if empty array
        return EMPTY_ARRAY;
    do { //repeat until swap function is no longer called
        //1. reset swap count with each loop
        swap_count = 0;
        for (int i = 0; i < (num_used - 1); i++) {
            //2. compare each number with its neighbor, swap if needed
            if (sort_need_swap(ascending, a[i], a[i + 1])) {
                swap(a[i], a[i + 1]);
                swap_count++;
            }
        }
    } while (swap_count != 0);

    //output
    return NO_ERROR;
}

ERRORS reverse(ITEM_TYPE a[], int num_used)
{
    /* Purpose: reverse the order of elements in a[ ]
   * Pre-condition: valid argument values.
   * Post-condition: elements in a[] has been set
   * to reversed order.
   * Dependency: swap()
   * TESTED: OCT 17, 2017
   */

    //process...
    if (num_used <= 0) //return if empty array
        return EMPTY_ARRAY;
    //two walkers, one from beginning, one from end
    for (int i = 0, j = (num_used - 1); i < j; i++, j--) {
        swap(a[i], a[j]);
    }

    //output...
    return NO_ERROR;
}

ERRORS delete_repeats(ITEM_TYPE a[], int& num_used)
{
    /* Purpose: remove all repeated items (save only one)
   * Pre-condition: valid argument values are given.
   * Post-condition: all duplicate items in given array
   * are deleted with only 1 original item left.
   * Dependency: search(), remove()
   * TESTED: OCT 20, 2017
   */

    //variables...
    ERRORS error = NO_ERROR;
    int i = 0;

    //process...
    if (num_used <= 0) //return if empty
        return EMPTY_ARRAY;
    while (i < num_used) {
        if (i == search(a, num_used, a[i])) //if walker equals search result, then not duplicate
            i++;
        else //duplicate
            error = remove(a, num_used, i);
    }

    //output...
    return error;
}

ERRORS shuffle(ITEM_TYPE a[], int num_used)
{
    /* Purpose: randomly rearrange elements in array.
   * Pre-condition: valid array elements are given.
   * Post-condition: array elements have been rearranged.
   * Dependency: GetNext(), swap()
   * TESTED: OCT 17, 2017
   */

    //variables...
    ERRORS error = NO_ERROR;
    int rand; //random number

    //process...
    if (num_used <= 0) //return if empty array
        error = EMPTY_ARRAY;
    for (int i = 0; i < num_used; i++) {
        //1. get a random number in range
        rand = GetNext(0, (num_used - 1));
        //2. swap current element with the randomly selected element
        swap(a[i], a[rand]);
    }

    //output...
    return error;
}
