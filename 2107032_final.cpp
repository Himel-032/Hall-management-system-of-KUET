    // Admin ID: 123
    // Admin password: 123


#include<iostream>
#include<string>
#include<vector>
#include<typeinfo>
#include<fstream>


using namespace std;
class registration;
class login;
class complain;
class KUET
{
public:
    virtual  void details()=0;     // Pure virtual funtion()
    virtual void contact()=0;      // Abstract base class
};
class Banga:public KUET
{
    int seats=100;
    int filled=0;
public:
    void contact()
    {
        string s;
        ifstream infile;
        infile.open("contact_info.txt");
        while(infile)
        {
            getline(infile,s);
            cout<<s<<endl;
        }
        infile.close();
    }
    void set_filled()
    {
        ifstream infile;
        infile.open("filled.txt");
        string dummy;
        getline(infile,dummy);
        while(dummy[filled]=='f' && filled<seats)
        {
            filled++;
        }
        filled++;
    }
    void upstatus(int n)
    {
        ifstream infile;
        infile.open("filled.txt");
        string dummy;
        getline(infile,dummy);
        infile.close();
        if(dummy[n-1]=='f')
            dummy[n-1]='v';
        else
            dummy[n-1]='f';
        ofstream outfile;
        outfile.open("filled.txt");
        outfile<<dummy;
        outfile.close();
    }
    virtual void details()
    {
        ifstream infile;
        infile.open("hall_info.txt");
        while(infile)
        {
            string s;
            getline(infile,s);
            cout<<s<<endl;
        }
        infile.close();
    }
    friend class registration;           // friend class
};

class student:public Banga
{
    int boarder,roll,batch;
    string name,dept,id,pass_stud,meal_stat;
public:
    void details()                         // redeclaration of pure virtual function()
    {
        cout<<"Name    : "<<name<<endl;
        cout<<"Id      : "<<id<<endl;
        cout<<"Dept    : "<<dept<<endl;
        cout<<"Roll    : "<<roll<<endl;
        cout<<"Batch   : "<<batch<<endl;
        cout<<"Boarder : "<<boarder<<endl;
    }
    friend class registration;
    friend class login;
    friend class meal;
    friend void all_students();
    friend void student_login(student a);
};

string pass_set(string s)               // unique password set for each student
{
    for(char &c:s)
    {
        if(c==' ')
            c='_';
    }
    return s;
}

template<class T>                  // Template (generic function())
T id_set(T s)
{
    T dummy;
    for(int i=0; i<s.size(); i++)
    {
        if(s[i]==' ')
            break;
        else
            dummy=dummy+s[i];
    }
    return dummy;
}

class registration:public student
{
public:
    string s;
    void get_info()
    {
        int a;
        cout<<"Give valid information: "<<endl<<endl;
        cout<<"Enter name: ";
        getline(cin,s);
        getline(cin,name);
        cout<<"Enter Dept(short form): ";
        getline(cin,dept);

        cout<<"Enter roll: ";
C:
        cin>>a;
                          // Exeption Handling
        try
        {
            if(a==0)
                throw a;
        }
        catch(...)
        {
            cout<<"Please,enter a valid roll: ";
            goto C;
        }
        roll=a;
        cout<<"Batch: ";
        cin>>batch;
    }
    void confirm()
    {
        set_filled();
        if(filled<seats)
        {
            student::id=id_set<string>(name)+to_string(roll);
            student::pass_stud=pass_set(name)+to_string(roll)+to_string(filled);
            cout<<"Registration successful..."<<endl;
            cout<<"Your id: "<<id<<endl;
            cout<<"Your password: "<<pass_stud<<endl;
            cout<<"Boarder no: "<<filled<<endl;
            upstatus(filled);
            ofstream outfile;
            string stud_file=id+".txt";
            outfile.open(stud_file);
            outfile<<filled<<endl<<id<<endl<<pass_stud<<endl<<name<<endl<<dept<<endl<<roll<<endl<<batch<<endl;
            outfile.close();
            outfile.open("all_stud.txt",ios::app);
            outfile<<id<<endl;
            outfile.close();
        }
        else
            cout<<"No seat available"<<endl;
    }
};



