#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

class person
{

 private:
    int priority;
    char name[50];
    char type;
    char group;

 public:
    void read();
    void personDisplay();
    void setType(char t);
    void setGroup(char g);
    void setPriority(int p);
    char getType();
    char getGroup();
    int getPriority();
};

class donor : public person
{

 private:
    int id;
    int age;
    int date;
    int month;
    int year;
    float qty;
    float weight;
    char HIV;
    char HTLV;
    char Hepatitis;
    char WNV;
    char Syphillis;
    int eligibility;

 public:
    void read();
    void display();
    void displayAll();
    void availability();
    int getQty();
    int getDate();
    int getMonth();
    int getYear();
};

class recipient : public person
{

 private:
    int qty;

 public:
    void read();
    void display();
    void displayAll();
    int assignPriority();
    void setQty(int q);
    void setRecipientPriority(int p);
    int getQty();
    int getRecipientPriority();
};

int donorSize = -1;
int recipientSize = -1;

donor *D = new donor[200];
recipient *R = new recipient[200];

int parent(int i)
{
	return (i - 1) / 2;
}

int leftChild(int i)
{
	return ((2 * i) + 1);
}

int rightChild(int i)
{
	return ((2 * i) + 2);
}

int donor::getDate()
{
    return date;
}

int donor::getMonth()
{
    return month;
}

int donor::getYear()
{
    return year;
}

void shiftUpDonor(int i)
{
   while(i>0 && (D[parent(i)].getYear() > D[i].getYear()) )
   {
      if(D[parent(i)].getYear() > D[i].getYear())
      {
         swap(D[parent(i)], D[i]);
         i = parent(i);
      }
      if (D[parent(i)].getYear() == D[i].getYear())
      {
         if(D[parent(i)].getMonth() == D[i].getMonth())
         {
            if(D[parent(i)].getDate() > D[i].getDate())
            {
                swap(D[parent(i)], D[i]);
                i = parent(i);
            }
         }
         else
         {
            if(D[parent(i)].getMonth() >D[i].getMonth())
            {
                swap(D[parent(i)], D[i]);
                i = parent(i);
            }
        }
     }
   }
}

void shiftDownDonor(int i)
{
	int maxIndex = i;
	int l = leftChild(i);
	if ((l <= donorSize))
	{
        if(D[l].getYear() < D[maxIndex].getYear())
        {
             maxIndex = l;
        }
        if(D[l].getYear() ==D[maxIndex].getYear())
        {
           if(D[l].getMonth() == D[maxIndex].getMonth())
           {
                if(D[l].getDate() < D[maxIndex].getDate())
                {
                   maxIndex = l;
                }
           }
           else
           {
                if(D[l].getMonth() < D[maxIndex].getMonth())
                {
                   maxIndex = l;
                }
          }
        }
	 }

	int r = rightChild(i);
	if (r <= donorSize  )
	{
        if(D[r].getYear() > D[maxIndex].getYear())
        {
            maxIndex = r;
        }
        if(D[r].getYear() == D[maxIndex].getYear())
        {
           if(D[l].getMonth() == D[maxIndex].getMonth())
           {
                if(D[l].getYear() < D[maxIndex].getYear())
                {
                   maxIndex = r;
                }
           }
           else
           {
                if(D[l].getMonth() < D[maxIndex].getMonth())
                {
                   maxIndex = r;
                }
           }
         }
	  }
      if (i != maxIndex)
      {
		  swap(D[i], D[maxIndex]);
		  shiftDownDonor(maxIndex);
      }
}

void insertDonor(donor d)
{
	donorSize = donorSize + 1;
	D[donorSize] = d;
	shiftUpDonor(donorSize);
}

void shiftUpRecipient(int i)
{
	while (i > 0 && R[parent(i)].getPriority() > R[i].getPriority())
    {
		swap(R[parent(i)], R[i]);
		i = parent(i);
	}
}

