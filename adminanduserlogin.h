
#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H
#include"accountfile.h"
// #include"mainmenu.h"

class AdminLogin
{

public:
    // void admin_customer();
    void admin_login(); // Admin Login Page
    void customer_login(); // customer Login Page
    void adminMenu(); // Admin Menu options
    void customerMenu(); // customer Menu options
    void write_account(); // function to write record in binary file
    void display_bal(int); // function to display balance amount details
    void modify_account(int); // function to modify record of file
    void logout();
    void deposit_withdraw(int, int); // function to desposit/withdraw amount for given accounts
};
class Menu
{
public:
	void mainMenuList();  // main menu list 	
};

void Menu::mainMenuList()
{
    AdminLogin adminlogin; //object for customer and admin
	std::cout << "\n\n\n\t  WELCOME TO ONLINE BANKING MANAGEMENT SYSTEM";
	char choice;
	do
	{
		cout << "\n\n\n\t MAIN MENU";
		cout << "\n\n\n\t 01. ADMIN";
		cout << "\n\n\n\t 02. Customer";
		cout << "\n\n\n\t 03. EXIT";
		cout << "\n\n\tSelect Your Option (1-3) ";
		cin >> choice;
		system("clear");
		switch (choice)
		{
		case '1':
			adminlogin.admin_login();
			break;
		case '2':
			adminlogin.customer_login();
			break;
		case '3':
			cout << "\n\n\tThanks for using bank managemnt system";
			adminlogin.logout();
			break;
		default:
			cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (choice != '3');
	system("clear");
}

//************01.customer CREATE NEW ACCOUNT*******************************
Account account;
Menu menuOp;
//********Created Account Saved in File************************
void AdminLogin::logout(){
    exit(1);
}
void AdminLogin::customer_login()

{

    string customerName;

    string customerPassword;

    int loginAttempt = 0;

    while (loginAttempt < 5)

    {

        cout << "customer name: ";

        cin >> customerName;

        cout << "customer Password: ";

        cin >> customerPassword;

        if (customerName == "customer" && customerPassword == "customer")

        {

            system("clear");

            cout << "Welcome To Online Banking System\n";

            customerMenu();
        }

        else

        {

            cout << "Invalid login attempt. Please try again.\n"
                 << '\n';

            loginAttempt++;
        }
    }

    if (loginAttempt == 5)

    {

        cout << "Too many login attempts! The program will now terminate.";
    }

    cout << "Thank you for logging in....\n";

    system("clear");
}

void AdminLogin::customerMenu()
{
    char choice;
    int number;
    do
    {
        cout << "\n\n\n\tMAIN MENU";

        cout << "\n\n\t01.CREATE NEW ACCOUNT";

        cout << "\n\n\t02. DEPOSIT AMOUNT";

        cout << "\n\n\t03. WITHDRAW AMOUNT";

        cout << "\n\n\t04. BALANCE ENQUIRY";

        cout << "\n\n\t05. EDIT ACCOUNT DETAILS";

        cout << "\n\n\t06. Back to Main Menu";

        cout << "\n\n\tSelect Your Option (1-6) ";

        cin >> choice;

        // system("clear");

        switch (choice)

        {

        case '1':

            write_account(); // new customer account

            break;

        case '2':

            cout << "\n\n\tEnter The account No. : ";
            cin >> number;

            deposit_withdraw(number, 1); // deposit and withdraw
            customerMenu();
            break;

        case '3':

            cout << "\n\n\tEnter The account No. : ";
            cin >> number;
            deposit_withdraw(number, 2); // deposit and withdraw
            cout << "Press Enter For Main Menu \n";
            break;

        case '4':

            cout << "\n\n\tEnter The account No. : ";
            cin >> number;

            display_bal(number); // Dispaly customer Account Balance
            cout << "Press Enter For Main Menu \n";
            break;

        case '5':

            cout << "\n\n\tEnter The account No. : ";
            cin >> number;

            modify_account(number); // Edit Account Details

            break;

        case '6':

            cout << "\n\n\tThanks for using bank managemnt system \n";
            menuOp.mainMenuList();
            break;

        default:
            cout << "\a";
        }

        cin.ignore();

        cin.get();

    } while (choice != '6');

    system("clear");

    // admin_customer(); // back to admin or customer menu
}


void AdminLogin::adminMenu()
{
    
    
    int choice;
    int number;
    do
    {
        cout << "\n\n\n\tMAIN MENU";

        cout << "\n\n\t01. ALL ACCOUNT HOLDER LIST";

        cout << "\n\n\t02. DELETE AN ACCOUNT";

        cout << "\n\n\t03. EXIT";

        cout << "\n\n\tSelect Your Option (1-3) ";

        cin >> choice;

        system("clear");

        switch (choice)
        {

        case 1:
            account.display_all(); // display all customer details
            cout << "Press Enter For Admin Menu \n";
            break;

        case 2:

            cout << "\n\n\tEnter The account No. : ";
            cin >> number;
            account.delete_account(number);// delete particular customer account

            break;

        case 3:

            cout << "\n\n\tThanks for using bank managemnt system \n";
            logout();
            break;

        default:
            cout << "\a";
        }

        cin.ignore();
        cin.get();

    } while (choice != '3');

    system("clear");

    // admin_customer(); // back to admin or customer menu
}




void AdminLogin::deposit_withdraw(int n, int option)

{

    int amt;

    bool found = false;

    Account account;

    fstream File;

    File.open("accountdetails.dat", ios::binary | ios::in | ios::out);

    if (!File)

    {

        cout << "File could not be open !! Press any Key...";

        return;
    }

    while (!File.eof() && found == false)

    {

        File.read(reinterpret_cast<char *>(&account), sizeof(Account));

        if (account.return_accno() == n)

        {

            account.show_account();

            if (option == 1)

            {

                cout << "\n\n\t***** TO DEPOSITE AMOUNT *****";

                cout << "\n\nEnter The amount to be deposited :";

                cin >> amt;

                account.deposit_amount(amt);
            }

            if (option == 2)

            {

                cout << "\n\n\tTO WITHDRAW AMOUNT ";

                cout << "\n\nEnter The amount to be withdraw :";

                cin >> amt;

                int bal = account.return_deposit() - amt;

                if ((bal < 500 && account.return_type() == 'S') || (bal < 1000 && account.return_type() == 'C'))

                    cout << "Insufficience balance";

                else

                    account.withdraw(amt);
            }

            int pos = (-1) * static_cast<int>(sizeof(account));

            File.seekp(pos, ios::cur);

            File.write(reinterpret_cast<char *>(&account), sizeof(Account));

            cout << "\n\n\t Record Updated";

            found = true;
        }
    }

    File.close();

    if (found == false)

        cout << "\n\n Record Not Found ";

    system("clear");
}


void AdminLogin::write_account()

{

    Account account;

    ofstream outFile;

    outFile.open("accountdetails.dat", ios::binary | ios::app);

    account.create_account();

    outFile.write(reinterpret_cast<char *>(&account), sizeof(Account));

    outFile.close();
}


//*******  Return Deposit Amount*****

int Account::return_deposit() const

{

    return deposit;
}

//******** Current / Savings *******

char Account::return_type() const

{

    return type;
}

//******** email *******

// characcount::return_email() const

//{

//	return email;

//}

//******** phone *******

//*********** 04. customer Display Account Balance*********************

void AdminLogin::display_bal(int n)

{

    Account account;

    bool flag = false;

    ifstream inFile;

    inFile.open("accountdetails.dat", ios::binary);

    if (!inFile)

    {

        cout << "File could not be open !! Press any Key...";

        return;
    }

    cout << "\n ***** BALANCE DETAILS ***** \n";

    while (inFile.read(reinterpret_cast<char *>(&account), sizeof(Account)))

    {

        if (account.return_accno() == n)

        {

            account.show_account();

            flag = true;
        }
    }

    inFile.close();

    if (flag == false)

        cout << "\n\nAccount number does not exist";

    system("clear");
}



void AdminLogin::admin_login()

{

    string customerName;

    string customerPassword;

    int loginAttempt = 0;

    while (loginAttempt < 5)

    {

        cout << " Admin customername: ";

        cin >> customerName;

        cout << "Admin Password: ";

        cin >> customerPassword;

        if (customerName == "admin" && customerPassword == "admin")

        {

            system("clear");

            cout << "Welcome To Online Banking System\n";

            adminMenu();
        }

        else

        {

            cout << "Invalid login attempt. Please try again.\n"
                 << '\n';

            loginAttempt++;
        }
    }

    if (loginAttempt == 5)

    {

        cout << "Too many login attempts! The program will now terminate.";
    }

    cout << "Thank you for logging in....\n";

    system("clear");
}


void AdminLogin::modify_account(int n)
{

    bool found = false;

    Account account;

    fstream File;

    File.open("accountdetails.dat", ios::binary | ios::in | ios::out);

    if (!File)

    {

        cout << "File could not be open !! Press any Key...";

        return;
    }

    while (!File.eof() && found == false)

    {

        File.read(reinterpret_cast<char *>(&account), sizeof(Account));
        if (account.return_accno() == n)
        {

            account.show_account();

            cout << "\n\nEnter The New Details of account :" << endl;

            account.modify();

            int pos = (-1) * static_cast<int>(sizeof(Account));

            File.seekp(pos, ios::cur);

            File.write(reinterpret_cast<char *>(&account), sizeof(Account));

            cout << "\n\n\t Record Updated Successfully......!";

            found = true;
        }
    }

    File.close();
    if (found == false)

        cout << "\n\n Record Not Found ";

    // system("clear");
}


#endif