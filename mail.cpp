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

    //-------------------------print main menu (M)
    line();
    cout<<"S : Sign up"<<endl;
    cout<<"L : Login"<<endl;
    cout<<"E : Exit"<<endl;
    line();
    cout<<"Enter choice : ";
    cin>>choice;

    //-------------------------menu choice
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

    //-------------------------exit program on E choice
    E:
    return 0;
}

//-------------------------function of sign up
void signup()
{
    ofstream fout;
    string fname,id,pass;

    system("CLS");

    //-------------------------ask for user id & password for sign up
    line();
    cout<<"New user registration";
    line();
    cout<<setw(12)<<"User ID : ";
    cin>>id;
    cout<<setw(12)<<"Password : ";
    cin>>pass;

    //-------------------------append user id & password in user.txt file
    fout.open("user.txt",ios::app);
    fout<<id<<'\t'<<pass<<endl;
    fout.close();

    //-------------------------create userid_s.txt file
    fname=id+"_s.txt";

    fout.open(fname.c_str(),ios::out);
    fout.close();

    //-------------------------create userid_r.txt file
    fname=id+"_r.txt";

    fout.open(fname.c_str(),ios::out);
    fout.close();

    //-------------------------call home screen function
    home(id);
}

//-------------------------function of login
void login()
{
    ifstream fin;
    string id,pass,cid,cpass;
    int found=0;
    char next;

    system("CLS");

    //-------------------------ask for user if & password for login
    line();
    cout<<"User Login";
    line();
    cout<<setw(12)<<"User ID : ";
    cin>>id;
    cout<<setw(12)<<"Password : ";
    cin>>pass;

    //-------------------------validate user id & password with entry in user.txt file
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

    //-------------------------invalid credential print error message
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
    //-------------------------valid credential call home screen function
    else
    {
            home(id);
    }
}

//-------------------------function of home screen
void home(string id)
{
    char choice;

    NEXT:

    system("CLS");

    //-------------------------print login user name on top
    line();
    cout<<"Hello "<<id<<"...";
    line();

    //-------------------------print user menu (U)
    cout<<"C : Compose mail"<<endl;
    cout<<"I : Inbox"<<endl;
    cout<<"S : Sent"<<endl;
    cout<<"E : log out"<<endl<<endl;
    cout<<"Enter choice : ";
    cin>>choice;

    //-------------------------menu choice
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

//-------------------------function of compose mail
void compose(string id)
{
    ifstream fin;
    ofstream fouts,foutr;
    int found=0;
    string fnames,fnamer,to,cid,cpass,data;
    char next;

    NEXT:

    system("CLS");

    //-------------------------print login user name on top
    line();
    cout<<"Hello "<<id<<"...";
    line();

    //-------------------------ask for user id in "To"
    cout<<"To : ";
    cin>>to;

    //-------------------------validate user id with entry in user.txt file
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

    //-------------------------invalidate user id print error message
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
    //-------------------------validate user id make entry in
    //-------------------------userid_s.txt file of sender and userid_r.txt file of receiver with content
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

        //-------------------------call home screen function
        home(id);
    }
}

//-------------------------function of inbox
void inbox(string id)
{
    ifstream fin;
    string fname,data;
    int c=0;
    char next;

    system("CLS");

    //-------------------------print login user name on top
    line();
    cout<<"Hello "<<id<<"...";
    line();

    //-------------------------print content of userid_r.txt
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

    cout<<endl<<"Press any key to go to home page : ";
    cin>>next;

    //-------------------------go back to home screen
    if(next)
    {
        home(id);
    }
}

//-------------------------function of sent mail
void sent(string id)
{
    ifstream fin;
    string fname,data;
    int c=0;
    char next;

    system("CLS");

    //-------------------------print login user name on top
    line();
    cout<<"Hello "<<id<<"...";
    line();

    //-------------------------print content of userid_s.txt
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

    cout<<endl<<"Press any key to go to home page : ";
    cin>>next;

    //-------------------------go back to home screen
    if(next)
    {
        home(id);
    }
}

//-------------------------function to print --- line as separator
void line()
{
    int i;
    cout<<endl;

    //-------------------------print 100 -
    for(i=0;i<100;i++)
    {
        cout<<"-";
    }
    cout<<endl;
}
