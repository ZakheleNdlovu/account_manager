#include <iostream>
#include <mysql.h>
#include <sstream>
#include <string>
#include <unistd.h>

using namespace std;

const char* hostname = "";
const char* user = "";
const char* password = "";
unsigned long port = ;
const char* database = "";
const char* unixsocket = NULL;
unsigned long cf = 0;

MYSQL* connect(){
	MYSQL* connect;
	connect = mysql_init(0);
	connect = mysql_real_connect(connect,hostname,user,password,database,port,unixsocket,cf);
	
	return connect;
	
	
}

void exit(){
	cout << "\nThank you for using our services\n";
	exit(0);
}

void signup(MYSQL* connect){
	MYSQL_RES* res;
	MYSQL_ROW row;
	stringstream ss, ss1;
	string name,surname,email,password,balance;
	
	
	cout << "Press (e) to exit\n";
	cout << "Name: ";
	cin >> name;
	
	if (name == "e" || name == "E"){
		exit();
	}
	cout << "Surname: ";
	cin >> surname;
	if (surname == "e" || name == "E"){
		exit();
	}
	
	cout << "Email: ";
	cin >> email;
	if (email == "e" || name == "E"){
		exit();
	}
	
	cout << "Password: ";
	cin >> password;
	if (password == "e" || name == "E"){
		exit();
	}
	cout << "Deposit amount: ";
	cin >> balance;
	if (balance == "e" || name == "E"){
		exit();
	}
	
	ss1 << "create table clients(id serial primary key,name varchar(50),surname varchar(50),email varchar(50),password varchar(50), balance varchar(50))";
	string query1 = ss1.str();
	const char* a = query1.c_str();
	int run_query = mysql_query(connect,a);
	ss << "insert into clients(name,surname,email,password,balance) values('"+name+"','"+surname+"','"+email+"','"+password+"','"+balance+"')";
	string query = ss.str();
	const char* q = query.c_str();
	int run = mysql_query(connect, q);
	cout << "\nRegistration successful" <<'\n';
		
	
	
	
}

void accountDetails(MYSQL* connect,string name){
	
	MYSQL_ROW row;
	MYSQL_RES* res;
	stringstream set_query;
	string name1,surname,email,password,balance;
	
	set_query << "select * from clients where name = '"+name+"'";
	string query = set_query.str();
	const char* f_query = query.c_str();
	int run = mysql_query(connect, f_query);
	res = mysql_store_result(connect);
	int count = mysql_num_fields(res);
	
	row = mysql_fetch_row(res);
	name1 = row[1];
	surname = row[2];
	email= row[3];
	password = row[4];
	balance = row[5];
	sleep(1);
	
	cout << "\nName    : " << name<< "\nSurname : " << surname << "\nE-mail  : " << email << "\nPassword: "<< password << "\nBalance : R" << balance << '\n';
	
	
	
}

void deposit(MYSQL* connect,string name, int balance){
	
	MYSQL_RES* res;
	MYSQL_ROW row;
	stringstream set_query1,string2int,int2string,set_query2;

	
	set_query1 << "select * from clients where name = '"+name+"'";
	string query = set_query1.str();
	const char* q = query.c_str();
	int run_query1 = mysql_query(connect,q);
	res = mysql_store_result(connect);
	row = mysql_fetch_row(res);
	
	string current_balance = row[5];
	string2int << current_balance;
	
	int int_balance;
	string2int >> int_balance;
	int new_bal = int_balance + balance;
	
	int2string << new_bal;
	string new_balance;
	
	int2string >> new_balance;
	
	set_query2 << "update clients set balance = '"+new_balance+"' where name = '"+name+"'";
	string query1 = set_query2.str();
	const char* f_query1 = query1.c_str();
	int run_query2 = mysql_query(connect, f_query1);
	
	cout << "Your new balance is: R"<< new_balance << '\n';
	
	
	
}

void withdrawal(MYSQL* connect,string name, int balance){
	
	MYSQL_RES* res;
	MYSQL_ROW row;
	stringstream set_query1,string2int,int2string, set_query2;

	
	set_query1 << "select * from clients where name = '"+name+"'";
	string query = set_query1.str();
	const char* q = query.c_str();
	int run = mysql_query(connect,q);
	res = mysql_store_result(connect);
	row = mysql_fetch_row(res);
	
	string current_balance = row[5];
	string2int << current_balance;
	
	int current_bal;
	string2int >> current_bal;
	
	if (balance > current_bal){
		cout << "Insufficient funds\n";
	}
	else{
		int new_bal = current_bal - balance;
		int2string << new_bal;
		string new_balance;
		int2string >> new_balance;
		set_query2 << "update clients set balance = '"+new_balance+"' where name = '"+name+"'";
		string query1 = set_query2.str();
		const char* f_query1 = query1.c_str();
		int run1 = mysql_query(connect, f_query1);
	
		cout << "Your new balance is: R"<< new_balance << '\n';
		
		
	}
	
	
	
}

