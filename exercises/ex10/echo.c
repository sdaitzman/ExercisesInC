/* Starter code for the echo exercise.

Loosely based on the example in Head First C Chapter 10
With modifications by Sam Daitzman

Note to self:
- pipe end 0 is the read end
- pipe end 1 is the write end

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void error(char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

void parent_code(int pipe_to_child[], int pipe_to_parent[]) {
    // close the read end of pipe to child
    close(pipe_to_child[0]);

    // write a string to the child
    char line[] = "I'm proud of you, child.";
    ssize_t size = write(pipe_to_child[1], line, strlen(line)+1);
    if (size == -1) error("Parent can't write to child");
    printf("Parent wrote %ld bytes\n", size);



    // close write side of parnet pipe
    close(pipe_to_parent[1]);

    // initialize a buffer
    int count = 128; // TODO: ask why 128 is a good idea for this...
    char buffer[count];

    // read from pipe from child
    ssize_t rsz = read(pipe_to_parent[0], buffer, count);
    if(rsz == -1) error("Parent failed to read from child");
    printf("Parent read %ld bytes from child. Got %s\n", rsz, buffer);


}


void child_code(int pipe_to_child[], int pipe_to_parent[]) {
    // close the write end of pipe to child
    close(pipe_to_child[1]);

    // make a new buffer
    int count = 128;
    char buffer[count];

    // read from pipe_to_child
    ssize_t size = read(pipe_to_child[0], buffer, count);
    if (size == -1) error("Child can't read from parent");
    printf("Child read %ld bytes.\n", size);
    printf("Child read: %s\n", buffer);


    // write a string to the parent
    char send[] = "Hello my parent :0";
    ssize_t wrsz = write(pipe_to_parent[1], send, strlen(send));
    if(wrsz == -1) error("Failed to write data to my parent");
    printf("Child wrote %ld bytes containing %s\n", wrsz, send);
    exit(0);
}


int main(int argc, char *argv[]) {
    // create pipes
    int pipe_to_child[2];
    int pipe_to_parent[2];

    // try opening pipes
    if (pipe(pipe_to_child) == -1) error("Can't create the pipe to child");
    if (pipe(pipe_to_parent) == -1) error("Can't create the pipe to parent");

    /*Fork a child process*/
    pid_t child_pid = fork();
    if (child_pid == -1) error("Can't fork process");

    if (child_pid == 0) {
        child_code(pipe_to_child, pipe_to_parent);
    } else parent_code(pipe_to_child, pipe_to_parent);

    int status;
    pid_t pid = wait(&status);
    if (pid == -1) error("Error waiting for child process");
    printf("Child %d exited with code %d\n", pid, status);
}
