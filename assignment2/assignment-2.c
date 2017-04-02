/*******************
Chikarmane, Akaash
avc536
Section #: 16290
EE312 - Assignment 2
*******************/

#include <stdio.h>

int main(void) {
	/*conversion constants*/
	const int TIMEOFFSET = 6;
	const double USD_EUR = .89;
	const double EUR_USD = 1.13;
	const double LB_G = 453.59237;
	const double MI_KM = 0.6213712;

	/*variables*/
	int choice = 0;	//used to decide which option to use
	int hour = 0;
	int minute = 0;
	int dollar = 0;
	int cent = 0;
	double euro = 0;
	int fahrenheit = 0;
	double celsius = 0;
	double kilogram = 0;
	int pound = 0;
	int ounce = 0;
	double kilometer = 0;
	double mile = 0;
	int dayindicator = -1;	//used to print "same", "next", or "previous" day
	double tempdouble = 0;	//used with EUR-USD to get "whole" cents while rounding, can be used elsewhere

	while (choice != 11) {
		printf("Enter a number from the menu (1-11) to select a specific conversion to perform or quit: ");
		scanf("%i", &choice);
		//Austin to Ireland time conversion - time given as two integers (hours and minutes)
		if (choice == 1) {
			printf("Enter Austin time to be converted, expressed in hours and minutes: ");
			scanf("%i %i", &hour, &minute);		//enter the Austin time
			printf("The time in Ireland equivalent to %i %i in Austin is ", hour, minute);	//print original time
			hour = hour + TIMEOFFSET;
			if (hour >= 24) {
				dayindicator = 1;	//1 if next day
				hour = hour % 24;
			}
			else {
				dayindicator = 0;	//0 if same day
			}
			printf("%i %i of the ", hour, minute);
			if (dayindicator) {
				printf("next day.\n");
			}
			else {
				printf("same day.\n");
			}
		}
		//Ireland to Austin time conversion - time given as two integers (hours and minutes)
		else if (choice == 2) {
			printf("Enter Ireland time to be converted, expressed in hours and minutes: ");
			scanf("%i %i", &hour, &minute);		//enter the Ireland time
			printf("The time in Ireland equivalent to %i %i in Austin is ", hour, minute);	//print original time
			hour = hour - TIMEOFFSET;
			if (hour < 0) {
				dayindicator = 1;	//1 if previous day
				hour = hour + 24;
			}
			else {
				dayindicator = 0;	//0 if same day
			}
			printf("%i %i of the ", hour, minute);
			if (dayindicator) {
				printf("previous day.\n");
			}
			else {
				printf("same day.\n");
			}
		}
		//USD to EUR currency conversion: EUR = .89*USD - USD given as two integers (dollars and cents)
		else if (choice == 3) {
			printf("Enter USD value: ");
			scanf("%i %i", &dollar, &cent);
			float convdollar = dollar;
			float convcent = cent;
			convdollar = convdollar*USD_EUR;
			dollar = convdollar;

			convcent = convcent*USD_EUR;
			cent = convcent;
			convcent = convcent - cent;
			if (convcent >= .5) {
				convcent = 1;
			}
			else {
				convcent = 0;
			}
			cent = cent + convcent;
			printf("EUR value is: %i %i\n", dollar, cent);
		}
		//EUR to USD currency conversion: USD = EUR*1.13 - EUR given as a real number
		else if (choice == 4) {
			printf("Enter EUR value: ");
			scanf("%lf", &euro);
			//while (1);
			euro = euro*EUR_USD;
			dollar = euro;			//dollar is now the converted dollar (stuff before the decimal point)
			euro = euro - dollar;		//euro is now just the stuff after the decimal point
			cent = euro * 100;			//gives the cents unrounded
			tempdouble = cent;
			tempdouble = tempdouble / 100;
			euro = (euro - tempdouble) * 100;	//subtracts the "whole" cents so that cents can be easily rounded using euro
			if (euro >= .5) {		//rounds the cents
				cent = cent + 1;
			}
			else {
				cent = cent + 0;
			}
			printf("USD value is: $%i %i\n", dollar, cent);
		}
		//Fahrenheit to Celsius temperature conversion: C = (5/9)(F-32) - F given as integer
		else if (choice == 5) {
			printf("Enter temperature in Fahrenheit: ");
			scanf("%i", &fahrenheit);
			fahrenheit = fahrenheit - 32;
			celsius = fahrenheit;
			celsius = celsius * 5;
			celsius = celsius / 9;
			printf("Temperature in Celsius is: %lf\n", celsius);
		}
		//Celsius to Fahrenheit temperature conversion: F = (9/5)C + 32 - C given as real number
		else if (choice == 6) {
			printf("Enter temperature in Celsius: ");
			scanf("%lf", &celsius);
			celsius = celsius * 9;
			celsius = celsius / 5;
			celsius = celsius + 32;
			fahrenheit = celsius;		//fahrenheit gets the whole number celsius (unrounded)
			celsius = celsius - fahrenheit;		//celsius is now the remainder (decimal)
			if (celsius >= .5) {
				fahrenheit = fahrenheit + 1;
			}
			else {
				fahrenheit = fahrenheit + 0;
			}
			printf("Temperature in Fahrenheit is: %i\n", fahrenheit);
		}
		//kg to lb-oz weight conversion - 1 lb = 453.59237 grams = 16 oz; 
		else if (choice == 7) {
			printf("Enter weight in kg: ");
			scanf("%lf", &kilogram);
			kilogram = kilogram * 1000;			//convert to grams
			kilogram = kilogram / LB_G;		//convert to pounds
			pound = kilogram;		//pound now has the whole numbered pounds
			kilogram = kilogram - pound;		//subtract the pounds to leave the decimal to convert to ounces
			kilogram = kilogram * 16;		//kilograms are in unrounded ounces
			ounce = kilogram;
			kilogram = kilogram - ounce;
			if (kilogram >= .5) {
				ounce = ounce + 1;
				if (ounce == 16) {
					pound = pound + 1;
					ounce = 0;
				}
			}
			else {
				ounce = ounce + 0;
			}
			printf("Weight in pounds and ounces is: %i lb %i oz\n", pound, ounce);
		}
		//lb-oz to kg weight conversion
		else if (choice == 8) {
			printf("Enter weight in pounds and ounces: ");
			scanf("%i %i", &pound, &ounce);
			ounce = ounce * 16;
			pound = pound + ounce;
			kilogram = pound * LB_G;
			kilogram = kilogram / 1000;
			printf("Weight in kg is: %lf kg\n", kilogram);
		}
		//km to miles distance conversion - 1 km = 0.6213712 miles
		else if (choice == 9) {
			printf("Enter distance in km: ");
			scanf("%lf", &kilometer);
			mile = kilometer * MI_KM;
			printf("Distance in miles is: %lf miles\n", mile);
		}
		//miles to km distance conversion - 1 km = 0.6213712 miles
		else if (choice == 10) {
			printf("Enter distance in miles: ");
			scanf("%lf", &mile);
			kilometer = mile / MI_KM;
			printf("Distance in kilometers is: %lf kilometers\n", kilometer);
		}
		//quit
		else if (choice == 11) {
			printf("Good Bye\n");
			return(0);
		}
		else {
			printf("Invalid input. Input must be from 1-11. Try again.\n");
		}
	}
}