#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
void StartGame()
{
    welcome();
    loading();
}
void welcome()
{
    printf("Welcome to Wordle\n...Press Enter to Start...\nPress H for help.\n");
    char ch;
    scanf("%c",&ch);
    if(ch=='H'||ch=='h')
    {
        help();
    }
}
void help()
{
    system("cls");
    printf("Here");
    //All the help here
    printf("\n---\nEnter any key to continue");
    int ch;
    scanf("%d",&ch);
}
void loading()
{
    for(int i=0;i<3;i++)
    {
        system("cls");
        printf("Loading");
        for(int j=0;j<=i;j++)
        {
            printf(".");
        }
        Sleep(300);
    }
void StartGame()
{
    welcome();
    loading();
}
}
int main()
{
    StartGame();
}
