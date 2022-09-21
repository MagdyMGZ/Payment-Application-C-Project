#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "app.h"

void appStart(void)
{
	// From the Flow Chart 
	// Card Module
	
	// Global Variables For Card Data (pointer to structure)
	ST_cardData_t card_holder_data;
	ST_cardData_t* cardData = &card_holder_data;

	// Card Errors 
	EN_cardError_t card_holder_name_error = getCardHolderName(cardData);
	
	// get the Card Holder Name and check the Validity
	if (card_holder_name_error == WRONG_NAME)
	{
		printf("Wrong Name !, please enter a valid name\n");
		return 0;
	}

	EN_cardError_t card_expiry_date_error = getCardExpiryDate(cardData);

	// get the Card Expiry Date and check the Validity
	if (card_expiry_date_error == WRONG_EXP_DATE)
	{
		printf("Wrong Expiry Date !, please enter a valid name\n");
		return 0;
	}

	EN_cardError_t card_PAN_error = getCardPAN(cardData);

	// get the Card PAN and check the Validity
	if (card_PAN_error == WRONG_PAN)
	{
		printf("Wrong Primary Account Number !, please enter a valid PAN\n");
		return 0;
	}
	
	// From the Flow Chart 
	// Terminal Module

	// Global Variables For terminal Data (pointer to structure)
	ST_terminalData_t terminal_data;
	ST_terminalData_t* termData = &terminal_data;

	// Terminal Errors
	EN_terminalError_t transaction_date = getTransactionDate(termData);
	
	// get the transaction date and check the Validity
	if (transaction_date == WRONG_DATE)
	{
		printf("Wrong Date !, please enter valid date\n");
		return 0;
	}
	
	EN_terminalError_t card_expired = isCardExpired(cardData, termData);

	// check the card is expired or not 
	if (card_expired == EXPIRED_CARD)
	{
		printf("This Card is Expired !, please enter valid card");
		return 0;
	}
	
	EN_terminalError_t trans_amount = getTransactionAmount(termData);

	// check the Validity of the transaction amount 
	if (trans_amount == INVALID_AMOUNT)
	{
		printf("Invalid Amount !, please enter valid amount\n");
		return 0;
	}

	EN_terminalError_t maxamount = setMaxAmount(termData);

	// set the maximum amount of the transaction
	if (maxamount == INVALID_MAX_AMOUNT)
	{
		printf("Invalid Max Amount !, please enter valid Max amount\n");
		return 0;
	}

	EN_terminalError_t below_maxamount = isBelowMaxAmount(termData);

	// check that the trans amount is exceed the max amount or not  
	if (below_maxamount == EXCEED_MAX_AMOUNT)
	{
		printf("Transaction Amount Exceed The Maximum Amount !, please enter valid amount\n");
		return 0;
	}

	// From the Flow Chart 
	// Server Module

	// Global Variables for transaction data (pointer to structure)
	ST_transaction_t transaction_data;
	ST_transaction_t* transData = &transaction_data;
	transData->cardHolderData = card_holder_data;
	transData->terminalData = terminal_data;

	// Transaction Error
	EN_serverError_t recieve_transaction_data = recieveTransactionData(transData);

	// Switch Case Alogrthim Check the Transaction Data Validity for many cases of erros
	switch (recieve_transaction_data)
	{
	case FRAUD_CARD:
		printf("This account is not found !\n");
		break;

	case DECLINED_INSUFFECIENT_FUND:
		saveTransaction(transData);
		printf("Transaction Amount Greater Than The Balance Amount !\n");
		break;

	case INTERNAL_SERVER_ERROR:
		saveTransaction(transData);
		printf("The Transaction Can't Be Saved !, Try Again\n");
		break;

	case APPROVED:
		printf("The Transaction Is Done Successfully, thanks !");
		break;

	default:
		break;
	}
	// Our project is finished
}