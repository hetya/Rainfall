#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char c[4242];

int main(int param_1,int param_2)
{
  int *puVar1;
  void *pvVar2;
  int *puVar3;
  FILE *__stream;
  
  puVar1 = (int *)malloc(8);
  *puVar1 = 1;
  pvVar2 = malloc(8);
  puVar1[1] = pvVar2;
  puVar3 = (int *)malloc(8);
  *puVar3 = 2;
  pvVar2 = malloc(8);
  puVar3[1] = pvVar2;
  strcpy((char *)puVar1[1],*(char **)(param_2 + 4));
  strcpy((char *)puVar3[1],*(char **)(param_2 + 8));
  __stream = fopen("/home/user/level8/.pass","r");
  fgets(c,0x44,__stream);
  puts("~~");
  return 0;
}


int m()
{
    return printf("%s - %d\n", 0x8049960, time(0));
}