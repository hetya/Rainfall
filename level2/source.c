#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void p(void) {
	unsigned int	addr;
	char			charset[64];
    const void      *pointer;

    fflush(stdout);
    gets(charset);
    pointer = (const void *)addr;
    if ( (addr & 0xB0000000) == -1342177280 ) {
        printf("(%p)\n", pointer);
        exit(1);
    }
    puts(charset);
    strdup(charset);
    return;
}

void main(void) {
    p();
    return;
}