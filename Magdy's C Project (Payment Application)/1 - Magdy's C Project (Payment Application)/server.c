#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "server.h"
                                                                  
// Valid Accounts Data Base                                    
ST_accountsDB_t accounts_database[max] = { {1000.0,RUNNING,"1234512345123450"}, {900.0 ,BLOCKED,"3412512345123451"},
                                           {100.0 ,RUNNING,"5634512345123452"}, {200.0 ,BLOCKED,"7834512345123453"}, 
                                           {6000.0,RUNNING,"9834512345123454"}, {6500.0,BLOCKED,"8734512345123455"}, 
                                           {5000.0,RUNNING,"7634512345123456"}, {4000.0,BLOCKED,"1234512345123457"}, 
                                           {8000.0,RUNNING,"6534512345123458"}, {7500.0,BLOCKED,"4034512345123459"} };
// set the transaction data base with 0s
ST_transaction_t transactions_database[max] = { 0 };
// number of transactions
uint32_t trans_number = 0;

//  the number of accounts (reference)
uint32_t account_number = 0;

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
    // store in enum variables the state for account_validity & amount_availability & trans_saving
    EN_serverError_t account_validity = isValidAccount(&transData->cardHolderData, accounts_database[account_number].primaryAccountNumber);
    EN_serverError_t amount_availability = isAmountAvailable(&transData->terminalData);
    EN_serverError_t trans_saving = saveTransaction(transData);
    // if the isValidAccount function return ACCOUNT_NOT_FOUND the card is FRAUD_CARD
    if (account_validity == ACCOUNT_NOT_FOUND)
    {
        return FRAUD_CARD;
    }
    // if the isAmountAvailable function return LOW_BALANCE when the transaction amount greater than the balance amount, therefore DECLINED_INSUFFECIENT_FUND
    if (amount_availability == LOW_BALANCE)
    {
        return DECLINED_INSUFFECIENT_FUND;
    }
    // if the saveTransaction function returns SAVING_FAILED can't save the transaction data, therefore INTERNAL_SERVER_ERROR or 
    // If the transaction can't be saved, for any reason (ex: dropped connection) will return SAVING_FAILED
    if (trans_saving == SAVING_FAILED)
    {
        return INTERNAL_SERVER_ERROR;
    }
    // show the Balance before updating the data base balance due to transaction operation
    printf("Balance Before Transaction : %f\n", accounts_database[account_number].balance);
    // update the data base with the new balance 
    accounts_database[account_number].balance -= transData->terminalData.transAmount;
    // show the Balance after updating the data base balance due to transaction operation
    printf("Balance After Transaction : %f\n", accounts_database[account_number].balance);

    return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
    // loop on accounts_database to check the existent of PAN and increment the account numbers 
    for (account_number = (account_number + 0) ; account_number < max ; account_number++)
    {
        if (strcmp(cardData->primaryAccountNumber, accounts_database[account_number].primaryAccountNumber) == 0)
        {
            return SERVER_OK;
        }
    }
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
    // check the availablity of the transaction amount, if the trans amount > data base balace , return low balance else server is ok 
    if (termData->transAmount > accounts_database[account_number].balance)
    {
        return LOW_BALANCE;
    }
    else
    {
        return SERVER_OK;
    }
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
    transData->transactionSequenceNumber = trans_number;
    if (transData->transactionSequenceNumber < max)
    {
        // save the user transaction data in transactions_database array
        transactions_database[transData->transactionSequenceNumber].transState = transData->transState;
        transactions_database[transData->transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber + 1;
        transactions_database[transData->transactionSequenceNumber].terminalData = transData->terminalData;
        transactions_database[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData;
        // increment the number of transactions 
        trans_number++;
        return SERVER_OK;
    }
    // If the transaction can't be saved, for any reason (ex: dropped connection) will return SAVING_FAILED
    return SAVING_FAILED;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
    // loop on transaction_database to check that the transactionSequenceNumber is found or not 
    for (int i = 0; i < max; i++)
    {
        if (transactionSequenceNumber == transactions_database[transData->transactionSequenceNumber].transactionSequenceNumber)
        {
            return SERVER_OK;
        }
    }
    return TRANSACTION_NOT_FOUND;
}