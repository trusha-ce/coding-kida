#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>

using namespace std;

void signup();
void login();
void home(string);
void compose(string);
void inbox(string);
void sent(string);
void line();

int main()
{
    char choice,next;

    NEXT:

    system("CLS");
    line();
    cout<<"S : Sign up"<<endl;
    cout<<"L : Login"<<endl;
    cout<<"E : Exit"<<endl;
    line();
    cout<<"Enter choice : ";
    cin>>choice;

    switch(choice)
    {
    case 'S':
        signup();
        break;
    case 'L':
        login();
        break;
    case 'E':
        goto E;
        break;
    default:
        goto NEXT;
    }

    E:
    return 0;
}

void signup()
{
    ofstream fout;
    string fname,id,pass;

    system("CLS");
    line();
    cout<<"New user registration";
    line();
    cout<<setw(12)<<"User ID : ";
    cin>>id;
    cout<<setw(12)<<"Password : ";
    cin>>pass;

    fout.open("user.txt",ios::app);
    fout<<id<<'\t'<<pass<<endl;
    fout.close();

    fname=id+"_s.txt";

    fout.open(fname.c_str(),ios::out);
    fout.close();

    fname=id+"_r.txt";

    fout.open(fname.c_str(),ios::out);
    fout.close();

    home(id);
}
void login()
{
    ifstream fin;
    string id,pass,cid,cpass;
    int found=0;
    char next;

    system("CLS");
    line();
    cout<<"User Login";
    line();
    cout<<setw(12)<<"User ID : ";
    cin>>id;
    cout<<setw(12)<<"Password : ";
    cin>>pass;

    fin.open("user.txt",ios::in);
    while(!fin.eof())
    {
        fin>>cid>>cpass;
        if(cid==id && cpass==pass)
        {
            found=1;
            break;
        }
    }
    fin.close();
    if(found==0)
    {
        cout<<endl<<"***** ERROR : invalid user ID or password. *****"<<endl<<"press 'y' to try again, press 'n' to exit : ";
        cin>>next;
        if(next=='y')
        {
            login();
        }
        else
        {
            main();
        }
    }
    else
    {
            home(id);
    }
}

void home(string id)
{
    char choice;

    NEXT:

    system("CLS");
    line();
    cout<<"Hello "<<id<<"...";
    line();

    cout<<"C : Compose mail"<<endl;
    cout<<"I : Inbox"<<endl;
    cout<<"S : Sent"<<endl;
    cout<<"E : log out"<<endl<<endl;
    cout<<"Enter choice : ";
    cin>>choice;

    switch(choice)
    {
    case 'C':
        compose(id);
        break;
    case 'I':
        inbox(id);
        break;
    case 'S':
        sent(id);
        break;
    case 'E':
        main();
        break;
    default:
       goto NEXT;
    }
}

void compose(string id)
{
    ifstream fin;
    ofstream fouts,foutr;
    int found=0;
    string fnames,fnamer,to,cid,cpass,data;
    char next;

    NEXT:

    system("CLS");
    line();
    cout<<"Hello "<<id<<"...";
    line();

    cout<<"To : ";
    cin>>to;

    fin.open("user.txt",ios::in);
    while(!fin.eof())
    {
        fin>>cid>>cpass;
        if(cid==to)
        {
            found=1;
            break;
        }
    }
    fin.close();
    if(found==0)
    {
        cout<<endl<<"ERROR : receiver does not exist."<<endl<<"press 'y' to try new user, press 'n' to exit : ";
        cin>>next;
        if(next=='y')
        {
            goto NEXT;
        }
        else
        {

            home(id);
        }
    }
    else
    {
        fnamer=to+"_r.txt";
        foutr.open(fnamer.c_str(),ios::app);
        foutr<<"From : "<<id<<endl<<"Message : ";

        fnames=id+"_s.txt";
        fouts.open(fnames.c_str(),ios::app);
        fouts<<"To : "<<to<<endl<<"Message : ";

        cout<<"Content : ";
        //do
        //{
            cin>>data;
            foutr<<data;
            fouts<<data;
        //}
        //while(data!='\n');

        foutr<<endl<<"#"<<endl;
        fouts<<endl<<"#"<<endl;

        foutr.close();
        fouts.close();

        home(id);
    }
}

void inbox(string id)
{
    ifstream fin;
    string fname,data;
    int c=0;
    char next;

    system("CLS");
    line();
    cout<<"Hello "<<id<<"...";
    line();

    fname=id+"_r.txt";
    fin.open(fname.c_str(),ios::in);
    if(fin.is_open())
    {
        while(getline(fin,data))
        {
            if(data=="#")
            {
                c++;
                cout<<"----------"<<endl;
            }
            else
            {
                cout<<data<<endl;
            }
        }
        cout<<endl<<"***  total mails : "<<c<<"  ***"<<endl;
        fin.close();
    }

    cout<<endl<<"Press 'b' to go to home page : ";
    cin>>next;
    if(next)
    {
        home(id);
    }
}

void sent(string id)
{
    ifstream fin;
    string fname,data;
    int c=0;
    char next;

    system("CLS");
    line();
    cout<<"Hello "<<id<<"...";
    line();

    fname=id+"_s.txt";
    fin.open(fname.c_str(),ios::in);
    if(fin.is_open())
    {
        while(getline(fin,data))
        {
            if(data=="#")
            {
                c++;
                cout<<"----------"<<endl;
            }
            else
            {
                cout<<data<<endl;
            }
        }
        cout<<endl<<"***  total mails : "<<c<<"  ***"<<endl;
        fin.close();
    }

    cout<<endl<<"Press 'b' to go to home page : ";
    cin>>next;
    if(next)
    {
        home(id);
    }
}

void line()
{
    int i;
    cout<<endl;
    for(i=0;i<100;i++)
    {
        cout<<"-";
    }
    cout<<endl;
}
