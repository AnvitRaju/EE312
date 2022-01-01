// Set <Project5.cpp>
// EE 312 Project 5 submission by
// Anvit Raju
// ar68234
// Slip days used: <2 in total, 1 for Project 1, 1 for this Project (Project 5)>
// Fall 2021


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way.
 * Please NOTE, you are responsible for ensuring that the functions work correctly in
 * your project solution. Just because the function works correctly in my solution does
 * NOT mean that the function will work correctly in yours.
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not u sed, and capacity is ignored/unused. Functions should assume that
 * the amount of storage available in the elements[] array is equal to length
 */


/* done for you already */
void destroySet(Set* self) {
    free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
    self->len = 0;
    self->elements = nullptr;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
    self->elements = (int*) malloc(sizeof(int));
    self->elements[0] = x;
    self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
    self->elements = (int*) malloc(other->len * sizeof(int));
    for (int k = 0; k < other->len; k += 1) {
        self->elements[k] = other->elements[k];
    }
    self->len = other->len;
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
    if (self == other) { return; }

    destroySet(self);
    createCopySet(self, other);
}


/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
    int first = 0;
    int middle;
    int last = self->len-1;

    while (first <= last){
        middle = (first+last)/2;

        if (self->elements[middle] == x){
            return true;
        }
        else if (self->elements[middle] > x){
            last = middle - 1;
        }
        else {
            first = middle + 1;
        }
    }
    return false;
}

//get index of x in set
int getIndex(Set* self, int x, int j){
    int i;
    int test=0;
    j = 0;

    if (x > self->elements[self->len-1]){
        i = self->len;
    }
    else if (x < self->elements[0]){
        i = 0;
    }
    else {
        for (i=1; i<self->len-1; i++){
            test++;
            if (x < self->elements[i]){
                if (x > self->elements[i-1]){
                    return i+j;
                }
            }
        }
    }
    return i+j;
}

/*
 * add x as a new member to this set.
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
    int test = 0;
    int check = 0;

    if (isEmptySet(self)){
        createSingletonSet(self,x);
        return;
    }

    if (isMemberSet(self,x) == true){
        return;
    }

    int i = getIndex(self, x, check);

    int* insertSet = (int*)malloc(4*(self->len)+4);
    self->len++;

    for (int k=0; k<self->len; k++){
        if (k == i){
            test++;
            insertSet[k] = x;
        }
        else if (k < i){
            test++;
            insertSet[k] = self->elements[k];
        }
        else if (k > i){
            insertSet[k] = self->elements[k-1];
        }
    }
    free(self->elements);
    self->elements = insertSet;
}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
    if (isMemberSet(self,x) == false){
        return;
    }

    if (isEmptySet(self)){
        return;
    }

    int test = 0;

    for (int i=0; i<self->len; i++){
        if (self->elements[i] == x){
            test++;
            for (i; i<self->len-1; i++){
                self->elements[i] = self->elements[i+1];
            }
            self->len -=1;
            break;
        }
    }
}

/* done for you already */
void displaySet(const Set* self) {
    int k;

    printf("{");

    if (self->len == 0) {
        printf("}");
    }
    else {
        for (k = 0; k< self->len; k += 1) {
            if (k < self->len - 1) {
                printf("%d,", self->elements[k]);
            } else {
                printf("%d}", self->elements[k]);
            }
        }
    }
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    if (self->len != other->len){
        return false;
    }

    for (int i=0; i<self->len; i++){
        if (self->elements[i] != other->elements[i]){
            return false;
        }
    }
    return true;
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {

    bool check = true;

    if (other->len < self->len){
        check = false;
        return false;
    }

    int selfI=0; //index used for self set
    int otherI=0; //index used for other set

    while (selfI<self->len && check==true){
        if (otherI >= other->len){
            return false;
        }
        else if (self->elements[selfI] == other->elements[otherI]){
            selfI++;
            otherI++;
        }
        else if (self->elements[selfI] < other->elements[otherI]){
            return false;
        }
        else if (self->elements[selfI] > other->elements[otherI]){
            otherI++;
        }
    }
    return true;
}


/* done for you */
bool isEmptySet(const Set* self) {
    return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
    if (isEqualToSet(self,other)){
        return;
    }
    if (isEmptySet(self)){
        return;
    }
    /*if (isEmptySet(other)){
        self->len = 0;
        self->elements = other->elements;
        return;
    }*/

    int selfI = 0; //index used for self set
    int otherI = 0; //index used for other set
    int intersectI = 0; //index used for new set I allocated with malloc
    int test = 0; //debugging

    int* intersectSet = (int*)malloc(4*self->len);

    while ((selfI<self->len) && (otherI<other->len)){
        test++;
        if (self->elements[selfI] == other->elements[otherI]){
            intersectSet[intersectI] = self->elements[selfI];
            selfI++;
            otherI++;
            intersectI++;
        }
        else if (self->elements[selfI] < other->elements[otherI]){
            selfI++;
        }
        else {
            otherI++;
        }
    }

    free(self->elements);
    self->elements = intersectSet;
    self->len = intersectI;
    return;
}



/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
    if ((isEmptySet(self)) || (isEmptySet(other))){
        return;
    }

    int selfI = 0; //index used for self set
    int otherI = 0; //index used for other set
    int subtractI = 0; //index used for new set I allocated with malloc
    int test = 0; //debugging

    int* subtractSet = (int*)malloc(4*self->len);

    while (selfI<self->len) {
        test++;
        if (otherI >= other->len){
            subtractSet[subtractI] = self->elements[selfI];
            selfI++;
            subtractI++;
        }
        else if (self->elements[selfI] == other->elements[otherI]){
            selfI++;
            otherI++;
        }
        else if (self->elements[selfI] < other->elements[otherI]){
            subtractSet[subtractI] = self->elements[selfI];
            selfI++;
            subtractI++;
        }
        else if (self->elements[selfI] > other->elements[otherI]) {
            otherI++;
        }
    }

    free(self->elements);
    self->elements = subtractSet;
    self->len = subtractI;
    return;

}


/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
    if (isEmptySet(other)) {
        return;
    }

    int selfI = 0; //index used for self set
    int otherI = 0; //index used for other set
    int unionI = 0; //index used for new set I allocated with malloc
    int test = 0; //debugging

    int *unionSet = (int*)malloc(4*(self->len + other->len));

    while ((selfI < self->len) || (otherI < other->len)) {
        test++;
        if (selfI >= self->len) {
            unionSet[unionI] = other->elements[otherI];
            otherI++;
            unionI++;
        } else if (otherI >= other->len) {
            unionSet[unionI] = self->elements[selfI];
            selfI++;
            unionI++;
        } else if (self->elements[selfI] == other->elements[otherI]) {
            unionSet[unionI] = self->elements[selfI];
            selfI++;
            otherI++;
            unionI++;
        } else if (self->elements[selfI] > other->elements[otherI]) {
            unionSet[unionI] = other->elements[otherI];
            otherI++;
            unionI++;
        } else if (self->elements[selfI] < other->elements[otherI]) {
            unionSet[unionI] = self->elements[selfI];
            selfI++;
            unionI++;
        }
    }

    free(self->elements);
    self->elements = unionSet;
    self->len = unionI;
    return;

}
