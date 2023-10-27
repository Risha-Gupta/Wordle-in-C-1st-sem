#Python code to convert that ugly txt 6 letter word list to a neat csv/txt
import csv
words = []#This is supposed to keep the lists
with open("wordle6.txt","r") as reade:
    alltext = reade.read()
    for wordIndex in range(len(alltext)):
        #Now alltext is a string where every letter is an element, we need to find 6 letter words from it and
        if(alltext[wordIndex].isupper()):#The words in the txt start with uppercase, so it will only return true when a 6 letter word starts
            #That was my assumption, which was later proved to be true
            alltext[wordIndex].lower()
            words.append((alltext[wordIndex:wordIndex+6]).lower())#It will add the allsmallcase 6 letter sets to words list
# Open the file in write mode
with open("wordle6letter.txt", "w") as file:
    # Write each element of the list on a new line
    for word in words:
        file.write(word + "\n")