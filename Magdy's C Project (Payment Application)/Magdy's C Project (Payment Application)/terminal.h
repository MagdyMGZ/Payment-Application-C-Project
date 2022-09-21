#ifndef TERMINAL_H
#define TERMINAL_H
#include "card.h"

// macros declarations
#define max_transdate 10
// set any maximum amount for any transaction
#define max_amount 5000

// Here there is the typedef(s) and Functions Prototypes

typedef unsigned char uint8_t;
typedef unsigned int unit32_t;

typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
	TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);

#endif
