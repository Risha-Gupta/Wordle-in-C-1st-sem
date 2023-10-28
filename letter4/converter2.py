import csv
words = []
with open("wordle4.txt","r") as reade:
    alltext = reade.read()
    for wordIndex in range(len(alltext)-4):
        if(alltext[wordIndex].isnumeric() and alltext[wordIndex+1].isalpha()):
            words.append(alltext[wordIndex+1:wordIndex+5])
        
with open("wordle4letter.txt", "w") as file:
    for word in words:
        file.write(word + "\n")