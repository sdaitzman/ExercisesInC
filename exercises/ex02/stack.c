/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

/*
int* foo()
No arguments
Creates an int array, length SIZE
Fills the array with int 42
Trues to return an array pointer to that array
*/
int *foo() {
    int i;
    
    // declare int array of length 5 in the stack
    int array[SIZE];

    // printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        // set each value of array to 42
        array[i] = 42;
    }
    return array;
}


/*
int* bar()
No arguments
Creates an int array, length SIZE
Fills the array with ints, counting up
*/
void bar() {
    int i;

    // declare int array of length 5 in the stack
    int array[SIZE];

    // printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        // set each value of array to its index
        array[i] = i;
    }
}

int main()
{
    // declare an empty iterator count int
    int i;

    // declare an int pointer to foo()'s int array...
    // ...which no longer exists after that stack is cleared :'(
    int *array = foo();

    // call bar(), allocating a new array over the same stack space
    bar();

    // count from 0 to 4
    for (i=0; i<SIZE; i++) {
        // print current contents of stack memory formerly used for array
        // (so, prints contents of memory int* array points at)
        printf("%d\n", array[i]);
    }

    // return success exit code
    return 0;
}
