/*
A program that adds a series of integers, separated by newlines
Copyright 2020 Sam Daitzman
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxInputLength 12
#define maxInts 12

int add(int* nums, int count) {
    int total = 0;
    for(int i = 0; i < count; i++) {
        total += nums[i];
    }
    return total;
}

int parseInput(char* userInput) {
    if(strlen(userInput) < 2) {
        printf("Hmm, I don't think you input anything. Try again maybe?\n");
        return 0;
    } else if(atoi(userInput) == 0) {
        printf("Hmm, I don't think that: %s is a valid number.\n", userInput);
        return 0;
    } else {
        printf("Got %i.\n", atoi(userInput));
        return atoi(userInput);
    }
    return 0;
}



int main() {
    
    printf("\n > ");

    char userInput[maxInputLength];
    int nums[maxInts];
    int count = 0;

    while(fgets(userInput, maxInputLength, stdin) != NULL) {

        if(strlen(userInput) >= maxInputLength - 1) {
            // TODO: talk to Allen about why these 
            printf("EXITING. Oh no that was too long! Please enter numbers of max length %i\n",maxInputLength-3);
            return 1;
        }

        int n = parseInput(userInput);
        if(n) nums[count++] = n;
        

        if(count >= maxInts) {
            printf("Max numbers reached. Calculating total...\n\n");
            break;
        }

        printf("\n > ");
    }

    int total = 0;

    for(int i = 0; i < count; i++) {
        total += nums[i];
    }

    printf("Added! Total: %i\n", add(nums, count));

    return 0;
}