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

int main(int argc, char **argv) {
  char *tab;
  char *tab_2;
  FILE *file;

  tab = malloc(8);
  tab[0] = 1;
  tab[4] = malloc(8);

  tab_2 = malloc(8);
  tab_2[0] = 2;
  tab_2[4] = malloc(8);

  strcpy(tab[4], argv[1]);
  strcpy(tab_2[4], argv[2]);

  file = fopen("/home/user/level8/.pass","r");
  fgets(c, 68, file);
  puts("~~");
  return 0;
}