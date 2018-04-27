#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
  //printf(1, "Hello World!!\n");
  int param = 0;
  param = atoi(argv[1]);
  if(param ==1){
	info(1);
  }else if(param ==2){    
   	info(2);
	for(int i =0;i<5 ;i++)
	  hello();
	info(2);
  }else if(param ==3){
	info(3);
  }else{
	printf(1, "unexpect input!! usage: test [1|2|3]\n");
  }

  exit();
}

