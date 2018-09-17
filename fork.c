#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include  <sys/wait.h>
#include <unistd.h>

#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED 1 /* XPG 4.2 - needed for WCOREDUMP() */


void vypsatUdaje(char *label)
	{
		printf("%s identification: \n", label);
		printf("	pid = %d,	ppid = %d,	pgrp = %d\n", (int)getpid(), (int)getppid(), (int)getpgrp());
		printf("	uid = %d,	gid = %d\n", (int)getuid(), (int)getgid());
		printf("	euid = %d,	egid = %d\n", (int)geteuid(), (int)getegid());		
	}

void ukonceni(char *label, int status)
{
	printf("%s exit (pid = %d):", label, (int)getpid());
	if(WIFEXITED(status)){
		printf("	normal termination (exit code = %d)\n", status);
	}else{
		if(WIFSIGNALED(status)){
			printf("	signal termination %s(signal = %d)\n","",WTERMSIG(status)); 
		}else{
			printf("	unknown type of termination\n");
		}
	}
}
	
int main(int argc, char *argv[]){

	int status, status2;
	pid_t pid;
	vypsatUdaje("grandparent");
//	char *argv = {"-all"};
//	char *const params = { "/bin/echo", "hello", NULL };
//	char *params[4]  = {"/bin/ls", "-l",0};

	if((pid = fork()) > 0) {
		wait(&status);
	//	ukonceni("grandparent", status);

	//	printf ("grandparent done\n");			
	} else {
		pid_t pid2;
		vypsatUdaje("parent");
		if ((pid2 = fork()) > 0) {
			wait(&status2);
			ukonceni("child", status2);
			ukonceni("parent", status2);
		
	//		sleep(1);
	//		printf ("parent up\n");
		} else {
			vypsatUdaje("child");
	//		while(1){
			
	//		}
	//		execv( "/bin/ls" , params);
	//		sleep(1);
	//		printf ("child wake up\n");
			execvp(argv[1], &argv[1]);
	//		execv("/bin/echo", argv);
			ukonceni("child", status2);
		}
		
	}



	return 0;
}