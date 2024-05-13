#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void n(void)
{
  system("/bin/cat /home/user/level7/.pass");
  return;
}

void m(void *param_1,int param_2,char *param_3,int param_4,int param_5)
{
  puts("Nope");
  return;
}

int main(int ac,char **av) {
  char *dest;
  void (*buff)(void);

  dest = (char *)malloc(64);
  buff = malloc(4);
  buff = &m;
  strcpy(dest, av[1]);
  buff();
  return 0;
}