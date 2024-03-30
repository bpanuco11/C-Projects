// Brandon Panuco
// 3 August 2022
// Mini Project 7


#include <iostream>
#include <string> 
#include <iomanip>
#include <ctype.h>
#include <cmath>

using namespace std;

// global variables
double volume, standardRate, totalShippingCost,
totalCost, totalPremiumDelivery;

string packageType;

// function prototypes
double getVolume(double width, double length, double height);
void getShippingCosts();
bool addContainer();
void inputValidate(double& measurement, string s);
void paymentMethod(int input);
void validateCreditCard(char* card, int* numbers);
void validateDriversLicense();
void validateCashPayment();
void deliveryMethod(int input);
void premiumDeliveryOptions();
bool isValidPremiumOption(int userInput);


int main() {

    //local variables
    int containerCount = 1;
    double small = 1.50;
    double medium = 2.50;
    double large = 3.0;
    double width, length, height;
    const double SALES_TAX = .0775;
    string customerName;

    cout << "****East County Cargo Transport****\n\n";
    cout << "Cashiering system 2.0\n\n";

    cout << "Starting at Transaction #1\n\n";

    cout << "Enter Customer's name: ";
    getline(cin, customerName);

    cout << "\nCustomer - " << customerName<<"\n\n";

    do {

        cout << "Enter dimensions for container #" << containerCount << " (in feet): ";

        cout << "\nHeight: ";
        cin >> height;
        inputValidate(height, "Height");

        cout << "\nLength: ";
        cin >> length;
        inputValidate(length, "Length");

        cout << "\nWidth: ";
        cin >> width;
        inputValidate(width, "Width");


        /* getVolume function will be called in every loop and
           its return value will be stored in volume for clarity */

        volume = getVolume(width, length, height);

        if (volume < 15) {

            standardRate = small;
            packageType = "Small Package";

        }
        else if (volume <= 45 && volume >= 15) {

            standardRate = medium;
            packageType = "Medium Package";

        }
        else if (volume > 45 && volume <= 65) {

            standardRate = large;
            packageType = "Large Package";

        }
        else {

            cout << "\nThis package exceeds the 65 cubic foot limit. Please input again.\n\n";
        }

        if (volume <= 65) {

            getShippingCosts();  // display current container costs
            containerCount++;
        }

    } while (volume > 65 || addContainer()); // end loop if volume doesnt exceed or no more containers to add

    double totalTax = (totalShippingCost + totalPremiumDelivery) * SALES_TAX;

   /* cout << "\n\n\n\n" << setw(55) << left << "Container Total " << setw(2) << left << "$ " << setw(8) << right <<
        totalShippingCost << "\n";

    cout << setw(55) << left << "Premium Delivery " << setw(2) << left << "$ " << setw(8) << right << totalPremiumDelivery << "\n\n";
    */
    cout <<"\n\n\n\n" << setw(55) << left << "Subtotal " << setw(2) << left << "$ " << setw(8) << right
        << totalShippingCost + totalPremiumDelivery << endl;

    cout << setw(55) << left << "Sales Tax - 7.75% " << setw(2) << left << "$ " << setw(8) << right << totalTax << "\n\n";

    totalCost = totalShippingCost + totalTax + totalPremiumDelivery;

    cout << setw(55) << left << "Total " << setw(2) << left << "$ " << setw(8) << right << totalCost << endl;

    int userInput;

    cout << "\nPayment (1. Cash, 2. Check, 3. Credit): ";
    cin >> userInput;

    while (cin.fail() || userInput < 1 || userInput >3) {

        cin.clear();
        cout << "Invalid Command. Try Again.\n\n";

        cout << "Payment (1. Cash, 2. Check, 3. Credit): ";

        cin.ignore(INT_MAX, '\n');
        cin >> userInput;

    }// end loop

    paymentMethod(userInput);

}// end main function

double getVolume(double width, double length, double height) {

    // local variable
    double boxVolume = width * length * height;

    return boxVolume;

}// end getVolume function

void getShippingCosts() {

    static int volumeContainerCount;

    cout << "\nVolume of container #" << ++volumeContainerCount << " is " << volume << " cu ft\n";

    double shippingCost = volume * standardRate;

    totalShippingCost += shippingCost;

    cout << setprecision(2) << fixed;

    cout << packageType << " ($" << standardRate << setw(35) << left << " per cu ft): " << setw(2) << left

        << "$ " << setw(8) << right << shippingCost << endl;



    // Small Package($1.50 per cu ft) :

    premiumDeliveryOptions();

    int userInput;
    cin >> userInput;

    while (cin.fail() || (userInput < 1 || userInput >3) || !isValidPremiumOption(userInput)) {

        cin.clear();
        cout << "\nInvalid Command. Try Again.\n\n";

        premiumDeliveryOptions();

        cin.ignore(INT_MAX, '\n');
        cin >> userInput;

    }// end loop

    deliveryMethod(userInput);

}// end getShippingCosts function