void shiftDownRecipient(int i)
{
	int minIndex = i;
	int l = leftChild(i);
	if (l <= recipientSize && R[l].getPriority() < R[minIndex].getPriority())
    {
		minIndex = l;
	}

	int r = rightChild(i);
	if (r <= recipientSize && R[r].getPriority() < R[minIndex].getPriority())
	{
		minIndex = r;
	}

	if (i != minIndex)
    {
		swap(R[i], R[minIndex]);
		shiftDownRecipient(minIndex);
	}
}

void insertRecipient(recipient r)
{
	recipientSize = recipientSize + 1;
	R[recipientSize] = r;
	shiftUpRecipient(recipientSize);
}

void insertIntoQueuesDonor()
{
    donor d;
    ifstream file;
    file.open("Donor.txt", ios::in | ios::binary);
    while(!file.eof() && file.read((char*)&d, sizeof(d)))
    {
        insertDonor(d);
    }
    file.close();
}

void insertIntoQueuesRecipient()
{
    recipient r;
    ifstream file;
    file.open("Recipient.txt", ios::in | ios::binary);
    while(!file.eof() && file.read((char*)&r, sizeof(r)))
    {
        insertRecipient(r);
    }
    file.close();
}

void person::setType(char t)
{
    type = t;
}

void person::setGroup(char g)
{
    group = g;
}

void person::setPriority(int p)
{
    priority = p;
}

char person::getType()
{
    return type;
}

char person::getGroup()
{
    return group;
}

int person::getPriority()
{
    return priority;
}

void person::read()
{
    cin.ignore();
    cout<<"Enter your name: ";
    fflush(stdin);
    cin.getline(name, 49);
    cout<<"Enter blood group: ";
    fflush(stdin);
    cin>>group;
    cout<<"Enter blood type: ";
    fflush(stdin);
    cin>>type;
}

void person::personDisplay()
{
    cout.setf(ios::left);
    cout<<setw(21)<<"\nName:"<<setw(20)<<name<<endl;
    cout<<setw(20)<<"Bloodgroup:"<<setw(3)<<group<<type<<endl;

}

int recipient::assignPriority()
{
    char g = this->getGroup();
    char t = this->getType();
    int q = this->getQty();

    if((g == 'ab' || g == 'AB') && t == '-')
    {
        if(q == 4)
            return 1;
        else if(q == 3)
            return 2;
        else if(q == 2)
            return 3;
        else if(q == 1)
            return 4;
    }

    else if((g == 'o' || g == 'O') && t == '-')
    {
        if(q == 4)
            return 5;
        else if(q == 3)
            return 6;
        else if(q == 2)
            return 7;
        else if(q == 1)
            return 8;
    }

    else if((g == 'a' || g == 'A') && t == '-')
    {
        if(q == 4)
            return 9;
        else if(q == 3)
            return 10;
        else if(q == 2)
            return 11;
        else if(q == 1)
            return 12;
    }

    else if((g == 'b' || g == 'B') && t == '-')
    {
        if(q == 4)
            return 13;
        else if(q == 3)
            return 14;
        else if(q == 2)
            return 15;
        else if(q == 1)
            return 16;
    }

    else if((g == 'ab' || g == 'AB') && t == '+')
    {
        if(q == 4)
            return 17;
        else if(q == 3)
            return 18;
        else if(q == 2)
            return 19;
        else if(q == 1)
            return 20;
    }

    else if((g == 'a' || g == 'AB') && t == '+')
    {
        if(q == 4)
            return 21;
        else if(q == 3)
            return 22;
        else if(q == 2)
            return 23;
        else if(q == 1)
            return 24;
    }

    else if((g == 'b' || g == 'B') && t == '+')
    {
        if(q == 4)
            return 25;
        else if(q == 3)
            return 26;
        else if(q == 2)
            return 27;
        else if(q == 1)
            return 28;
    }

    else if((g == 'o' || g == 'O') && t == '+')
    {
        if(q == 4)
            return 29;
        else if(q == 3)
            return 30;
        else if(q == 2)
            return 31;
        else if(q == 1)
            return 32;
    }
}

void recipient::setQty(int q)
{
    qty = q;
}

int recipient::getQty()
{
    return qty;
}

