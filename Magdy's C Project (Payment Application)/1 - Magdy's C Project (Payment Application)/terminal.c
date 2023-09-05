#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{   
	// prompt the user for The Transaction Date                     (0123456789)
	printf("Please Enter The Transaction Date in this format (DD/MM/YYYY) : ");
	scanf("%s", &termData->transactionDate);

	// corner case for the Date length
	if (strlen(termData->transactionDate) < max_transdate || (termData->transactionDate) == NULL)
	{
		return WRONG_DATE;
	}
	// corner case to check the Date format
	for (int i = 0; i < strlen(termData->transactionDate); i++)
	{
		if ((i == 2) || (i == 5))
		{
			if (termData->transactionDate[i] != '/')
			{
				return WRONG_DATE;
			}
		}
		else
		{
			if (!isdigit(termData->transactionDate[i]))
			{
				return WRONG_DATE;
			}
		}
	}
	printf("The Transaction Date is : %s\n", termData->transactionDate);
	return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	// (0123456789)              (01234)
	// (DD/MM/YYYY)              (MM/YY)
	// my goal is to get (MM)(s) and (YY)(s) characters to be integers in the same format to make the comparison 

	// pointer to the last two char in the card expiry date which represents (YY)
	uint8_t* Years_Exp_Date = &cardData->cardExpirationDate[3];

	// pointer to the first two char in the card expiry date which represents (MM)
	uint8_t* Months_Exp_Date = &cardData->cardExpirationDate[0];

	// pointer to the last two char in the transaction date which represents (YY) 
	uint8_t* Years_Trans_Date = &termData->transactionDate[8];

	// pointer to the two char in the transaction date which represents (MM) in the format (DD/MM/YYYY)
	uint8_t* Months_Trans_Date = &termData->transactionDate[3];

	// creating integers with a format of "YYMM" to compare between them
	// atoi function is in #include <stdlib.h> library that converts our any char* to integer digits
	// atoi converts uint8_t* to integers then do comparison
	unit32_t EXP_Date_Int = 100 * atoi(Years_Exp_Date) + atoi(Months_Exp_Date);
	unit32_t Trans_Date_Int = 100 * atoi(Years_Trans_Date) + atoi(Months_Trans_Date);
	// The Comparison
	if (Trans_Date_Int < EXP_Date_Int)
	{
		return TERMINAL_OK; 
	}
	else
	{
		return EXPIRED_CARD;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	// prompt the user for The Transaction Amount
	printf("Please Enter The Transaction Amount : ");
	// using scanf_s to prevents stack overflow
	scanf_s("%f", &termData->transAmount);
	// corner case to check that positive transaction amount
	if (termData->transAmount <= 0)
	{
		return INVALID_AMOUNT;
	}
	else
	{
		printf("The Transaction Amount is : %f\n", termData->transAmount);
		return TERMINAL_OK;
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	// check that the transaction amount is EXCEED maximum amount or not
	if ((termData->transAmount) > (termData->maxTransAmount))
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	// set the maximum amount 
	termData->maxTransAmount = max_amount;
	
	printf("The Maximum Transaction Amount is : %f\n", termData->maxTransAmount);

	if ((termData->maxTransAmount) <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}