void all_students()
{                                           // STL
    vector<string>v;
    ifstream infile;
    infile.open("all_stud.txt");
    cout<<"Students list: "<<endl;
    cout<<"_______________"<<endl;

    while(infile)
    {
        string s;
        getline(infile,s);
        s=s+".txt";
        v.push_back(s);

    }
    cout<<"_______________"<<endl;
    infile.close();

    for(int i=1; i<v.size()-1; i++)
    {
        string s;
        infile.open(v[i]);
        getline(infile,s);
        cout<<"Boarder no: "<<s<<endl;
        getline(infile,s);
        cout<<"ID:       : "<<s<<endl;
        getline(infile,s);
        cout<<"Password  : "<<s<<endl;
        getline(infile,s);
        cout<<"Name      : "<<s<<endl;
        getline(infile,s);
        cout<<"Dept.     : "<<s<<endl;
        getline(infile,s);
        cout<<"Roll      : "<<s<<endl;
        getline(infile,s);
        cout<<"Batch     : "<<s<<endl;
        infile.close();
        cout<<endl;

    }

}

void notify()
{
    string s,g;
    cout<<"Write Notice to add:   ";
    getline(cin,g);
    getline(cin,s);
    ofstream outfile;
    outfile.open("notice.txt",ios::app);
    outfile.seekp(0);
    if(s!="\n")
        outfile<<s<<endl;
    outfile.close();
}

class complain
{
    string id,statement,s;
public:
    void add()
    {
        cout<<"Enter id: ";
        cin>>id;
        cout<<"Enter complain  statement: ";
        getline(cin,s);
        getline(cin,statement);
    }
                                   // Operator overloading


    friend istream& operator>>(istream &cin,complain &c)
    {
        ofstream outfile;
        outfile.open("complain.txt",ios::app);
        outfile<<c.id<<endl;
        outfile<<c.statement<<endl;
        outfile.close();
        return cin;
    }
    friend ostream& operator<<(ostream &cout,complain &c)
    {
        cout<<"All complains: "<<endl;
        ifstream infile;
        infile.open("complain.txt");
        while(infile)
        {
            getline(infile,c.id);
            cout<<"ID : "<<c.id<<endl;
            getline(infile,c.statement);
            cout<<"Statement : "<<c.statement<<endl;
        }
        infile.close();
        return cout;
    }

};

class admin:public Banga
{
    string id,pass_admin;
public:
    void authority()
    {

        cout<<"Welcome Provost"<<endl<<endl;
B:
        cout<<"Enter number to acces menu"<<endl;
        cout<<"1. Get list of all students."<<endl;
        cout<<"2.view complains."<<endl;
        cout<<"3. Add notice."<<endl;
        cout<<"0. Log out."<<endl;
        while(1)
        {
            int n;
            cout<<"Choice option: ";
            cin>>n;
            if(n==0) break;
            else if(n==1)
            {
                all_students();
                goto B;

            }
            else if(n==2)
            {
                complain c;
                cout<<c;
                goto B;
            }
            else if(n==3)
            {
                notify();
                goto B;
            }
            else cout<<"invalid choice"<<endl;
        }
    }
    void show_notice()
    {
        ifstream infile;
        infile.open("notice.txt");
        cout<<"Notice board: "<<endl;
        while(infile)
        {
            string s;
            getline(infile,s);
            cout<<s<<endl;
        }
        infile.close();
    }
    friend class login;
};

