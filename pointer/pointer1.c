#include <stdio.h>

int main(void){
  //i内容为3，假设变量i本身所在的内存地址为“0x8000”
  int i = 3;
  //为指针变量p申请一块内存地址，假设地址为"0x7000"，内容为null
  int *p;
  //将i的地址存放在p内存中
  p = &i;
  printf("i 存放的内容的值：%d;\ni 的地址:%p\n\n",i,&i);

  printf("p 存放的地址的值：%p;\np 自己所在的地址：%p;\np 存放的地址所指所存放内容的值：%d\n\n",p,&p,*p);

  return 0;
}