bool addContainer() {

    char userResponse;
    bool isCommandValid = false;

    do {

        cout << "\nAnother container (Y/N): ";
        cin >> userResponse;
        cin.ignore(INT_MAX, '\n');

        if (userResponse == 'Y' || userResponse == 'y') {

            cout << "\n";
            return true;

        }
        else if (userResponse == 'N' || userResponse == 'n') {

            return false;

        }
        else {

            cout << "\nInvalid command. Try again: \n";
        }

    } while (!isCommandValid);// never ending loop

}// end addContainer function

void inputValidate(double& measurement, string measureType) {

    while (cin.fail()) {

        cin.clear();
        cin.ignore(INT_MAX, '\n');

        cout << "\nInvalid Measurement. Re-Enter " << measureType << " Again: ";
        cin >> measurement;

    }// end while loop

    cin.ignore(INT_MAX, '\n');

}// end inputValidate

void paymentMethod(int input) {

    if (input == 1) {

        validateCashPayment();
    }

    else if (input == 2) {

        validateDriversLicense();
        cout << setw(55) << left << "Accepted Check Payment: " << setw(2) << left << "$ " << setw(8) << right << totalCost << endl;

    }

    else {

        char visaOrMaster;
        string creditCardType;
        int cardDigits;

        validateCreditCard(&visaOrMaster, &cardDigits);

        if (visaOrMaster == 'v' || visaOrMaster == 'V')
            creditCardType = "Visa";
        else
            creditCardType = "Master";

        cout << "\n";
        cout << "Accepted " << creditCardType << " ending in " << cardDigits << setw(27) << left << " for the amount of "
            << setw(2) << left << "$ " << setw(8) << right << totalCost << endl;


    }

}// end paymentMethod function

void validateCreditCard(char* creditCard, int* cardNumbers) {

    int cardDigits;
    bool isCardValid = false;
    char card;

    do {

        cout << "\n" << setw(55) << left << "Enter V for Visa or M for MasterCard: " << setw(2) << left << setw(8) << right;
        cin >> card;
        *creditCard = card;
        cin.ignore(INT_MAX, '\n');

        if ((*creditCard != 'v' && *creditCard != 'V') && (*creditCard != 'm' && *creditCard != 'M')) {

            cout << "\nInvalid command. Try again: \n";

        }
        else
            isCardValid = true;

    } while (cin.fail() || !isCardValid);

    cout << "\n" << setw(55) << left << "Enter Last Four Digits of the Card: " << setw(2) << left << setw(8) << right;
    cin >> cardDigits;
    *cardNumbers = cardDigits;

    int digitCount = 0;

    while (!cin.fail() && cardDigits != 0) {

        cardDigits = cardDigits / 10;
        digitCount++;

    }// end loop

    while (cin.fail() || digitCount != 4) {

        cin.clear();
        cin.ignore(INT_MAX, '\n');

        cout << "\nInvalid Credit Card. Try Again.";

        cout << setw(55) << left << "Enter Last Four Digits of the Card: " << setw(2) << left << setw(8) << right;
        cin >> cardDigits;
        *cardNumbers = cardDigits;

        digitCount = 0;

        while (!cin.fail() && cardDigits != 0) {

            cardDigits = cardDigits / 10;
            digitCount++;

        }// end loop

    }// end loop

}// end validateCreditCard function

void validateDriversLicense() {

    string driverLicense;

    bool isLicenseValid;

    do {

        isLicenseValid = true;

        cout << "\n" << setw(55) << left << "Enter Driver License No: " << setw(2) << left << setw(8) << right;
        cin >> driverLicense;

        const int SIZE = 8;

        if (isalpha(driverLicense[0]) && driverLicense.length() == SIZE) {

            for (int i = 1; i < driverLicense.length(); i++) {

                if (!isdigit(driverLicense[i]) && isLicenseValid) {

                    isLicenseValid = false;

                }// end inner if statment

            }// end loop 

        }// end if statement

        else
            isLicenseValid = false;

        if (!isLicenseValid)
            cout << "\nInvalid License No. Try Again.\n";

    } while (!isLicenseValid);

}// end validateDriversLicense() function

