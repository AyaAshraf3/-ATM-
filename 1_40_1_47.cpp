#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <limits>
#include <ctype.h>
#include <locale.h>
#include <cstdlib>
using namespace std;
class ATM {

private:
	char Account_Name[100];
	char Card_Number[100];  //maximum number is 10 digits separated by spaces
	float Amount;


public:

	ATM() { Amount = 0.0; };

	void create_new_acc();
    void check_name(char*);
    void check_card_number(char*);
    char* get_card_num();
    void Deposit();
	void Withdrawal();
	void Transfer(ATM&);
    bool check_enough_money();
    void Print_acc_data();
	int find_account(char*);
	void print_sending();
	void print_receiving();
	void check_input_money(char*);
};
void ATM:: create_new_acc() {

		cout << "please enter the account name:";                       //this function gets the account name from the user for the 1st time and calls another
		cin.clear();                                                   //function to check its validation. if the name's valid,it gets the card number from the user
		cin.getline(Account_Name, 100);                               //and calls another function to check its validation too. if the number's valid ,it stores
        check_name(Account_Name);                                    //the account name and the card number.
		cout << "Please enter the account number(10 numbers each separated by space):";
		cin.getline(Card_Number, 100);
		check_card_number(Card_Number);
}

void ATM:: check_name(char Account_Name[]){                          //this function checks validation of input name.
     bool cond=1;
     int i;
     while(cond){




       for ( i = 0; i <Account_Name[i]!='\0'; i++) { //iteration on every character of the array

             //checking if first letter is space
                if(Account_Name[0]==' '){
                cout <<endl<< " Invalid input ! Name must contain only letters" <<endl<< endl;
				cout << "please enter the account name:";
		        cin.getline(Account_Name, 100);
				break;
                }

            //checking if double or more spaces are existed
            if (((Account_Name[i]==' ')&&(Account_Name[i-1]==' ')) && ((Account_Name[i]==' ')&&(Account_Name[i+1]==' '))){
                cout <<endl<<" Invalid input ! Name must contain only letters" <<endl<< endl;
				cout << "please enter the account name:";

		        cin.getline(Account_Name, 100);
				break;
            }


            //checking if special characters or symbols are existed
			if ((!((Account_Name[i] >= 'a' && Account_Name[i] <= 'z') || (Account_Name[i] >= 'A' && Account_Name[i] <= 'Z') || Account_Name[i]==' '))){

				cout <<endl<< " Invalid input ! Name must contain only letters" << endl<<endl;
				cout << "please enter the account name:";
		        cin.getline(Account_Name, 100);
				break;
            }
    } //end of the for loop

                //checking if pressing enter key
				if(strlen(Account_Name)==0){
                cout<<endl<<"Empty name is not accepted "<< endl<<endl;
				cout << "please enter the account name:";
		        cin.getline(Account_Name, 100);
		        }


			    if (i==strlen(Account_Name))  //indication that iteration ended without any error(ideal case)
                    cond=0;
    } //end of while loop
}

 void ATM:: check_card_number(char card_num_arr[]){            //this function checks validation of input card number
      tryagain:
         bool check_card =0;
         int i;
         int same_num_counter=0;
         char first_num = card_num_arr[0];
		for( i=0; i< card_num_arr[i]!='\0';i++){               //iteration on every character of the array

            //checking if same number is repeated
            if(card_num_arr[i]==first_num){
                same_num_counter++;
            }
            //checking if there're special characters or symbols
            if (!(card_num_arr[i]<='9' && card_num_arr[i]>='0' || card_num_arr[i]==' ')){
                check_card = 1;
                break;
            }
            //checking if there're spaces in even indices
            if ((i%2==1) && (card_num_arr[i]!=' ')){
                check_card = 1;
                break;
            }
            //checking if there're numbers in odd indices
            if ((i%2==0) && (card_num_arr[i]==' ')){
                check_card = 1;
                break;
            }
        }   //end of the for loop

        if (i==19 &&same_num_counter!=10) check_card = 0;      //indication that iteration ended without any error(ideal case) & the card number consists of various digits
        else check_card = 1;


        while(check_card) {
            cout<<endl<<"ERROR! invalid number"<<endl <<"Card number must be unique"<<endl<<"10 numbers separated by spaces"<<endl<<"Not characters"<<endl;
            cout << endl<<"Please enter the account number(10 numbers each separated by space):";
	     	cin.getline(card_num_arr, 100);
		goto tryagain;
        }
}

