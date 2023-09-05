
// Project title : Payment Application.
// Name : Magdy Ahmed Abass Abdelhamid.
// Country : Egypt , City : Giza.
// I am a student in Faculty of Engineering, Cairo University, Electronics and Electrical Communication Departement

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
} ST_cardData_t;

typedef struct ST_terminalData_t
{
    double transAmount;
    double maxTransAmount;
    uint8_t transactionDate[11];
} ST_terminalData_t;

typedef enum EN_transStat_t
{
    DECLINED, APPROVED
} EN_transStat_t;

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t transData;
    EN_transStat_t transStat;
} ST_transaction_t;

typedef struct ST_accountBalance_t
{
    uint8_t primaryAccountNumber[20];
    double balance;
} ST_accountBalance_t;

extern void card(struct ST_cardData_t *card);

extern uint8_t terminal(struct ST_cardData_t *card, struct ST_terminalData_t *terminal);
extern uint8_t checkDate(uint8_t expirationDate[6], uint8_t terminalDate[11]);

extern uint8_t server(struct ST_accountBalance_t *dataBase, struct ST_cardData_t *card, struct ST_terminalData_t *terminal);
extern uint8_t linearSearch(struct ST_accountBalance_t *dataBase, uint8_t size, uint8_t *target);
extern void printArray(struct ST_accountBalance_t *dataBase, uint32_t size);


// data base of the payment application
struct ST_accountBalance_t dataBase[] =
{
    {"123456789", 1000.00},
    {"234567891", 6000.00},
    {"567891234", 3250.25},
    {"456789123", 1500.12},
    {"258649173", 500.00},
    {"654823719", 2100.00},
    {"971362485", 0.00},
    {"793148625", 900.00},
    {"123123456", 150.12},
    {"456789321", 8000.55},
};

// prototype of clear function, it is used to clear the structures after the transaction
void clear(struct ST_cardData_t *c, struct ST_terminalData_t *t);

int main()
{
    //Initializing the card and terminal structures
    struct ST_cardData_t c = {"", "", ""};
    struct ST_terminalData_t t = {0.0, 6000.0, ""};
    //Initializing user input, 'y'--> yes, and 'n'--> no
    uint8_t userInput = 'y';
    // creating pointers to structs to pass by reference the structures to external functions
    struct ST_cardData_t *cptr = &c;
    struct ST_terminalData_t *tptr = &t;
    printf("\t\tWelcome\n");
    //program loop
    while (userInput == 'y')
    {
        //sending the card struct to the card function to store the card data in it
        card(cptr);
        //sending the terminal struct to the terminal function to store the terminal data in it
        /* the terminal function will return either 1, or 255
            -'1' if the terminal conditions are successfully completed
            -'255' if error happened during the conditions
        */
        uint8_t result = terminal(cptr, tptr);
        if (result == 1)
        {
            // if terminal conditions are successfully done, the server function will be executed
            // the result variable here that this function will return is the index of the user
            // the index is used to update the data base with the new balance
            result = server(dataBase, cptr, tptr);
        }
        if (result != 255)
        {
            // updating the balance of the user with index [result] with his new balance after transaction
            dataBase[result].balance = dataBase[result].balance - t.transAmount;
        }
        // print array function is used to print the database to show how it is automatically updated after each successful transaction
        printArray(dataBase, 10);
        // clear function is used after each transaction to clear the structs variables
        clear(cptr, tptr);
        // check whether user wants to create another transaction or not
        printf("Do you want to continue (y/n)?\n");
        scanf(" %c", &userInput);
    }
    return 0;
}

// implementation of clear function
// it is used in main() to clear the attributes of the struct after each transaction
void clear(struct ST_cardData_t *c, struct ST_terminalData_t *t)
{
    memset(c->primaryAccountNumber, 0, 20);
    memset(c->cardHolderName, 0, 25);
    memset(c->cardExpirationDate, 0, 6);
    memset(t->transactionDate, 0, 11);
    t->transAmount = 0.0;
    t->maxTransAmount = 6000;
}


