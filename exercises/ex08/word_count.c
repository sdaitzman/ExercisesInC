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
    GList* list = NULL;
    list = g_list_append(list, "Hello world!");
    printf("The first item is '%s'\n", (char *) g_list_first(list)->data);

    gsize length;
    gchar *content, *filename = "file.txt";
    if(g_file_get_contents(filename, &content, &length, NULL)) {
        printf("Got %s\n", content);

        g_strchomp(content);

        gchar *space = " ";
        gchar *nl = "\n";

        gchar **words = g_strsplit(content, space, 999);

        // TODO: look into https://developer.gnome.org/glib/stable/glib-Lexical-Scanner.html

        gchar *current = words[0];
        int i = 0;
        while(current != NULL) {
            current = words[i];
            printf("Output: %s\n", current);
            i++;
        }

    } else {
        printf("Failed to parse file, unfortunately.");
        return 1;
    }


    return 0;
}
