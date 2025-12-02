#include <iostream>
#include<windows.h>
#include <mysql.h>
#include <string>
#include <conio.h>
#include <sstream>
#include <fstream>
#include <vector>
#include "data.h"

using namespace std;


bool login();
void functions();
void searchStocks();
void PEanalysis();
void Evebanalysis();
void Recommend();
void userActivity();
void close();

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

vector<string> separate_words(string text)
{
    vector<string> words;
    istringstream iss(text);
    string word;
    while (iss >> word)
    {
        words.push_back(word);
    }
    return words;
}
struct PnL
{
    string name;
    double TotalB;
    double TotalS;
    double Rpnl;
    double URpnl;
    double NETpnl;
    double Charges;
};

string Username,Password;

int main()
{


    GetThingsReady();

    if(login())
    {
        return 0;
    }

    else
    {
        cout<<"\nProper account validation is mandatory to use our program!!\n"<<endl;
        cout<<"Press any key to exit..."<<endl;
        getch();
        return 0;
    }
}

bool login()
{
    SetConsoleTextAttribute(h,4);
    ifstream ip("Home.txt");
    string home;
    while(ip.eof()==0)
    {
        getline(ip,home);
        cout<<home<<endl;
    }
    ip.close();
    SetConsoleTextAttribute(h,7);

    cout<<"   1)  Existing User"<<endl;
    cout<<"   2)  New User"<<endl;
    cout<<"   3)  Close application "<<endl;
    cout<<endl<<endl;
    int choice;

    int flag =1;
    cout<<"Your Choice : ";
    while(flag)
    {
        cin>>choice;
        system("cls");
        if(choice==1)
        {
            flag =0;
            string user;
            char pass[32];

            SetConsoleTextAttribute(h,4);
            ifstream ip("Login.txt");
            string log;
            while(ip.eof()==0)
            {
                getline(ip,log);
                cout<<log<<endl;
            }
            ip.close();
            SetConsoleTextAttribute(h,7);

            cout<<"     Enter username : ";
            cin>>user;
            cout<<"     Enter password : ";

            char c='A';
            int index=0;

            while(c!=13)      // 13 is ASCII value of Enter key
            {
                c=getch();

                if(isprint(c))
                {
                    cout<<"*";
                    pass[index++] = c;
                }

                else if (c==8 && index)     // 8 is ASCII value of Backspace key
                {
                    pass[index--]='A';
                    cout<<("\b \b");
                }

            }
            pass[index]='\0';
            system("cls");
            cout<<"\nValidating";
            for(int i=1; i<=5; i++)
            {
                for(int j=0; j<=100000000; j++)
                {
                }
                cout<<".";
            }

            string u,p;
            ifstream in;
            in.open("C:\\Users\\hp\\OneDrive\\Desktop\\Project\\Users.txt");

            while(in.eof()==0)
            {
                getline(in,u);
                if(u==user)
                {
                    if(in.eof()==0)
                    {
                        getline(in,p);
                        string password(pass);
                        if(p==password)
                        {
                            system("cls");
                            cout<<"\nLOGIN SUCCESSFUL\n\n"<<endl;
                            Username = user;
                            Password = password;
                            cout<<"Press any key to continue...."<<endl;
                            getch();
                            system("cls");
                            functions();
                            return true;
                        }
                    }
                    else
                    {
                        break;
                    }

                }

            }

            in.close();
            system("cls");
            cout<<"\nLOGIN FAILED\n";
            cout<<"Username or Password is invalid!\n";
            cout<<"\nPress any key to go back"<<endl;

            getch();

            system("cls");
            login();

        }



        else if (choice==2)
        {
            flag =0;
A:
            string user;
            char pass[32];
            SetConsoleTextAttribute(h,4);
            ifstream ip("Create.txt");
            string create;
            while(ip.eof()==0)
            {
                getline(ip,create);
                cout<<create<<endl;
            }
            ip.close();
            SetConsoleTextAttribute(h,7);

            cout<<"     Enter new username : ";
            cin>>user;
            cout<<"     Enter your password : ";

            char c='A';
            int index=0;

            while(c!=13)      // 13 is ASCII value of Enter key
            {
                c=getch();

                if(isprint(c))
                {
                    cout<<"*";
                    pass[index++] = c;
                }

                else if (c==8 && index)     // 8 is ASCII value of Backspace key
                {
                    pass[index--]='A';
                    cout<<("\b \b");
                }

            }
            pass[index]='\0';

            ip.open("Users.txt");
            string check;

            while(ip.eof()==0)
            {
                getline(ip,check);
                if(check==user)
                {
                    cout<<"\n\nOOPS!!! Username already taken!!"<<endl;
                    cout<<"\nPress any key and try a different username"<<endl;
                    getch();
                    system("cls");
                    goto A;
                }
            }
            cout<<"\n\nEverything looks perfect\n";
            ip.close();
            string password(pass);
            Username = user;
            Password = password;
            ofstream out("Users.txt",ios_base::app);
            out<<"\n" + user + "\n" + password;

            out.close();
            string aadhar,mobile,ac,dob,pan;
            cout<<"\n     Enter your aadhar number : ";
            cin>>aadhar;
            cout<<"     Enter your pan number : ";
            cin>>pan;
            cout<<"     Enter your mobile number : ";
            cin>>mobile;
            cout<<"     Enter you Date Of Birth (DayMonthYear): ";
            cin>>dob;
            cout<<"     Enter your Account no : ";
            cin>>ac;
            d.insertUsersIntoTable(user,aadhar,pan,dob,ac,mobile);
            cout<<"\nAccount created successfully\n"<<endl;
            cout<<"Press any key to continue..."<<endl;
            getch();
            system("cls");
            functions();
            return true;
        }



        else if(choice ==3)
        {
            system("cls");

            SetConsoleTextAttribute(h,2);
            ifstream ip("Exit.txt");
            string exit;
            while(ip.eof()==0)
            {
                getline(ip,exit);
                cout<<exit<<endl;
            }
            ip.close();
            SetConsoleTextAttribute(h,7);


            return false;
        }



        else
        {
            cout<<"INVALID CHOICE !!!!\n\n"<<endl;
            cout<<"Press any key to go back and try again..."<<endl;
            getch();
            system("cls");
            login();

        }

    }
    return true;
}

