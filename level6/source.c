int main(int argc, char const *argv[])
{
    
    return 0;
}

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
  void (*ppcVar1)(void);

  dest = (char *)malloc(64);
  ppcVar1 = malloc(4);
  ppcVar1 = &m;
  strcpy(dest, av[1]);
  ppcVar1();
  return 0;
}