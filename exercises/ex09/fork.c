/* Example code for Exercises in C.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>





// Question 2: Memory Sharing Across Forks
/*

We are interested in seeing whether different types of memory are shared across
forks, so I'll create a few variables that are global, stack and heap variables
and print them out. 

As expected they're all separate. Logs:

Creating child 0.
Creating child 1.
After changing: i=0      a_global=100    a_static=100    a_stack=100     a_heap=0
Before changing: i=0     a_global=101    a_static=101    a_stack=101     a_heap=1
Creating child 2.
Hello from child 0.
After changing: i=1      a_global=100    a_static=100    a_stack=100     a_heap=0
Before changing: i=1     a_global=101    a_static=101    a_stack=101     a_heap=1
Hello from the parent.
Child 65864 exited with error code 0.
After changing: i=2      a_global=100    a_static=100    a_stack=100     a_heap=0
Before changing: i=2     a_global=101    a_static=101    a_stack=101     a_heap=1
Hello from child 1.
Child 65865 exited with error code 1.
Hello from child 2.
Child 65866 exited with error code 2.
Elapsed time = 2.002215 seconds.


*/


       int a_global = 100;
static int a_static = 100;



// errno is an external global variable that contains
// error information
extern int errno;


// get_seconds returns the number of seconds since the
// beginning of the day, with microsecond precision
double get_seconds() {
    struct timeval tv[1];

    gettimeofday(tv, NULL);
    return tv->tv_sec + tv->tv_usec / 1e6;
}



// modified child_code to take stack and heap variables for testing, and to
// print out the global and static variables created above
// TODO: ask about why the stack int here is passed by pointer like this
void child_code(int i, int* a_stack, int* a_heap)
{

    printf("After changing: i=%d \t a_global=%d \t a_static=%d \t a_stack=%d \t a_heap=%d\n", i, a_global, a_static, *a_stack, *a_heap);

    a_global++;
    a_static++;
    (*a_stack)++;
    (*a_heap)++;

    printf("Before changing: i=%d \t a_global=%d \t a_static=%d \t a_stack=%d \t a_heap=%d\n", i, a_global, a_static, *a_stack, *a_heap);


    sleep(i);
    printf("Hello from child %d.\n", i);
}



// main takes two parameters: argc is the number of command-line
// arguments; argv is an array of strings containing the command
// line arguments
int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    double start, stop;
    int i, num_children;


    // I added two new variables, one on the stack and one on the heap
    int  a_stack = 100;
    int* a_heap = malloc(sizeof(int));

    // the first command-line argument is the name of the executable.
    // if there is a second, it is the number of children to create.
    if (argc == 2) {
        num_children = atoi(argv[1]);
    } else {
        num_children = 1;
    }

    // get the start time
    start = get_seconds();

    for (i=0; i<num_children; i++) {

        // create a child process
        printf("Creating child %d.\n", i);
        pid = fork();

        /* check for an error */
        if (pid == -1) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        /* see if we're the parent or the child */
        if (pid == 0) {

            // modification: I pass the stack and heap variables

            child_code(i, &a_stack, a_heap);
            exit(i);
        }
    }

    /* parent continues */
    printf("Hello from the parent.\n");

    for (i=0; i<num_children; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
        printf("Child %d exited with error code %d.\n", pid, status);
    }
    // compute the elapsed time
    stop = get_seconds();
    printf("Elapsed time = %f seconds.\n", stop - start);

    exit(0);
}
