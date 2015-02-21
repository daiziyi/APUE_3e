/*
source: 
1. APUE.3e P.224  <计时并执行所有命令参数>


edit by: agena 2015.02.20

*/

/*
执行:

a. 交互式运行
$ ./a.out "sleep 5" "date" "man bash >/dev/null"

*/

/*
1. 打算进程的执行时间!


*/

#include "apue.h"
#include <sys/times.h>

static void pr_times(clock_t, struct tms *, struct tms *);
static void do_cmd(char *);

int 
main(int argc, char *argv[])
{
	int i;
	setbuf(stdout, NULL);		//???
	for(i = 1; i < argc; i++)
		do_cmd(argv[i]);		//每个参数为一个命令
	exit(0);	
}

static void
do_cmd(char *cmd)		//执行并统计"命令"时间
{
	struct tms tmsstart, tmsend;
	clock_t start, end;
	int	status;

	printf("\ncommand: %s\n", cmd);
	
	if((start = times(&tmsstart)) == -1)		//开始时间值
	{
		//err_sys("times error");
		printf("time error");
	}

	if((status = system(cmd)) < 0)				//执行命令
	{	
		//err_sys("system() error");
		printf("system() error");
	}

	if((end = times(&tmsend)) == -1)		//命令结束时间值
	{
		//err_sys("times error");
		printf("times error");
	}

	pr_times(end-start, &tmsstart, &tmsend);
	//pr_exit(status);		//???线程

}

static void
pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend)
{
	static long clktck = 0;
	if (clktck == 0)	
		if ((clktck = sysconf(_SC_CLK_TCK)) < 0)
		{
			//err_sys("sysconf error");
			printf("sysconf error");
		}

	printf(" real: %7.2f\n", real / (double) clktck);
	printf(" user: %7.2f\n",
		(tmsend->tms_utime - tmsstart->tms_utime) / (double) clktck);
	printf(" sys: %7.2f\n", 
		(tmsend->tms_stime - tmsstart->tms_stime) / (double) clktck);
	printf(" child user: %7.2f\n",
		(tmsend->tms_cutime - tmsstart->tms_cutime) / (double) clktck);
	printf(" child sys: %7.2f\n",
		(tmsend->tms_cstime - tmsstart->tms_cstime) / (double) clktck);
}