void updatePassword(MYSQL* connect,string name, string passwordd){
	
	stringstream get_password, return_password,set_query;
	MYSQL_RES* res;
	MYSQL_ROW row;
	
	set_query << "update clients set password = '"+passwordd+"' where name = '"+name+"'";
	string str_query = set_query.str();
	const char* query = str_query.c_str();
	int run_query = mysql_query(connect,query);
	cout << "Password updated!" << '\n';
	
	
}

void updateEmail(MYSQL* connect,string name, string new_email){
	stringstream set_query;
	set_query << "update clients set email = '"+new_email+"' where name = '"+name+"'";
	string str_query = set_query.str();
	const char* query = str_query.c_str();
	int run_query = mysql_query(connect, query);
	
	cout << "update successful\n";
}
void checkBalance(MYSQL* connect,string name){
	stringstream set_query;
	MYSQL_ROW row;
	MYSQL_RES* res;
	
	set_query << "select balance from clients where name = '"+name+"'";
	string str_query = set_query.str();
	const char* query = str_query.c_str();
	int run_query = mysql_query(connect, query);
	
	res = mysql_store_result(connect);
	row = mysql_fetch_row(res);
	
	cout << "Your balance is: R" << *row << '\n';
}

bool signIn(MYSQL* connect,string name, string password1){
	MYSQL_RES* res;
	MYSQL_ROW row;
	stringstream getinfo;
	
	getinfo << "select * from clients where name = '"+name+"'";
	string query = getinfo.str();
	const char* f_query = query.c_str();
	int run_query = mysql_query(connect,f_query);
	res = mysql_store_result(connect);
	row = mysql_fetch_row(res);
	
	string db_name = row[1];
	string db_password = row[4];
	
	if (name == db_name && password1 == db_password){
		return true;
	}
	else{
		return false;
	}
	
}

void transact(MYSQL* connect,string name){
	
	string password,email;
	bool k = true;
	while (k){
		sleep(1);
		cout << "\nTRANSACT\n\nChoose a number:\n1. Check Balance\n2. Deposit\n3. Withdrawal\n4. Update password\n5. Update E-mail\n6. Account details\n7. Exit\n: ";
		int transact;
		cin >> transact;
				
		switch (transact){
			case 1:
				checkBalance(connect,name);
				break;
						
			case 2:
				cout << "Amount: ";
				int d_amount;
				cin >> d_amount;
				deposit(connect,name, d_amount);
				break;
			
			case 3:
				cout << "Amount: ";
				int w_amount;
				cin >> w_amount;
				withdrawal(connect,name,w_amount);
				break;
			
			case 4:
				cout << "Enter your new password: ";
				cin >> password;
				updatePassword(connect,name,password);
				
				break;
				
			case 5:
				cout << "Your new email: ";
				cin >> email;
				updateEmail(connect,name,email);
				break;
				
			case 6:
				accountDetails(connect,name);
				break;
				
			case 7:
				
				cout << "\nThank you for using our services :)\n";
				exit(0);
			
		}

	}
}
	

int main(){
	
	MYSQL* conn = connect();
	cout << "*******************************"<< '\n';
	cout << "*           WELCOME           *"<< '\n';
	cout << "*******************************"<< '\n';
	
	while (true){
		cout << "\n1. Log in\n2. Sign up\n3. Exit\n: ";
		string r;
		cin >> r;
		string name, password;
		
		int attempts = 5;
		if (r == "1" ){
			while (attempts > 0){
				cout<< "\nName: ";
				cin >> name;
				cout << "Password: ";
				cin >> password;
				sleep(1);
				if (signIn(conn,name,password)){
					while(true){
						transact(conn,name);
					}
				}
				else{
					cout << "log in failed\n";
					sleep(2);
				}
			}
		}
		else if(r == "2"){
			signup(conn);
			cout << "\nRegistration complete\n";
		}
		else if(r == "3"){
			cout << "\nThank you for using our services\n";
			exit(0);
		}
		else{
			cout << "\nInvalid input!\n";
		}
	}
	return 0;
}
