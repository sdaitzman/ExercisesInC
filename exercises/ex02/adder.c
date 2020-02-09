/*
A program that adds a series of integers, separated by newlines
Copyright 2020 Sam Daitzman
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxInputLength 20
#define maxInts 5

int add() {
    return 0;
}

int getInput() {
    return 0;
}



int main() {
    
    printf("\n > ");

    char userInput[maxInputLength];
    int nums[maxInts];
    int count = 0;

    while(fgets(userInput, maxInputLength, stdin) != NULL) {
        int n = atoi(userInput);

        if(strlen(userInput) < 2) {
            printf("Hmm, I don't think you input anything. Try again maybe?\n");
        } else if(n == 0) {
            printf("Hmm, I don't think that: %s is a valid number.\n", userInput);
        } else {
            printf("Got %i for %i-th number.\n", n, count);
            nums[count++] = n;
        }
        printf("\n > ");
    }

    printf("Adding!");

    return 0;
}