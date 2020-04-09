/*

word_count.c
Sam Daitzman // 2020
Reads a text file, splits lines into words, and counts the frequency of each word.
Prints the results to stdout.

*/

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

void print_hash_table(gpointer key, gpointer value, gpointer user_data) {
    printf("%s: %i\n", (char*) key, *(int*) value);
}

int main(int argc, char** argv) {
    // holds the size of the file
    gsize length;

    // declares content and filename strings
    gchar *content, *filename = "file.txt";

    // fileparsing check
    if(g_file_get_contents(filename, &content, &length, NULL)) { 
        
        // printf("Got %s\n", content);

        // switches to the familiar JS regex parser (can use logical (OR |) to
        // set multiple option flags in this enum
        GRegexCompileFlags regexflags =
            (GRegexCompileFlags) (G_REGEX_JAVASCRIPT_COMPAT);
        
        // turns on regex matching for carriage returns
        GRegexMatchFlags matchflags =
            (GRegexMatchFlags) (G_REGEX_MATCH_NEWLINE_CRLF);

        // match spaces (\040) or newlines(\n), and some punctuation
        gchar *pattern = "\040|\n|;|,|[.]";
        gchar **words = g_regex_split_simple(pattern, content, regexflags, 0);

        // pointer to current parsed word
        gchar *current = words[0];

        // declare a hash table to track word counts
        GHashTable *wordCount = g_hash_table_new(g_str_hash, g_str_equal);


        // iterate through parsed words
        int i = 0;
        while(current != NULL) {
            // print current word for debugging
            // printf("Output: %s\n", current);

            // if the current word is not yet in the hashmap, add it
            if(!g_hash_table_contains(wordCount, current)){
                // set initial value to compound literal pointer to 1
                int initialValue = 1;
                int *initialPointerVal = &initialValue;
                g_hash_table_insert(wordCount, current, initialPointerVal);
                // printf("%s \t: added, now of length %i\n", current, g_hash_table_size(wordCount));
            } else {
                // iterate the word in the hashmap

                // increase value by 1
                int val = *(int*) g_hash_table_lookup(wordCount, current) + 1;
                int *valPointer = &val;

                // set value in hashmap
                g_hash_table_replace(wordCount, current, valPointer);

                // print current status
                // printf("%s \t: iterated to %i in hashmap of length %i\n", current, *valPointer, g_hash_table_size(wordCount));
            }

            // iterate to next word
            i++;
            current = words[i];
        }

        g_hash_table_foreach(wordCount, print_hash_table, NULL);


    } else {
        printf("Failed to parse file, unfortunately.");
        return 1;
    }

    // these are 261238937 and 193491849 which do not collide
    // printf("%i\n", g_str_hash("hello"));
    // printf("%i\n", g_str_hash("foo"));

    // program reached end with no errrors
    return 0;
}
