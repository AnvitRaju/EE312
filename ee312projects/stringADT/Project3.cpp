// String ADT <Project3.cpp>
// EE 312 Project 3 submission by
// Anvit Raju
// ar68234
// Slip days used: (1 already used for Project 1, 1 remaining)
// Fall 2021



#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "UTString.h"

/*
 * Helper macro to find the signature of a UTString
 * Treat this like a function that takes a UTString*
 * Accesses a uint32_t from where the signature should be located
 */
#define CHECK(s) (*(uint32_t*) ((s)->string + (s)->length + 1))

/*
 * Checks if a UTString is valid or not.
 */
bool isOurs(const UTString* s) {
    if (CHECK(s) == SIGNATURE) {
        return true;
    }
    else {
        return false;
    }
}

/*
 * Allocate a utstring on the heap.
 * Initialize the string correctly by copying src.
 * Return a pointer to the UTString.
 */
UTString* utstrdup(const char* src) {
    //Allocate UTString on heap
    UTString* str = (UTString*)malloc(sizeof(UTString));

    //length of src to use for struct
    int len = strlen(src);

    str->length = len;
    str->capacity = len;
    str->string = (char*)malloc((sizeof(char))*(len+5));

    //copy src into string
    for (int i=0; i<(len+1); i++){
        str->string[i] = src[i];
    }

    CHECK(str) = SIGNATURE;
    return str;
}

/*
 * Returns the length of s.
 *  s must be a valid UTString.
 */
uint32_t utstrlen(const UTString* s) {
    assert(isOurs(s));
    return s->length;
}

/*
 * Append the string suffix to the UTString s.
 *  s must be a valid UTString.
 * Do not allocate any additional storage: only append as many characters
 *  as will actually fit in s.
 * Update the length of s.
 * Return s with the above changes. */
UTString* utstrcat(UTString* s, const char* suffix) {
    assert(isOurs(s));

    int len = s->length;
    int cap = s->capacity;
    int lenofSuffix = strlen(suffix); //holds the length of suffix

    int totallen = s->length+lenofSuffix; //used for iterating through UTString s with the appended suffix

    int i = 0;

    for (len; ((len < cap) && (len < totallen)); len++) {
        s->string[len] = suffix[i];
        i += 1;
    }

    s->length = len;
    s->string[len] = '\0';
    CHECK(s) = SIGNATURE;
    return s;

}

/*
 * Copy src into dst.
 *  dst must be a valid UTString.
 *  src is an ordinary string.
 * Do not allocate any additional storage: only copy as many characters
 *  as will actually fit in dst.
 * Update the length of dst.
 * Return dst with the above changes.
 */
UTString* utstrcpy(UTString* dst, const char* src) {
    assert(isOurs(dst));
    int i;
    int j = 0;
    int test = 0;

    //copy src into dst
    for (i=0; (src[i] != 0) && (i < dst->capacity); i++){
        dst->string[i] = src[i];
    }

    //check variable for debugging
    while (src[j] != 0){
        if (dst->length == dst->capacity){
            break;
        }
        test += 1;
        j++;
    }

    dst->length = i;
    dst->string[i] = '\0';

    CHECK(dst) = SIGNATURE;
    return dst;
}

/*
 * Free all memory associated with the given UTString.
 */
void utstrfree(UTString* self) {
    assert(isOurs(self));
    free(self->string);
    free(self);
}

/*
 * Make s have at least as much capacity as new_capacity.
 *  s must be a valid UTString.
 * If s has enough capacity already, do nothing.
 * If s does not have enough capacity, then allocate enough capacity,
 *  copy the old string and the null terminator, free the old string,
 *  and update all relevant metadata.
 * Return s with the above changes.
 */
UTString* utstrrealloc(UTString* s, uint32_t new_capacity) {
    assert(isOurs(s));

    //int cap = s->capacity;
    int i;
    int k = 0;
    int check = 0;

    char* originalstr = s->string;

    //make sure s has much capacity as new_capacity
    if (new_capacity < s->capacity){
        return s;
    }
    else{

        //allocate enough capacity
        char* new_string = (char*) malloc(new_capacity+5);

        s->capacity = new_capacity;
        s->string = new_string;

        for (i=0; (originalstr[i] != '\0'); i++){
            if (i<s->capacity){
                s->string[i] = originalstr[i];
            }
        }

        check++;
        int len = 1;

        check = i;
        while (k<len){
            s->length = check;
            s->string[i] = '\0';
            k += 1;
        }

        s->capacity = new_capacity;

        free(originalstr);
        CHECK(s) = SIGNATURE;
        return s;
    }
}
