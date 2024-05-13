#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char c[50]; /* size ??? */

void m(void) {
  time_t t;

  t = time(0);
  printf("%s - %d\n", c, (int)t);
  return;
}

int main(int ac, char **av) {
  char *eax;
  char *eax_4;
  FILE *file;

  eax = malloc(8);
  eax[0] = 1;
  eax[4] = malloc(8);

  eax_4 = malloc(8);
  eax_4[0] = 2;
  eax_4[4] = malloc(8);

  strcpy(eax[4], av[1]);
  strcpy(eax_4[4], av[2]);

  file = fopen("/home/user/level8/.pass","r");
  fgets(c, 68, file);
  puts("~~");
  return 0;
}