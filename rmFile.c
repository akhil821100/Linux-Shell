#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char const *argv[])
{	
	if ((argc >= 3) && (strcmp(argv[1], "-i") == 0)) {
		for (int i = 2; i < argc; i++) {
			printf("rm: Do you really want to delete the file %s (y/n)", argv[i]);
			char ans[100];
			scanf("%s", ans);
			//printf("%s", ans);
			//printf("cool");
			if (strcmp(ans, "y") == 0) {
				int status = remove(argv[i]);
				if (status == -1) {
					printf("Error: Directory %s can't be created\n", argv[i]);
				}
			}
			else if (strcmp(ans, "n") == 0) {

			}
			else {
				printf("You can only give y or n as input\n");
				i = i - 1;
			}
		}
		exit(0);
	} 
	else if ((argc == 2) && (strcmp(argv[1], "--help") == 0)) {
		printf("rm: Removes the specified files\n");
		printf("Options:\n");
		printf("-i: It asks a warning message that do you really want to delete the file. (Answer has to entered either y or n).\n");
		printf("–help: Prints information about this command.\n");
		exit(0);
	}
	else if ((argc >= 2) && (strcmp(argv[1], "-i") != 0)) {
		for (int i = 1; i < argc; i++) {
			int status = remove(argv[i]);
			if (status == -1) {
				printf("Error: File %s can't be deleted\n", argv[i]);
			}
		}
		exit(0);
	}

	
	
	else {
		printf("Error : There is an error in the arguments or options\n");
		exit(1);
	}

	/*
	int status = remove("test1.txt");
	printf("%d", status);
	*/
}