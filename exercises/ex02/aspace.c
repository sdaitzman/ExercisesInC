/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int var1;

void localVar(int number) {
    int local = number;
    printf ("Address of local is %p\n", &local);
}

int main ()
{
    int var2 = 5;

    void *p = malloc(128);
    void *q = malloc(128);

    char *s = "Hello, World";
 
    printf (" Address of main is %p\n", main);
    printf (" Address of var1 is %p\n", &var1);
    printf (" Address of var2 is %p\n", &var2);
    printf ("        p points to %p\n", p);
    printf ("        p points to %p\n", &*p);

    printf ("        q points to %p\n", q);
    printf ("    Address of q is %p\n", &q);

    printf ("    Address of p is %p\n", &p);
    printf ("        s points to %p\n", s);
    printf ("    Address of s is %p\n", &s);

    localVar(10);

    return 0;
}
