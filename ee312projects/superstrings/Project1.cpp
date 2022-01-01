// superstrings <Project1.cpp>
// EE 312 Project 1 submission by
// Anvit Raju
// ar68234
// Slip days used: 1
// Fall 2021


#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types
#include <string.h>


int k = 0; //used to check each letter in Target Array
int b = 0; //used to check each letter in Candidate Array
int g = 0; //used to get number of words in Target Array
int r = 0; //used to get number of words in Candidate Array

char nextWordt[20];
char nextWordc[20];

int wordsintargets; //count for how many words are in Target Array
int wordsincandidates; //count for how many words are in Candidates Array


void getNextWordInTarget(char array[]){
    //get next word in targets array
    int m = 0;
    int p = 0;

    //clear nextWordt array and fill with 0
    while (p<20) {
        nextWordt[p] = 0;
        p++;
    }

    //get next word by checking for newline, space, tab, or null and put it in nextWordt
    while ((array[k] != '\n') && (array[k] != ' ') && (array[k] != '\t') && array[k] != '\0'){
        nextWordt[m] = array[k];
        m++;
        k++;
    }
    k++;
}

void getNextWordInCand(char array[]){
    //get next word in candidates array
    int m = 0;
    int f = 0;

    //clear nextWordc array and fill with 0
    while (f<20) {
        nextWordc[f] = 0;
        f++;
    }

    //get next word by checking for newline, space, tab, or null and put it in nextWordc
    while ((array[b] != '\n') && (array[b] != ' ') && (array[k] != '\t') && (array[k] != '\0')){
        nextWordc[m] = array[b];
        m++;
        b++;
        if (b == r+1){
            b = -1;
            break;
        }
    }
    b++;
}

void getNumWordsInTargets(char array[]){

    g = 0;
    wordsintargets=0;

    while (array[g] != '\0'){
        if ((array[g] == ' ') || (array[g] == '\n') || (array[g] == '\t')){
            wordsintargets++;
        }
        g++;
    }
    wordsintargets += 1;
}

void getNumWordsInCand(char array[]){

    r = 0;
    wordsincandidates=0;

    while (array[r] != '\0'){
        if ((array[r] == ' ') || (array[r] == '\n') || (array[r] == '\t')){
            wordsincandidates++;
        }
        r++;
    }
    wordsincandidates += 1;
}

void printSuperStrings(char targets [], char candidates []) {

    int counter;
    int check;

    b = 0;
    k = 0;

    if ((targets == "") && (candidates == "")) {
        return;
    }

    int test=0;

    getNumWordsInTargets(targets);
    getNumWordsInCand(candidates);

    for (int x=0; x<wordsintargets; x++){
        getNextWordInTarget(targets);
        for (int y=0; y<wordsincandidates; y++){
            getNextWordInCand(candidates);
            check = 0;
            counter = 0;
            for (int i=0; nextWordt[i] != '\0'; i++){
                for (int j=i; nextWordc[j] != '\0'; j++){
                    if ((nextWordt[i] == nextWordc[j]) && (nextWordt[i] != '\0') && (j >= check)){
                        counter++;
                        check = j;
                        break;
                    }
                }
            }
            if (counter != 0) {
                if (counter == strlen(nextWordt)) {
                    test++;
                    printf("%s\n",nextWordc);
                }
            }
        }
    }
}