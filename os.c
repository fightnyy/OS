#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

//fork 쓰면 child 에게는 0이 반환되고 parent에게는 자식의 pid(processor id)값이 반환된다. 실패하면 parent 에게는 -1이 반환되고 child도 만들어지지 않는다. 
//또한 에러번호도 적절하게 세팅된다.

void forkexample()
{
    pid_t pid;
    if((pid=fork())==0)
    {
        printf("I am %d, a child of %d\n",getpid(),getppid());
    }
    else
    {
       printf("I am %d, a parent of %d\n",getpid(),pid);
    }
    
}

int main()
{
   forkexample();
   return 0;
}