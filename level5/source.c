#include <stdio.h>
#include <stdlib.h>

void o(void) {
  system("/bin/sh");
  exit(1);
}

void n(void) {
  char var_20c[520];

  fgets(var_20c, 512, stdin);
  printf(var_20c);
  exit(1);
}

int main(void) {
  n();
  return 0;
}