#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

void printGMT();
char* month(int monthNo);
char* weekDay(int dayNo);
void printTime();
void help();

int main(int argc, char const *argv[])
{
	//printf("Entered");
	if (argc == 1) {
		printTime();
		exit(0);
	}
	else if (argc == 2 && (strcmp(argv[1], "-u") == 0)) {
		printGMT();
		exit(0);
	}
	else if (argc == 2 && (strcmp(argv[1], "--help") == 0)) {
		help();
		exit(0);
	}
	else {
		printf("Error: There is an error in the arguments or options.\n");
		exit(1);
	}
    
    
    /*
    printf("%d\n", argc);            // Tu no of arguments argc se check kar yeh Last NULL ko count nahi karta hain.
    printf("%s\n", argv[0]);
    printf("%s\n", argv[1]);
    printf("%s\n", argv[2]);
    */
    //printf("%s", month(1));
	//return 0;
}

/*
int main()
{
}
*/

void printTime() {
	time_t curTime;   
    time(&curTime);
    printf("%s", ctime(&curTime));
}


void printGMT() {
	time_t curTime;   // not a primitive datatype
    time(&curTime);
	struct tm *GMtime = gmtime(&curTime);
	printf ("%s %s %d %2d:%02d:%02d %d\n", weekDay(GMtime->tm_wday), month(GMtime->tm_mon), GMtime->tm_mday, GMtime->tm_hour % 24, GMtime->tm_min, GMtime->tm_sec, 1900 + GMtime->tm_year);       // %02d ka work dekh

}

char* month(int monthNo) {
	char* arr[] = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec"}; 
	return arr[monthNo];
}

char* weekDay(int dayNo) {
	char* arr[] = {"Sun", "Mon", "Tue", "Wed", "Thurs", "Fri", "Sat"};
	return arr[dayNo];
}

void help() {
	printf("Prints the date and time in the default time zone of linux ubuntu system. (Generally, the default time zone of a linux system is PDT(Pacific Day Light time), so it prints according to that. )\n"); 
	printf("Options:\n");
	printf("-u: It prints the date and time according to GMT time zone\n");
	printf("–help: Prints information about this command\n");
}





