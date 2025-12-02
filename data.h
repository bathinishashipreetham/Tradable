#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <fstream>

using namespace std;



class Data
{
    MYSQL* conn;

public:
    Data()
    {
        conn = mysql_init(0);
        conn = mysql_real_connect(conn,"172.16.82.217","admin","admin","stocks",0,NULL,0);                    //172.16.82.217 is IP address
    }

    void insertStocksIntoTable();

    void insertUsersIntoTable(string user,string aadhar, string pan,string dob, string ac, string mobile);

    void findStock(string smbl);

    void PEAnalysis(string smbl);

    void EvebAnalysis(string smbl);

    void recommendStocks();

};

Data d;

void Data::insertStocksIntoTable()
{

    stringstream ss;

    ss<<"INSERT INTO info_stocks VALUES('mb','My Bank','Finance',120,125,142,138,12,3,4,5,8,9,15)";
    string query = ss.str();
    const char* q = query.c_str();
    mysql_query(conn,q);


    mysql_query(conn,"INSERT INTO info_stocks VALUES('mw','Man Work lmdt','Industrial',46,39,45,48,14,21,17,29,11,17,22)");

    mysql_query(conn,"INSERT INTO info_stocks VALUES('wt','Web Tech','IT',192,198,208,241,13,23,17,11,14,10,18)");
}

void Data::insertUsersIntoTable(string user,string aadhar, string pan,string dob, string ac, string mobile)
{
    stringstream ss;
    ss<< "INSERT INTO info_user VALUES('" + user + "','" + aadhar + "','" + pan + "','" + dob + "','" + ac + "','" + mobile + "')";
    string query = ss.str();
    const char *q = query.c_str();
    mysql_query(conn,q);
}

void Data::findStock(string smbl)
{

    string filename;
    system("cls");
    cout<<"Searching Database";
    for(int i=1; i<=5; i++)
    {
        for(int j=0; j<=100000000; j++)
        {
        }
        cout<<".";
    }
    system("cls");
    int qstate = 0;
    MYSQL_ROW row;
    MYSQL_RES* res;
    stringstream ss;

    ss<<"SELECT * FROM info_stocks where Symbol = '" + smbl + "'";
    string query = ss.str();
    const char *q = query.c_str();
    qstate = mysql_query(conn,q);

    int flag = 0;

    if(qstate==0)
    {

        res = mysql_store_result(conn);

        while(row = mysql_fetch_row(res))
        {
            flag = 1;
            string s(row[1]);
            filename = s;
            cout<<"   STOCK FOUND!!!\n\n";
            cout<<"     Symbol : "<<row[0]<<endl;
            cout<<"     Name : "<<row[1]<<endl;
            cout<<"     Sector : "<<row[2]<<endl;
            cout<<"     Current Price : "<<row[6]<<endl;
            cout<<"     PE : "<<row[7]<<endl;
            cout<<"     Indus PE : "<<row[13]<<endl;
        }
    }

    if(flag==1)
    {
        cout<<"\n\nWant more detailed information??"<<endl;
        cout<<"Do you want to download a file with detailed stock analysis?\n"<<endl;
        cout<<"1)Yes, Please!      2)No, Thanks!\n\n"<<endl;
        int choice;
B:
        cout<<"Your choice : ";
        cin>>choice;

        if(choice == 1)
        {
            cout<<"\nDownloading";
            for(int i=1; i<=5; i++)
            {
                for(int j=0; j<=150000000; j++)
                {
                }
                cout<<".";
            }


            ofstream out;

            out.open("C:\\Users\\hp\\OneDrive\\Desktop\\Viewed Stocks\\" + filename + ".txt");
            int qstate2 = 0;
            MYSQL_ROW row2;
            MYSQL_RES* res2;
            stringstream ss2;
            ss2<<"SELECT * FROM info_stocks where Symbol = '" + smbl + "'";
            string query2 = ss2.str();
            const char *q2 = query2.c_str();
            qstate2 = mysql_query(conn,q2);


            res2 = mysql_store_result(conn);

            while(row2 = mysql_fetch_row(res2))
            {
                out<<"Symbol : "<<row2[0]<<endl;
                out<<"Name : "<<row2[1]<<endl;
                out<<"Sector : "<<row2[2]<<endl;
                out<<"Price in first quarter of the year : "<<row2[3]<<endl;
                out<<"Price in second quarter of the year : "<<row2[4]<<endl;
                out<<"Price in third quarter of the year : "<<row2[5]<<endl;
                out<<"Current Price : "<<row2[6]<<endl;
                out<<"PE : "<<row2[7]<<endl;
                out<<"EV : "<<row2[8]<<endl;
                out<<"EBITDA : "<<row2[9]<<endl;
                out<<"Debt : "<<row2[10]<<endl;
                out<<"CARG : "<<row2[11]<<endl;
                out<<"Share outstanding : "<<row2[12]<<endl;
                out<<"Indus PE : "<<row2[13]<<endl;
                out<<endl<<endl;
            }

            out.close();

            system("cls");
            cout<<"\nDownload complete\n\n"<<endl;

        }

        else if(choice ==2)
        {
            cout<<endl;
        }
        else
        {

            cout<<"\nInvalid choice !!!"<<endl;
            goto B;
        }

    }
    if(flag==0)
    {
        system("cls");
        cout<<"\nInvalid symbol!!!!\n" <<endl;
    }

    return;
}

