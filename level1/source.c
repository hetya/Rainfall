#include <stdio.h>

void run(void) {
	printf("Good... Wait what?\n");
	system("/bin/sh");
	return;
}

int main(void) {
    char local_50[76];

    gets(local_50);
    return 0;
}