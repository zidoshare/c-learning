#include <stdio.h>

// int *：用来表示接收地址
void swap(int *a,int *b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

int main(int argc,const char *argv[]){
  int a = 3, b = 5;
  int *p ;
  p = &a;
  printf("p变量的值为：%d\n",*p);
  swap(&a, &b);
  printf("a=%d; b=%d\n",a,b);
  return 0;
}
