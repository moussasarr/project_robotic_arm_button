#include <stdio.h>
#include <stdlib.h>
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdlib.h>
#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "rs232.h"
#define RUNNING 1


int main()
{   printf("----------------------------------------------------------------------\n\n");
    puts("Welcome to PUSH COUNTER appliction  :)");
    puts("Type any key to test here ...");
    printf("----------------------------------------------------------------------\n\n");
    while (RUNNING){
        char c = getch();



        if(c != ' ') {
            printf("Not a space button... Program listening for push button .\n\n");
        }
        else {
            printf("Finally pressed a space bar. Updating counter now ...\n");


            // Send an ASCII string to the display for the first time
            // Or increment the value of the display

            int i=0,
            cport_nr=0,        /* /dev/ttyS0 (COM1 on windows) */
            bdrate=9600;       /* 9600 baud */

            char mode[]={'8','N','1',0},
            str[2][512];
            strcpy(str[0], "The quick brown fox jumped over the lazy grey dog.\n");
            strcpy(str[1], "Happy serial programming!.\n");
            if(RS232_OpenComport(cport_nr, bdrate, mode))
            {
                printf("Can not open comport\n");
            return(0);
            }

  while(1)
  {
    RS232_cputs(cport_nr, str[i]);

    printf("sent: %s\n", str[i]);

#ifdef _WIN32
    Sleep(1000);
#else
    usleep(1000000);  /* sleep for 1 Second */
#endif

    i++;

    i %= 2;
  }





















        }
    }
     return(0);

}




int getch (void)
{
        int ch;
        struct termios oldt, newt;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON|ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        return ch;
}
