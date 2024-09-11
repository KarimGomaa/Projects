#include <iostream>
#include <cstring>
#include<stdio.h> /* to use exit */

using namespace std;

static int account_number = 0; /* global variable to track the number of accounts created */

/* Class representing an ATM with account details */
class ATM {
    char Account_name[100]; /* stores the account holder's name */
    char Card_number[11];   /* stores the card number (10 digits) */
    float Amount;           /* stores the account balance */

public:
    void check_Input(float &money); /* checks and validates input money */
    int find_acc(char cardnumber[]); /* finds account by card number */
    void create_new_acc(char new_account_name[], char new_card_number[]); /* creates a new account */
    void Deposit(); /* deposits money into the account */
    void Withdrawal(); /* withdraws money from the account */
    void Transfer(ATM&); /* transfers money between accounts */
    void Print_acc_data(); /* prints account details */
};

const int accounts_maxnum = 100; /* maximum number of accounts allowed */
ATM accounts[accounts_maxnum]; /* global array to store ATM accounts */

/* Function to check and validate input money */
void ATM::check_Input(float &money) {
    while((cin.peek() != '\n') || (!cin) || money < 0) /* ensure money is a valid positive number */
    {
       cout << "Input Error\n" << "please enter a valid number: ";
       cin.clear(); /* clear error flags */
       cin.ignore(1000, '\n'); /* ignore invalid input */
       cin >> money; /* take valid input again */
    }
}

/* Function to find the account index by card number */
int ATM::find_acc(char cardnumber[]) {
    for (int counter = 0; counter < account_number; counter++) /* loop through existing accounts */
    {
        if (strcmp(accounts[counter].Card_number, cardnumber) == 0) /* check if card number matches */
            return counter; /* return the index if match found */
    }
    return -1; /* return -1 if no match found */
}

/* Function to create a new account */
void ATM::create_new_acc(char new_account_name[], char new_card_number[]) {
    strcpy(Account_name, new_account_name); /* set account name */
    strcpy(Card_number, new_card_number);   /* set card number */
    Amount = 0; /* initialize account balance to zero */
    Print_acc_data(); /* display the account details */
}

/* Function to deposit money into the account */
void ATM::Deposit() {
    float deposit_value;
    cout << "Please enter the amount to be deposited (press 0 if you don't want to deposit money anymore): ";
    cin >> deposit_value;
    check_Input(deposit_value); /* validate deposit amount */
    Amount += deposit_value + (0.01 * deposit_value); /* add deposit amount plus 1% */
    Print_acc_data(); /* display updated account details */
}

/* Function to withdraw money from the account */
void ATM::Withdrawal() {
    float withdrawn_amount;
    while (1) {
        cout << "Please enter the amount to be withdrawn (press 0 if you don't want to withdraw money anymore): ";
        cin >> withdrawn_amount;
        check_Input(withdrawn_amount); /* validate withdrawal amount */
        if (Amount < (1.03 * withdrawn_amount)) { /* check if there is enough balance */
            cout << "ERROR, The money in your account is not enough, you only have (" << Amount << ") in your account, please try again\n ";
            continue;
        }
        break;
    }
    Amount -= (1.03 * withdrawn_amount); /* subtract the amount and a 3% fee */
    Print_acc_data(); /* display updated account details */
}

/* Function to transfer money between accounts */
void ATM::Transfer(ATM &receiving_acc) {
    float Transfered_amount;
    while (1) {
        cout << "Please enter the amount to be transfered (press 0 if you don't want to transfer money anymore): ";
        cin >> Transfered_amount;
        check_Input(Transfered_amount); /* validate transfer amount */
        if (Amount < (1.015 * Transfered_amount)) { /* check if there is enough balance for transfer */
            cout << "ERROR, The money in your account is not enough, you only have (" << Amount << ") in your account, please try again\n ";
            continue;
        }
        break; /* exit loop once transfer amount is valid */
    }

    /* Transfer the money, deduct 1.5% from the sending account and credit 98.5% to the receiving account */
    Amount -= 1.015 * Transfered_amount;
    receiving_acc.Amount += 0.985 * Transfered_amount;

    cout << "Sending account: " << endl;
    Print_acc_data(); /* display sending account details */
    cout << "Receiving account: " << endl;
    receiving_acc.Print_acc_data(); /* display receiving account details */
}

