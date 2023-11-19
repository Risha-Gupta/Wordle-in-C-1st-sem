#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
//All user defined functions here
void stop(int milliseconds);
void cls();
void loading();
void start();
void choose();
void help();
void exitGame();
void nextslide(int a);
void generateLevel(int level);
void begin4();
void rand4();
int findlen4();
void generateGuess4();
void generateSol4();
void displayWordle4();
void printSol(int d);
int checkExist4(char* buffer);
int checkSize4(char* buffer);
void input4();
void editSol4();
void winCheck4();
void begin5();
void rand5();
int findlen5();
void generateGuess5();
void generateSol5();
void displayWordle5();
int checkExist5(char* buffer);
int checkSize5(char* buffer);
void input5();
void editSol5();
void winCheck5();
void begin6();
void rand6();
int findlen6();
void generateGuess6();
void generateSol6();
void displayWordle6();
int checkExist6(char* buffer);
int checkSize6(char* buffer);
void input6();
void editSol6();
void winCheck6();
//All global variables
char* word;
char* guessWord;
int* sol;
int* guess;
int round = 0;
//Main function
int main()
{
    start();
}
void cls()
{
    //It will clear the screen
    system("clear");
}
void stop(int milliseconds)
{
    sleep(milliseconds/1000);
}
void loading()
{
    printf("loading...");
    printf("Press enter to continue");
    int ch;
    scanf("%d",&ch);
    cls();
}
void exitGame()
{
    cls();
    printf("Thank you for playing\n");
    printf("Exiting");
    printf("\nPress any key to continue\n");
    int ch;
    scanf("%d",&ch);
    cls();
    exit(0);
}
void help()
{
    cls();
    //All the help here
    printf("This is a guided tutorial");
    nextslide(3);
    printf("Welcome to GUESSle, a GUESS Guessing game.\n");
    printf("The original version was released in October, 2021 by Josh Wardle.\n");
    printf("This is a Remastered Version of the game in C.\n");
    nextslide(7);
    printf("The game begins with a 6 row matrix as given below:\n");
    generateLevel(5);
    nextslide(5);
    printf("Let us learn using an example");
    nextslide(2);
    printf("Let us say you have to guess the GUESS 'PLANT'");
    printf("\nYou won't be told what you are supposed to guess, it is just for the example");
    nextslide(7);
    printf("So you enter your first guess: STAND");
    nextslide(5);
    printf("The computer will return: ");
    printf("S :[ T :/ A :) N :) D :[");
    nextslide(10);
    printf("\nThis was because: \n");
    printf(":) means that the letter is in the right location\n");
    printf(":/ means that the letter exists in the GUESS but is not in the right location\n");
    printf(":[ means that the letter does not exist in the GUESS\n");
    nextslide(10);
    printf("So\nS :[ T :/ A :) N :) D :[ \nMeans that\n");
    printf("S and D are not in the original GUESS, i.e. PLANT\n");
    printf("T is in the wrong location and A and N are in the right location");
    nextslide(15);
    printf("This will fill one row.");
    printf("\nThe game will go on till either you find the correct GUESS or you use up your six attempts\n");
    printf("You will be revealed the answer when the game ends.");
    nextslide(9);
    printf("All the Best");
    printf("\n\n---\nEnter any key to continue\n");
    int ch;
    scanf("%d",&ch);
    cls();
}
void nextslide(int a)
{
    stop(a*1000);
    cls();
}
void start()
{
    cls();
    printf("Welcome to The Wordle Game\n");
    printf("---Press 1 to continue\n");
    printf("---Press 2 for help\n");
    printf("---Press 3 to exit\n");
    int choice;
    printf("Enter your choice here: ");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            loading();
            choose();
            break;
        case 2:
            loading();
            help();
            break;
        case 3:
            exitGame();
            break;
        default:
            printf("Invalid choice\n");
            start();
    }
}
void choose()
{
    cls();
    printf("Choose your level\n");
    printf("---Press 1 for 4 letters\n");
    printf("---Press 2 for 5 letters\n");
    printf("---Press 3 for 6 letters\n");
    printf("---Press 4 to go back\n");
    int choice;
    printf("Enter your choice here: ");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            loading();
            printf("You have chosen 4 letters\n");
            begin4();
            break;
        case 2:
            loading();
            printf("You have chosen 5 letters\n");
            begin5();
            break;
        case 3:
            loading();
            printf("You have chosen 6 letters\n");
            begin6();
            break;
        case 4:
            start();
            break;
        default:
            printf("Invalid choice\n");
            choose();
            break;
    }
}
//Generates an empty matrix for the turtorial
void generateLevel(int level)
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<level;j++)
            printf(" _ ");
        printf("\n");
    }
}
//-//-//-//-//-//-//-//-//-//-//-//
//for 4 letter word
void begin4()
{
    cls();
    printf("Welcome to the 4 letter game\n");
    printf("You have 6 attempts to guess the word\n");
    printf("The word is a 4 letter word\n");
    printf("Press enter to continue\n");
    int ch;
    scanf("%d",&ch);
    cls();
    rand4();
    generateGuess4();
    generateSol4();
    displayWordle4();
    for(int i=0;i<6;i++)
    {
        input4();
        editSol4();
        cls();
        displayWordle4();
        winCheck4();
        round++;
    }
}
void rand4()
{
    //picks a random word from common4.txt
    FILE *fp;
    fp=fopen("common4.txt","r");
    word = (char*)malloc(4*sizeof(char));
    int length = findlen4();
    //To find a random number between 1 and length
    srand(time(0));
    int random = rand()%length;
    int count=0;
    while(count<random)
    {
        fscanf(fp,"%s",word);
        count++;
    }
    fclose(fp);
}
int findlen4()
{
    //to find number of lines in common4.txt
    FILE *fp;
    fp=fopen("common4.txt","r");
    int count=0;
    char ch;
    while((ch=fgetc(fp))!=EOF)
    {
        if(ch=='\n')
            count++;
    }
    return(count);
}
void generateGuess4()
{
    guess = (int*)malloc(sizeof(int)*6*4);
    for(int i=0;i<6*4;i++)
    {
        *(guess+i) = '_';
    }
}
void generateSol4()
{
    sol = (int*)malloc(sizeof(int)*6*4);
    for(int i=0;i<6*4;i++)
    {
        *(sol+i) = '0';
    }
}
void displayWordle4()
{
    printf("Solution is %s\n",word);
    printf("Wordle\n");
    printf("Round: %d\n",round);
    printf("Guess: \n");
    for(int i=0;i<6*4;i++)
    {
        printf("%c",*(guess+i));
        printf(" ");
        printSol(*(sol+i));
        printf(" ");
        if((i+1)%4==0)
        {
            printf("\n");
        }
    }
    printf("\n");
}
void input4()
{
    label:
    printf("Enter your guess: ");
    char buffer[10];
    scanf("%s",buffer);
    if((!checkSize4(buffer))||(!checkExist4(buffer)))
    {
        printf("Invalid input\n");
        printf("Press enter to continue\n");
        int ch;
        scanf("%d",&ch);
        cls();
        printf("ENTER A VALID INPUT\n");
        goto label;
    }
    guessWord = (char*)malloc(4*sizeof(char));
    for(int i=0;i<4;i++)
    {
        *(guessWord+i) = buffer[i];
    }
    for(int i=0;i<4;i++)
    {
        *(guess+round*4+i) = *(guessWord+i);
    }
}
int checkSize4(char* buffer)
{
    int len = strlen(buffer);
    if(len!=4)
        return(0);
    else
        return(1);
}
int checkExist4(char* buffer)
{
    FILE *fp;
    fp=fopen("wordle4letter.txt","r");
    if(fp==NULL)
    {
        printf("File not found\n");
        exit(0);
    }
    char* word = (char*)malloc(10*sizeof(char));
    while (fgets(word, 10, fp) != NULL)
    {
        *(word+4) = '\0';
        if (strcmp(word, buffer) == 0)
            return 1;
    }
    if (feof(fp))
    {
        // Reached end of file without finding a match
        buffer[0] = '\0';
        return 0;
    }
    fclose(fp);
    return(0);
}
void editSol4()
{
    for(int i=0;i<4;i++)
    {
        *(sol+round*4+i) = 3;
        if(*(guess+round*4+i)==*(word+i))
        {
            *(sol+round*4+i) = 1;
        }
        else
        {
            for(int j=0;j<4;j++)
            {
                if(*(guess+round*4+i)==*(word+j))
                {
                    *(sol+round*4+i) = 2;
                }
            }
        }
    }
}
void winCheck4()
{
    int flag=0;
    for(int i=0;i<4;i++)
    {
        if(*(sol+round*4+i)!=1)
        {
            flag=1;
        }
    }
    if(flag==0)
    {
        cls();
        printf("You won\n");
        printf("The word was %s\n",word);
        printf("Press enter to continue\n");
        int ch;
        scanf("%d",&ch);
        cls();
        start();
    }
    else if(flag==1)
    {
        cls();
        printf("You lost\n");
        printf("The word was %s\n",word);
        printf("Press enter to continue\n");
        int ch;
        scanf("%d",&ch);
        cls();
        start();
    }
}
//-//-//-//-//-//-//-//-//-//-//-//
//for 5 letter word
void begin5()
{
    cls();
    printf("Welcome to the 5 letter game\n");
    printf("You have 6 attempts to guess the word\n");
    printf("The word is a 5 letter word\n");
    printf("Press enter to continue\n");
    int ch;
    scanf("%d",&ch);
    cls();
    rand5();
    generateGuess5();
    generateSol5();
    displayWordle5();
    for(int i=0;i<6;i++)
    {
        input5();
        editSol5();
        cls();
        displayWordle5();
        winCheck5();
        round++;
    }
}
void rand5()
{
    //picks a random word from common5.txt
    FILE *fp;
    fp=fopen("common5.txt","r");
    word = (char*)malloc(5*sizeof(char));
    int length = findlen5();
    //To find a random number between 1 and length
    srand(time(0));
    int random = rand()%length;
    int count=0;
    while(count<random)
    {
        fscanf(fp,"%s",word);
        count++;
    }
    fclose(fp);
}
int findlen5()
{
    //to find number of lines in common5.txt
    FILE *fp;
    fp=fopen("common5.txt","r");
    int count=0;
    char ch;
    while((ch=fgetc(fp))!=EOF)
    {
        if(ch=='\n')
            count++;
    }
    return(count);
}
void generateGuess5()
{
    guess = (int*)malloc(sizeof(int)*6*5);
    for(int i=0;i<6*5;i++)
    {
        *(guess+i) = '_';
    }
}
void generateSol5()
{
    sol = (int*)malloc(sizeof(int)*6*5);
    for(int i=0;i<6*5;i++)
    {
        *(sol+i) = '0';
    }
}
void displayWordle5()
{
    printf("Solution is %s\n",word);
    printf("Wordle\n");
    printf("Round: %d\n",round);
    printf("Guess: \n");
    for(int i=0;i<6*5;i++)
    {
        printf("%c",*(guess+i));
        printf(" ");
        printSol(*(sol+i));
        printf(" ");
        if((i+1)%5==0)
        {
            printf("\n");
        }
    }
    printf("\n");
}
void input5()
{
    label:
    printf("Enter your guess: ");
    char buffer[10];
    scanf("%s",buffer);
    if((!checkSize5(buffer))||(!checkExist5(buffer)))
    {
        printf("Invalid input\n");
        printf("Press enter to continue\n");
        int ch;
        scanf("%d",&ch);
        cls();
        printf("ENTER A VALID INPUT\n");
        goto label;
    }
    guessWord = (char*)malloc(5*sizeof(char));
    for(int i=0;i<5;i++)
    {
        *(guessWord+i) = buffer[i];
    }
    for(int i=0;i<5;i++)
    {
        *(guess+round*5+i) = *(guessWord+i);
    }
}
int checkSize5(char* buffer)
{
    int len = strlen(buffer);
    if(len!=5)
        return(0);
    else
        return(1);
}
int checkExist5(char* buffer)
{
    FILE *fp;
    fp=fopen("wordle5letter.txt","r");
    if(fp==NULL)
    {
        printf("File not found\n");
        exit(0);
    }
    char* word = (char*)malloc(10*sizeof(char));
    while (fgets(word, 10, fp) != NULL)
    {
        *(word+5) = '\0';
        if (strcmp(word, buffer) == 0)
            return 1;
    }
    if (feof(fp))
    {
        // Reached end of file without finding a match
        buffer[0] = '\0';
        return 0;
    }
    fclose(fp);
    return(0);
}
void editSol5()
{
    for(int i=0;i<5;i++)
    {
        *(sol+round*5+i) = 3;
        if(*(guess+round*5+i)==*(word+i))
        {
            *(sol+round*5+i) = 1;
        }
        else
        {
            for(int j=0;j<5;j++)
            {
                if(*(guess+round*5+i)==*(word+j))
                {
                    *(sol+round*5+i) = 2;
                }
            }
        }
    }
}
void winCheck5()
{
    int flag=0;
    for(int i=0;i<5;i++)
    {
        if(*(sol+round*5+i)!=1)
        {
            flag=1;
        }
    }
    if(flag==0)
    {
        cls();
        printf("You won\n");
        printf("The word was %s\n",word);
        printf("Press enter to continue\n");
        int ch;
        scanf("%d",&ch);
        cls();
        start();
    }
    else if(flag==1)
    {
        cls();
        printf("You lost\n");
        printf("The word was %s\n",word);
        printf("Press enter to continue\n");
        int ch;
        scanf("%d",&ch);
        cls();
        start();
    }
}
//-//-//-//-//-//-//-//-//-//-//-//
//for 6 letter word
void begin6()
{
    cls();
    printf("Welcome to the 6 letter game\n");
    printf("You have 6 attempts to guess the word\n");
    printf("The word is a 6 letter word\n");
    printf("Press enter to continue\n");
    int ch;
    scanf("%d",&ch);
    cls();
    rand6();
    generateGuess6();
    generateSol6();
    displayWordle6();
    for(int i=0;i<6;i++)
    {
        input6();
        editSol6();
        cls();
        displayWordle6();
        winCheck6();
        round++;
    }
}
void rand6()
{
    //picks a random word from common6.txt
    FILE *fp;
    fp=fopen("common6.txt","r");
    word = (char*)malloc(6*sizeof(char));
    int length = findlen6();
    //To find a random number between 1 and length
    srand(time(0));
    int random = rand()%length;
    int count=0;
    while(count<random)
    {
        fscanf(fp,"%s",word);
        count++;
    }
    fclose(fp);
}
int findlen6()
{
    //to find number of lines in common6.txt
    FILE *fp;
    fp=fopen("common6.txt","r");
    int count=0;
    char ch;
    while((ch=fgetc(fp))!=EOF)
    {
        if(ch=='\n')
            count++;
    }
    return(count);
}
void generateGuess6()
{
    guess = (int*)malloc(sizeof(int)*6*6);
    for(int i=0;i<6*6;i++)
    {
        *(guess+i) = '_';
    }
}
void generateSol6()
{
    sol = (int*)malloc(sizeof(int)*6*6);
    for(int i=0;i<6*6;i++)
    {
        *(sol+i) = '0';
    }
}
void displayWordle6()
{
    printf("Solution is- %s\n",word);
    printf("Wordle\n");
    printf("Round: %d\n",round);
    printf("Guess: \n");
    for(int i=0;i<6*6;i++)
    {
        printf("%c",*(guess+i));
        printf(" ");
        printSol(*(sol+i));
        printf(" ");
        if((i+1)%6==0)
        {
            printf("\n");
        }
    }
    printf("\n");
}
void input6()
{
    label:
    printf("Enter your guess: ");
    char buffer[10];
    scanf("%s",buffer);
    if((!checkSize6(buffer))||(!checkExist6(buffer)))
    {
        printf("Invalid input\n");
        printf("Press enter to continue\n");
        int ch;
        scanf("%d",&ch);
        cls();
        printf("ENTER A VALID INPUT\n");
        goto label;
    }
    guessWord = (char*)malloc(6*sizeof(char));
    for(int i=0;i<6;i++)
    {
        *(guessWord+i) = buffer[i];
    }
    for(int i=0;i<6;i++)
    {
        *(guess+round*6+i) = *(guessWord+i);
    }
}
int checkSize6(char* buffer)
{
    int len = strlen(buffer);
    if(len!=6)
        return(0);
    else
        return(1);
}
int checkExist6(char* buffer)
{
    FILE *fp;
    fp=fopen("wordle6letter.txt","r");
    if(fp==NULL)
    {
        printf("File not found\n");
        exit(0);
    }
    char* word = (char*)malloc(10*sizeof(char));
    while (fgets(word, 10, fp) != NULL)
    {
        *(word+6) = '\0';
        if (strcmp(word, buffer) == 0)
            return 1;
    }
    if (feof(fp))
    {
        // Reached end of file without finding a match
        buffer[0] = '\0';
        return 0;
    }
    fclose(fp);
    return(0);
}
void editSol6()
{
    for(int i=0;i<6;i++)
    {
        *(sol+round*6+i) = 3;
        if(*(guess+round*6+i)==*(word+i))
        {
            *(sol+round*6+i) = 1;
        }
        else
        {
            for(int j=0;j<6;j++)
            {
                if(*(guess+round*6+i)==*(word+j))
                {
                    *(sol+round*6+i) = 2;
                }
            }
        }
    }
}
void winCheck6()
{
    int flag=0;
    for(int i=0;i<6;i++)
    {
        if(*(sol+round*6+i)!=1)
        {
            flag=1;
        }
    }
    if(flag==0)
    {
        cls();
        printf("You won\n");
        printf("The word was %s\n",word);
        printf("Press enter to continue\n");
        int ch;
        scanf("%d",&ch);
        cls();
        start();
    }
    else if(flag==1)
    {
        cls();
        printf("You lost\n");
        printf("The word was %s\n",word);
        printf("Press enter to continue\n");
        int ch;
        scanf("%d",&ch);
        cls();
        start();
    }
}
//NO difficulty specific functions
void printSol(int d)
{
    switch(d)
    {
        case 1:
        printf(":)");
        break;
        case 2:
        printf(":/");
        break;
        case 3:
        printf(":[");
        break;
        default:
        printf("  ");
        break;
    }
}
