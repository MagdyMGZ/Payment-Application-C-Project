#ifndef CARD_H
#define CARD_H

// macros declarations
#define max_name 24
#define min_name 20
#define expiry_date_len 5
#define max_pan 19
#define min_pan 16

// Here there is the typedef(s) and Functions Prototypes

typedef unsigned char uint8_t;

typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);

EN_cardError_t getCardPAN(ST_cardData_t* cardData);

#endif