/* Function to print account details */
void ATM::Print_acc_data() {
    cout << "Name : " << Account_name << endl;
    cout << "Card number : " << Card_number << endl;
    cout << "Amount : " << Amount << endl;
}

/* Function to validate the account name */
void valid_account_name(char accountname[])
{
    while(1)
    {   
        /* Ensuring the account name doesn't exceed the array size (100 characters) */
        if(!cin)
        {
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "ERROR, card number shouldn't exceed 100 letters\n" << "please enter valid account name: ";
            cin.getline(accountname, 100);
            continue;
        }

        /* Ensuring the account name contains only letters and spaces */
        bool error = false;
        for(int counter = 0; accountname[counter]; counter++)
        { 
            if (!( (accountname[counter] >= 65 && accountname[counter] <= 90) || 
                   (accountname[counter] >= 97 && accountname[counter] <= 122) || 
                    accountname[counter] == 32 ))
            {   
                error = true;
                cout << "ERROR, account name must contain letters and spaces only\n" << "please enter a valid name: ";
                cin.getline(accountname, 100);
                break;
            }
        }
        
        if(error)
            continue; /* Start the loop again if there's an error */

        /* Ensuring the account name doesn't contain consecutive spaces */
        bool double_space = false;
        for(int i = 0; i < (strlen(accountname) - 1); i++)
        {
            if(accountname[i] == ' ' && accountname[i+1] == ' ')
            {  
                double_space = true;
                cout << "ERROR, name can't contain consecutive spaces\n" << "please enter valid account name: ";
                cin.getline(accountname, 100);
                break;
            }
        }

        if(double_space)
            continue; /* Restart loop if consecutive spaces are found */

        /* Ensuring the name doesn't start or end with a space */
        if (accountname[0] == ' ' || accountname[strlen(accountname) - 1] == ' ')
        {
            cout << "ERROR, name can't start or end with space\n" << "please enter valid account name: ";
            cin.getline(accountname, 100);
            continue;
        }

        /* Ensuring the account name is at least three characters long */
        if(strlen(accountname) < 3)
        {
            cout << "ERROR, Name is too short\n" << "please enter valid account name: ";
            cin.getline(accountname, 100);
            continue;
        }

        /* Ensuring the account name doesn't contain more than 4 consecutive identical letters */
        int letter_ascii;
        bool unrealistic_input = false;
        for(int k = 0; k < (strlen(accountname) - 3); k++)
        {   
            letter_ascii = accountname[k];
            if(letter_ascii == accountname[k+1] && letter_ascii == accountname[k+2] && letter_ascii == accountname[k+3])
            {   
                unrealistic_input = true;
                cout << "ERROR, name can't include more than 4 identical consecutive letters\n" << "please enter valid account name: ";
                cin.getline(accountname, 100);
                break;
            }
        }

        if(unrealistic_input)
            continue; /* Restart the loop if unrealistic input is found */

        break; /* Break the loop when a valid account name is found */
    }
}

/* Function to validate the card number */
void valid_card_number(char cardnumber[])
{
    while (1)
    {  
        /* Ensuring the card number doesn't exceed the array size (10 digits) */
        if (!cin)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input, please try again\n" << "Please enter valid account number (10 numbers only): ";
            cin.getline(cardnumber, 11);
            continue;
        }

        /* Ensuring all characters are numbers */
        int error = 0;
        for (int i = 0; cardnumber[i]; i++)
        {
            if (!(cardnumber[i] >= 48 && cardnumber[i] <= 57))
            {   
                error = 1;
                cout << "ERROR, only numbers are allowed in the account number, please try again\n" << "Please enter valid account number (10 numbers only): ";
                cin.getline(cardnumber, 11);
                break;
            }
        }
        if (error == 1)
            continue; /* Restart the loop if invalid characters are found */

        /* Ensuring the card number contains exactly 10 digits */
        if (strlen(cardnumber) < 10)
        {
            cout << "ERROR, card number should contain 10 numbers, not less than that, please try again\n " << "Please enter valid account number (10 numbers only): ";
            cin.getline(cardnumber, 11);
            continue;
        }

        /* Ensuring the card number doesn't contain all identical digits */
        int first = cardnumber[0];
        int x;
        for (int j = 1; cardnumber[j]; j++)
        {
            x = cardnumber[j];
            if (x != first)
                break;
        }
        if (x == first)
        {
            cout << "ERROR, 10 numbers can't all be the same, please try again\n " << "Please enter valid account number (10 numbers only): ";
            cin.getline(cardnumber, 11);
            continue;
        }

        break; /* Break the loop when a valid card number is found */
    }
}