char* ATM:: get_card_num() {        //this function returns the card number of the user to be used in main

		return Card_Number;
}

void ATM:: Deposit() {                                               //this function gets the amount of money to deposited from the user then calls another
		char deposit_money[100];                                    //function to check the validation of the deposit money. if it's valid it performs
		cout << "Please enter the amount to be deposited: " ;      //the calculation operation on the amount.
		cin.getline(deposit_money, 100);
		check_input_money(deposit_money);
		Amount += stof(deposit_money )+ (0.01f * stof(deposit_money));
}

void ATM:: Withdrawal() {
    bool withdrawal_cond=1;                                            //this function gets the amount of money to withdrawn from the user then calls another
    char withdrawn_money[100];                                        //function to check the validation of the withdrawal money and if the amount of user allows the operation or not
	    while(withdrawal_cond){                                      //if it's valid it performs the calculation operation on the amount.
		cout << "Please enter the amount to be withdrawn: ";
		cin.getline(withdrawn_money,100);
		check_input_money(withdrawn_money);
		float money=(1.03f*stof(withdrawn_money));
		if(Amount<money){
		cout<<endl<<"the withdrawal money is larger than the amount."<<endl<<"the balance you have is: "<<Amount<<" and be aware that 3% of transferred money will be also deduced"<<endl<<endl;
        }
         else if(Amount>money)
            withdrawal_cond =0;
        }//end of the while loop
		Amount = Amount - (stof(withdrawn_money) + 0.03f * stof(withdrawn_money));

}

void ATM:: Transfer(ATM &recieving_account) {
	    char transfered_money[100]; bool transfer_money_cond=1;         //this function gets the amount of money to be transferred from the user then calls another
	    while(transfer_money_cond){                                    //function to check the validation of the transferred money and if the amount of user allows the operation or not
	    cout<<"please enter the amount to be transferred:";           //if it's valid it performs the calculation operation on the amount.
		cin.getline(transfered_money,100);
		check_input_money(transfered_money);
		if (Amount< (1.015*stof(transfered_money))){
            cout<<endl<<"the transferred money is larger than the sending amount."<<endl;
            cout<<"the balance you have is: "<<Amount<<" and be aware that 1.5% of transferred money will be also deduced"<<endl<<endl;
        }
         else if (Amount>(1.015*stof(transfered_money)))
            transfer_money_cond=0;
        }//end of the while loop
		Amount = Amount - stof(transfered_money) - 0.015f * stof(transfered_money);
		recieving_account.Amount = recieving_account.Amount + stof(transfered_money) - 0.015f * stof(transfered_money);
}

bool ATM::check_enough_money(){
	  if(Amount==0)                  //this function returns 1 if the amount is zero and stops the operation of the transfer or withdrawal
        return 1;                   //and returns the user back to the main menu
      else return 0;
}

void ATM::Print_acc_data() {
		cout << endl << "name: ";                    //this function shows the data of the user after the creation or deposit or withdrawal operations
		cout << Account_Name;

		cout << endl << "card number: ";
		for (int i = 0; i < 20; i = i + 2) {
			cout << Card_Number[i];
		}
		cout << endl << "amount: ";
		cout << Amount << endl;
}

int ATM::find_account(char arr[20]){
                                                    //this function researches in all accounts of users by card number to know to which of them it belongs
		for (int i = 0; i < 20; i = i + 2)         //and return 1 when it found it and 0 if did not
		{
			if (Card_Number[i] != arr[i])
				return 0;
		}
		return 1;
}


void ATM::print_sending() {
		cout << endl << "sending account: "<<endl<<"name:";     //this function shows the data of the sending user after the transfer operation
		cout << Account_Name;
		cout << endl << "Card Number: ";
		for (int i = 0; i < 20; i = i + 2) {
			cout << Card_Number[i];
		}
		cout << endl << "amount: ";
		cout << Amount << endl;

}

