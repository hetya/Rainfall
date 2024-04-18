void main(void) {
    p();
    return;
}


void p(void) {
	unsigned int	check;
	char			local50[76];

    fflush(stdout);
    gets(local50);
    if ((check & 0xb0000000) == 0xb0000000) {
        printf("(%p)\n", check);
        exit(1);
    }
    puts(local50);
    strdup(local50);
    return;
}
