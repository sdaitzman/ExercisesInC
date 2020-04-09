/*

word_count.c
Sam Daitzman // 2020
Reads a text file, splits lines into words, and counts the frequency of each word.
Prints the results to stdout.

*/

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>



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
        GHashTable *wordCount = g_hash_table_new(&g_str_hash, &g_str_equal);

        // iterate through parsed words
        int i = 0;
        while(current != NULL) {
            // print current word for debugging
            printf("Output: %s\n", current);

            if(!g_hash_table_contains(wordCount, current)){
                // set initial value to compound literal pointer to 1
                g_hash_table_insert(wordCount, current, &((int){1}));
                printf("Did not contain %s\n", current);
            } else {
                gint *val = g_hash_table_lookup(wordCount, current);
                *val = *val + 1;
                printf("Did contain %s with count %i\n", current, *val);
            }

            // iterate to next word
            i++;
            current = words[i];
        }


    } else {
        printf("Failed to parse file, unfortunately.");
        return 1;
    }

    // program reached end with no errrors
    return 0;
}
