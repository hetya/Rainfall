#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int		main(int argc, char **argv)
{
	int		nb;
	char	str[40];

	nb = atoi(argv[1]);
	if (nb > 9)
		return (1);
	memcpy(str, argv[2], nb * 4);
	if (nb == 1464814662)
		execl("/bin/sh", "sh", NULL);
	return (0);
}