void functions()
{
    SetConsoleTextAttribute(h,1);
    ifstream ip("Functions.txt");
    string func;
    while(ip.eof()==0)
    {
        getline(ip,func);
        cout<<func<<endl;
    }
    ip.close();
    SetConsoleTextAttribute(h,7);
    cout<<"     1) Search your stocks"<<endl;
    cout<<"     2) PE analysis of Stocks"<<endl;
    cout<<"     3) EV/Ebitda analysis of Stocks"<<endl;
    cout<<"     4) Recommend Stocks"<<endl;
    cout<<"     5) User Activity"<<endl;
    cout<<"     6) Exit\n\n"<<endl;


    cout<<"Your Choice : ";
    int choice;
    cin>>choice;

    switch(choice)
    {

    case 1:
        searchStocks();
        break;
    case 6:
        close();
        break;
    case 2:
        PEanalysis();
        break;
    case 3:
        Evebanalysis();
        break;
    case 4:
        Recommend();
        break;
    case 5:
        userActivity();
        break;
    default :
        system("cls");
        cout<<"\nINVALID OPTION!!!!\n\n"<<endl;
        cout<<"Press any key to try again..."<<endl;
        getch();
        system("cls");
        functions();

    };

}

void searchStocks()
{
    system("cls");
    string smbl;
    cout<<"************************ FIND YOUR STOCKS ************************\n\n\n";
    cout<<"     Enter the Ticker symbol for the stock you want to search : ";
    cin>>smbl;


    d.findStock(smbl);

    cout<<"Press any key to return to home page..."<<endl;
    getch();
    system("cls");
    functions();


}

void PEanalysis()
{
    system("cls");
    string smbl;
    cout<<"************************ PE ANALYSIS ************************\n\n\n";
    cout<<"     Enter the Ticker symbol for the stock you want to analyze: ";
    cin>>smbl;


    d.PEAnalysis(smbl);

    cout<<"Press any key to return to home page..."<<endl;
    getch();
    system("cls");
    functions();
}