void insertRecipient();

void recipient::read()
{
    person::read();
    cin.ignore();
    cout.setf(ios::left);
    quantityvalidity:
    cout<<"Enter quantity of blood needed: ";
    cin>>qty;
    if(qty>4)
    {
        cout<<"\nQuantity above 4 units(1 unit = 330 ml) is not allowed."<<endl<<"Try again."<<endl;
        goto quantityvalidity;
    }
    this->setPriority(this->assignPriority());
    system("cls");
    ofstream f;
    f.open("Recipient.txt", ios::out | ios::app | ios::binary);
    f.write((char*)&(*this), sizeof(*this));
    f.close();
	recipientSize = -1;
	insertIntoQueuesRecipient();
}

void recipient::display()
{
    person::personDisplay();
    cout.setf(ios::left);
    cout<<setw(20)<<"Quantity Needed:"<<qty<<" units"<<endl;
    int p = this->getPriority();
    if(p<10)
    {
        cout<<setw(20)<<"Priority:"<<setw(20)<<"High priority"<<endl;
    }
    else if(p>10 && p<20)
    {
        cout<<setw(20)<<"Priority:"<<setw(20)<<"Moderate priority"<<endl;
    }
    else if(p>20)
    {
        cout<<setw(20)<<"Priority:"<<setw(20)<<"Low priority"<<endl;
    }

    cout << endl << endl;
}

void recipient::displayAll()
{
    recipient r;
    cout<<"\n  DISPLAYING RECIPIENT DETAILS :\n\n";
    ifstream file;
    file.open("Recipient.txt", ios::in | ios::binary);
    file.seekg(0);
    while(!file.eof() && file.read((char*)&r , sizeof(r)))
    {
        r.display();
    }
    file.close();
}

void donor::read()
{
    person::read();
    cin.ignore();
    agevalidity:
    cout<<"Enter your age: ";
    cin>>age;
    if(age<18)
    {
        cout<<"Not eligible to donate blood."<<endl<<"Try again."<<endl;
        goto agevalidity;
    }
    weightvalidity:
    cout<<"Enter your weight: ";
    cin>>weight;
    if(weight<45)
    {
        cout<<"Weight under 45 kgs is not eligible to donate blood."<<endl<<"Try again"<<endl;
        goto weightvalidity;
    }
    quantityvalidity:
    cout<<"Quantity of blood donated: ";
    cin>>qty;
    if(qty>4)
    {
        cout<<"Quantity above 4 units is not allowed."<<endl<<"Try again."<<endl;
        goto quantityvalidity;
    }
    cout<<"Enter date:\n";
    cout<<"Day:";
    cin>>date;
    cout<<"Month:";
    cin>>month;
    cout<<"Year:";
    cin>>year;
    cout<<"HIV status: ";
    cin>>HIV;
    cout<<"HTLV status: ";
    cin>>HTLV;
    cout<<"Hepatitis status: ";
    cin>>Hepatitis;
    cout<<"WNV status: ";
    cin>>WNV;
    cout<<"Syphillis status: ";
    cin>>Syphillis;
    if(HIV=='+'||HTLV=='+'||Hepatitis=='+'||WNV=='+'||Syphillis=='+')
        eligibility=0;
    else
        eligibility=1;
    ofstream file;
    file.open("Donor.txt", ios::out | ios::app | ios::binary);
    file.write((char*)&(*this), sizeof(*this));
    file.close();
    system("cls");

    cout<<"\n THANK YOU FOR DONATING BLOOD...\n\n";
    donorSize = -1;
    insertIntoQueuesDonor();
}