void validateCashPayment() {

    bool isPaymentValid;

 
    do {

        isPaymentValid = true;
        double amountAccepted;
        cout << "\n" << setw(55) << left << "Accepted: " << setw(2) << left << "$   ";
        cin >> amountAccepted;

        while (totalCost != 0 && cin.good()) {

            if (amountAccepted >= totalCost) {

                cout << setw(55) << left << "Change: " << setw(2) << left << "$ " << setw(8) << right << amountAccepted - totalCost;
                totalCost = 0;
            }
            else {

                totalCost -= amountAccepted;

                if (totalCost < .01)
                    totalCost = 0;

                cout << setw(55) << left << "Total Remainding: " << setw(2) << left << "$ " << setw(8) << right << totalCost << endl;

                if (totalCost != 0) {
                    cout <<"\n" << setw(55) << left << "Accepted: " << setw(2) << left << "$ " << setw(8) << right;
                    cin >> amountAccepted;
                }

            }// end else

        }// end while loop

        if (cin.fail()) {

            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid Payment. Try Again\n";

            isPaymentValid = false;

        }// end if statement

    } while (!isPaymentValid);// end loop

}// end validateCashPayment function

void premiumDeliveryOptions() {

    cout << "\nHow is this container to be shipped:\n\n";

    if (volume < 30) {
        cout << "(1) Standard - (one to two weeks) - No change to the price\n";
        cout << "(2) Fast Ground - (3 to 5 business days) - Extra $1.50 per cubic foot\n";
        cout << "(3) Air - (1 to 2 business days) - Only applies to packages under 30 cubic feet - Extra $3.00 per cubic foot\n";
    }
    else {

        cout << "(1) Standard - (one to two weeks) - No change to the price\n";
        cout << "(2) Fast Ground - (3 to 5 business days) - Extra $1.50 per cubic foot\n";

    }
    cout << "\nDelivery: ";

}// end premiumDeliveryOptions function

void deliveryMethod(int input) {

    double costPerCubicFeet;
    double currentPremiumDelivery = 0.0;

    if (input == 1) {

        costPerCubicFeet = 0.0;

        cout << "\n" << setw(55) << left << "Standard: " << setw(2) << left
            << "$ " << setw(8) << right << currentPremiumDelivery << endl;

    }
    else if (input == 2) {

        costPerCubicFeet = 1.50;
        currentPremiumDelivery = volume * costPerCubicFeet;

        cout << "\n" << setw(55) << left << "Fast Ground ($1.50 per cu ft):" << setw(2) << left
            << "$ " << setw(8) << right << currentPremiumDelivery << endl;

    }
    else {

        costPerCubicFeet = 3.00;
        currentPremiumDelivery = volume * costPerCubicFeet;

        cout << "\n" << setw(55) << left << "Air ($3.00 per cu ft):" << setw(2) << left
            << "$ " << setw(8) << right << currentPremiumDelivery << endl;

    }

    totalPremiumDelivery += currentPremiumDelivery;

}// end deliveryMethod function

bool isValidPremiumOption(int userInput) {


    if (volume >= 30 && userInput == 3) {

        return false;

    }
    else {

        return true;

    }

}// end validatePremiumOption function

/*

****East County Cargo Transport****

Cashiering system 2.0

Starting at Transaction #1

Enter Customer's name: Jerry Lewis

Customer - Jerry Lewis

Enter dimensions for container #1 (in feet):
Height: 3

Length: 4

Width: 2

Volume of container #1 is 24 cu ft
Medium Package ($2.50 per cu ft):                       $    60.00

How is this container to be shipped:

(1) Standard - (one to two weeks) - No change to the price
(2) Fast Ground - (3 to 5 business days) - Extra $1.50 per cubic foot
(3) Air - (1 to 2 business days) - Only applies to packages under 30 cubic feet - Extra $3.00 per cubic foot

Delivery: 2

Fast Ground ($1.50 per cu ft):                         $    36.00

Another container (Y/N): y

Enter dimensions for container #2 (in feet):
Height: 9

Length: 2

Width: 3

Volume of container #2 is 54.00 cu ft
Large Package ($3.00 per cu ft):                       $   162.00

How is this container to be shipped:

(1) Standard - (one to two weeks) - No change to the price
(2) Fast Ground - (3 to 5 business days) - Extra $1.50 per cubic foot

Delivery: 1

Standard:                                              $     0.00

Another container (Y/N): y

Enter dimensions for container #3 (in feet):
Height: 1

Length: 2

Width: 4

Volume of container #3 is 8.00 cu ft
Small Package ($1.50 per cu ft):                       $    12.00

How is this container to be shipped:

(1) Standard - (one to two weeks) - No change to the price
(2) Fast Ground - (3 to 5 business days) - Extra $1.50 per cubic foot
(3) Air - (1 to 2 business days) - Only applies to packages under 30 cubic feet - Extra $3.00 per cubic foot

Delivery: 3

Air ($3.00 per cu ft):                                 $    24.00

Another container (Y/N): n




Subtotal                                               $   294.00
Sales Tax - 7.75%                                      $    22.79

Total                                                  $   316.79

Payment (1. Cash, 2. Check, 3. Credit): 1

Accepted:                                              $   320.00
Change:                                                $     3.21


*/