#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int lang = 0;

void greetuser(char *user)
{
	char buffer[64];

	if (lang == 1)
	{
		strcpy(buffer, "Hyvää päivää ");
	}
	else if (lang == 2)
	{
		strcpy(buffer, "Goedemiddag! ");
	}
	else if (lang == 0)
	{
		strcpy(buffer, "Hello ");
	}
	strcat(buffer, user);
	puts(buffer);
}

int main(int argc, char **argv)
{
	char	buffer[72];
	char	*env = NULL;

	if (argc != 3)
		return 1;

	memset(buffer, 0, 72);
	strncpy(buffer, argv[1], 40);
	strncpy(&buffer[40], argv[2], 32);
	env = getenv("LANG");
	if (env != 0)
	{
		if (memcmp(env, "fi", 2) == 0)
		{
			lang = 1;
		}
		else if (memcmp(env, "nl", 2) == 0)
		{
			lang = 2;
		}
	}

	greetuser(buffer);
	return 0;
}