#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char const *argv[])
{
	if (argc == 1) {
		while (1) {
			char* line;
			size_t bSize = 0;
			int status = getline(&line, &bSize, stdin);          // lines are having new line character at the end
			printf("%s", line);
			if (status == -1) {
				if (feof(stdin)) {
      				exit(0);  
    			}
    			else {
    				printf("Error: There occurs a system call error while reading the input\n.");
    				exit(1);
    			} 
			}
		}
	}
	else if ((argc == 2) && (strcmp(argv[1], "--help") == 0)) {
		printf("If you do not provide any argument and just press enter, then whatever text you will print, it will print exactly the same text again\n");
		printf("If you specify the file names as arguments, then it will print the contents of the files. (You can provide more than one file at a time as argument).\n");
		printf("Options: \n");
		printf("-n: It will print the contents of the files by printing the line number also.\n");
		printf("2)	–help: Prints information about this command\n");
		exit(0);
	}
	else if ((argc >= 2) && (strcmp(argv[1], "-n") != 0)) {                     
		for (int i = 1; i < argc; i++) {
			FILE *fptr = fopen(argv[i], "r");
			if (fptr == NULL) {          
				printf("Error: File %s does not exist", argv[i]);
				exit(1);                  // Tujhe isko use karne ke liye niche waitpid() mein parameter 0 se hatkar kuch aur karna padega.
			}
			char line[350];
			//int lineNum = 1;
			while (fgets(line, sizeof(line), fptr) != NULL) {
				printf("%s", line);
			}
			fclose(fptr);
		}
		exit(0);
	}
	else if ((argc >= 3) && (strcmp(argv[1], "-n") == 0)) {
		int lineNum = 1;
		int isLineNumInc = 1;
		for (int i = 2; i < argc; i++) {
			FILE *fptr = fopen(argv[i], "r");
			if (fptr == NULL) {          
				printf("Error: File %s does not exist", argv[i]);
				exit(1);                  // Tujhe isko use karne ke liye niche waitpid() mein parameter 0 se hatkar kuch aur karna padega.
			}
			char line[350];
			while (fgets(line, sizeof(line), fptr) != NULL) {
				if (isLineNumInc == 1) {
					printf("    %d  %s", lineNum, line);
				}
				else {
					printf("%s", line);
				}
				
				int len = strlen(line);
				if (line[len - 1] == '\n') {
					lineNum = lineNum + 1;
					isLineNumInc = 1;
				}
				else {
					isLineNumInc = 0;
				}
			}
			fclose(fptr);
		}
		exit(0);
	}
	else {
		printf("Error: Error : There is an error in the arguments or options\n");
		exit(1);
	}
}