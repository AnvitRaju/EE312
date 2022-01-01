#include <stdio.h>
#include <assert.h>
#include <string.h>

#define SIZE 26

int are_anagrams(char[], char[]);
int sortword(char[]);

int main() {
    printf("running test 'iceman' and 'cinema'...\n");
    char iceman[] = "iceman";
    char cinema[] = "cinema";

    assert(are_anagrams(iceman, cinema));
    printf("passed!\n");

    printf("running test 'raganam' and 'anagram'...\n");
    char raganam[] = "raganam";
    char anagram[] = "anagram";

    assert(are_anagrams(raganam, anagram));
    printf("passed!\n");
    
    printf("running test 'listen' and 'silent'...\n");
    char listen[] = "listen";
    char silent[] = "silent";

    assert(are_anagrams(listen, silent));
    printf("passed!\n");

    printf("running test 'mole' and 'meal'...\n");
    char mole[] = "mole";
    char meal[] = "meal";

    assert(!are_anagrams(mole, meal));
    printf("passed!\n");

    printf("running test 'happy' and 'sad'...\n");
    char happy[] = "happy";
    char sad[] = "sad";

    assert(!are_anagrams(happy, sad));
    printf("passed!\n");
}

int sortword(char word[]){
    char origletter;
    for (int i=0; i<strlen(word)-1; i++){
        for (int j=i+1; j<strlen(word); j++){
            if (word[i]>word[j]){
                origletter = word[i];
                word[i] = word[j];
                word[j] = origletter;
            }
        }
    }
}

int are_anagrams(char first_word[], char second_word[]) {
    if (strlen(first_word) != strlen(second_word)){
        return 0; //words are not anagrams
    }
    sortword(first_word);
    sortword(second_word);

    for (int i=0; i<strlen(first_word); i++){
        if (first_word[i] != second_word[i]){
            return 0; //words are not anagrams
        }
    }
}
