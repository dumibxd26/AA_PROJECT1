#include <iostream>
#include <cstring>

using namespace std;

int main(void)
{
    for(int i = 7; i < 33; i++) {

        char command[100];
        char number[3];
        strcpy(command, ".\\DijkstraPQ.exe in\\test");

        itoa(i, number, 10);
        strcat(command, number);
        strcat(command, ".in");

        strcat(command, " out\\test");
        strcat(command, number);
        strcat(command, ".out");

        system(command);
    }

    return 0;
}