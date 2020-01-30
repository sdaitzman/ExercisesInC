/* 
* A card-counting program, split into functions
 * Copyright 2020 Sam Daitzman
 * CC-BY-SA all content I have the power to license
 * Based on code from "Head First C"
 * Created as part of Software Systems at Olin College
 */

#include <stdio.h>
#include <stdlib.h>



/*  Calculates value of current card
    int card: number of card (1-11) */
int card_value(int val) {
    // printf("%i",val);
    if((val > 2) && (val < 7)) {
        return 1;
    } else if(val == 10) {
        return -1;
    }
    return 0;
}

/*  Runs the main program loop
    Process returns 0 when user inputs 'X' */
int main() {
    // declare a char array
    char card_name[3];
    int count = 0;
    do {
        puts("Enter the card_name: ");
        
        // scan for two characters worth of character string (1 null is added)
        scanf("%2s", card_name);
        int val = 0;
        switch(card_name[0]) {
        case 'K':
        case 'Q':
        case 'J':
            val = 10;
            break;
        case 'A':
            val = 11;
            break;
        case 'X':
            continue;
        default:
            val = atoi(card_name);
            if((val < 1) || (val > 10)) {
                puts("I don't understand that value.");
                continue;
            }
        }
        count += card_value(val);
        printf("Current count: %i\n", count);
    } while (card_name [0] != 'x');
    return 0;
}