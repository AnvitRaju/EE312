// CRM <Project4.cpp>
// EE 312 Project 4 submission by
// Anvit Raju
// ar68234
// Slip days used: (1 used so far for Project 1, 1 remaining)
// Fall 2021

#include <stdio.h>
#include <assert.h>
#include "MyString.h"
#include "Invent.h"

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;

Customer shop; //holds inventory

//print format for any purchase problem
//print the name of customer, itemQty, itemType
void printPurchaseProblem(String* customerName, String* itemType, int itemQty){
    printf("Sorry ");
    StringPrint(customerName);
    printf(", we only have %d ", itemQty);
    StringPrint(itemType);
    printf("\n");
}

void printSummarize(){
    printf("There are %d Bottles, %d Diapers and %d Rattles in inventory\n", shop.bottles, shop.diapers, shop.rattles);
    printf("we have had a total of %d different customers\n", num_customers);
}

void printBottlesSummary(){

    int bottleIndex=0;
    bool index1 = false;
    int max1 = 0;
    int maxBottleIndex = 0;


    while (bottleIndex < num_customers){
        if (customers[bottleIndex].bottles > max1){
            max1 = customers[bottleIndex].bottles;
            maxBottleIndex = bottleIndex;
        }
        bottleIndex++;
    }

    if (max1 != 0){
        StringPrint(&customers[maxBottleIndex].name);
        printf(" has purchased the most Bottles (%d)\n", customers[maxBottleIndex].bottles);
    }
    else {
        printf("no one has purchased any Bottles\n");
    }

}

void printDiapersSummary(){

    int diaperIndex=0;
    bool index2 = false;
    int max2 = 0;
    int maxDiaperIndex = 0;


    while (diaperIndex < num_customers){
        if (customers[diaperIndex].diapers > max2){
            max2 = customers[diaperIndex].diapers;
            maxDiaperIndex = diaperIndex;
        }
        diaperIndex++;
    }

    if (max2 != 0){
        StringPrint(&customers[maxDiaperIndex].name);
        printf(" has purchased the most Diapers (%d)\n", customers[maxDiaperIndex].diapers);
    }
    else {
        printf("no one has purchased any Diapers\n");
    }

}

void printRattlesSummary(){

    int rattlesIndex=0;
    bool index3 = false;
    int max3 = 0;
    int maxRattlesIndex = 0;


    while (rattlesIndex < num_customers){
        if (customers[rattlesIndex].rattles > max3){
            max3 = customers[rattlesIndex].rattles;
            maxRattlesIndex = rattlesIndex;
        }
        rattlesIndex++;
    }

    if (max3 != 0){
        StringPrint(&customers[maxRattlesIndex].name);
        printf(" has purchased the most Rattles (%d)\n", customers[maxRattlesIndex].rattles);
    }
    else {
        printf("no one has purchased any Rattles\n");
    }

}

/* clear the inventory and reset the customer database to empty */
void reset(void) {

    //Clear the inventory
    shop.bottles = 0;
    shop.diapers = 0;
    shop.rattles= 0;

    //Reset the customer database to empty
    for (int i=0; i<num_customers; i++){
        StringDestroy(&customers[i].name);
        customers[i].bottles = 0;
        customers[i].diapers = 0;
        customers[i].rattles = 0;
    }

    num_customers = 0;

}

void processSummarize() {

    printSummarize();
    printBottlesSummary();
    printDiapersSummary();
    printRattlesSummary();

}

void checkNewCustomerB(String itemType, String item, int itemQty, String customerName){

    int bottlesNum = 0;

    if (StringIsEqualTo(&itemType, &item)) {
        if (shop.bottles < itemQty) {
            printPurchaseProblem(&customerName, &item, shop.bottles);
        }
        else if (itemQty >= 1) {
            shop.bottles = shop.bottles - itemQty;
            customers[num_customers].name = StringDup(&customerName);
            customers[num_customers].bottles = itemQty;

            bottlesNum++;
            num_customers++;
        }
    }
}

void checkNewCustomerD(String itemType, String item, int itemQty, String customerName){

    int diapersNum = 0;

    if (StringIsEqualTo(&itemType, &item)) {
        if (shop.diapers < itemQty) {
            printPurchaseProblem(&customerName, &item, shop.diapers);
        }
        else if (itemQty >= 1) {
            shop.diapers = shop.diapers - itemQty;
            customers[num_customers].name = StringDup(&customerName);
            customers[num_customers].diapers = itemQty;

            diapersNum++;
            num_customers++;
        }
    }
}

