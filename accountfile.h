#ifndef ACCOUNTFILE_H
#define ACCOUNTFILE_H
#include <bits/stdc++.h>
// #include <cctype>
// #include <fstream>
// #include <iomanip>
using namespace std;
class Account
{
public:
    int accountNo;
    char account;
    char name[50];
    int deposit;
    char type;
    int phone;
    char email[50];

public:
    void create_account();      // function to get data from user
    void show_account() const;  // function to show data on screen
    void modify();              // function to add new data
    void deposit_amount(int);   // function to accept amount and add to balance amount
    void withdraw(int);         // function to accept amount and subtract from balance amount
    void report() const;        // function to show data in tabular format
    int return_accno() const;   // function to return account number
    int return_deposit() const; // function to return balance amount
    char return_type() const;   // function to return type of account
    char return_email() const;  // function to return email of account
    int return_phone() const;   // function to return phone no of account
    void delete_account(int);   // function to delete record of file
    void display_all();         // function to display all account details

}; // class ends here

void Account::create_account()

{
    cout << "\nEnter The account No. :";
    cin >> accountNo;
    cout << "\n\nEnter The Name of The account Holder : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\n\n Enter Mobile Number:";
    cin >> phone;
    cout << "\n\n Enter Email:";
    cin >> email;
    cout << "\nEnter Type of The account (Current/Savings) : ";
    cout << "\n c for current account";
    cout << "\n s for savings Account";
    cout << "\nEnter Account Type : ";
    cin >> type;
    type = toupper(type);
    cout << "\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
    cin >> deposit;
    cout << "Account Created.....";
    // system("clear");
}

void Account::delete_account(int n) // 1231

{

    Account account;

    ifstream inFile;

    ofstream outFile;

    inFile.open("accountdetails.dat", ios::binary); 

    if (!inFile)

    {

        cout << "File could not be open !! Press any Key...";

        return;
    }

    outFile.open("Temp.dat", ios::binary);

    inFile.seekg(0, ios::beg);

    while (inFile.read(reinterpret_cast<char *>(&account), sizeof(Account)))

    {

        if (account.return_accno() != n) // 1232 != 1231

        {

            outFile.write(reinterpret_cast<char *>(&account), sizeof(Account));
        }
    }

    inFile.close();

    outFile.close();

    remove("accountdetails.dat");

    rename("Temp.dat", "accountdetails.dat");

    cout << "\n\n\tRecord Deleted Successfully....";

    // system("clear");
}

void Account::display_all()

{

    Account account;

    ifstream inFile;

    inFile.open("accountdetails.dat", ios::binary);

    if (!inFile)

    {

        cout << "File could not be open !! Press any Key...";

        return;
    }

    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";

    cout << "==================================================================================\n";

    cout << "A/c no.      NAME           Type         Balance          Email           Phone\n";

    cout << "====================================================================================\n";

    while (inFile.read(reinterpret_cast<char *>(&account), sizeof(Account)))

    {

        account.report();
    }

    inFile.close();
}

void Account::show_account() const

{

    cout << "\nAccount No. : " << accountNo;

    cout << "\nAccount Holder Name : " << name;

    cout << "\nAccount Email:" << email;

    cout << "\n Account Phone:" << phone;

    cout << "\nType of Account : " << type;

    cout << "\nBalance amount : " << deposit;
}

void Account::report() const
{

    cout << accountNo << setw(10) << " " << name << setw(10) << " " << type << setw(10) << " " << deposit << setw(10) << " " << email << setw(10) << " " << phone << endl;
}


void Account::modify()

{

    cout << "\nAccount No. : " << accountNo;

    cout << "\nModify Account Holder Name : ";

    cin.ignore(); //white space 

    cin.getline(name, 50);

    cout << "\n\n Enter Mobile Number:";

    cin >> phone;

    cout << "\n\n Enter Email:";

    cin >> email;

    cout << "\nModify Type of Account (s for savings / c for current): ";

    cin >> type;

    type = toupper(type);
    cout << "\nModify Balance amount : ";

    cin >> deposit;
}

int Account::return_phone() const

{

    return phone;
}

//************Functionality for Deposit/Withdraw*********************

void Account::deposit_amount(int x)

{

    deposit += x;
}

//******03.Withdraw***************

void Account::withdraw(int x)

{

    deposit -= x;
}

//******  Return Account Number ******

int Account::return_accno() const

{

    return accountNo;
}

#endif