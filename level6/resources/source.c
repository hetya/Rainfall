#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void n(void)
{
  system("/bin/cat /home/user/level7/.pass");
  return;
}

void m(void)
{
  puts("Nope");
  return;
}

int main(int argc,char **argv) {
  char *dest;
  void (*func_pointer)(void);

  dest = (char *)malloc(64);
  func_pointer = malloc(4);
  func_pointer = &m;
  strcpy(dest, argv[1]);
  func_pointer();
  return 0;
}