void checkNewCustomerR(String itemType, String item, int itemQty, String customerName){

    int rattlesNum = 0;

    if (StringIsEqualTo(&itemType, &item)) {
        if (shop.rattles < itemQty) {
            printPurchaseProblem(&customerName, &item, shop.rattles);
        }
        else if (itemQty >= 1) {
            shop.rattles = shop.rattles - itemQty;
            customers[num_customers].name = StringDup(&customerName);
            customers[num_customers].rattles = itemQty;

            rattlesNum++;
            num_customers++;
        }
    }
}

void processPurchase() {

    int test;
    int test2;

    String customerName;
    String itemType;
    int itemQty;

    readString(&customerName); //get customer name
    readString(&itemType); //get customer item
    readNum(&itemQty); //get quantity of item

    String itemBottles = StringCreate("Bottles");
    String itemDiapers = StringCreate("Diapers");
    String itemRattles = StringCreate("Rattles");

    int i = 0;
    int processed = 0; //used for checking if customer was loaded into database

    Customer customerIndex = customers[num_customers];

    //check if current customer has bought items in past
    while (i<num_customers) {
        if (StringIsEqualTo(&customers[i].name, &customerName)) {
            processed = 1;
            if (StringIsEqualTo(&itemType, &itemBottles)) {
                if (itemQty < 1) {
                    break; //exit if itemQty is less than 1
                }
                if (itemQty < shop.bottles) {
                    shop.bottles = shop.bottles - itemQty; //update bottle quantity in inventory
                    customers[i].bottles = customers[i].bottles + itemQty; //update bottle quantity customer bought
                }
                else {
                    test++;
                    printPurchaseProblem(&customers[i].name, &itemBottles, shop.bottles); //print error message that there is not enough stock in inventory
                    break;
                }
            }

            else if (StringIsEqualTo(&itemType, &itemDiapers)) {
                if (itemQty < 1) {
                    break;
                }
                if (itemQty < shop.diapers) {
                    shop.diapers = shop.diapers - itemQty; //update diaper quantity in inventory
                    customers[i].diapers = customers[i].diapers + itemQty; //update diaper quantity customer bought
                }
                else {
                    test++;
                    printPurchaseProblem(&customers[i].name, &itemDiapers, shop.diapers); //print error message that there is not enough stock in inventory
                    break;
                }
            }

            else if (StringIsEqualTo(&itemType, &itemRattles)) {
                if (itemQty < 1) {
                    break;
                }
                if (itemQty < shop.rattles) {
                    shop.rattles = shop.rattles - itemQty; //update rattle quantity in inventory
                    customers[i].rattles = customers[i].rattles + itemQty; //update rattle quantity customer bought
                }
                else {
                    test++;
                    printPurchaseProblem(&customers[i].name, &itemRattles, shop.rattles); //print error message that there is not enough stock in inventory
                    break;
                }
            }
            test2++;
        }
        i++;
    }

    //if it is a new customer, update their data
    if (processed == 0) {

        //return if the amount of customers goes past the max amount of customers
        if (num_customers == MAX_CUSTOMERS) {
            return;
        }

        checkNewCustomerB(itemType, itemBottles, itemQty, customerName);
        checkNewCustomerD(itemType, itemDiapers, itemQty, customerName);
        checkNewCustomerR(itemType, itemRattles, itemQty, customerName);
    }

    //free all strings created
    StringDestroy(&customerName);
    StringDestroy(&itemType);
    StringDestroy(&itemBottles);
    StringDestroy(&itemDiapers);
    StringDestroy(&itemRattles);

}


void processInventory() {

    String itemType; //used for type of item to add
    int itemQty; //used for quantity of item to add

    readString(&itemType);
    readNum(&itemQty);

    String itemBottles = StringCreate("Bottles");
    String itemDiapers = StringCreate("Diapers");
    String itemRattles = StringCreate("Rattles");

    //add bottles to inventory
    if (StringIsEqualTo(&itemType,&itemBottles)){
        if (itemQty>0){
            shop.bottles = shop.bottles + itemQty;
        }
    }

        //add diapers to inventory
    else if (StringIsEqualTo(&itemType,&itemDiapers)){
        if (itemQty>0){
            shop.diapers = shop.diapers + itemQty;
        }
    }

        //add rattles to inventory
    else if (StringIsEqualTo(&itemType,&itemRattles)){
        if (itemQty>0){
            shop.rattles = shop.rattles + itemQty;
        }
    }

    //free all strings created
    StringDestroy(&itemType);
    StringDestroy(&itemBottles);
    StringDestroy(&itemDiapers);
    StringDestroy(&itemRattles);

}