void Evebanalysis()
{
    system("cls");
    string smbl;
    cout<<"********************** EV/Ebidta ANALYSIS **********************\n\n\n";
    cout<<"     Enter the Ticker symbol for the stock you want to analyze : ";
    cin>>smbl;


    d.EvebAnalysis(smbl);

    cout<<"Press any key to return to home page..."<<endl;
    getch();
    system("cls");
    functions();

}

void Recommend()
{
    d.recommendStocks();
    cout<<"Press any key to return to home page..."<<endl;
    getch();
    system("cls");
    functions();
}

void userActivity()
{
    system("cls");

    int ch;

    cout<<"****** WELCOME TO USER ACTIVITY ******\n\n"<<endl;

    cout<<"\nChoose from the following options\n"<<endl;
    cout<<"     1) Enter new trades"<<endl;
    cout<<"     2) View TradeBook"<<endl;
    cout<<"     3) View PnL Statement\n\n"<<endl;
    cout<<"Your choice : ";
    cin>>ch;
    switch(ch)
    {
    case 1:
    {
        int n;
        system("cls");
        cout<<"Enter the number of trades : ";
        cin>>n;
        vector<string> trades;
        ofstream wfile(Password+Username+"tradebook.txt",ios_base::app);

        if(wfile.fail())
        {
            cout<<"OOPS!!! Error opening the file!!\n\n"<<endl;
            cout<<"Press any key to go back...."<<endl;
            getch();
            functions();

        }
        for(int i = 0; i<n; i++)
        {
            string SS,SP,QTY,B_S,Date;

            cout<<"\nEnter the data for trade : "<<i+1<<endl;
            fflush(stdin);
            cout<<"Enter Stock Symbol : ";
            cin>>SS;
            fflush(stdin);
            cout<<"Enter the Share price : ";
            cin>>SP;
            fflush(stdin);
            cout<<"Enter the number of shares bought/sold : ";
            cin>>QTY;
            cout<<"Enter whether shares were sold/bought S/B : ";
            cin>>B_S;
            fflush(stdin);
            cout<<"Enter Date in the format"<<"DD MM YYYY : ";
            getline(cin,Date);


            trades.push_back(SS+" "+SP+" "+QTY+" "+B_S+" "+Date ) ;
            wfile<<trades[i]<<endl;
        }
        wfile.close();
        cout<<"\n\nSaving Data";
        for(int i=1; i<=5; i++)
        {
            for(int j=0; j<=100000000; j++)
            {
            }
            cout<<".";
        }
        system("cls");
        cout<<"\nData Saved Successfully!\n\n"<<endl;
        cout<<"Press any key to continue..."<<endl;
        getch();
        system("cls");
        functions();
        break;
    }
    case 2:
    {
        system("cls");
        ifstream rfile;
        rfile.open(Password+Username+"tradebook.txt");
        vector<string> lines;
        string line;

        while (getline(rfile, line))
            lines.push_back(line);
        vector<string>::iterator i;
        vector<vector<string>> trade_data;
        vector<string> words;

        for(i=lines.begin(); i!=lines.end(); i++)
        {
            words= separate_words(*i);
            trade_data.push_back(words);
        }

        vector<vector<string>>::iterator it;
        for(it=trade_data.begin(); it!=trade_data.end(); it++)
        {
            cout<<"Stock Symbol: "<<(*it)[0]<<endl;
            cout<<"Share Price: "<<(*it)[1]<<endl;
            cout<<"Quantity: "<<(*it)[2]<<endl;
            cout<<"Buy/Sell: "<<(*it)[3]<<endl;
            cout<<"Date: "<<(*it)[4]<<"-"<<(*it)[5]<<"-"<<(*it)[6]<<endl<<endl;
        }
        cout<<"\nPress any key to continue..."<<endl;
        getch();
        system("cls");
        functions();
        break;
    }
    case 3:
    {
        system("cls");
        ifstream rfile(Password+Username+"tradebook.txt");
        if(rfile.fail())
        {
            cout<<"\nError in opening file!!\n\n"<<endl;
            cout<<"Press any key to go back..."<<endl;
            getch();
            system("cls");
            functions();
        }
        vector<string> lines;
        string line;

        while (getline(rfile, line))
            lines.push_back(line);

        vector<string>::iterator i;
        vector<vector<string>> trade_data;
        vector<string> words;

        for(i=lines.begin(); i!=lines.end(); i++)
        {
            words= separate_words(*i);
            trade_data.push_back(words);
        }
        int l,j,k,flag;
        double sumB,sumS,rsums,rsumb,unrealprice,current_sp;
        PnL temp;
        vector<PnL> pnl_data;

        for(l=0; l<trade_data.size(); l++)
        {
            flag = 1;
            sumB = 0;
            sumS = 0;
            rsums = 0;
            rsumb = 0;
            for(j=l-1; j>=0; j--)
            {
                if(trade_data[l][0]==trade_data[j][0])
                {
                    flag = 0;
                    break;
                }
            }
            for(k=l; k<trade_data.size()&&flag; k++)
            {
                if(trade_data[l][0]==trade_data[k][0])
                {
                    if(trade_data[k][3]=="B")
                    {
                        sumB = sumB + stod(trade_data[k][2])*stod(trade_data[k][1]);
                        rsumb = rsumb + stod(trade_data[k][2]);
                    }
                    else if(trade_data[k][3]=="S")
                    {
                        sumS = sumS + stod(trade_data[k][2])*stod(trade_data[k][1]);
                        rsums = rsums + stod(trade_data[k][2]);
                    }
                    if((rsumb>rsums)&&(trade_data[k][3]=="B"))
                    {
                        unrealprice = stod(trade_data[k][1]);

                    }

                }
            }
            if(flag)
            {
                temp.name = trade_data[l][0];
                temp.TotalB = sumB;
                temp.TotalS= sumS;
                temp.Charges = (0.001)*(sumB+sumS);
                cout<<"Enter the current share price of "<<trade_data[l][0]<<" : ";
                cin>>current_sp;
                temp.URpnl = (rsumb - rsums)*(current_sp-unrealprice);
                temp.NETpnl = sumB-sumS;
                temp.Rpnl = temp.NETpnl - temp.URpnl;
                pnl_data.push_back(temp);
            }
        }
        vector<PnL>::iterator itp;
        ofstream wfile(Password+Username+"PnL.txt");
        cout<<"\n\n\n";
        cout<<"Stock Name\tTotal_Buy_Value\tTotal_Sold_Value   Unrealised_PnL\tNet_PnL\t    Realised_PnL\tTaxes_n_Charges"<<endl;
        wfile<<"Stock Name\tTotal_Buy_Value\t\tTotal_Sold_Value \t  Unrealised_PnL\t\tNet_PnL\t\t    Realised_PnL\t\tTaxes_n_Charges"<<endl;
        for(itp=pnl_data.begin(); itp!=pnl_data.end(); itp++)
        {
            cout<<itp->name<<"\t\t"<<itp->TotalB<<"\t\t"<<itp->TotalS<<"\t\t  "<<itp->URpnl<<"\t\t  "<<itp->NETpnl<<"\t\t  "<<itp->Rpnl<<"\t\t  "<<itp->Charges<<endl;
            wfile<<itp->name<<"\t\t"<<to_string(itp->TotalB)<<"\t\t"<<to_string(itp->TotalS)<<"\t\t  "<<to_string(itp->URpnl)<<"\t\t  "<<to_string(itp->NETpnl)<<"\t\t  "<<itp->Rpnl<<"\t\t  "<<itp->Charges<<endl;
        }


        rfile.close();
        cout<<"\n\n\nPress any key to go back..."<<endl;
        getch();
        system("cls");
        functions();
        break;
    }
    }
}


void close()
{
B:
    system("cls");

    cout<<"\nDo you really want to exit? :-(\n"<<endl<<"      1)No :-)                2)Yes\n\n"<<endl;
    cout<<"Your choice : ";
    int choice;

    cin>>choice;
    switch(choice)
    {

    case 1:
        system("cls");
        return functions();

    case 2:
    {
        system("cls");

        SetConsoleTextAttribute(h,2);
        ifstream ip("Exit.txt");
        string exit;
        while(ip.eof()==0)
        {
            getline(ip,exit);
            cout<<exit<<endl;
        }
        ip.close();
        SetConsoleTextAttribute(h,7);

        cout<<"Press any key to exit..."<<endl;
        getch();
        break;
    }

    default :
        system("cls");
        cout<<"\nYou have entered incorrect value!!\n\n\n"<<endl;
        cout<<"Press any key to try again..."<<endl;
        getch();
        goto B;

    };

}
