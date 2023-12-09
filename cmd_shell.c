#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
	char *ptr , cmd[512] , *args[32] ;
	int i , ret , err, s ;
	while(1) {
		printf("Order_boss> ") ;
		gets(cmd) ;

		i= 0 ;
		ptr = strtok(cmd , " ") ;
		args[i] = ptr ;
		i++ ;
		do{
			ptr = strtok(NULL , " " ) ;
			args[i] = ptr ;
			i++ ;
		} while(ptr != NULL) ;

		if(strcmp (args[0] , "exit") == 0) 
			_exit(0) ;
		else if (strcmp(args[0] , "cd") == 0) 
			chdir(args[1] ) ;
		else{
			ret = fork() ;
			if(ret == 0) {
				err = execvp(args[0] , args) ;
				if(err<0) {
					perror ("Sorry sir i'm not able to complete the Order") ;
					_exit(1) ;
				}
			}
			else 
				waitpid(-1 , &s , 0) ;
		}
	}
	return 0 ;
}
