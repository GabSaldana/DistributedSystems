#include <sys/types.h>
#include <stdio.h>

main()
{
   pid_t pid;
   int j;

   for(j = 0; j < 10; j++){
      
      pid = fork();
       if(pid != 0){
	   wait(NULL);	
	   sleep(3);
       }
	else if(pid == 0){
	   printf("El padre del proceso %d es %d, j = %d\n", getpid(), getppid(), j);
	   exit(0);
	}
	else{
	   printf("Error\n");
	   exit(1);
	}
   }

}

