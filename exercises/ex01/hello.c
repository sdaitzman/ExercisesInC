#include <stdio.h>

int main() {
    int x = 5;
    int y = x + 1;
    printf("%i",y);
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
- optimized2.s is the assembly code after compiling with the flag -O2
    Lots of lines have been removed entirely!! Specifically: lines 13-22
    In the new file, lines 13-15 are added and quite different
- printX.s is the assembly code after switching to print x (not Hello World)
    I compiled this without optimizations turned on. I notice that 
    a couple lines changed, but surprisingly few. There's an interesting line in
    the resulting file at line 30, where the string "%i" appears in the Assembly
- printXO2.s contains the optimized version of the above
    I notice a similar result to before, with many fewer lines in a similar way
- The same pattern continues for PrintY.s and PrintYO2.s
    I noticed that PrintY has lots of movl operations in particular.










*/