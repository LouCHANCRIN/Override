#include <stdio.h>
#include <bufings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/prctl.h>

int			main(void)
{
	int     i = 0;
	char    buf[128];
	int	    j;		
	int	    k;
	int	    l;
	pid_t   pid;

	pid = fork();
	bzero(&(buf[0]), 128);
	if (pid == 0)
	{
		prctl(1, 1);
		ptrace(0, 0, 0, 0);
		puts("Give me some shellcode, k");
		gets(&(buf[0]));
		return (0);
	}
	do
	{
		wait(&i);
		if ((i & 127) == 0 || ((i & 127) + 1) / 2 > 0)
		{
			puts("child is exiting...");
			return (0);
		}
	} while (ptrace(3, pid, 44, 0) != 11);
	puts("no exec() for you");
	kill(pid, 9);
	return (0);
}