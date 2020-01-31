#include <stdio.h>

int main() {
    int x = 5;
    printf("Hello, World!\n");
    return 0;
}

/* 

All compilations were performed on macOS 10.15.3
    with gcc from XCode Developer Tools

Files and observations:
- unmodified.s is the original assembly code
- addedInt.s is the assembly code after adding 'int x = 5'
    Diff photo is committed as file 'diff after adding int x = 5.png'
    On line 15, we see a new line 'movl	$5, -8(%rbp)'
    I think that line is adding the int value 5 to a particular memory location
    Later in the file, I see a line 'movl	%eax, -12(%rbp)'
    That line may be changing the amount of reclaimed memory. I'm unsure.
- 










*/