void donor::display()
{
    cout.setf(ios::left);
    person::personDisplay();
    cout<<setw(20)<<"Age:"<<setw(15)<<age<<endl;
    cout<<setw(20)<<"Weight:"<<setw(15)<<setprecision(2)<<weight<<endl;
    cout<<setw(20)<<"Quantity Donated:"<<qty<<" units"<<endl;
    cout<<setw(20)<<"Date of Donation:"<<date<<"/"<<month<<"/"<<year<<endl;
    cout<<setw(20)<<"HIV status:"<<HIV<<" ve"<<endl;
    cout<<setw(20)<<"HTLV status:"<<HTLV<<" ve"<<endl;
    cout<<setw(20)<<"Hepatitis status:"<<Hepatitis<<" ve"<<endl;
    cout<<setw(20)<<"WNV status:"<<WNV<<" ve"<<endl;
    cout<<setw(20)<<"Syphillis status:"<<Syphillis<<" ve"<<endl;
    if(eligibility == 1)
        cout<<setw(20)<<"Eligibility:"<<setw(15)<<"Eligible"<<endl;
    else if(eligibility == 0)
        cout<<setw(20)<<"Eligibility:"<<setw(15)<<"Not Eligible"<<endl;
}

void donor::displayAll()
{
    donor d;
    cout<<"\n  DISPLAYING DONOR DETAILS :\n\n";
    ifstream file;
    file.open("Donor.txt", ios::in | ios::binary);
    file.seekg(0);
    while(!file.eof() && file.read((char*)&d , sizeof(d)))
    {
        d.display();
    }
    file.close();
}

int donor::getQty()
{
    return qty;
}

void donor::availability()
{
    donor d;
    int aPlus=0, aMinus=0, bPlus=0, bMinus=0, oPlus=0, oMinus=0, abPlus=0, abMinus=0;
    ifstream file;
    file.open("Donor.txt", ios::in | ios::binary);
    while(!file.eof() && file.read((char*)&d, sizeof(d)))
    {
        if((d.getGroup()== 'a' || d.getGroup()=='A') && d.getType()=='+')
            aPlus+=d.getQty();

        else if ((d.getGroup()=='a' || d.getGroup()=='A') && d.getType()=='-')
            aMinus+=d.getQty();

        else if ((d.getGroup()=='b' || d.getGroup()=='B') && d.getType()=='+')
            bPlus+=d.getQty();

        else if ((d.getGroup()=='b' || d.getGroup()=='B') && d.getType()=='-')
            bMinus+=d.getQty();

        else if ((d.getGroup()=='o' || d.getGroup()=='O') && d.getType()=='+')
            oPlus+=d.getQty();

        else if ((d.getGroup()=='o' || d.getGroup()=='O') && d.getType()=='-')
            oMinus+=d.getQty();

        else if ((d.getGroup()=='ab' || d.getGroup()=='AB') && d.getType()=='+')
            abPlus+=d.getQty();

        else if ((d.getGroup()=='ab' || d.getGroup()=='AB') && d.getType()=='-')
            abMinus+=d.getQty();

    }
    file.close();

    cout<<"\nAVAILABLE BLOOD :\n\n";
    cout<<"A +ve     :"<<aPlus<<" unit"<<endl;
    cout<<"A -ve     :"<<aMinus<<" unit"<<endl;
    cout<<"B +ve     :"<<bPlus<<" unit"<<endl;
    cout<<"B -ve     :"<<bMinus<<" unit"<<endl;
    cout<<"O +ve     :"<<oPlus<<" unit"<<endl;
    cout<<"O -ve     :"<<oMinus<<" unit"<<endl;
    cout<<"AB +ve    :"<<abPlus<<" unit"<<endl;
    cout<<"AB -ve    :"<<abMinus<<" unit"<<endl;
}

donor getMax()
{
    return D[0];
}

donor extractMax()
{
    donor result = D[0];
    D[0] = D[donorSize];
    donorSize = donorSize - 1;
    shiftDownDonor(0);
    return result;
}

void removeDonor(int i)
{
    D[i] = getMax();
    shiftUpDonor(i);
    extractMax();
}