void ATM::print_receiving() {
		cout << endl << "receiving account: "<<endl<<"name:";   //this function shows the data of the receiving user after the transfer operation
		cout << Account_Name;
		cout << endl << "Card Number: ";
		for (int i = 0; i < 20; i = i + 2) {
			cout << Card_Number[i];
		}
		cout << endl << "amount: ";
		cout << Amount << endl;
}

void ATM::check_input_money(char input_money[]){          //this function checks the validation of the input money if it contains symbols or alphabetical characters
	    for( int i=0; i< input_money[i]!='\0';i++){
            if((input_money[0]=='0')){
                cout <<endl<<"Invalid input! must be digits only and the first digit can't be zero"<<endl<<endl<<"enter money again:";
                cin.getline(input_money, 100);
                check_input_money(input_money);
                break;
            }

            if ((input_money[i]<='9' && input_money[i]>='0' ) || (input_money[i]=='.'))  {

            }
            else {
                cout <<endl<<"Invalid input! must be digits only and the first digit can't be zero"<<endl<<endl<<"enter money again:";
                cin.getline(input_money, 100);
                check_input_money(input_money);
                break;
            }

	    if(strlen(input_money)==0){
                cout<<endl<<"invalid input"<< endl<<endl;
				cout << "enter money again:";
		        cin.getline(input_money, 100);
		        }


}
}









