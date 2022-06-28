#include<stdio.h>
#include <unistd.h> 
#include<sys/wait.h>
#include<stdlib.h> 
#include<string.h>
#include <limits.h>


void printWorkingDir();


int main() {
	char* intComArr[] = {"cd", "echo", "history", "pwd", "exit"};
	char* extComArr[] = {"date", "ls", "cat", "rm", "mkdir"};
	char* baseAddress = "/home/akhil/Desktop/Assign2/";
	char* extComFileArr[] = {"dateFile", "lsFile", "catFile", "rmFile", "mkdirFile"};
	
	
	while (1) {
		char cwd[PATH_MAX];
		getcwd(cwd, PATH_MAX);
		printf("akhil@shell:%s $ ", cwd);      

		char* line;
		size_t bSize = 0;
		getline(&line, &bSize, stdin);          // lines are having new line character at the end
		

		
		FILE *fptr1 = fopen("historyNum.txt", "r");
		int hisNoAvailable;
		fscanf(fptr1, "%d", &hisNoAvailable);
		
		fptr1 = fopen("historyNum.txt", "w");
		fprintf(fptr1, "%d", hisNoAvailable + 1);
		//char arr[] = "hello";
		//char str[] = "hello";
		//char arr[] = "hello";
		
		FILE *fptr2 = fopen("historyList.txt", "a");
		//char num[100];
		//sprintf(num, "%d", hisNoAvailable);
		fprintf(fptr2, "%d  %s", hisNoAvailable, line);
		



		//fclose(fptr1);
		//fptr1 = fopen("historyNum.txt", "r");
		//fopen("historyNum.txt", "a");
		//fopen("historyList.txt", "r");
		//fclose(fptr1);
		//fclose(fptr2);
		//free(fptr1);
		//free(fptr2);


		int len = strlen(line);
		line[len - 1] = '\0';                   // removed the new line character. String length also charges
		int noOfTokens = 1;
		for (int i = 0; i < strlen(line); i++) {
			if (line[i] == ' ') {
				noOfTokens = noOfTokens + 1;
			}
		}
		noOfTokens = noOfTokens + 1;
		//printf("%d\n", noOfTokens);
		//noOfTokens = noOfTokens + 1;  // for NULL
		


		char* tokens[noOfTokens];
		char* token = strtok(line, " ");
		int ind = 0;
		while (token != NULL) {
			tokens[ind] = token;
			token = strtok(NULL, " ");
			ind = ind + 1;
		}
		tokens[ind] = NULL;


		//split(line, noOfTokens, &tokens);
		//printf("%s", tokens[0]);
		//printf("%s", tokens[2]);
		//printf("%s", tokens[2]);
		//break;
		//free(line);
		int found = 0;
		for (int i = 0; i < 5; i++) {
			if (strcmp(intComArr[i], tokens[0]) == 0) {
				found = 1;
				if (i == 0) {
					int noOfArg = noOfTokens - 1;
					if (noOfArg == 1) {
						chdir(getenv("HOME"));
					}
					else if (noOfArg == 2 && (strcmp(tokens[1], "~") == 0)) {
						chdir(getenv("HOME"));
					}
					else if (noOfArg == 2 && (strcmp(tokens[1], "-L") == 0)) {
						chdir(getenv("HOME"));
					}
					else if (noOfArg == 2 && (strcmp(tokens[1], "--help") == 0)) {
						printf("Changes the directory. (note that you can specify a directory whose name has spaces, then enquote in double quotes).\n");
						printf("Options:\n");
						printf("-L: If you use this option, then you can provide the symbolic path\n");
						printf("–help: Prints information about this command.\n");
						
					}
					else if (noOfArg == 3 && (strcmp(tokens[1], "-L") == 0)) {
						int status = chdir(tokens[2]);
						if (status != 0) {
							printf("Error: The directory does not exist\n");
						}
					}
					else if (noOfArg >= 2 && (tokens[1][0] == '"' && tokens[noOfArg - 1][strlen(tokens[noOfArg - 1]) - 1] == '"')) {
						char myDir[400] = "";
						tokens[noOfArg - 1][strlen(tokens[noOfArg - 1]) - 1] = '\0';
						tokens[1] = tokens[1] + 1;
						for (int j = 1; j < noOfArg; j++) {
							strcat(myDir, tokens[j]);
							if (j != noOfArg - 1) {
								strcat(myDir, " ");
							}
						}
						int status = chdir(myDir);
						if (status != 0) {
							printf("Error: The directory does not exist\n");
						}
					}
					else if (noOfArg == 2) {
						int status = chdir(tokens[1]);
						if (status != 0) {
							printf("Error: The directory does not exist\n");
						}
					}
					else {
						printf("Error: There is an error in the arguments or options.\n");
					}
				}
				else if (i == 1) {
					int noOfArg = noOfTokens - 1;
					if (noOfArg == 1) {
						printf("\n");
					}
					else if ((noOfArg == 2) && (strcmp(tokens[1], "-n") == 0)) {
						//printf("");
					}
					else if ((noOfArg == 2) && (strcmp(tokens[1], "--help") == 0)){
						printf("Prints whatever you have written after it.\n");
						printf("Options:\n");
						printf("-n: it print whatever you have supplied and then it prints the “terminal line tag” in the same line.\n");
						printf("–help: Prints information about this command.\n");
					}
					else if ((noOfArg >= 2) && (strcmp(tokens[1], "-n") != 0)) {
						for (int j = 1; j < noOfArg; j++) {
							for (int k = 0; k < strlen(tokens[j]); k++) {
								if (tokens[j][k] == '\n') {
									printf("n");
								}
								else if (tokens[j][k] == '\t') {
									printf("t");
								}
								else if (tokens[j][k] == '\\') {
									printf("\\");
								}
								else if (tokens[j][k] == '\b') {
									printf("b");
								}
								else if (tokens[j][k] == '\a') {
									printf("a");
								}
								else if (tokens[j][k] == '\v') {
									printf("v");
								}
								else if (tokens[j][k] == '\0') {
									printf("0");
								}
								else if ((tokens[j][k] == '"') && (k == 0 || k == strlen(tokens[j]) - 1) && ((tokens[j][0] == '"') && (tokens[j][strlen(tokens[j]) - 1] == '"'))) {

								}
								else {
									printf("%c", tokens[j][k]);
								}

							}
							if (j == noOfArg - 1) {
								printf("\n");
							}
							else {
								printf(" ");
							}
						}
					}
					else if ((noOfArg >= 3) && (strcmp(tokens[1], "-n") == 0)) {
						for (int j = 2; j < noOfArg; j++) {
							for (int k = 0; k < strlen(tokens[j]); k++) {
								if (tokens[j][k] == '\n') {
									printf("n");
								}
								else if (tokens[j][k] == '\t') {
									printf("t");
								}
								else if (tokens[j][k] == '\\') {
									printf("\\");
								}
								else if (tokens[j][k] == '\b') {
									printf("b");
								}
								else if (tokens[j][k] == '\a') {
									printf("a");
								}
								else if (tokens[j][k] == '\v') {
									printf("v");
								}
								else if (tokens[j][k] == '\0') {
									printf("0");
								}
								else if ((tokens[j][k] == '"') && (k == 0 || k == strlen(tokens[j]) - 1) && ((tokens[j][0] == '"') && (tokens[j][strlen(tokens[j]) - 1] == '"'))) {
									
								}
								else {
									printf("%c", tokens[j][k]);
								}

							}
							if (j == noOfArg - 1) {
								//printf("");
							}
							else {
								printf(" ");
							}
						}
					}
					else {
						printf("Error : There is an error in the arguments or options\n");
					}
				}
				
				else if (i == 2) {
					int noOfArg = noOfTokens - 1;
					if (noOfArg == 1) {
						FILE *fptr3 = fopen("history.txt", "r");
						char line1[350];
						//int lineNum = 0;
						while (fgets(line1, sizeof(line1), fptr3) != NULL) {
							printf("%s", line1);
						}
						fclose(fptr3);

						FILE *fptr4 = fopen("historyList.txt", "r");
						//char line2[350];
						//int lineNum = 0;
						while (fgets(line1, sizeof(line1), fptr4) != NULL) {
							printf("%s", line1);
						}
						fclose(fptr4);
						//free(fptr3);
						//free(fptr4);
						//free(line1);
					}
					else if (noOfArg == 2 && (strcmp(tokens[1], "-a") == 0)) {
						FILE *fptr3 = fopen("historyList.txt", "r");
						FILE *fptr4 = fopen("history.txt", "a");
						char line1[350];
						while (fgets(line1, sizeof(line1), fptr3) != NULL) {
							fprintf(fptr4, "%s", line1);
						}
						fclose(fptr3);
						fclose(fptr4);
						fptr3 = fopen("historyList.txt", "w");
						fclose(fptr3);
						//free(fptr3);
						//free(fptr4);
						//free(fptr5);
						//free(line1);
					}
					else if (noOfArg == 2 && (strcmp(tokens[1], "--help") == 0)) {
						printf("history: prints history.\n");
					}
					else {
						printf("Error: There is an error in the arguments or options.\n");
					}
				}
				else if (i == 3) {
					int noOfArg = noOfTokens - 1;
					if (noOfArg == 1) {
						printWorkingDir();
					}
					else if (noOfArg == 2 && (strcmp(tokens[1], "-L")== 0)) {
						printWorkingDir();
					}
					else if (noOfArg == 2 && (strcmp(tokens[1], "--help") == 0)) {
						printf("prints working directory\n");
					}
					else {
						printf("Error : There is an error in the arguments or options\n");
					}
					
				}
				else if (i == 4) {
					int noOfArg = noOfTokens - 1;
					if (noOfArg == 1) {
						
						FILE *fptr3 = fopen("historyList.txt", "r");
						FILE *fptr4 = fopen("history.txt", "a");
						char line1[350];
						while (fgets(line1, sizeof(line1), fptr3) != NULL) {
							fprintf(fptr4, "%s", line1);
						}
						fclose(fptr3);
						fclose(fptr4);
						fptr3 = fopen("historyList.txt", "w");
						fclose(fptr3);
						//free(fptr3);
						//free(fptr4);
						//free(fptr5);
						//free(line1);
						
						exit(0);
					}
					else if (noOfArg == 2 && (strcmp(tokens[1], "--version") == 0)) {
						printf("mkdir: Version - 8.2.3\n");
						printf("Developed by Akhil Anand\n");
					}
					else if (noOfArg == 2 && (strcmp(tokens[1], "--help") == 0)) {
						printf("exits the shell\n");
					}
					else {
						printf("Error: There is an error in the arguments or options.\n");
					}
				}

				break;
			}
		}
		if (found == 0) {
			//printf("Enter1");
			for (int i = 0; i < 5; i++) {
				if (strcmp(extComArr[i], tokens[0]) == 0) {
					//printf("Enter2\n");
					found = 1;
					int pid = fork();
					if (pid == 0) {                 // pid < 0 ka bhi kar
						//printf("child\n");
						//printf("%s\n", baseAddress);
						char* path = (char *) malloc(1 + strlen(baseAddress)+ strlen(extComFileArr[i]));
						strcat(path, baseAddress);
						strcat(path, extComFileArr[i]);
						//char* path = "";
						//strcat(path, baseAddress);
						//printf("%s\n", path);
						//printf("%s\n", baseAddress);
						//strcat(path, extComFileArr[i]);
						//printf("%s\n", path);
						tokens[0] = path; 
						//char* args[]={"/home/akhil/Desktop/csvAssign/dateFile", "-u", NULL}; 
        				execv(tokens[0], tokens); 
					}
					else {
						wait(NULL);
					}
					break;
				}
			}
		}

		if (found == 0) {
			printf("Error : The command is not recognised.\n");
		}
		fclose(fptr1);
		fclose(fptr2);
		
		
	}
	exit(0);
}


void printWorkingDir() {
	char cwd[PATH_MAX];
	if (getcwd(cwd, PATH_MAX) != NULL) {
       printf("%s\n", cwd);
   	} 
   	else {
       printf("Error : Working directory can't be printed\n");
   	}
}







