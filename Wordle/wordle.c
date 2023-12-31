#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif
//For using Sleep in C
#include <stdlib.h>
#include <string.h>
int level,round;
char WORDLE[10],turn[10],scrambled[10],WORDLE2[10];
char GUESS[6][6] = {
    {'-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-'}
};
int SOLUTION[6][6] = {
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
};
void generateLevel(int level);
int GUESSCheck(char *GUESS);
int StartGame();
int  welcome();
void help();
int options();
void loading();
void nextslide(int a);
void gameSetUp();
//It will display the main matrix
char* solDisp(int i);
//It will display the solution along the GUESS Matrix
char* wordInput();
//Word input will ask for the entry in each matrix row and check for its validity
void wordCheck();
void paste();
//Paste function will edit the main matrix whenever a valid entry is passed
int check4(char GUESS[level]);
int check5(char GUESS[level]);
int check6(char GUESS[level]);
int randint(int min_num, int max_num);
void generateRandomWord();
void pick4();
void pick5();
void pick6();
int init(char ch);
void pause(int milliseconds);
int checkWin();
void unscramble();
void scramble();
int numinit(int num,int rand[level]);
void scramble();
int deleter(int num);
void quiz();
void end();
//To check if the character ch exists in WORDLE at all
//Main Function
int main()
{
    //We now have the level
    level = StartGame()+3;
    generateRandomWord();
    //This will pick a random word for the player to guess based on the level.
    gameSetUp();
    //Display the initial game set up
    for(round=0;round<6;round++)
    {
        gameSetUp();
        wordInput();
        paste();
        wordCheck();
        if(checkWin())
        {
            printf("You won!");

            break;
        }
        //Will take the word input and then check if it is a valid word
        //To qualify as a valid word, must be 'level'letters long
        //Must be in dictionary
    }
    if(!checkWin())
    {
        system("cls");
        printf("You have run out of trials!\n\n");
        gameSetUp();
        printf("You lost!");
        printf("\nThe word was %s",WORDLE);
    }
    //Now to display the next options
    //If the user won, we take him to the quiz
    //If the user lost, we take him to a practise minigame
    //For lost
    if(!checkWin())
    {
        printf("\n\nPress 1 to play again\nPress 2 for a practise minigame\nPress 3 to leave\n");
        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            system("cls");
            for(int i=0;i<=3;i++)
            {
                printf("Resetting Parameters!");
                for(int j=0;j<=i;j++)
                {
                    printf(".");
                }
                pause(300);
                system("cls");
            }
            //This will launch the main program from here
        level = 0;
        round = 0;
        for(int i=0;i<6;i++)
        {
            for(int j=0;j<6;j++)
            {
                GUESS[i][j] = '-';
            }
        }
        for(int i=0;i<6;i++)
        {
            for(int j=0;j<6;j++)
            {
                SOLUTION[i][j] = 0;
            }
        }
        *WORDLE = '\0';
        *turn = '\0';
        *scrambled = '\0';
        *WORDLE2 = '\0';
        main();
        }
        else if(ch==2)
        {
            unscramble();
        }
        else if(ch==3)
        {
            quiz();
        }
        else
        {
            system("cls");
            printf("Thank you for playing!");
            exit(0);
            return 0;
        }
    }
    else
    {
    if(checkWin())
    {
        system("cls");
        printf("Congratulations! You won!\n\n");
        gameSetUp();
        printf("The word was %s",WORDLE);
        printf("\n\nPress 1 to play again\nPress 2 for a practise minigame\nPress 3 to leave");
        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            system("cls");
            for(int i=0;i<=3;i++)
            {
                printf("Resetting Parameters!");
                for(int j=0;j<=i;j++)
                {
                    printf(".");
                }
                pause(300);
                system("cls");
            }
            //This will launch the main program from here
            level = 0;
            round = 0;
            for(int i=0;i<6;i++)
            {
                for(int j=0;j<6;j++)
                {
                    GUESS[i][j] = '-';
                }
            }
            for(int i=0;i<6;i++)
            {
                for(int j=0;j<6;j++)
                {
                    SOLUTION[i][j] = 0;
                }
            }
            *WORDLE = '\0';
            *turn = '\0';
            *scrambled = '\0';
            *WORDLE2 = '\0';
            main();
    }
    else if(ch==2)
    {
        unscramble();
    }
    else if(ch==3)
    {
        quiz();
    }
    else
    {
        system("cls");
        printf("Thank you for playing!");
        exit(0);
        return 0;
    }
}
    }
    return 0;
}
//This function puts the program to sleep for set milliseconds
void pause(int milliseconds)
{ // cross-platform sleep function
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    if (milliseconds >= 1000)
      sleep(milliseconds / 1000);
    usleep((milliseconds % 1000) * 1000);
#endif
}
//This is the first program that is called and it is supposed to welcome the player
int StartGame()
{
    return(welcome());
}
int  welcome()
{
    printf("Welcome to GUESSle\n...Press Enter to Start...\nPress H for help.\n");
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
//This will display the help menu in a slide show fashion
void help()
{
    system("cls");
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
    char ch;
    scanf("%d",&ch);
    system("cls");
}
//This helps show things in a slideshow fashion
void nextslide(int a)
{
    pause(a*1000);
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
        pause(300);
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
//sends word to three different functions, based on their length
int GUESSCheck(char GUESS[level])
{
    //This code will invoke one of 3 different methods, depending on the level
    if(level==4)
        return(check4(GUESS));
    if(level==5)
        return(check5(GUESS));
    if(level==6)
        return(check6(GUESS));
}
//This will display the matrix after every turn
//It prints the user entered character
//Then the solution, passed through solDisp()
void gameSetUp()
{
    system("cls");
    printf("Enter The GUESS: \n");
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<level;j++)
        {
            printf("%c %s ",GUESS[i][j],solDisp(SOLUTION[i][j]));
        }
        printf("\n");
    }
}
//Used to print the solution, called by gameSetUp
char* solDisp(int i)
{
    if(i==2)
        return(":/");
    else if(i==1)
        return(":)");
    else if(i==3)
        return(":[");
    else
        return("  ");
}
//It will return the input after every turn
//It will ask the user to press again if length is wrong or the word does not exist in the dictionary
char* wordInput()
{
    start:
    printf("Enter the word here: ");
    char buffer[100];
    gets(buffer);
    if(!(strcheck1(buffer)))
    {
        printf("Please enter a %d lettered word!",level);
        nextslide(3);
        gameSetUp();
        goto start;
        //The function calls itself as if to start over
    }
    if(!GUESSCheck(buffer))
    //To check if it is in the dictionary
    {
        printf("Please enter a valid word");
        nextslide(3);
        gameSetUp();
        goto start;
    }
    nextslide(1);
    strcpy(turn,buffer);
    //The paste function will simply put it in the GUESS DDA
}
//It checks if the length is appropiate
int strcheck1(char* wordishere)
{
    int len=0;
    while(*(wordishere+len)!='\0')
    {
        len++;
    }
    if(len==level)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//This is used to update the solution matrix
void wordCheck()
{
    for(int i=0;i<level;i++)
    {
        if(*(turn+i)==*(WORDLE+i))
        {
            (SOLUTION[round])[i]=1;
        }
        else if(init(*(turn+i)))
        {
            (SOLUTION[round])[i]=2;
        }
        else
        {
            (SOLUTION[round])[i]=3;
        }
    }
}
//This is used to update the guess matrix
void paste()
{
    for(int i=0;i<level;i++)
    {
        GUESS[round][i]=*(turn+i);
    }
}
//This is used to check if corresponding 4 lettered word is a dictionary word
int check4(char wor[level])
{
    char data[5];
    FILE *file = fopen("C:/Users/itsar/OneDrive/Documents/GitHub/Wordle-in-C-1st-sem/letter4/wordle4letter.txt", "r");
    while(fgets(data, sizeof(data), file))
    {
        if(strcmp(data, wor)==0)
            return 1;
    }
    return 0;
}
//This is used to check if corresponding 5 lettered word is a dictionary word
int check5(char wor[level])
{
    char data[6];
    FILE *file = fopen("C:/Users/itsar/OneDrive/Documents/GitHub/Wordle-in-C-1st-sem/letter5/wordle5.txt", "r");
    while(fgets(data, sizeof(data), file))
    {
        if(strcmp(data, wor)==0)
            return 1;
    }
    return 0;
}
//This is used to check if corresponding 6 lettered word is a dictionary word
int check6(char wor[level])
{
    char data[7];
    FILE *file = fopen("C:/Users/itsar/OneDrive/Documents/GitHub/Wordle-in-C-1st-sem/letter6/wordle6letter.txt", "r");
    while(fgets(data, sizeof(data), file))
    {
        if(strcmp(data, wor)==0)
            return 1;
    }
    return 0;
}
//Generate a random integer from the min index to max index
int randint(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1;
        // include max_num in output
    }
    else
    {
        low_num = max_num + 1;
        // include max_num in output
        hi_num = min_num;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}
//Diverts the logic to three channels
void generateRandomWord()
{
    if(level==4)
    {
        pick4();
        return;
    }
    if(level==5)
    {
        pick5();
        return;
    }
    if(level==6)
    {
        pick6();
        return;
    }
}
//First finds the number of 4 lettered words we have
//Then picks a random index using randint()
void pick4()
{
    char data[5];
    FILE *file = fopen("C:/Users/itsar/OneDrive/Documents/GitHub/Wordle-in-C-1st-sem/letter4/common4.txt", "r");
    int len = 0;
    while(fgets(data, sizeof(data), file))
    {
        len++;
    }
    int var;
    var = randint(0,len);
    len=0;
    fclose(file);
    FILE *foil = fopen("C:/Users/itsar/OneDrive/Documents/GitHub/Wordle-in-C-1st-sem/letter4/common4.txt", "r");
    while(fgets(data, sizeof(data), foil))
    {
        if(len==var)
        {
            strcpy(WORDLE,data);
            break;
        }
        len++;
    }
    if(strlen(WORDLE)!=4)
    {
    char fourLetterWords[25][5] = {"cake", "desk", "fish", "girl", "home", "idea", "jazz", "kite", "love", "moon", "nest", "open", "pink", "quiz", "rain", "star", "time", "urge", "vase", "wish", "xray", "yawn", "zeal", "able", "baby"};
    int k = randint(0,24);
    strcpy(WORDLE,fourLetterWords[k]);
    }
}
void pick5()
{
    char data[6];
    FILE *file = fopen("C:/Users/itsar/OneDrive/Documents/GitHub/Wordle-in-C-1st-sem/letter5/common5.txt", "r");
    int len = 0;
    while(fgets(data, sizeof(data), file))
    {
        len++;
    }
    int var;
    var = randint(0,len);
    len=0;
    fclose(file);
    FILE *foil = fopen("C:/Users/itsar/OneDrive/Documents/GitHub/Wordle-in-C-1st-sem/letter5/common5.txt", "r");
    while(fgets(data, sizeof(data), foil))
    {
        if(len==var)
        {
            strcpy(WORDLE,data);
            break;
        }
        len++;
    }
    if(strlen(WORDLE)!=5)
    {
    char fiveLetterWords[25][6] = {"apple", "beach", "chair", "dance", "earth", "faith", "ghost", "house", "igloo", "joker", "karma", "lemon", "mango", "night", "ocean", "piano", "queen", "river", "sugar", "table", "umbra", "virus", "water", "xenon", "youth"};
    int k = randint(0,24);
    strcpy(WORDLE,fiveLetterWords[k]);
    }
}
void pick6()
{
    char data[7];
    FILE *file = fopen("C:/Users/itsar/OneDrive/Documents/GitHub/Wordle-in-C-1st-sem/letter6/common6.txt", "r");
    int len = 0;
    while(fgets(data, sizeof(data), file))
    {
        len++;
    }
    int var;
    var = randint(0,len);
    len=0;
    fclose(file);
    FILE *foil = fopen("C:/Users/itsar/OneDrive/Documents/GitHub/Wordle-in-C-1st-sem/letter6/common6.txt", "r");
    while(fgets(data, sizeof(data), foil))
    {
        if(len==var)
        {
            strcpy(WORDLE,data);
            break;
        }
        len++;
    }
    if(strlen(WORDLE)!=6)
    {
    char sixLetterWords[25][7] = {"banana", "camera", "dancer", "eleven", "family", "guitar", "honest", "insect", "jacket", "kettle", "lemon", "monkey", "number", "orange", "pencil", "quartz", "rabbit", "singer", "tissue", "umbrella", "violet", "window", "xyloph", "yellow"};
    int k = randint(0,24);
    strcpy(WORDLE,sixLetterWords[k]);
    }
}
//Checks if a character is in a string or not
int init(char ch) {
    for (int i = 0; i < level; i++) {
        if (WORDLE[i] == ch) {
            return 1;
        }
    }
    return 0;
}
//Check if the user entered word is correct
int checkWin()
{
    if(!strcmp(turn,WORDLE))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//A minigame
void unscramble()
{
    system("cls");
    printf("Welcome to unscramble!");
    printf("\nIt is a simple game where you have to unscramble the given word.");
    printf("\nYou will be given 3 chances to unscramble the word.");
    printf("\nThere will be 10 rounds!");
    nextslide(15);
    loading();
    system("cls");
    for(int  j=0;j<10;j++)
    {
    begin:
    generateRandomWord();
    scramble();
    printf("The word is: %s\n",scrambled);
        printf("Attempt %d\n",j+1);
    for(int i=0;i<3;i++)
    {
        char word[10];
        printf("Enter guess number %d: ",i+1);
        scanf("%s",word);
        if(!strcmp(word,WORDLE))
        {
            printf("Great Job!");
            nextslide(2);
            break;
        }
    }
    printf("The word was %s",WORDLE);
    nextslide(3);
    }
}
//scrambles a word
void scramble()
{
    strcpy(WORDLE2,WORDLE);
    for(int i=0;i<strlen(WORDLE);i++)
    {
        int j = randint(0,strlen(WORDLE2)-1);
        *(scrambled+i) = *(WORDLE2+j);
        deleter(j);
    }
    *(scrambled+strlen(WORDLE)-1) = *WORDLE2;
}
int deleter(int num)
{
    for(int i=num;i<strlen(WORDLE2);i++)
    {
        *(WORDLE2+i) = *(WORDLE2+i+1);
    }
}
int numinit(int num,int rand[level])
{
    for(int i=0;i<level;i++)
    {
        if(*(rand+i)==num)
        {
            return 1;
        }
    }
    return 0;
}
//This is a minigame quiz
void quiz()
{
    system("cls");
    printf("Welcome to the English Proficiency Test!");
    nextslide(3);
    printf("\nThis is a test to check your proficiency in English.");
    nextslide(2);
    printf("\nThere will be 20 questions.");
    printf("\nYou will be given 4 options for each question.");
    nextslide(3);
    printf("\nYou will have to guess the correct word from the description.");
    printf("\nYou will be given 1 mark for each correct answer.");
    printf("\nThere is no negative marking.");
    nextslide(3);
    printf("\nAll the best!");
    nextslide(1);
    loading();
    system("cls");
    int score = 0;
    /*pattern
    question
    option(1,2,3,4)
    answer
    */
   char buffer[100];
   printf("What is an indefinetely long amount of time?\n");
   scanf("%s",buffer);
    if(!strcmp(buffer,"aeon"))
    {
         score++;
    }
    printf("What is the study of the origin of words?\n");
    scanf("%s",buffer);
    if(!strcmp(buffer,"etymology"))
    {
         score++;
    }
    printf("What is the study of the meaning of words?\n");
    scanf("%s",buffer);
    if(!strcmp(buffer,"semantics"))
    {
         score++;
    }
    printf("What is the study of the structure of words?\n");
    scanf("%s",buffer);
    if(!strcmp(buffer,"morphology"))
    {
         score++;
    }
    printf("What is the study of the sound of words?\n");
    scanf("%s",buffer);
    if(!strcmp(buffer,"phonology"))
    {
         score++;
    }
    printf("What is the study of the formation of sentences?\n");
    scanf("%s",buffer);
    if(!strcmp(buffer,"syntax"))
    {
         score++;
    }
    printf("A word that is fluent and smooth but innocent and shallow?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"glib"))
    {
        score++;
    }
    printf("A word that means to make something less severe or intense?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"abate"))
    {
        score++;
    }
    printf("A word that means to make something more attractive or interesting?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"spice"))
    {
        score++;
    }
    printf("A word that means to make something more complex or difficult to understand?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"obscure"))
    {
        score++;
    }
    printf("A word that means to make something more lively or exciting?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"enliven"))
    {
        score++;
    }
    printf("A word that means to make something more intense or extreme?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"heighten"))
    {
        score++;
    }
    printf("A word that means to make something more clear or understandable?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"clarify"))
    {
        score++;
    }
    printf("A word that means to make something more beautiful or attractive?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"beautify"))
    {
        score++;
    }
    printf("A word that means to make something more interesting or exciting?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"fascinate"))
    {
        score++;
    }
    printf("A word that means to make something more fluent and smooth but innocent and shallow?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"glib"))
    {
        score++;
    }
    printf("A word that means to make something less severe or intense?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"abate"))
    {
        score++;
    }
    printf("A word that means to make something more attractive or interesting?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"spice"))
    {
        score++;
    }
    printf("A word that means to make something more complex or difficult to understand?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"obscure"))
    {
        score++;
    }
    printf("A word that means to make something more lively or exciting?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"enliven"))
    {
        score++;
    }
    printf("A word that means to make something more intense or extreme?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"heighten"))
    {
        score++;
    }
    printf("A word that means to make something more clear or understandable?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"clarify"))
    {
        score++;
    }

    printf("A word that means to make something more beautiful or attractive?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"beautify"))
    {
        score++;
    }
    printf("A word that means to make something more interesting or exciting?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"fascinate"))
    {
        score++;
    }
    printf("A word that means to make something more peaceful or calm?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"pacify"))
    {
        score++;
    }
    printf("A word that means to make something more lively and cheerful?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"enliven"))
    {
        score++;
    }
    printf("A word that means to make something more complicated or difficult?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"complicate"))
    {
        score++;
    }
    printf("A word that means to make something more mysterious or puzzling?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"mystify"))
    {
        score++;
    }
    printf("A word that means to make something more attractive or interesting?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"allure"))
    {
        score++;
    }
    printf("A word that means to make something more lively or energetic?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"vitalize"))
    {
        score++;
    }
    printf("A word that means to make something more complex or intricate?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"elaborate"))
    {
        score++;
    }
    printf("A word that means to make something more beautiful or attractive?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"ornament"))
    {
        score++;
    }
    printf("A word that means to make something more peaceful or calm?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"tranquilize"))
    {
        score++;
    }
    printf("A word that means to make something more lively or exciting?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"stimulate"))
    {
        score++;
    }
    printf("A word that means to make something more complex or difficult to understand?");
    scanf("%s",buffer);
    if(!strcmp(buffer,"complicate"))
    {
        score++;
    }
// One-word questions related to the history of English and its literature
printf("A word that means a medieval poet or musician who sang or recited poems, especially epic poems?");
scanf("%s",buffer);
if(!strcmp(buffer,"scop"))
{
    score++;
}
printf("A word that means a long narrative poem, especially one that tells the deeds and adventures of heroic or legendary figures or the history of a nation?");
scanf("%s",buffer);
if(!strcmp(buffer,"epic"))
{
    score++;
}
printf("A word that means a type of poem that expresses the thoughts and feelings of the poet, often in a song-like style?");
scanf("%s",buffer);
if(!strcmp(buffer,"lyric"))
{
    score++;
}
printf("A word that means a type of poem that tells a story, often in a song-like style?");
scanf("%s",buffer);
if(!strcmp(buffer,"ballad"))
{
    score++;
}
printf("A word that means a type of play that is serious and often ends in disaster for the main character?");
scanf("%s",buffer);
if(!strcmp(buffer,"tragedy"))
{
    score++;
}
printf("A word that means a type of play that is funny and often ends happily?");
scanf("%s",buffer);
if(!strcmp(buffer,"comedy"))
{
    score++;
}
printf("A word that means a type of play that is serious and often ends happily?");
scanf("%s",buffer);
if(!strcmp(buffer,"romance"))
{
    score++;
}
printf("A word that means a type of play that is serious and often deals with historical events or figures?");
scanf("%s",buffer);
if(!strcmp(buffer,"history"))
{
    score++;
}
printf("A word that means a type of play that is serious and often deals with moral or ethical issues?");
scanf("%s",buffer);
if(!strcmp(buffer,"morality"))
{
    score++;
}
printf("A word that means a type of play that is serious and often deals with religious or spiritual themes?");
scanf("%s",buffer);
if(!strcmp(buffer,"mystery"))
{
    score++;
}
printf("Well Played!");
printf("\nYour score is %d",score);
printf("\nPress 1 to print your certificate!");
int ch;
scanf("%d",&ch);
if(ch==1)
{
    system("cls");
    printf("Congratulations!");
    printf("\nYou have successfully completed the English Proficiency Test!");
    printf("\nYou have scored %d out of 30!",score);
    printf("\nYou are hereby awarded the certificate of English Proficiency!");
    printf("\n\n---\n\n");
    printf("Press 1 to play again\nPress 2 for a practise minigame\nPress 3 to leave");
    int ch;
    scanf("%d",&ch);
    if(ch==1)
    {
        system("cls");
        for(int i=0;i<=3;i++)
        {
            printf("Resetting Parameters!");
            for(int j=0;j<=i;j++)
            {
                printf(".");
            }
            pause(300);
            system("cls");
        }
        //This will launch the main program from here
        level = 0;
        round = 0;
        for(int i=0;i<6;i++)
        {
            for(int j=0;j<6;j++)
            {
                GUESS[i][j] = '-';
            }
        }
        for(int i=0;i<6;i++)
        {
            for(int j=0;j<6;j++)
            {
                SOLUTION[i][j] = 0;
            }
        }
        *WORDLE = '\0';
        *turn = '\0';
        *scrambled = '\0';
        *WORDLE2 = '\0';
        main();
}
    }
    else if(ch==2)
    {
        unscramble();
    }
    else if(ch==3)
    {
        quiz();
    }
    else
    {
        system("cls");
        printf("Thank you for playing!");
        exit(0);
        return 0;
    }
}
/*
Submitted for MiniProject
OddSem 2023
Class of 2027
Batch -> B9
Branch -> BTech CSE
Members:
    Risha Gupta
    Devyani Sharma
    Arnav Sharma
    Anushka Tayal
*/
