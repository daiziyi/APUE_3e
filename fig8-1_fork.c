
/*
source: 
1. APUE.3e P.183  <fork 函数实例>


edit by: agena 2015.02.17

*/

/*
执行:

a. 交互式运行
$ ./a.out

b. 标准输出重定向
$ ./a.out > temp.out
*/


#include "apue.h"
int globvar = 6;	/* external variable */
char buf[] = "a write to stdout\n";

int
main(void)
{
	int var;	/* automatic variable on the stack */
	pid_t pid;
	var = 88;

	/* write函数: 不帶缓冲  */
	/* strlen 与 sizeof的区别??? */
	if(write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
	{
		//err_sys("write error");
		printf("write error");
	}
	printf("before fork\n");

	if((pid = fork()) < 0)		
	{
		//err_sys("fork error");
		printf("fork error");
	}
	else if (pid == 0)			/* 子进程 */
	{
		globvar++;
		var++;
	}
	else 						/* 父进程*/
	{
		sleep(2);				/*阻塞,让子进程先执行! */
	}

	/*在标准重定向执行时,将输出再次 */
	printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
	exit(0);
}




