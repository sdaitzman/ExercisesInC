/* Example from Head First C.

Downloaded from https://github.com/twcamper/head-first-c

Modified by Allen Downey.
Modified again by Sam Daitzman.

*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


void error(char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int main(int argc, char *argv[]) {
    pid_t pid;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <search phrase>\n", argv[0]);
        return 1;
    }
    const char *PYTHON = "/usr/bin/python2";
    const char *SCRIPT = "rssgossip.py";
    char *feeds[] = {
        "http://www.nytimes.com/services/xml/rss/nyt/Africa.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/Americas.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/MiddleEast.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/Europe.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/AsiaPacific.xml"
    };
    int num_feeds = 5;
    char *search_phrase = argv[1];
    char var[255];
    int status;

    for (int i=0; i<num_feeds; i++) {

        // create forks
        pid = fork();
        if(pid < 0) {
            error("An error occurred in forking the process.");
        } else if(pid == 0) {
            sprintf(var, "RSS_FEED=%s", feeds[i]);
            char *vars[] = {var, NULL};
            int res = execle(PYTHON, PYTHON, SCRIPT, search_phrase, NULL, vars);
            if (res == -1) error("Can't run script.");
        }

        // handle waits
        pid = wait(&status);
        if(pid < 0) error("wait() encountered some error.");
        status = WEXITSTATUS(status);
        if(status != 0) fprintf(stderr, "Process error: %d\n", status);

    }
    return 0;
}
