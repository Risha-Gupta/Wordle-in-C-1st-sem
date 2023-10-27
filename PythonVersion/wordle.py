#Code for a game of wordle
import os #to use clear screen
import time#To use sleep function and measure time taken...if we want to add something like that
import csv
import random
import sys
global game
def cls():
    os.system('cls' if os.name == 'nt' else 'clear')
def startingScreen():#def is used to display the main screen
    cls()#Just clears the screen
    i=input("...Press Enter to Start...")
    time.sleep(0.1)
    cls()
    for i in range(0,4):#Will show Loading... in a cool way
        print("Loading"+"."*i)
        time.sleep(0.5)
        cls()
def selectCSV():#To choose the random word from the short list
    with open("wordle.csv","r") as myFile:
        reade = csv.reader(myFile)
        dictionary = []#Dictionary is a list (or array) that has list of all the strings in "wordle.csv"
        for i in reade:
            dictionary.append(i[0])
        return(dictionary[random.randint(0,len(dictionary)-1)])#This will generate a random natural number under dict length
        #Then returns the string
def generateLevel(n):#To generate the grids
    level = ["_","_","_","_","_"]
    game = []
    for i in range(n):
        game.append(level)
    return(game)
def levelInput():
    turns=int(input("How Many Levels Do You Want? "))
    game = generateLevel(turns)
    cls()
    return [turns,game]
def displayGame(game,result,level,turns):
    cls()
    for i in range(turns):
        res=''
        for j in range(5):
            res+=" "+game[i][j]+result[i][j]+" "
        if(level==i):
            for k in range(len(res)):
                print(res[0:k],"\r",end='')
                time.sleep(0.1)
        else:
            print(res,end='')
        print()
    print("Enter the Word here: ",end="")
def wordleListGenerator():
    with open("wordlepp.csv","r") as myFile:
        reade = csv.reader(myFile)
        wordleList = []
        for i in reade:
            wordleList.append(i[0])
    return wordleList
def inputWord(wordleList,game,result,level,turns):
    userGuess = input()
    userGuess=userGuess.lower()
    if(len(userGuess)!=5):
        print("Enter a 5 letter word.")
        time.sleep(2)
        cls
        displayGame(game,result,level,turns)
        return(inputWord(wordleList,game,result,level,turns))
    elif(userGuess not in wordleList):
        print("Word not in dictionary")
        time.sleep(2)
        cls()
        displayGame(game,result,level,turns)
        return(inputWord(wordleList,game,result,level,turns))
    else:
        return(userGuess)
def modifyGrid(wordle,userGuess,game,result,i):
    for j in range(5):
        game[i]=userGuess
        if(userGuess[j] in wordle):
            if(userGuess[j]==wordle[j]):
                result[i][j]=' 🟩 '
            else:
                result[i][j]=' 🟧 '
        else:
            result[i][j]=' ⬛ '
def win(wordle,i):
    time.sleep(2)
    cls()
    print("\rCongratulations🥳🥳🥳!\nYou guessed the correct word '",wordle,"' in ",i+1,"attempts.")
    time.sleep(5)
    sys.exit()
def lost(wordle):
    cls()
    print("\rYou exceeded the maximum number of trials‼️\nThe correct answer was ",wordle)
#----------------------------------------------------------------------------------------------main Function
startingScreen()
wordle = selectCSV()#This will put a random word from the shorter list into wordle variable
 #                   The user is supposed to guess the word in "wordle"
gar = levelInput()
turns = gar[0]
game = gar[1]
result=[]
wordleList = wordleListGenerator()
for i in range(turns):
    result.append(["    ","    ","    ","    ","    "])
displayGame(game,result,0,turns)
for i in range(turns):
    userGuess = inputWord(wordleList,game,result,i,turns)
    modifyGrid(wordle,userGuess,game,result,i)
    displayGame(game,result,i,turns)
    if(wordle==userGuess):
        win(wordle,i)
lost(wordle)
time.sleep(5)