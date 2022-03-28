/*
C
pop.c
Mohamad Al-Jaf
Student ID : 500728521
Assignment #2 - Simulate Vending Machine
CPS 393 Section 210
Instructor: L.Hiraki
Purpose : To simulate operation of a pop vending machine.
*/
#include <stdio.h>
#include <stdlib.h> /* required for the exit command to work */
#define PRICE_MULTIPLE 5
#define LOWER_SELLING_PRICE 5
#define UPPER_SELLING_PRICE 105
#define NICKEL 5
#define DIME 10
#define QUARTER 25

typedef struct
{
	int dimes;
	int nickels;
	int given;
} Transaction;

/* returns only the first character the user enters */
char getInput()
{
	char firstLetter = getchar();

	while (getchar() != '\n'); /* loops until the newline is reach */

	return toupper(firstLetter); /* returns the first character in upper case */
}

/* Checks to see if the user over paid and if so calculates the change in dimes and nickels and prints it out */
void giveChange(int price_pop, int total_cents)
{
	Transaction change = { 0, 0, total_cents - price_pop };
	int overPay;

	if (total_cents >= price_pop)
	{
		change.given = total_cents - price_pop;
	}
	else
	{
		change.given = total_cents; /* if the user has decided to get a refund */
	}

	overPay = change.given;

	if (overPay != 0) /* if overpayment and change is required */
	{
		while (overPay >= DIME) /* while the over payment amount is equal or greater than a dime dispense a dime*/
		{
			change.dimes++;
			overPay -= DIME;
		}

		while (overPay >= NICKEL) /* while the over payment amount is equal or greater than a nickel dispense a nickel*/
		{
			change.nickels++;
			overPay -= NICKEL;
		}
	}

	printf("    Change given: %d cents as %d dime(s) and %d nickel(s).", change.given, change.dimes, change.nickels);
	return;
}

/* Resets the vending machine and gives the user their change back */
void ResetMachine(int* total_cents, int price_pop)
{
	giveChange(price_pop, *total_cents);
	*total_cents = 0;
}

int main(int argc, char *argv[])
{
	char input_coin;
	int price_pop = 0;
	int total_cents = 0;
	int remaining_cost;

	if (argc != 2) /* requires the user to enter only 1 argument */
	{
		printf("Error: Please only enter 1 argument.\n");
	}
	else
	{
		price_pop = atoi(argv[1]);

		if (price_pop < LOWER_SELLING_PRICE || price_pop > UPPER_SELLING_PRICE)
		{
			printf("Price must be from %d to %d cents inclusive\n", LOWER_SELLING_PRICE, UPPER_SELLING_PRICE);
			price_pop = 0;
		}
		else
		{
			if (price_pop % PRICE_MULTIPLE != 0) /* if price entered isn't a multiple of PRICE_MULTIPLE then display an error message */
			{
				printf("Price must be a multiple of %d.\n", PRICE_MULTIPLE);
				price_pop = 0;
			}
		}
	}

	if (price_pop == 0)
	{
		printf("Usage: pop [price]\n");
		exit(1); /* exits if the price of pop entered is invalid */
	}
	else
	{
		price_pop = atoi(argv[1]);
	}

	printf("\nWelcome to my C Pop Machine!\n\n");
	printf("Pop is %d cents. Please insert any combination of nickels [N or n], dimes [D or d] or quarters [Q or q]. You can also press R or r for coin return.\n", price_pop);

	do
	{
		printf("\nEnter coin (NDQR): ");
		input_coin = getInput();

		switch (input_coin)
		{
		case 'N':
			printf("  Nickel detected.\n");
			total_cents += NICKEL;
			break;
		case 'D':
			printf("  Dime detected.\n");
			total_cents += DIME;
			break;
		case 'Q':
			printf("  Quarter detected.\n");
			total_cents += QUARTER;
			break;
		case 'R':
			ResetMachine(&total_cents, price_pop);
			continue; /* restarts the vending machine */
			break;
		case 'E': /* refunds the user their money back in dimes and nickels and quits the program */
			giveChange(price_pop, total_cents);
			printf("\nShutting down. Goodbye.\n\n");
			exit(1);
			break;
		default:
			printf("  Unknown coin rejected.\n");
			break;
		}

		printf("    You have inserted a total of %d cents.\n", total_cents);
		remaining_cost = price_pop - total_cents;

		if (remaining_cost > 0)
		{
			printf("    Please insert %d more cents.", remaining_cost);
		}
		else
		{
			printf("    Pop is dispensed. Thank you for your business! Please come again.\n");
			ResetMachine(&total_cents, price_pop);
		}
	} while (total_cents < price_pop); /* loops until the user presses E */

	return (0);
}