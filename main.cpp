#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
using namespace std;
class Account
{
private:
    char name[100];
    char fathers_name[100];
    long long int phone_no;
    char type[10];
    long long int acc_no;
    char email[100];
    int atm_pin;
    long double acc_balance = 0.0;

public:
    char *getName()
    {
        return name;
    }

    long long int getAccNo()
    {
        return acc_no;
    }

    long double getAccBalance()
    {
        return acc_balance;
    }

    int getPin()
    {
        return atm_pin;
    }

    void openAccount()
    {
        fstream accounts;
        cout << "Enter the name of accout holder: ";
        cin.ignore();
        cin.getline(name, 100);
        cout << "Enter the fathers name of accout holder: ";
        cin.getline(fathers_name, 100);
        cout << "Enter the phone number (max. 10 digits): ";
        cin >> phone_no;
        cout << "Enter the email address : ";
        cin.ignore();
        cin.getline(email, 100);
        cout << "Enter the account number (max. 10 digits): ";
        cin >> acc_no;
        cout << "Which type of account (current or savings) : ";
        cin >> type;
        cout << "Enter the total balance : ";
        cin >> acc_balance;
        cout << "Set ATM PIN (max. 4 digits): ";
        cin >> atm_pin;

        accounts.open("accounts.dat", ios::out | ios::app | ios::binary);
        accounts.write((char *)this, sizeof(*this));
        accounts.close();

        cout << "\nAccount Created Successfully!";
    }
    void withdrawMoney()
    {
        fstream accounts, temp;
        long long int acc_num;
        long double withdraw_money;
        cout << "Enter account number : ";
        cin >> acc_num;

        accounts.open("accounts.dat", ios::in | ios::out | ios::ate | ios::binary);
        temp.open("temp.dat", ios::out | ios::app | ios::binary);

        accounts.seekg(0);
        accounts.read((char *)this, sizeof(*this));

        while (!accounts.eof())
        {
            if (acc_no == acc_num)
            {
                cout << "Enter amount to withdraw: ";
                cin >> withdraw_money;

                if (acc_balance < withdraw_money)
                {
                    cout << "Insufficient balance to withdraw.";
                }
                else
                {
                    acc_balance = acc_balance - withdraw_money;
                    temp.write((char *)this, sizeof(*this));
                    cout << "Account balance after withdrawal : " << acc_balance << endl;
                }
            }
            else
            {
                temp.write((char *)this, sizeof(*this));
            }
            accounts.read((char *)this, sizeof(*this));
        }

        accounts.close();
        temp.close();
        remove("accounts.dat");
        rename("temp.dat", "accounts.dat");
    }

    void viewAllAccounts()
    {
        system("cls");

        fstream accounts;

        accounts.open("accounts.dat", ios::in | ios::app | ios::binary);
        if (!accounts)
        {
            cout << "\nFile Not Found...!!!";
        }
        else
        {
            cout << "\n\n";
            cout << "ACCOUNT DETAILS\n\n";
            cout << "Account No."
                 << "\t-----\t"
                 << "Name"
                 << "\t-----\t"
                 << "Balance\n";

            accounts.read((char *)this, sizeof(*this));
            while (!accounts.eof())
            {
                cout << "\n"
                     << acc_no << "\t-----\t" << name << "\t-----\t" << acc_balance << "\n";
                accounts.read((char *)this, sizeof(*this));
            }
            accounts.close();
        }
    }

    void getAccountDetails()
    {
        cout << "accout holder name = " << name << endl;
        cout << "fathers name = " << fathers_name << endl;
        cout << "phone number  = " << phone_no << endl;
        cout << "account number = " << acc_no << endl;
        cout << "account type = " << type << endl;
        cout << "email = " << email << endl;
        cout << "total balence = " << acc_balance << endl;
    }
};
int main()
{
    Account A;
    int choise;
    while (1)
    {
        cout << "\n~~~~~ WELCOME TO AGC ATM ~~~~~\n\n";

        cout << "1. Open Account\n";
        cout << "2. Withdraw Money\n";
        cout << "3. View All Account Details\n";
        cout << "4. Get Account Details\n";
        cout << "5. Exit\n";

        cout << "Enter your choise : ";
        cin >> choise;
        switch (choise)
        {
        case 1:
            A.openAccount();
            break;
        case 2:
            A.withdrawMoney();
            break;
        case 3:
            A.viewAllAccounts();
            break;
        case 4:
            A.getAccountDetails();
            break;
        case 5:
            exit(1);
            break;
        default:
            cout << "\nInvalid choise\n"
                 << endl;
        }
    }
    return 0;
}