void searchBlood(char g, char t,int q)
{
    int flag = 0;
    cout<<"x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x\n";
    cout<<"X               DONOR                 X\n";
    cout<<"x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x\n\n";
    for(int i=0;i<=donorSize;i++)
    {
        if((D[i].getGroup() == g) && (D[i].getType() == t) && (D[i].getQty() >=  q))
        {
            ofstream f;
            f.open("temp.txt", ios::out | ios::app | ios::binary);
            for(int j=0; j<=donorSize; j++)
            {
                if(i == j)
                {
                    continue;
                }
                else
                {
                    f.write((char*)&(D[j]), sizeof(D[j]));
                }
            }
            f.close();
            remove("Donor.txt");
            rename("temp.txt","Donor.txt");

            flag = 1;
            D[i].display();
            removeDonor(i);
        }
    }
    if(flag == 0)
    {
        cout<<"REQUESTED BLOOD IS NOT AVAILABLE!\n\n";
    }
}

void distributeBlood()
{
    cout<<"x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x\n";
    cout<<"X             RECIPIENT               X\n";
    cout<<"x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x\n\n";
    R[0].display();

    ofstream f;
    f.open("temp.txt", ios::out | ios::app | ios::binary);
    for(int i=1; i<=recipientSize; i++)
    {
        f.write((char*)&(R[i]), sizeof(R[i]));
    }
    f.close();
    remove("Recipient.txt");
    rename("temp.txt","Recipient.txt");

    searchBlood(R[0].getGroup(),R[0].getType(),R[0].getQty());
	R[0] = R[recipientSize];
	recipientSize = recipientSize - 1;
	shiftDownRecipient(0);
}

int main()
{
    int option ,choice;

    insertIntoQueuesDonor();
    insertIntoQueuesRecipient();

    while(1)
    {
        cout<<"\nx-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x\n";
        cout<<"X             MAIN MENU               X\n";
        cout<<"x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x";
        cout<<"\n\n   1.ADMIN\n   2.DONOR\n   3.RECIPIENT\n   4.EXIT\n\n   Enter your option :";
        cin>>option;

        system("cls");
        if(option == 1)
        {
            int password = 56565 , pw;
            cout<<"\nEnter password :";
            cin>>pw;
            if(pw == password)
            {
                while(1)
                {
                    cout<<"\n1.DONOR LIST\n2.RECIPIENT LIST\n3.CHECK FOR AVAILABLE BLOOD\n4.DISTRIBUTE BLOOD\n5.EXIT\n\n   Enter your option :";
                    cin>>choice;

                    if(choice == 1)
                    {
                        system("cls");
                        donor d;
                        d.displayAll();
                    }

                    else if(choice == 2)
                    {
                        system("cls");
                        recipient r;
                        r.displayAll();
                    }

                    else if(choice == 3)
                    {
                        system("cls");
                        donor d;
                        d.availability();
                    }

                    else if(choice == 4)
                    {
                        system("cls");
                        if(recipientSize == -1)
                        {
                            cout<<"\nTHERE ARE NO MORE RECIPIENTS!\n\n";
                        }
                        else
                        {
                            distributeBlood();
                        }
                    }
                    else if(choice == 5)
                    {
                        system("cls");
                        break;
                    }
                    else
                    {
                        cout<<"\nEnter a valid option...";
                    }
                }
            }
            else
            {
                cout<<"INVALID PASSWORD...\n";
            }
        }

        else if(option == 2)
        {
           int x;
           system("cls");
           donor d;
           d.read();
           cout<<"\n1.DONOR SUMMARY\n2.BACK TO MAIN MENU\n\n   Enter your option :";
           cin>>x;
           if(x==1)
           {
               system("cls");
               cout<<"      DONOR SUMMARY \n";
               d.display();
           }
           else
           {
               system("cls");
               continue;
           }
        }

        else if(option == 3)
        {
           int y;
           system("cls");
           recipient r;
           r.read();
           cout<<"\n1.RECIPIENT SUMMARY\n2.BACK TO MAIN MENU\n\n   Enter your option :";
           cin>>y;
           if(y==1)
           {
               system("cls");
               cout<<"    RECIPIENT SUMMARY \n";
               r.display();
           }
           else
           {
               system("cls");
               continue;
           }
        }

        else if(option == 4)
        {
            system("cls");
            break;
        }

        else
        {
            cout<<"\nEnter a valid option...\n";
        }
    }
}