class login:virtual public student,virtual public admin
{
public:
    void process()
    {
        cout<<"Log in portal"<<endl;
        cout<<"1.student login"<<endl;
        cout<<"2.provost login"<<endl;
        cout<<"choose a option: ";
        int n;
        cin>>n;
        if(n==1)
        {
            string id,pass;
            cout<<"Enter your id: ";
            cin>>id;
            cout<<"Enter password: ";
            cin>>pass;
            string fname=id+".txt";
            ifstream infile;
            infile.open(fname);
            if(infile.is_open())
            {
                student a;
                string s;
                getline(infile,s);
                a.boarder=stoi(s);
                getline(infile,s);
                a.id=s;
                getline(infile,s);
                a.pass_stud=s;
                if(a.pass_stud==pass)
                {
                    getline(infile,s);
                    a.name=s;
                    getline(infile,s);
                    a.dept=s;
                    getline(infile,s);
                    a.roll=stoi(s);
                    getline(infile,s);
                    a.batch=stoi(s);
                    infile.close();
                    student_login(a);
                }
                else
                    cout<<"wrong id or password"<<endl;
            }
            else
                cout<<"Account does not exist"<<endl;
        }
        else if(n==2)
        {
            string id,pass;
            cout<<"Enter provost id: ";
            cin>>id;
            cout<<"Enter password: ";
            cin>>pass;
            admin admn;
            ifstream infile;
            infile.open("admin.txt");
            getline(infile,admn.id);
            getline(infile,admn.pass_admin);
            if(admn.id == id && admn.pass_admin == pass)
                admn.authority();
            else
                cout<<"Wrong id or password"<<endl;

        }
    }
    friend void student_login(student a);
};

class meal:public login
{
    student a;
public:
    meal() {}
    meal(student &s)
    {
        a=s;
    }
    void meal_info()
    {
        cout<<"Available item to eat: "<<endl;
        cout<<"1.Breakfast = XXX"<<endl;
        cout<<"2.Lunch = Rice,Egg,chicken,Lentils"<<endl;
        cout<<"3.Dinner = Rice,Beaf,Sweet,Fish"<<endl;
    }
};

void student_login(student a)
{
    cout<<endl<<"Hello! "<<endl<<a.name<<endl<<endl;
A:
    cout<<"Enter choice to access:"<<endl;
    cout<<"1.Information"<<endl;
    cout<<"2.Meal information"<<endl;
    cout<<"0.Log out"<<endl<<endl;
    while(1)
    {
        int n;
        cout<<"choose a option: ";
        cin>>n;
        if(n==0)
            break;
        else if(n==1)
        {
            a.details();
            goto A;
        }

        else if(n==2)
        {
            meal m(a);
            m.meal_info();
            goto A;
        }
        else
        {
            cout<<"Invalid choice"<<endl;
            goto A;
        }

    }
}


int main()
{
    cout<<"*********************************************************************"<<endl;
    cout<<"||  Welcome to BANGABANDHU SHEIKH MUJIBUR RAHMAN HALL,KUET,KHULNA  ||"<<endl;
    cout<<"*********************************************************************"<<endl<<endl;
A:
    cout << "MAIN MENU\n\nEnter number to access menu" << endl<<endl;
    cout<<"====================="<<endl;
    cout << "1. Hall Details" << endl;
    cout << "2. New Registration" << endl;
    cout << "3. Login" << endl;
    cout << "4. Notice Board" << endl;
    cout << "5. Complain Box" << endl;
    cout << "6. Contact information" << endl;
    cout << "0. Terminate Session" << endl;
    cout << "======================" << endl;
    cout << endl;
    while(1)
    {
        int n;
        Banga l;
        KUET *b=&l;           // base class pointer holding derived class object ( polymorphism)
        cout<<"chose a option: ";
        cin>>n;
        cout<<endl;



        if(n==0)
            break;
        else if(n==1)
        {
            b->details();
            goto A;
        }

        else if(n==2)
        {
            registration reg;
            reg.get_info();
            reg.confirm();
            goto A;
        }
        else if(n==3)
        {
            login lg;
            lg.process();
            goto A;
        }
        else if(n==4)
        {
            admin ad;
            ad.show_notice();
            goto A;
        }
        else if(n==5)
        {
            complain cmp;
            cmp.add();
            cin>>cmp;
            goto A;
        }
        else if(n==6)
        {
            Banga* ptr=dynamic_cast<Banga*>(b);  // RTTI
            ptr->contact();
            goto A;
        }
        else
        {
            cout<<"Invalid choice"<<endl;
            goto A;
        }

    }
    return 0;
}
