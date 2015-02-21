/*
source: 
1. APUE.3e P.187  <图8-3 vfork 函数实例>


edit by: agena 2015.02.20

*/

/*
执行:

a. 交互式运行
$ ./a.out 

*/

/*
1. 对比fork()与vfork()的区别
2. vfork(): 保证子进程先运行,在子进程调用exec或exit()之后父进程才可能被调度
3. exit()与_exit()的区别?

*/

#include "apue.h"

int globvar = 6;

int 
main(void)
{
	int var;
	pid_t pid;

	var = 88;
	printf("before vfrok\n");
	if((pid = vfork()) < 0){
		//err_sys("vfork error");
		printf("vfork error");	
	} else if (pid == 0){
		globvar++;
		var++;
		_exit(0);		/* exit() */
	}
	
	/* 父进程继续执行 */
	printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
	exit(0);
}















