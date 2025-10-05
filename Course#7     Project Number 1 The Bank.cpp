

#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
#include<cctype>
using namespace std;
enum EnChoose{Show=1,Add=2,Delete=3,Update=4,Find=5,Exist=6};
struct SClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool TheMark = false;
};
string ReadAccountNumber()
{
	string AccountNumber;
	cout << "\n Please Enter AccountNumber  ? : ";
	getline(cin >> ws,  AccountNumber);

	return AccountNumber;
}
void ShowTheMenu();
void GoBackToMainMenu()
{
	cout << "\n Press Any Key To Go Bcak To The Main Menu . ";
	system("pause");
	ShowTheMenu();
}
vector<string>Split(string Line, string Delim)
{
	vector<string> split;
	string word = "";
	int Pos = 0;

	while ((Pos = Line.find(Delim)) != std::string::npos)
	{
		word = Line.substr(0, Pos);

		if (word != " ")
		{
			split.push_back(word);
		}

		Line.erase(0, Pos + Delim.length());
	}
	if (Line != " ")
	{
		split.push_back(Line);
	}

	return split;
}
SClient ConvertLineToDataClient(vector<string> split)
{
	SClient Client;
	Client.AccountNumber = split[0];
	Client.PinCode = split[1];
	Client.Name = split[2];
	Client.Phone = split[3];
	Client.AccountBalance = stod(split[4]);

	return Client;
}
vector<SClient> vClient()
{
	vector<SClient> vclient;
	fstream Houssam;
	Houssam.open("Houssam.txt", ios::in);
	if (Houssam.is_open())
	{
		string Line;
		SClient Client;
		while (getline(Houssam, Line))
		{
			Client = ConvertLineToDataClient(Split(Line, "#//#"));
			vclient.push_back(Client);
		}

		Houssam.close();
	}

	return vclient;
}
void PrintDataClient(SClient Client)
{
	cout << "| " << left << setw(18) << Client.AccountNumber << "| " << left << setw(17) << Client.PinCode << "| " << left << setw(40) << Client.Name << "| " << left << setw(20) << Client.Phone << "| " << left << setw(14) << Client.AccountBalance;
}
void ShowClientList()
{
	vector<SClient> vclient = vClient();
	cout << "\n\n \t\t\t\t\t Client List (" << vclient.size() << ") Client(s) . \n\n";
	cout << "________________________________________________________________________________________________________________________\n";
	cout << "| " << left << setw(18) << "Account Number " << "| " << left << setw(17) << "Pin Code " << "| " << left << setw(40) << "Client Name " << "| " << left << setw(20) << "Phone " << "| " << left << setw(14) << "Balance \n";
	cout << "___________________________________________________________________________________________________________________\n";

	for (SClient& Client : vclient)
	{
		PrintDataClient(Client);
		cout << endl;
	}
	cout << "________________________________________________________________________________________________________________________\n";
}
bool IsAccountNumberIsThere(string AccountNumber)
{
	fstream Houssam;
	Houssam.open("Houssam.txt", ios::in);
		if (Houssam.is_open())
		{
			string Line;
			SClient Client;
			while (getline(Houssam, Line))
			{
				Client = ConvertLineToDataClient(Split(Line, "#//#"));
				if (Client.AccountNumber == AccountNumber)
				{
					Houssam.close();
					return true;
				}

			}

			Houssam.close();
		}

		return false;
	
}
SClient  AddClient()
{
	SClient Client;
	cout << "_______________________________________________\n";
	cout << "\t\t Adding New Client : \n";
	cout << "_______________________________________________\n";
	cout << " Enter Account Number : ";
	getline(cin >> ws, Client.AccountNumber);
	while (IsAccountNumberIsThere(Client.AccountNumber))
	{
		cout << " Client With (" << Client.AccountNumber << ") Already Exist , Enter Another Account Number : ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << " Enter Pin Code : ";
	getline(cin, Client.PinCode);
	cout << " Enter Name : ";
	getline(cin, Client.Name);
	cout << " Enter Phone : ";
	getline(cin, Client.Phone);
	cout << " Enter Account Balance : ";
	cin >> Client.AccountBalance;

	return Client;

}
string ConvertDataClientToLine(SClient Client, string Separater)
{
	string Line = "";
	Line += Client.AccountNumber + Separater;
	Line += Client.PinCode + Separater;
	Line += Client.Name + Separater;
	Line += Client.Phone + Separater;
	Line += to_string(Client.AccountBalance);

	return Line;
}
void AddNewClient()
{
	char AddMore = 'Y';
	do
	{
		SClient Client = AddClient();
		fstream Houssam;
		Houssam.open("Houssam.txt", ios::out | ios::app);
		if (Houssam.is_open())
		{
				string Line = ConvertDataClientToLine(Client, "#//#");
				Houssam << Line << endl;
				Houssam.close();

				cout << "\n Client Added Successfully Do You Want to Add More ClientS ? [Y or N ] . ";
				cin >> AddMore;
		}
	} while (toupper(AddMore) == 'Y');

}
bool FindClientByAccountNumber(SClient& Client,vector<SClient>vclient,string AccountNumber )
{
	for (SClient& C : vclient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
void PrintClient(SClient client)
{
	cout << "\n The Following Are The Client Details : \n";
	cout << "______________________________________________________\n";
	cout << " Account Number : " << client.AccountNumber << endl;
	cout << " Pin Code : " << client.PinCode << endl;
	cout << " Name : " << client.Name << endl;
	cout << " Phone : " << client.Phone << endl;
	cout << " Account Balance : " << client.AccountBalance << endl;
	cout << "______________________________________________________\n";
}
bool MarkToDoSomeThing(vector<SClient>& vclient, string AccountNumber)
{
	for (SClient& C : vclient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.TheMark = true;
			return true;
		}
	}
	return false;
}
void SaveDataToFile(vector<SClient>& vclient)
{
	fstream Houssam;
	Houssam.open("Houssam.txt", ios::out);
	if (Houssam.is_open())
	{
		string Line = "";

		for (SClient& C : vclient)
		{
			if (C.TheMark == false)
			{
				Line = ConvertDataClientToLine(C, "#//#");
				Houssam << Line << endl;
			}
		}

		Houssam.close();
	}
}
bool DeleteClientS(vector<SClient> vclient)
{
	cout << "______________________________________________\n";
	cout << "\t\t Delete Client Screen \n";
	cout << "______________________________________________\n";
	string AccountNumber;
	AccountNumber = ReadAccountNumber();
	char Delete = 'Y';
	SClient Client;
	if (FindClientByAccountNumber(Client, vclient,AccountNumber))
	{
		PrintClient(Client);
		cout << "\n\n Are You Sure You Want To Delete This Client [Y or N] ?  ";
		cin >> Delete;
		if (toupper(Delete) == 'Y')
		{
			MarkToDoSomeThing(vclient, AccountNumber);
			SaveDataToFile(vclient);

			cout << "\n Client Deleted Successfully . \n\n";
			return true;
		}
	}
	else
	{
		cout << "\n\n Client With (" << AccountNumber << ") is Not Found . \n\n";
		return false;
	}
}
SClient ChangeClientInfo(string AccountNumber)
{
	
	SClient Client;
	Client.AccountNumber = AccountNumber;

	cout << " Enter Pin Code  : ";
	getline(cin >> ws, Client.PinCode);
	cout << " Enter Name : ";
	getline(cin,Client.Name);
	cout << " Enter Phone : ";
	getline(cin, Client.Phone);
	cout << " Enter Account Balance : ";
	cin >> Client.AccountBalance;

	return Client;

}
bool UpdateClientInfo(vector<SClient>vclient)
{
	cout << "_________________________________________________\n";
	cout << "\t\t Update Client Info Screen \n";
	cout << "_________________________________________________\n";
	string AccountNumber = ReadAccountNumber();
	SClient Client;
	char Update;

	if (FindClientByAccountNumber(Client, vclient, AccountNumber))
	{
		SClient client;
		PrintClient(Client);
		cout << "\n\n Are You Sure You want To Update This Client ? [Y or N] .  ";
		cin >> Update;
		if (toupper(Update) == 'Y')
		{
			for (SClient& C : vclient)
			{
				if (C.AccountNumber == AccountNumber)
				{
					 C  = ChangeClientInfo(AccountNumber);
				}
			}

			SaveDataToFile(vclient);

			cout << "\n Client Updated Successfully . \n";
			return true;
		}
	}
	else
	{
		cout << "\n Client With (" << AccountNumber << ") is Not Found . \n";
		return false;
	}
}
bool FindClientInfo(vector<SClient> vclient)
{
	cout << "_________________________________________________________\n";
	cout << "\t\t\t Find Client Screen \n";
	cout << "_________________________________________________________\n";
	string AccountNumber = ReadAccountNumber();
	SClient Client;
	if (FindClientByAccountNumber(Client, vclient, AccountNumber))
	{
		PrintClient(Client);
		return true;
	}
	else
	{
		cout << "\n Client With (" << AccountNumber << ") is Not Found .\n";
		return false;
	}
}
void EndProject()
{
	cout << "_____________________________________\n";
	cout << "\t Programe Ends :-) \n";
	cout << "_____________________________________\n";
}

EnChoose ChooseWhatDoYouWantToDo(string Message)
{
	int Choose;
	do
	{
		cout <<  Message << "  ";
		cin >> Choose;
	} while (Choose < 1 || Choose>6);

	return (EnChoose)Choose;
}
void ShowAllScreans(EnChoose Choose)
{
	switch (Choose)
	{
	case EnChoose::Show:
		system("cls");
		ShowClientList();
		GoBackToMainMenu();
		break;
	case EnChoose::Add:
		system("cls");
		AddNewClient();
		GoBackToMainMenu();
		break;
	case EnChoose::Delete:
		system("cls");
		DeleteClientS(vClient());
		GoBackToMainMenu();
		break;
	case::EnChoose::Update:
		system("cls");
		UpdateClientInfo(vClient());
		GoBackToMainMenu();
		break;
	case::EnChoose::Find:
		system("cls");
		FindClientInfo(vClient());
		GoBackToMainMenu();
		break;
	case::EnChoose::Exist:
		system("cls");
		EndProject();
		break;

	}
}
void ShowTheMenu()
{
	system("cls");
	cout << "======================================================================================\n";
	cout << "\t\t\t\t Main Manue Screen\n";
	cout << "======================================================================================\n";
	cout << "\t[1] Show Client List \n";
	cout << "\t[2] Add NewClient \n";
	cout << "\t[3] Delete Client \n";
	cout << "\t[4] Update Client Info \n";
	cout << "\t[5] Find Client \n";
	cout << "\t[6] Exist \n";
	cout << "=======================================================================================\n\n";
	EnChoose Choose = ChooseWhatDoYouWantToDo("Choose What Do you Want To Do ? [1 To 6]");
	cout << "\n\n";
	ShowAllScreans(Choose);

}



int main()
{
	ShowTheMenu();

}
  