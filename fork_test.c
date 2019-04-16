#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void InitialDisplay(int tHeight,int cNumber)
{
		printf("\nPid:(%d)\tProcess Starting",getpid());
		printf("\nPid:(%d)\tParent's ID:%d",getpid(),getppid());
		printf("\nPid:(%d)\tHeight of the tree(H): %d\n",getpid(),tHeight);
}

void FunctionChild(int tHeight,int cNumber, pid_t pid)
{
		char tempHeight_1[50]; //Temp for Execv
		char tempChild[50]; //Temp for Execv
		sprintf(tempHeight_1,"%d",tHeight); // Sending h to execv
		sprintf(tempChild,"%d",cNumber); // sending c child to execv
		
		printf("\nPid:(%d)\tCreating (C): %d childeren at height(H-1): %d\n",getppid(),cNumber,tHeight);
		
		char *argExe[] = {"./fork",tempHeight_1,tempChild,NULL}; // char array for execv	
		int eReturn = execv(argExe[0],argExe); 	
			
			if(eReturn==-1) // if execv return's error
			{
				printf("Error: Execv Failed\n");
				exit(1);
			}
}

void FunctionParent(int child)
{
		int i;
		for(i=0; i<child;i++) // Parent waiting untill all child proccess are over 
		{
			wait(NULL);
		} 
}		

int main(int argc, char *argv[])  // Step 1
{
	int tHeight = atoi (argv[1]); 
	int cNumber = atoi (argv[2]);
		pid_t pid;
	if(argc==3)
	{
		InitialDisplay(tHeight,cNumber); //Step 2

		if(tHeight>1)	// Step 3
		{
			int status;
			int cCount=0;
			for(cCount = 0; cCount<cNumber; cCount++)
			{
				pid = fork();
				if(pid == -1)
				{
					printf("Error: Fork Failed\n");
					exit(0);
				}
			    if(pid == 0) // in child process
				{
					FunctionChild(tHeight-1,cNumber,pid);
				}
				if(pid >1)	// in Parent Process
				{
					FunctionParent(cNumber);
				}
			}
		}
	}
	else
	{
		printf("Error: Invalid inputs- Enter 2 integer inputs\n");
	}
	printf("\nPid:(%d)\tProcess terminating at height: %d\n",getpid(),tHeight); // Termination Print
	return 0;
}