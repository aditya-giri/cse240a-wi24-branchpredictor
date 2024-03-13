#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "predictor.h"

void usage();
int handle_option(char *arg);
int read_branch(uint32_t *pc, uint8_t *outcome);

// Have to update
void usage() {
    printf("Usage: predictor <options> [<trace>]\n");
    printf("       bunzip -kc trace.bz2 | predictor <options>\n");
    printf(" Options:\n");
    printf(" --help       Print this message\n");
    printf(" --verbose    Print predictions on stdout\n");
    printf(" --<type>     Branch prediction scheme:\n");
    printf("    static\n"
           "    gshare:<# ghistory>\n"
           "    tournament:<# ghistory>:<# lhistory>:<# index>\n"
           "    custom\n");
}

int handle_option(char *arg) {
    // TODO
    return 1;
}

int read_branch(uint32_t *pc, uint8_t *outcome) {
    // TODO
    return 1;
}

int main(int argc, char *argv[]) {
    // TODO
    return 0;
}