void Data::PEAnalysis(string smbl)
{

    int qstate = 0;
    MYSQL_ROW row;
    MYSQL_RES* res;
    stringstream ss;

    ss<<"SELECT * FROM info_stocks where Symbol = '" + smbl + "'";
    string query = ss.str();
    const char *q = query.c_str();
    qstate = mysql_query(conn,q);

    int flag = 0;

    if(qstate==0)
    {

        res = mysql_store_result(conn);

        while(row = mysql_fetch_row(res))
        {
            flag = 1;
            string name = row[1];
            char* ips= row[13];
            char* ps = row[7];
            double ip = atof(ips);
            double p = atof(ps);
            cout<<"\n     Name : "<<name<<endl;
            cout<<"     Industry : "<<row[2]<<endl;
            cout<<"     PE ratio : "<<p<<endl;
            cout<<"     Industry PE ratio average : "<<ip<<endl;
            if(ip>p)
            {

                cout<<"\n\nSince, PE for this stock ("<<p<<") is better than industrial average("<<ip<<")"<<endl;
                cout<<"So, It is recommended to BUY this stock \n\n"<<endl;
            }
            else
            {
                cout<<"\n\nSince, industrial average PE ("<<p<<") is better than PE of this stock("<<ip<<")"<<endl;
                cout<<"So, It is recommended NOT to BUY this stock \n\n"<<endl;
            }
        }
    }
    if(flag==0)
    {
        system("cls");
        cout<<"Invalid Symbol!!!!\n\n"<<endl;
        return;
    }
}

void Data::EvebAnalysis(string smbl)
{

    int qstate = 0;
    MYSQL_ROW row;
    MYSQL_RES* res;
    stringstream ss;

    ss<<"SELECT * FROM info_stocks where Symbol = '" + smbl + "'";
    string query = ss.str();
    const char *q = query.c_str();
    qstate = mysql_query(conn,q);

    int flag = 0;

    if(qstate==0)
    {

        res = mysql_store_result(conn);

        while(row = mysql_fetch_row(res))
        {
            flag = 1;
            char* curr_Price = row[6];
            char* ebda= row[9];
            char* ev = row[8];
            char* carg = row[11];
            char* debt = row[10];
            char* share = row[12];
            double Current_Price = atof(curr_Price);
            double SHARE = atof(share);
            double EB = atof(ebda);
            double EV = atof(ev);
            double CARG = atof(carg);
            double DEBT = atof(debt);
            double curr_EVEB = EV/EB;
            double exp_EB = EB + (CARG*EB)/100.0;
            double forcasted_EV = exp_EB*curr_EVEB - DEBT;

            double Target_Price = forcasted_EV/SHARE;
            double Entry_Price = 0.66*Target_Price;

            cout<<"\n     Name : "<<row[1]<<endl;
            cout<<"     Current Price : "<<row[6]<<endl;
            cout<<"     EV : "<<EV<<endl;
            cout<<"     EBITDA : "<<EB<<endl;
            cout<<"     Current EV/EBITDA ratio : "<<curr_EVEB<<endl;
            cout<<"     Expected EBITDA : "<<exp_EB<<endl;
            cout<<"     Forcasted EV : "<<forcasted_EV<<endl;
            cout<<"     Share Outstandings : "<<SHARE<<endl;
            cout<<"     Target Price : "<<Target_Price<<endl;
            cout<<"     Entry Price : "<<Entry_Price<<endl;

            if(Entry_Price<=Current_Price)
            {
                cout<<"\nSince, Entry price for this stock ("<<Entry_Price<<") is lower than the current market price ("<<Current_Price<<")"<<endl;
                cout<<"So, The company is fairly over-valued and it is recommended NOT to BUY this stock\n\n "<<endl;
            }
            else
            {
                cout<<"\nSince, Entry price for this stock ("<<Entry_Price<<") is higher than the current market price ("<<Current_Price<<")"<<endl;
                cout<<"So, The company is currently under-valued and it is recommended to BUY this stock\n\n "<<endl;
            }
        }
    }
    if(flag==0)
    {
        system("cls");
        cout<<"Invalid Symbol!!!!\n\n"<<endl;
        return;
    }



}

void Data::recommendStocks()
{

    system("cls");
    cout<<"Searching Database";
    for(int i=1; i<=5; i++)
    {
        for(int j=0; j<=100000000; j++)
        {
        }
        cout<<".";
    }
    system("cls");


    int qstate = 0;
    MYSQL_ROW row;
    MYSQL_RES* res;
    stringstream ss;

    ss<<"SELECT Name,PE FROM info_stocks order by PE ASC";
    string query = ss.str();
    const char *q = query.c_str();
    qstate = mysql_query(conn,q);


    if(qstate==0)
    {

        res = mysql_store_result(conn);
        int i=1;
        while(row = mysql_fetch_row(res))
        {

            string name = row[0];
            char* pe = row[1];
            double PE = atof(pe);

            cout<<"\n"<<i++;
            cout<<"    Name : "<<name<<endl;
            cout<<"     PE ratio : "<<PE<<endl<<endl;

        }
    }


}

void GetThingsReady()
{

    d.insertStocksIntoTable();

}
