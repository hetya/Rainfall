#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char c[50];

void m(void) {
  time_t t;

  t = time(0);
  printf("%s - %d\n", c, (int)t);
  return;
}

int main(int ac, char **av) {
  char *buff;
  char *buff_2;
  FILE *file;

  buff = malloc(8);
  buff[0] = 1;
  buff[4] = malloc(8);

  buff_2 = malloc(8);
  buff_2[0] = 2;
  buff_2[4] = malloc(8);

  strcpy(buff[4], av[1]);
  strcpy(buff_2[4], av[2]);

  file = fopen("/home/user/level8/.pass","r");
  fgets(c, 68, file);
  puts("~~");
  return 0;
}