/* Function to check the operation number */
int check_operation_number() /* Check that operation number is a valid integer between 1 and 5 */
{   
    int operation_num;
    cout << "******************************************************\n" << "1----Create new account\n" << "2----Deposit\n" << "3----Transfer to another account\n" << "4----Withdrawal\n" << "5----Exit\n" << "Please enter the number of operation: ";
    cin >> operation_num;

    /* Ensuring a valid number (1 to 5) is entered */
    while ((cin.peek() != '\n') || (!cin) || operation_num > 5 || operation_num < 1)
    {
        cout << "Input Error, please enter number from 1 to 5 only\n" << "Please enter the number of operation: ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> operation_num;
    }

    return operation_num;
}


/* Main function */
int main() {
    char acc_name[100];     /* to store the input account name */
    char card_number[11];   /* to store the input card number */
    int sender_acc_index;   /* to store the index of the sender's account */
    int receiver_acc_index; /* to store the index of the receiver's account */
    int User_input;         /* to store the user's input choice */

    while (1) {
        cout << "-------------------Welcome to the ATM project------------------------" << endl;
        cout << "If you would like to create a new account, please press 1" << endl;
        cout << "If you would like to deposit money, please press 2" << endl;
        cout << "If you would like to withdraw money, please press 3" << endl;
        cout << "If you would like to transfer money, please press 4" << endl;
        cout << "If you would like to close the ATM project, please press 5" << endl;
        cout << "please enter your option: ";
        cin >> User_input; /* take user input */
        cout << "*********************************************************************" << endl;

        switch (User_input) {
            case 1:
                if (account_number >= accounts_maxnum) {
                    cout << "ERROR: The maximum number of accounts has been reached." << endl;
                    break;
                }
                cout << "Please enter the account name: ";
                cin.ignore();
                cin.getline(acc_name, 100); /* take account name */
                cout << "Please enter a 10-digit card number: ";
                cin >> card_number; /* take card number */
                while((cin.peek() != '\n') || (!cin) || (strlen(card_number) != 10)) {
                    cout << "Error: Please enter a valid 10-digit card number: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cin >> card_number;
                }
                accounts[account_number].create_new_acc(acc_name, card_number); /* create new account */
                account_number++; /* increment the account count */
                break;

            case 2:
                cout << "Please enter your card number: ";
                cin >> card_number;
                sender_acc_index = accounts[0].find_acc(card_number); /* find account by card number */
                if (sender_acc_index == -1) {
                    cout << "ERROR: The account does not exist." << endl;
                    break;
                }
                accounts[sender_acc_index].Deposit(); /* perform deposit */
                break;

            case 3:
                cout << "Please enter your card number: ";
                cin >> card_number;
                sender_acc_index = accounts[0].find_acc(card_number); /* find account by card number */
                if (sender_acc_index == -1) {
                    cout << "ERROR: The account does not exist." << endl;
                    break;
                }
                accounts[sender_acc_index].Withdrawal(); /* perform withdrawal */
                break;

            case 4:
                cout << "Please enter your card number: ";
                cin >> card_number;
                sender_acc_index = accounts[0].find_acc(card_number); /* find sender account */
                if (sender_acc_index == -1) {
                    cout << "ERROR: The sender account does not exist." << endl;
                    break;
                }
                cout << "Please enter the receiver's card number: ";
                cin >> card_number;
                receiver_acc_index = accounts[0].find_acc(card_number); /* find receiver account */
                if (receiver_acc_index == -1) {
                    cout << "ERROR: The receiver account does not exist." << endl;
                    break;
                }
                accounts[sender_acc_index].Transfer(accounts[receiver_acc_index]); /* perform transfer */
                break;

            case 5:
                cout << "Thank you for using the ATM. Goodbye!" << endl;
                exit(0); /* exit the program */

            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }

    return 0;
}
