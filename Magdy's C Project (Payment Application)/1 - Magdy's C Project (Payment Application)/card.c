#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	// prompt the user for The Card Holder's Name
	printf("Please Enter The Card Holder's Name : ");
	// using scanf_s to prevents stack overflow
	scanf_s("%[^\n]s", &cardData->cardHolderName, max_name + 1);
	// corner case for the name length
	if (strlen(cardData->cardHolderName) < min_name || strlen(cardData->cardHolderName) > max_name || (cardData->cardHolderName) == NULL)
	{
		return WRONG_NAME;
	}
	// loop to char(s) to check that all the characters are only spaces and alphabets
	for (int i = 0 ; i < strlen(cardData->cardHolderName) ; i++)
	{
		// using isalpha function in <ctype> library to check that the char is alphabet
		if ((cardData->cardHolderName[i] != 32) && !(isalpha(cardData->cardHolderName[i])))
		{
			return WRONG_NAME;
		}
	}
	printf("Welcome, %s\n", cardData->cardHolderName);
	return CARD_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	// prompt the user for the card expiry date                     (01234)
	printf("Please Enter The Card Expiry Date In This Format (MM/YY) : ");
	// using scanf_s to prevents stack overflow
	scanf_s("%s", &cardData->cardExpirationDate, expiry_date_len + 1);
	// corner case for the Date length
	if ((cardData->cardExpirationDate == NULL) || strlen(cardData->cardExpirationDate) != expiry_date_len)
	{
		return WRONG_EXP_DATE;
	}
	// corner case to check the Date format
	// using isdigit function in <ctype> library to check that the char is a digit
	if (!isdigit(cardData->cardExpirationDate[0]) || !isdigit(cardData->cardExpirationDate[1]) || !isdigit(cardData->cardExpirationDate[3]) || !isdigit(cardData->cardExpirationDate[4]))
	{
		return WRONG_EXP_DATE;
	}

	if ((cardData->cardExpirationDate[2]) != '/')
	{
		return WRONG_EXP_DATE;
	}
	printf("The Card Expiry Date is : %s\n", cardData->cardExpirationDate);
	return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	// prompt the user for the card PAN
	printf("Please Enter The Card's Primary Account Number : ");
	// using scanf_s to prevents stack overflow
	scanf_s("%s", &cardData->primaryAccountNumber, max_pan + 1);
	// check the PAN length (its format)
	if ((cardData->primaryAccountNumber) == NULL || strlen(cardData->primaryAccountNumber) < min_pan || strlen(cardData->primaryAccountNumber) > max_pan)
	{
		return WRONG_PAN;
	}
	// check that all characters in PAN is digit using function isdigit in ctype library
	for (int i = 0; i < strlen(cardData->primaryAccountNumber); i++)
	{
		if (!isdigit(cardData->primaryAccountNumber[i]))
		{
			return WRONG_PAN;
		}
	}
	printf("The Primary Account Number is : %s\n", cardData->primaryAccountNumber);
	return CARD_OK;
}
