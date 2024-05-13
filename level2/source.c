#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void p(void) {
	unsigned int	retaddr;
	char			s[64];
    const void      *v2;

    fflush(stdout);
    gets(s);
    v2 = (const void *)retaddr;
    if ( (retaddr & 0xB0000000) == -1342177280 ) {
        printf("(%p)\n", v2);
        exit(1);
    }
    puts(s);
    strdup(s);
    return;
}

void main(void) {
    p();
    return;
}