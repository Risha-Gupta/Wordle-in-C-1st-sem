#include <stdio.h>
#include <Windows.h>
//For using Sleep in C
#include <stdlib.h>
#include <string.h>
#define MATRIX 6
//Solutions will store the answers to its adjacent solutions
//It will show 0 if it is empty, 1 if :), 2 if :/ and 3 for :[
void generateLevel(int level);
char USER[MATRIX][MATRIX];
int SOLUTIONS[MATRIX][MATRIX];
int StartGame();
int  welcome();
void help();
int options();
void loading();
void initializeAns(int **SOL);
void initializeMain(int **Main);
//It will make all the solutions equal to zero
void displayAns(int num);
//Display SOLUTION
//This will print the array, here r is the number of rows and c is the number of columns
//Main Function
int main()
{
    //We now have the level
    int level = StartGame()+3;
    initializeAns(SOLUTIONS);
    initializeMain(USER);
    //Taking input from the user
    
    //It will initialize the entire SOLUTIONS to 0

    return 0;
}

int StartGame()
{
    return(welcome());
}

int  welcome()
{
    printf("Welcome to Wordle\n...Press Enter to Start...\nPress H for help.\n");
    char ch;//
    scanf("%c",&ch);
    //If no character is entered or any character other than h is entered, the code proceeds
    //If h or H is entered, the code first gives the instructions
    if(ch=='H'||ch=='h')
    {
        help();
        //This will redirect the user to the help menu
    }
    loading();
    return(options());
}

void help()
{
    system("cls");
    //All the help here
    printf("This is a guided tutorial");
    nextslide(3);
    printf("Welcome to Wordle, a word Guessing game.\n");
    printf("The original version was released in October, 2021 by Josh Wardle.\n");
    printf("This is a Remastered Version of the game in C.\n");
    nextslide(7);
    printf("The game begins with a 6 row matrix as given below:\n");
    generateLevel(5);
    nextslide(5);
    printf("Let us learn using an example");
    nextslide(2);
    printf("Let us say you have to guess the word 'PLANT'");
    printf("\nYou won't be told what you are supposed to guess, it is just for the example");
    nextslide(7);
    printf("So you enter your first guess: STAND");
    nextslide(5);
    printf("The computer will return: ");
    printf("S :[ T :/ A :) N :) D :[");
    nextslide(10);
    printf("\nThis was because: \n");
    printf(":) means that the letter is in the right location\n");
    printf(":/ means that the letter exists in the word but is not in the right location\n");
    printf(":[ means that the letter does not exist in the word\n");
    nextslide(10);
    printf("So\nS :[ T :/ A :) N :) D :[ \nMeans that\n");
    printf("S and D are not in the original word, i.e. PLANT\n");
    printf("T is in the wrong location and A and N are in the right location");
    nextslide(15);
    printf("This will fill one row.");
    printf("\nThe game will go on till either you find the correct word or you use up your six attempts\n");
    printf("You will be revealed the answer when the game ends.");
    nextslide(9);
    printf("All the Best");
    printf("\n\n---\nEnter any key to continue\n");
    char ch;
    scanf("%d",&ch);
    system("cls");
}
void nextslide(int a)
{
    Sleep(a*1000);
    system("cls");
}
int options()
{
edef:
    system("cls");
    printf("There are 3 difficulty modes: \n");
    printf("Easy\t1\nMedium\t2\nHard\t3\n");
    int mode;
    printf("Enter Your Choice: ");
    char buffer[10];
    fgets(buffer, 10, stdin);
    mode = atoi(buffer);
    if(!(mode>0 && mode <4))
    {
        printf("Please enter 1, 2 or 3");
        Sleep(1100);
        goto edef;
    }
    return mode;
}

//Loading function to simulate a loading screen
void loading()
{
    for(int i=0;i<3;i++)
        //We print it with no dots, then erase, then with multiple
    {
        system("cls");
        //This command will clear the Command Line Interface
        printf("Loading");
        for(int j=0;j<=i;j++)
        {
            printf(".");
        }
        Sleep(300);
}
}

void generateLevel(int level)
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<level;j++)
            printf(" _ ");
        printf("\n");
    }
}
void displayAns(int num)
{
    if(num==1)
    {
        printf(":)");
        return;
    }
    else if(num==2)
    {
        printf(":/");
        return;
    }
    else if(num==3)
    {
        printf(":[");
        return;
    }
    else
    {
        printf(" ");
        return;
    }
}
void initializeAns(int **SOL)
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<6;j++)
        {
            SOL[i][j]=0;
        }
    }
}
void initializeMain(int **Main)
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<6;j++)
        {
            Main[i][j]='-';
        }
    }
}
/*
Submitted for MiniProject
OddSem 2023
Class of 2028
Batch -> B9
Branch -> BTech CSE
Members:
    Risha Gupta
    Devyani Sharma
    Arnav Sharma
    Anushka Tayal
*/
