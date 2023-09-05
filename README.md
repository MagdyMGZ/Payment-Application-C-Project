# Project Discribtion Link: https://review.udacity.com/#!/rubrics/4939/view
# Payment-Application-C-Project

1 - Magdy's C Project ( Payment Application ) (Which You Can Open The Code) in this Folder 
    There Is Folder That Called Magdy's C Project ( Payment Application ) Open it you Can 
    Find All The .h and .c Files
    .h files ( card.h / terminal.h / server.h / app.h )
    .c files ( card.c / terminal.c / server.c / app.c / main.c ).

2 - ScreenShots That Required In The Rubric In The Project In Folders.


Payment systems are now available everywhere and everyone interacts with these systems every day.

There are different types of transactions you can make, SALE, REFUND, Pre-Authorization, and VOID.

SALE: means to buy something and its price will be deducted from your bank account.
REFUND: this means that you will return something and wants your money back to your bank account.
Pre-Authorization: means holding an amount of money from your account, e.g Hotel reservation.
VOID: this means canceling the transaction, e.g if the seller entered the wrong amount.


You are required to implement the SALE transaction only by simulating the card, terminal(ATM), and the server.

# Payment Application

#### Video Demo:  <https://youtu.be/qVceHoUUdPI>
#### Description:

# Abstract :

This project was written in C.

Payment systems are now available everywhere and everyone interacts with these systems every day.

There are different types of transactions you can make, SALE, REFUND, Pre-Authorization, and VOID.

SALE: means to buy something and its price will be deducted from your bank account.

REFUND: this means that you will return something and wants your money back to your bank account.

Pre-Authorization: means holding an amount of money from your account, e.g Hotel reservation.

VOID: this means canceling the transaction, e.g if the seller entered the wrong amount.

I implement the SALE transaction only by simulating the card, terminal(ATM), and the server.

I used these libraries in this project :
<stdio.h> , <string.h> , <math.h> , <stdlib.h> , <ctype.h>

# typedefs :

unsigned char to be uint8_t , unsigned int to be uint32_t.
struct ST_cardData_t : that contains the card name, the card primary account number, and card expiration date.
struct ST_terminalData_t : that contains the transaction amount, the maximum transaction amount in the transaction operation, and the transaction date.
enum EN_transStat_t : that returns the state of any thing to be DECLINED = 0 or APPROVED = 1.
struct ST_transaction_t : that contains all the above data (ST_cardData_t cardHolderData , ST_terminalData_t transData , EN_transStat_t transStat).
struct ST_accountBalance_t : which is the account data that contains the card primary account number and the balance of this account.

# Functions :

These are All the functions I thought I should highlight:

main() :
1 - Initializing the card and terminal structures.
2 - Initializing user input, 'y'--> yes, and 'n'--> no.
3 - creating pointers to structs to pass by reference the structures to external functions.
4 - program loop if userInput == 'y' else close the program.
5 - sending the card struct to the card function to store the card data in it & sending the terminal struct to the terminal function to store the terminal data in it.
6 - if terminal conditions are successfully done, the server function will be executed.
7 - print array function is used to print the database to show how it is automatically updated after each successful transaction.
8 - clear function is used after each transaction to clear the structs variables.
9 - check whether user wants to create another transaction or not.

card() :
1 - reading card data from user.
2 - placing data entered in the struct that will be passed to this function.
3 - prompt the user for The Card Holder's Name.
4 - prompt the user for the card PAN (Primary Account Number).
5 - prompt the user for the card expiry date int this format (MM/YY).

terminal() :
1 - store terminal data user entered (transaction amount and transaction date).
2 - prompt the user for The Transaction Amount.
3 - check if the transaction amount is bigger than the max terminal amount.
4 - if the transaction amount < max transaction amount the code will proceed.
5 - check whether the card is expired or not from checkDate function.

checkDate() :
fucntion used to compare the dates (The Expiration Date of the Card & The Transaction Date).

server() :
1 - created to search for the user in the data base and checks his balance if found.
2 - using linear search algorithm to search for the primary account number user entered.
3 - checks whether the account balance is sufficient or not for the transaction.

linearSearch() :
1 - used to search for a target string in an array.
2 - target here will be the primary account number user entered.
3 - array is the primary account numbers in the data base.

printArray() :
used to print the array-> used to show the update in database after each transaction.

clear() :
it is used in main() to clear the attributes of the struct after each transaction.

# Instructions :

You would find demonstrated test cases (User Stories).
This demonstrates how someone would use the Simulator.

The test cases describe different scenarios that would happen:

1 - Transaction approved user story :
As a bank customer have an account and has a valid and not expired card, I want to withdraw an amount of money less than the maximum allowed and
less than or equal to the amount in my balance, so that I am expecting that the transaction is approved and my account balance is reduced by the withdrawn amount.
# (Happy Story Prints The Transaction is APPROVED.)

2 - Exceed the maximum amount user story :
As a bank customer have an account, that has a valid and not expired card, I want to withdraw an amount of money that exceeds the maximum allowed
amount so that I am expecting that the transaction declined.
# (prints The Transaction is DECLINED & Error: Transaction Amount > Maximum Transaction Amount).

3 - Insufficient fund user story :
As a bank customer have an account and has a valid and not expired card, I want to withdraw an amount of money less than
the maximum allowed and larger than the amount in my balance so that I am expecting that the transaction declined.
# (prints The Transaction is DECLINED & Error: Transaction amount > Account Balance).

4 - Expired card user story :
As a bank customer have an account, have a valid but expired card, I want to withdraw an amount of money so that
I expect that the transaction declined.
# (prints The Transaction is DECLINED & Error: Card is Expired!).

5 - Invalid card user story:
As a bank customer have an account and has a valid and not expired stolen card, I want to block anyone from using my card
so that I am expecting that any transaction made by this card is declined.
# (prints The Transaction is DECLINED & Error: Account is not found).

# Data Base :

In each Account there is a Primary account number and the account balance amount.

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