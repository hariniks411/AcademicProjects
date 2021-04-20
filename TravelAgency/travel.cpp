#include<conio.h>
#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
struct date
{
    int day;
    int month;
    int year;
};
void printHeader()
{
    cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    cout<<"\t\t\tVINAYAKAM TRAVEL AGENCY\n\n";
    cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    cout<<"\n\t\tYOU ARE VIEWING  VINAYAKAM TRAVEL AGENCY\n";
}
void printFooter()
{
    cout<<"\n\t\t\t\t=$PROGRAM ENDS$=\n";
    cout<<"\n*******************************************************************************";
}
void printTable()
{
    cout<<"\n\n\n\n\t                  TRAVEL CHART PLAN";
    cout<<"\n--------------------------------------------------------------------------------\n";
    cout<<"ID\tFROM\t\t\tTO\t\tTIME\t\tSEATS\tBUSFARE";
    cout<<"\n--------------------------------------------------------------------------------\n";
}
class Bus;
class TripBooking
{
private:
    int BusId,count1;
    int Age[60];
    int NumberOfPassengers;
    int Fare[60];
    date d;
public:
    string Name;
    void display(TripBooking t[],int n);
    int setData(Bus l[],int n);
    void displayHistory();
    friend void checkAvailability(Bus b[],int n);
};
class Bus
{
    string Source;
    string Destination;
    string ArrivalTime;
    string ReturnTime;
    int MaxSeats,i,Fare;
    int AvailableSeats[13][92];
    TripBooking *t;
public:
    int Id;
    void addBus();
    void editBus();
    void checkAvailability(Bus l[],int n);
    friend int TripBooking::setData(Bus l[],int n);
    friend void TripBooking::displayHistory();
    friend void checkAvailability(Bus b[],int n);
    Bus(){}
    Bus(int a,string b,string c,string d,string e,int f,int g,TripBooking *tr)
    {
        Id=a;
        Source=b;
        Destination=c;
        ArrivalTime=d;
        ReturnTime=e;
        MaxSeats=f;
        Fare=g;
        for(int j=0;j<92;j++)
        {
            AvailableSeats[Id][j]=MaxSeats;
        }
        t=tr;
    }
    void displayData();
};
class MyException
{
public:
    int what;
    string s;
    MyException(){what=0;s='\0';}
    MyException(int x,string y)
    {
        what=x;
        s=y;
    }
};
void Bus::editBus()
{
        cout<<"ENTER BUS ID:";
        cin>>Id;
        cout<<"ENTER SOURCE PLACE:";
        cin>>Source;
        cout<<"ENTER DESTINATION PLACE:";
        cin>>Destination;
        cout<<"ENTER ARRIVAL TIME:";
        cin>>ArrivalTime;
        cout<<"MAXIMUM SEATS:";
        cin>>MaxSeats;
        cout<<"ENTER BUS FARE:";
        cin>>Fare;
        for(int j=0;j<92;j++)
        {
            AvailableSeats[Id][j]=MaxSeats;
        }
}
void Bus::displayData()
{
    if((Source.length()<8)&&(Destination.length()<8))
        cout<<Id<<"\t"<<Source<<"\t\t\t"<<Destination<<"\t\t"<<ArrivalTime<<"\t\t "<<MaxSeats<<"\t"<<Fare<<"\n";
    else if((Source.length()>=8)&&(Destination.length()>=8))
        cout<<Id<<"\t"<<Source<<"\t\t"<<Destination<<"\t"<<ArrivalTime<<"\t\t "<<MaxSeats<<"\t"<<Fare<<"\n";
    else if((Source.length()<8)&&(Destination.length()>=8))
        cout<<Id<<"\t"<<Source<<"\t\t\t"<<Destination<<"\t"<<ArrivalTime<<"\t\t "<<MaxSeats<<"\t"<<Fare<<"\n";
    else
        cout<<Id<<"\t"<<Source<<"\t\t"<<Destination<<"\t\t"<<ArrivalTime<<"\t\t "<<MaxSeats<<"\t"<<Fare<<"\n";
}
void Bus::addBus()
{
    cout<<"ENTER BUS ID:";
    cin>>Id;
    cout<<"ENTER SOURCE PLACE:";
    cin>>Source;
    cout<<"ENTER DESTINATION PLACE:";
    cin>>Destination;
    cout<<"ENTER ARRIVAL TIME:";
    cin>>ArrivalTime;
    cout<<"MAXIMUM SEATS:";
    cin>>MaxSeats;
    cout<<"ENTER BUS FARE:";
    cin>>Fare;
    for(int j=0;j<92;j++)
    {
        AvailableSeats[Id][j]=MaxSeats;
    }
}
int TripBooking::setData(Bus l[],int n)
{
    int age[60],i,count1=0,count=0,sum=0,a,c,tempDay,tempMonth,tempYear;
    cout<<"NAME:\t";
    cin>>Name;
    try{
        cout<<"ENTER BUS ID:\t";
        cin>>a;
        if(a<0)  throw MyException(a,"Bus Id can't be negative!\n");
        if(a>n)  throw MyException(a,"Bus not available in this id!\n");
        BusId=a;
        for(i=0;i<n;i++)
            if(a==l[i].Id)
                for(int j=0;j<60;j++)
                    Fare[j]=l[i].Fare;
        cout<<"ENTER TRIP DATE:\t";
        cin>>tempDay;
        if(tempDay<1||tempDay>31)
            throw MyException(tempDay,"Days should be mentioned within 1 and 31 days");
        cin>>tempMonth;
        if(tempMonth!=10&&tempMonth!=11&&tempMonth!=12)
            throw MyException(tempMonth,"You can book tickets only for the months oct,nov and dec");
        d.month=tempMonth;
        cin>>tempYear;
        if(tempYear!=2020)
            throw MyException(tempYear,"You can book tickets only for the year 2020!");
        d.year=tempYear;
        if(tempMonth==11&&tempDay==31)
            throw MyException(tempDay,"November has 30 days!");
        d.day=tempDay;
        cout<<"ENTER NUMBER OF PASSENGERS:\t";
        cin>>NumberOfPassengers;
        for(i=0;i<n;i++)
        {
            if(BusId==l[i].Id)
            {
				if(tempMonth==10)
					count=tempDay;
				else if(tempMonth==11)
					count=tempDay+31;
				else
					count=61+tempDay;
				if(l[i].AvailableSeats[BusId][count]-NumberOfPassengers<0)
					 throw MyException(l[i].AvailableSeats[BusId][count]-NumberOfPassengers,"That much number of seats are not available!");
				l[i].AvailableSeats[BusId][count]-=NumberOfPassengers;
        	}
        }
        	for(i=0;i<NumberOfPassengers;i++)
            {
                cout<<"Enter Age:";
                cin>>age[i];
                if(age[i]<0)
                    throw MyException(age[i],"Age can't be negative!\n");
                if(age[i]>110)
                    throw MyException(age[i],"Age should be mentioned within 110!\n");
                Age[i]=age[i];
                if(age[i]>0&&age[i]<13||age[i]>70)
                    Fare[i]=(Fare[i])/2;
            }
            count1=i;
            for(int j=0;j<i;j++)
                sum+=Fare[j];
        cout<<"\n\tTHANK YOU:)!\n";
        return sum;
    }
        catch(MyException e)
        {
            cout<<e.s<<"("<<e.what<<")"<<"\n";
        }
}
void TripBooking::display(TripBooking t[],int n)
{
    TripBooking temp;
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(t[i].BusId>t[j].BusId)
            {
                temp=t[i];
                t[i]=t[j];
                t[j]=temp;
            }
        }
    }
    for(i=0;i<n;i++)
        t[i].displayHistory();
}
void TripBooking::displayHistory()
{
    cout<<"NAME="<<Name<<"\n";
    /*cout<<"CUSTOMER AGE="<<"\n";
    for(int i=0;i<count1;i++)
        cout<<Age[i]<<"\n";*/
    cout<<"NUMBER OF PASSENGERS="<<NumberOfPassengers<<"\n";
    cout<<"TRIP DATE="<<d.day<<"/"<<d.month<<"/"<<d.year<<"\n";
    cout<<"BUS ID BOOKED="<<BusId<<"\n";
}
void checkAvailability(Bus b[],int n)
{
    int count=0,id,month,day,year;
    cout<<"Enter Bus Id:";
    cin>>id;
    cout<<"Enter date:";
    cin>>day;
    cin>>month;
    cin>>year;
    for(int i=0;i<n;i++)
    {
        if(b[i].Id==id)
        {
            if(month==10)
                count=day;
            else if(month==11)
                count=31+day;
            else
                count=61+day;
            cout<<"The ticket availability is "<< b[i].AvailableSeats[id][count]<<".\n";
        }
    }
}
int main()
{
    int option,i,j=0,r,n=0,opt1,opt2,temp1=0,temp2=0;
    Bus l[15];
    TripBooking *a,tr[50];
    Bus b[]={Bus(1,"Chennai","Kovai","4.30pm","10.00 a.m",47,1500,a),Bus(2,"Madurai","Salem","5.30am","5.50p.m",55,500,a),
    Bus(3,"Trichy","Kochin","3.30am","6.00pm",50,1000,a),Bus(4,"Erode","Chennai","8.30pm","8.30am",47,1500,a),
    Bus(5,"Kovai","Salem","2.30pm","11.00pm",50,600,a),Bus(6,"Vellore","Kovai","5.30pm","6.00 am",60,1000,a),
    Bus(7,"Ooty","Salem","1.30pm","4.00am",50,300,a),Bus(8,"Krishnagiri","Tiruppur","1.30pm","11.00pm",60,500,a),
    Bus(9,"Trichy","Chennai","7.30pm","5.00am",45,1000,a),Bus(10,"Erode","Ooty","8.00pm","8.00am",50,499,a)};
    for(i=0;i<10;i++)
    {
        l[i]=b[i];
        n++;
    }
    a=tr;
    while(1)
    {
        string pass;
        char ch;
        system("cls");
        printHeader();
        cout<<"\n\t\t1.TRAVEL AGENCY\n\t\t2.CUSTOMER\n\t\t3.EXIT\n";
        cout<<"\n\nENTER AN OPTION=";
        cin>>option;
        if(option==1)
        {
            system("cls");
            cout << "Enter password:";
            ch = _getch();
            while(ch != 13){//character 13 is enter
            pass.push_back(ch);
            cout << '*';
            ch = _getch();
            }
            system("cls");
            if(pass=="abc123")
            {
                printHeader();
            while(temp1==0)
            {
                cout<<"1.ADD BUS\n2.DISPLAY CUSTOMER HISTORY\n\ta.DISPLAY ALL\n\tb.DISPLAY IN SORTED ORDER BASED ON ID\n3.EDIT BUS DETAILS\n4.EXIT\n";
                cout<<"Enter option:";
                cin>>opt1;
                switch(opt1)
                {
                    case 1:l[n].addBus();++n;system("cls");break;
                    case 2:{char op;
                            cout<<"Enter 'a' or 'b':";
                             cin>>op;
                             switch(op)
                             {
                                 case 'a':{ifstream infile;
                                            infile.open("TRAVELS.DAT",ios::in|ios::binary);
                                            if(!infile){
                                            cout<<"File cannot be opened!\n";
                                            return 1;
                                            }
                                            int k=0;
                                            while(infile&&k<j)
                                            {
                                                infile.read((char*)&tr[k],sizeof(TripBooking));
                                                tr[k].displayHistory();
                                                k++;
                                            }
                                            infile.close();
                                            break;}
                                case 'b':{tr[0].display(tr,j);break;}
                                default:cout<<"Enter a valid option!\n";
                             }
                             break;
                             }
                    case 3:{
                            int id;
                            cout<<"Enter bus id:";
                            cin>>id;
                            for(i=0;i<n;i++)
                            {
                                if(l[i].Id==id)
                                    l[i].editBus();
                            }
                            system("cls");
                            break;}
                    case 4:temp1=1;break;
                    default:cout<<"Enter a valid option!!";
                }
            }
            }
            else    cout<<"\nIncorrect Password!!\n";
            cout<<"\n\n";
         }
         else if(option==2)
         {
             system("cls");
             printHeader();
                 printTable();
        for(i=0;i<n;i++)  l[i].displayData();
        cout<<"\n-------------------------------------------------------------------------------\n";
             while(temp2==0)
             {
                 cout<<"Age based concessions are provided (1-12) and greater than 70\n";
                 cout<<"1.BOOK TICKETS\n2.CHECK TICKET AVAILABILITY\n3.SHOW BUS DETAILS\n4.EXIT\nEnter option:";
                 cin>>opt2;
                 switch(opt2)
                 {
                     case 1:{int sum;
                    ofstream outfile;
                    if(j==0)
                        outfile.open("TRAVELS.DAT",ios::out|ios::binary);
                    else
                        outfile.open("TRAVELS.DAT",ios::app|ios::binary);
                    sum=tr[j].setData(l,n);
                    outfile.write((char*)&tr[j], sizeof(TripBooking));
                    j++;
                    outfile.close();system("cls");
                    cout<<tr[j-1].Name<<"!"<<"Total ticket cost is "<<sum<<"\n";
                    break;}
                    case 2:checkAvailability(l,n);break;
                    case 3:{printTable();
                    for(i=0;i<n;i++)
                        l[i].displayData();
                    cout<<"\n-------------------------------------------------------------------------------\n";
                    break;}
                    case 4:temp2=1;break;
                    default:cout<<"\nEnter a valid option!\n";break;
                 }
             }
             cout<<"\n\n";
         }
         else if(option==3)
            return 0;
         else
            cout<<"\nEnter a valid option!\n";
        temp1=0;
        temp2=0;
    }
}
