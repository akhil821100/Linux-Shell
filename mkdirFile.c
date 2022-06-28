#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<stdlib.h>
#include<string.h>


// Tu shell.c file mein /name/ ke andar wale strings ko ek saath karke yahan bhej
//  TU special charater /name/ ka use kar for above purpose 


int main(int argc, char const *argv[])
{
	//printf("Entered\n");
	if ((argc == 2) && (strcmp(argv[1], "--help") == 0)) {
		printf("Creates Directory\n");
		printf("Options:\n");
		printf("-v: It prints the name of the directories, after creating it.\n");
		printf("--help: Prints information about this command\n");
		exit(0);
	}
	else if ((argc >= 3) && (strcmp(argv[1], "-v") == 0)) {
		for (int i = 2; i < argc; i++) {
			int status = mkdir(argv[i], 0777);
			if (status == -1) {
				printf("Error: Directory %s can't be created\n", argv[i]);
			}
			else {
				printf("mkdir: created Directory %s\n", argv[i]);
			}
		}
		exit(0);
	} 
	else if (argc >= 2 && (argv[1][0] == '"' && argv[argc - 1][strlen(argv[argc - 1]) - 1] == '"')) {
		char myDir[400] = "";
		//argv[argc - 1][strlen(argv[argc - 1]) - 1] = '\0';
		//argv[1] = argv[1] + 1;
		for (int j = 1; j < argc; j++) {
			strcat(myDir, argv[j]);
			if (j != argc - 1) {
				strcat(myDir, " ");
			}
		}
		//myDir = myDir + 1;
		int len = strlen(myDir);
		myDir[len-1] = '\0';
		char* myDir1 = myDir;
		myDir1 = myDir1 + 1;
		mkdir(myDir1, 0777);
		exit(0);
	}
	else if ((argc >= 2) && (strcmp(argv[1], "-v") != 0)) {
		for (int i = 1; i < argc; i++) {
			int status = mkdir(argv[i], 0777);
			if (status == -1) {
				printf("Error: Directory %s can't be created\n", argv[i]);
			}
		}
		exit(0);
	}

	
	
	else {
		printf("Error : There is an error in the arguments or options\n");
		exit(1);
	}
	
	/*int status = mkdir("testDir1/testDir2", 0777);       // Agar dirctory pehle se hi hain, toh bhi yeh bana deta hain. So, done
	if (status == -1) {
		printf("Error: Directory can't be created.");
		exit(1);
	}
	else {
		exit(0);
	}*/
}