int main()
{
    ATM arr[100];               //system for maximum 100 accounts
    int cardlength;
	int found = 0;

	double max_operations_num = pow(10, 1000);   //too far number that allows the user to make many operations
	int max_accs_counter = 0;   //maximum number of created accounts is 100
	char input_card_num[100];
	char request[100];    //number of operation in main menu


	for (int i = 1; i <= max_operations_num; i++) {
            bool operation_cond=1;
            while(operation_cond){ //checks the validation of number of operation that it does not contain letters or double of numbers
                int flag=1;
		cout << endl <<"1----Create new account " << endl << "2----Deposit " << endl << "3----transfer to another account" << endl << "4----withdrawal" << endl << "5----exit";
		cout <<endl<< "please enter the number of operation:";

        cin.getline(request, 100);

		for(int i=0;i<request[i]!='\0';i++){

            if (!(request[i]<='9' && request[i]>='0')){

			    flag=0;
			}
        }
			if(!flag || strlen(request)!=1){
                    operation_cond=1;
            cout << endl << "MUST BE ONE NUMBER!" <<endl<<endl;}
                else operation_cond=0;
    }//end of the while loop that checks the number of operation


	if (request[0] == '5') break;                //exit operation when he presses number 5

		else if (max_accs_counter > 100)
		{
			cout <<endl <<"the system reached the maximum no. of accounts = 100 account" << endl;
			break;
		}

    else {

    switch (request[0]) {

        case('1'): {

            bool cond=1;
			arr[max_accs_counter].create_new_acc();                                  //in this case it creates an account and checks if it's already existed or not
			while(cond){

				int index;
				int found = 0;
				for (index = 0; index < max_accs_counter ; index++){

					found = arr[index].find_account(arr[max_accs_counter].get_card_num());
					if (found) {

						cout << endl << "Invalid Card Number! This account is already existed"<<endl<<endl;

                        arr[max_accs_counter].create_new_acc();
						break;
					}
				}

				if (found == 0) {                                            //if it's valid and does not exist before then it calls another function to print its data
                                   cond=0;                                  //and increment the counter responsible for the number of the accounts
					               arr[max_accs_counter].Print_acc_data();
                                   max_accs_counter++;
                                }

		 }
		  break;
    }

			case('2'): {
			    bool cond=1;
			    cout <<"Please enter the account number(10 numbers each separated by space):";
                cin.clear();
				cin.getline(input_card_num, 100);                           //in this case we first check if the card number exists or not. if it exists
			    while(cond){                                               //it goes to the deposit function and prints it's data
				int index = 0;

				arr[max_accs_counter].check_card_number(input_card_num);
				for (index = 0; index < 100; index++)
				{
					found = arr[index].find_account(input_card_num);
					if (found) {

						arr[index].Deposit();
						arr[index].Print_acc_data();
						cond=0;
						break;
					}
				}
					if (!found && index == 100){
						cout <<endl<< "Account does not exist" << endl<<endl;
						cout <<"Please enter the account number(10 numbers each separated by space):";
				        cin.getline(input_card_num, 100);
                    }
                }

				break;
    }


			case('3'): {
			    bool cond=1;
			    char sending_card_num[20];
			    char receiving_card_num[20];
			    int sending_account;
			    int recieving_account;

			            if(max_accs_counter<2) {         //if there's only one account it does not perform the transfer operation and returns the user back to the main menu
                            cout<<endl<<"there's only one account in the program so you can't transfer money"<<endl<<endl;
                            break;
			            }

				cout << "please enter the number of the sending account(10 numbers each separated by space):";
				cin.clear();
				cin.getline(sending_card_num, 20);

				while(cond){                                                            //checks if the account card number already exists or not
				arr[max_accs_counter].check_card_number(sending_card_num);
				int i=0;
				for ( i = 0; i < 100; i++)
				{
					found = arr[i].find_account(sending_card_num);
					if (found) {
						sending_account = i;
						cond=0;
						break;
					}
                }

                    if(!found && i==100){
						cout << endl<<"Account does not exist" <<endl<< endl;
                        cout << "please enter the number of the sending account(10 numbers each separated by space):";
				        cin.getline(sending_card_num, 20);
				    }
				}

                           //end of sending account

                bool cond3=1;bool flag = 0;
               while(cond3) {
                    bool cond2=1;
				    cout <<  "please enter the number of the receiving account(10 numbers each separated by space):";
				    cin.getline(receiving_card_num, 20);

                while(cond2){
				arr[max_accs_counter].check_card_number(receiving_card_num);     //check if the account card number already exists or not
				int j=0;
				for (j = 0; j < 100; j++){

					found = arr[j].find_account(receiving_card_num);
					if (found) {
						recieving_account = j;
						cond2=0;
						break;
					}
                }
					if(!found && j==100){
						cout << "Account does not exist" <<endl<< endl;
						cout << endl << "please enter the number of the receiving account(10 numbers each separated by space):";
				        cin.getline(receiving_card_num, 20);
				    }
                }

				for (int i = 0; i < 20; i++) {                                       //checks if the receiving account is the same as the sending account
					if ( receiving_card_num[i] !=sending_card_num[i]) {
						flag = 1;
						cond3=0;
						break;
					}
				}
				if (flag == 0) {
					cout << endl << "It's the same sending account !" <<endl<< endl;

				}
        }
                if (flag == 1 && !arr[sending_account].check_enough_money())       //checks if the sending account has zero money to transfer
                    {                                                             //if yes it returns the user back to the main menu
				arr[sending_account].Transfer(arr[recieving_account]);
				arr[sending_account].print_sending();
				arr[recieving_account].print_receiving();
				break;
			        }

			    else
			     {
                cout<<endl<<"the sending account has zero money"<<endl<<"you can only perform deposit operation first"<<endl<<endl;
                break;
			     }
    }

			case('4'): {
			    bool cond=1;
				int index = 0;
				cout << "please enter the number of the account(10 numbers each separated by space):";
				cin.clear();
				cin.getline(input_card_num, 100);

				while(cond){                                                       //checks if the account card number already exists or not
				arr[max_accs_counter].check_card_number(input_card_num);
				for (index = 0; index < 100; index++){

					found = arr[index].find_account(input_card_num);
					if (found) {


						cond=0;
						break;
					}
				}
					if (!found && index == 100){
						cout << endl << "Account does not exist" <<endl<< endl;
						cout << "please enter the number of the account(10 numbers each separated by space):";
				        cin.getline(input_card_num, 100);
				    }

                }
               if (arr[index].check_enough_money()){                    //checks if the account has zero money to withdrawal, if yes it returns the user back to main menu
                cout<<endl<<"this account has zero money"<<endl<<"you can only perform deposit operation first"<<endl<<endl;
                break;
               }
                   else  {
                            arr[index].Withdrawal();
                            arr[index].Print_acc_data();
						 }


				break;
			}

			default: cout <<endl<<"Your selection must be between 1 and 5!" << endl<<endl;
			break;
			}
		}
	}
}


