#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/* For this class I used code from here: https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html */

static struct termios orig_termios; /* global, need to change that later */

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); 
}

void enableRawMode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

char getInput(){
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) != 1) {
        c = '\0';
    }
    return c;
}
