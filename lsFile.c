#include <stdio.h> 
#include <dirent.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<stdlib.h>
#include<string.h>
  
int main(int argc, char const *argv[]) 
{ 
    if (argc == 1) {
        struct dirent *dirEnt; 
        DIR *dir = opendir("."); 
        if (dir == NULL) {
            printf("Error : Current working directory can't be opened"); 
            exit(1);
        } 
        while ((dirEnt = readdir(dir)) != NULL) {
            if ((strcmp(dirEnt->d_name, ".") != 0) && (strcmp(dirEnt->d_name, "..") != 0)) {              
                printf("%s\n", dirEnt->d_name);
            }   
        }
        closedir(dir);     
        exit(0);
    }
    else if (argc == 2 && (strcmp(argv[1], "-F") == 0)) {
        struct dirent *dirEnt; 
        DIR *dir = opendir("."); 
        if (dir == NULL) {
            printf("Error : Current working directory can't be opened"); 
            exit(1);
        } 
        while ((dirEnt = readdir(dir)) != NULL) {
            if ((strcmp(dirEnt->d_name, ".") != 0) && (strcmp(dirEnt->d_name, "..") != 0)) {
                if (dirEnt->d_type == DT_DIR) {
                    printf("%s/\n", dirEnt->d_name);
                }
                else {
                    printf("%s\n", dirEnt->d_name);
                }
            }   
        }
        closedir(dir);     
        exit(0);
    }
    else if (argc == 2 && (strcmp(argv[1], "--help") == 0)) {
        printf("ls :  Prints the files and folders in working directory.\n");
        printf("Options:\n");
        printf("-F : Prints the files and fodders in working directory. The folder name will be ended by forward slash\n");
        printf("–help : Prints information about this command\n");
        exit(0);
    }
    else {
        printf("Error: There is an error in the arguments or options.\n");
        exit(1);
    }
} 