// reading card data from user
// placing data entered in the struct that will be passed to this function
void card(struct ST_cardData_t *client)
{
    printf("Please enter card data:\n");
    printf("Please enter card holder name:\n");
    scanf("%[^\n]%*c", client->cardHolderName);
    printf("Please enter account number:\n");
    scanf(" %s", client->primaryAccountNumber);
    printf("Please enter card Expiry Date:\t\t(MM/YY)\n");
    scanf(" %s", client->cardExpirationDate);
}


// used to search for a target string in an array
// target here will be the primary account number user entered
// array is the primary account numbers in the data base
uint8_t linearSearch(struct ST_accountBalance_t *dataBaseaccounts, uint8_t size, uint8_t *target)
{
    for (int i = 0; i < size; i++)
    {
        // check whether the two strings are equal or not
        if (strcmp((char *) dataBase[i].primaryAccountNumber, (char *) target) == 0)
        {
            // if found return index of the customer
            return i;
        }
    }
    return -1;
}

// function used to print the array-> used to show the update in database after each transaction
void printArray(struct ST_accountBalance_t *dataBaseaccounts, uint32_t size)
{
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        printf("%s\t%0.2f\n", dataBase[i].primaryAccountNumber, dataBase[i].balance);
    }
}


// store terminal data user entered transaction amount and transaction date
uint8_t terminal(struct ST_cardData_t *c, struct ST_terminalData_t *t)
{
    printf("\nPlease enter terminal data:\n");
    printf("Please Enter the transaction Amount:\n");
    scanf("%lf", &t->transAmount);
    // check if the transaction amount is bigger than the max terminal amount
    if (t->transAmount > t->maxTransAmount)
    {
        printf("The Transaction is DECLINED\n");
        printf("Error: Transaction Amount > Maximum Transaction Amount\n");
        return -1;
    }
    // if the transaction amount < max transaction amount the code will proceed
    printf("Please Enter transaction Date:\t\t (DD/MM/YYYY)\n");
    scanf(" %s", t->transactionDate);
    // check whether the card is expired or not
    uint8_t dateValidation = checkDate(c->cardExpirationDate, t->transactionDate);
    if (dateValidation == 0)
    {
        printf("The Transaction is DECLINED\n");
        printf("Error: Card is Expired!\n");
        return -1;
    }
    // if the code reached this far it indicates that the terminal conditions are all passed successful
    return 1;
}

// fucntion used to compare the dates
uint8_t checkDate(uint8_t expirationDate[6], uint8_t terminalDate[11])
{
    // creating pointers at exact locations at both character arrays

    // expiration date example: MM/YY
    // last 2 digits indicates to year
    uint8_t *expirationDateYears  = &expirationDate[3];
    // first 2 digits indicates to month
    uint8_t *expirationDateMonths = &expirationDate[0];

    // terminal date example: DD/MM/YYYY
    // last 2 digits indicates to years that will be compared
    uint8_t *terminalDateYears    = &terminalDate[8];
    // Months digits that will be compared
    uint8_t *terminalDateMonths   = &terminalDate[3];

    // creating integers with a format of "YYMM" to compare between them
    uint32_t expirationDateInt = 100 * atoi((char *)expirationDateYears) + atoi((char *)expirationDateMonths);
    uint32_t terminalDateInt = 100 * atoi((char *)terminalDateYears) + atoi((char *)terminalDateMonths);
    // comparing
    if (terminalDateInt < expirationDateInt)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


// server function is created to search for the user in the data base and checks his balance if found
uint8_t server(struct ST_accountBalance_t *dataBaseaccounts, struct ST_cardData_t *card, struct ST_terminalData_t *t)
{
    // using linear search algorithm to search for the primary account number user entered
    uint8_t result = linearSearch(dataBase, 10, card->primaryAccountNumber);
    // 255 indicates not fount --> '-1'
    if (result == (255))
    {
        printf("The Transaction is DECLINED\n");
        printf("Error: Account is not found !\n");
        return -1;
    }

    /*if code reached here it indicates that the account is found
     and the result variable hold index of the user account, balance
     */
    // checks whether the account balance is sufficient or not for the transaction
    if (dataBase[result].balance < t->transAmount)
    {
        printf("The Transaction is DECLINED\n");
        printf("Error: Transaction amount > Account Balance.\n");
        return -1;
    }
    //function successfully ended if the code reached here
    printf("The Transaction is APPROVED.\n");
    // returning the result to update teh database
    return result;
}