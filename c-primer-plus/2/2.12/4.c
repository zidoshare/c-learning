#include "stdio.h"

void jolly()
{
  printf("For he's a jolly good fellow!\n");
}

void deny()
{
  printf("Which nobody can deny\n");
}

int main()
{
  int i = 3;
  while(i--)
  {
    jolly();
  }
  deny();
  return 0;
}
