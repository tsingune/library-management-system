#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip.h>
#include<graphics.h>
class book
{
	char bno[6];
	char bname[50];
	char aname[20];
  public:
	void create_book()
	{
		cout<<"\nNEW BOOK ENTRY...\n";
		cout<<"\nEnter The book no.";
		cin>>bno;
		cout<<"\n\nEnter The Name of The Book ";
		gets(bname);
		cout<<"\n\nEnter The Author's Name ";
		gets(aname);
		cout<<"\n\n\nBook Created..";
	}

	void show_book()
	{
		cleardevice();
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"c:\\TURBOC3\\BGI");
line(15,10,622,10);
line(15,10,15,466);
line(15,466,622,466);
line(622,466,622,10);
line(25,20,611,20);
line(25,20,25,455);
line(25,455,611,455);
line(611,455,611,20);
setbkcolor(4);
       settextstyle(1,0,4);
	setcolor(6);

		gotoxy(35,8);
		cout<<"BOOK NO.="<<bno;
		gotoxy(35,8);
		cout<<"\nBook Name : ";
		puts(bname);
		gotoxy(35,8);
		cout<<"Author Name : ";
		puts(aname);
	}

	void modify_book()
	{
		cout<<"\nBook no. : "<<bno;
		cout<<"\nModify Book Name : ";
		gets(bname);
		cout<<"\nModify Author's Name of Book : ";
		gets(aname);
	}

	char* retbno()
	{
		return bno;
	}

	void report()
	{cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;}

};         //class ends here

class student
{
	char admno[6];
	char name[20];
	char stbno[6];
	int token;
public:
	void create_student()
	{
		clrscr();
		cout<<"\nNEW STUDENT ENTRY...\n";
		cout<<"\nEnter The admission no. ";
		cin>>admno;
		cout<<"\n\nEnter The Name of The Student ";
		gets(name);
		token=0;
		stbno[0]='/0';
		cout<<"\n\nStudent Record Created..";
	}

	void show_student()
	{
		cout<<"\nAdmission no. : "<<admno;
		cout<<"\nStudent Name : ";
		puts(name);
		cout<<"\nNo of Book issued : "<<token;
		if(token==1)
			cout<<"\nBook No "<<stbno;
	}

	void modify_student()
	{
		cout<<"\nAdmission no. : "<<admno;
		cout<<"\nModify Student Name : ";
		gets(name);
	}

	char* retadmno()
	{
		return admno;
	}

	char* retstbno()
	{
		return stbno;
	}

	int rettoken()
	{
		return token;
	}

	void addtoken()
	{token=1;}

	void resettoken()
	{token=0;}

	void getstbno(char t[])
	{
		strcpy(stbno,t);
	}

	void report()
	{cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl;}

};         //class ends here

//    	global declaration for stream object, object

fstream fp,fp1;
book bk;
student st;

//    	function to write in file

void write_book()
{
	char ch;
	fp.open("book.dat",ios::out|ios::app);
	do
	{
		clrscr();
		bk.create_book();
		fp.write((char*)&bk,sizeof(book));
		cout<<"\n\nDo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

void write_student()
{
	char ch;
	fp.open("student.dat",ios::out|ios::app);
	do
	{
		st.create_student();
		fp.write((char*)&st,sizeof(student));
		cout<<"\n\ndo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

//    	function to read specific record from file

void display_spb(char n[])
{
	cout<<"\nBOOK DETAILS\n";
	int flag=0;
	fp.open("book.dat",ios::in);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.show_book();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
		cout<<"\n\nBook does not exist";
	getch();
}

void display_sps(char n[])
{
	cout<<"\nSTUDENT DETAILS\n";
	int flag=0;
	fp.open("student.dat",ios::in);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if((strcmpi(st.retadmno(),n)==0))
		{
			st.show_student();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
		cout<<"\n\nStudent does not exist";
	getch();
}

//    	function to modify record of file

void modify_book()
{
	char n[6];
	int found=0;
	clrscr();
	cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
	cout<<"\n\n\tEnter The book no. of The book";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(book)) && found==0)
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.show_book();
			cout<<"\nEnter The New Details of book"<<endl;
			bk.modify_book();
			int pos=-1*sizeof(bk);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&bk,sizeof(book));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}

	fp.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}

void modify_student()
{
	char n[6];
	int found=0;
	clrscr();
	cout<<"\n\n\tMODIFY STUDENT RECORD... ";
	cout<<"\n\n\tEnter The admission no. of The student";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
			st.show_student();
			cout<<"\nEnter The New Details of student"<<endl;
			st.modify_student();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&st,sizeof(student));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}

	fp.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}

//    	function to delete record of file

void delete_student()
{
	char n[6];
	int flag=0;
	clrscr();
	cout<<"\n\n\n\tDELETE STUDENT...";
	cout<<"\n\nEnter The admission no. of the Student You Want To Delete : ";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if(strcmpi(st.retadmno(),n)!=0)
			fp2.write((char*)&st,sizeof(student));
		else
			flag=1;
	}

	fp2.close();
	fp.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	if(flag==1)
		cout<<"\n\n\tRecord Deleted ..";
	else
		cout<<"\n\nRecord not found";
	getch();
}


void delete_book()
{
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"c:\\TURBOC3\\BGI");
	setbkcolor(3);
	char n[6];
	clrscr();
	cout<<"\n\n\n\tDELETE BOOK ...";
	cout<<"\n\nEnter The Book no. of the Book You Want To Delete : ";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)!=0)
		{
			fp2.write((char*)&bk,sizeof(book));
		}
	}

	fp2.close();
	fp.close();
	remove("book.dat");
	rename("Temp.dat","book.dat");
	cout<<"\n\n\tRecord Deleted ..";
	getch();
}

//    	function to display all students list

void display_alls()
{
	clrscr();
	cleardevice();
	fp.open("student.dat",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		getch();
		return;
	}

	cout<<"\n\n\t\tSTUDENT LIST\n\n";
	cout<<"==================================================================\n";
	cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
	cout<<"==================================================================\n";

	while(fp.read((char*)&st,sizeof(student)))
	{
		st.report();
	}

	fp.close();
	getch();
}

//    	function to display Books list

void display_allb()
{
	clrscr();
	cleardevice();
	fp.open("book.dat",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		getch();
		return;
	}

	cout<<"\n\n\t\tBook LIST\n\n";
	cout<<"=========================================================================\n";
	cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
	cout<<"=========================================================================\n";

	while(fp.read((char*)&bk,sizeof(book)))
	{
		bk.report();
	}
	fp.close();
	getch();
}

//    	function to issue book

void book_issue()
{
	char sn[6],bn[6];
	int found=0,flag=0;
	clrscr();
	cleardevice();
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"c:\\TURBOC3\\BGI");
line(15,10,622,10);
line(15,10,15,466);
line(15,466,622,466);
line(622,466,622,10);
line(25,20,611,20);
line(25,20,25,455);
line(25,455,611,455);
line(611,455,611,20);
setbkcolor(8);
       settextstyle(1,0,4);
	setcolor(6);
	outtextxy(145,50,"BOOK ISSUE ...");
       //	cout<<"\n\nBOOK ISSUE ...";
       //	cout<<"\n\n\tEnter The student's admission no.";
       settextstyle(3,0,1);
       setcolor(15);
       outtextxy(140,101,"Enter The student's admission no.=");

       settextstyle(3,0,1) ;
       setcolor(0);
       gotoxy(58,8);
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
	fp1.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettoken()==0)
			{       settextstyle(3,0,1);
				setcolor(15);
				outtextxy(140,131,"Enter the book no.=");
			       // cout<<"\n\n\tEnter the book no. ";
				    gotoxy(42,10);
				    cin>>bn;
				while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
				{
					if(strcmpi(bk.retbno(),bn)==0)
					{
						bk.show_book();
						flag=1;
						st.addtoken();
						st.getstbno(bk.retbno());
					int pos=-1*sizeof(st);
						fp.seekp(pos,ios::cur);
						fp.write((char*)&st,sizeof(student));
						cout<<"\n\n\t Book issued successfully\n\nPlease Note: Write the current date in backside of your book and submit within 15 days fine Rs. 1 for each day after 15 days period";
					}
				}
				if(flag==0)
				{
			settextstyle(3,0,1) ;
			setcolor(15);
			outtextxy(125,175,"Book no does not exist...Enter a valid book no.!!!");
			}
			}
			else
				cout<<"You have not returned the last book ";

		}
	}
	if(found==0)
	{
		settextstyle(3,0,1) ;
		setcolor(15);
		outtextxy(145,145,"Student record not exist...");
	}
	getch();
	fp.close();
	fp1.close();
}

//    	function to deposit book

void book_deposit()
{
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    clrscr();
    cleardevice();
    line(15,10,622,10);
line(15,10,15,466);
line(15,466,622,466);
line(622,466,622,10);
line(25,20,611,20);
line(25,20,25,455);
line(25,455,611,455);
line(611,455,611,20);
  setbkcolor(8);
      settextstyle(1,0,4);
      setcolor(6);
      outtextxy(160,60,"BOOK DEPOSIT ...");
      settextstyle(3,0,1);
      setcolor(15);
      outtextxy(160,110,"Enter The student admission no.");

   // cout<<"\n\nBOOK DEPOSIT ...";
   // cout<<"\n\n\tEnter The student’s admission no.";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
	    if(strcmpi(st.retadmno(),sn)==0)
	    {
		    found=1;
		    if(st.rettoken()==1)
		    {
			while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
			{
			   if(strcmpi(bk.retbno(),st.retstbno())==0)
			{
				bk.show_book();
				flag=1;
				 settextstyle(3,0,1);
				 setcolor(15);
				 outtextxy(160,140,"Book deposited in no. of days");
			     //	cout<<"\n\nBook deposited in no. of days";
				cin>>day;
				if(day>15)
				{
				   fine=(day-15)*1;
				   settextstyle(3,0,1);
				 setcolor(15);
				 outtextxy(160,170,"Fine has to deposited Rs.");
				  cout<<"\n\nFine has to deposited Rs. "<<fine;
				}
					st.resettoken();
					int pos=-1*sizeof(st);
					fp.seekp(pos,ios::cur);
					fp.write((char*)&st,sizeof(student));
					settextstyle(3,0,1);
				 setcolor(15);
				 outtextxy(160,200,"Book deposited successfully");
				       // cout<<"\n\n\t Book deposited successfully";
			}
		    }
		  if(flag==0)
		    cout<<"Book no does not exist";
		      }
		 else
			cout<<"No book is issued..please check!!";
		}
	   }
      if(found==0)
	cout<<"Student record not exist...";
	getch();
  fp.close();
  fp1.close();
  }

//    	INTRODUCTION FUNCTION

void intro()
{
	cleardevice();
	int gdriver = DETECT,gmode;
	initgraph(&gdriver,&gmode, "c:\\TURBOC3\\BGI");
line(15,10,622,10);
line(15,10,15,466);
line(15,466,622,466);
line(622,466,622,10);
line(25,20,611,20);
line(25,20,25,455);
line(25,455,611,455);
line(611,455,611,20);
	  setbkcolor(1);
	  setcolor(6);
	 // setfillstyle(1,1);
	 // floodfill(96,51,3);
	  setfillstyle(8,5);
	  rectangle(95,50,535,130);
	settextstyle(1,0,4);
	setcolor(6);
	outtextxy(145,50,"LIBRARY");
	setcolor(6);
	outtextxy(280,50,"MANAGEMENT");
	setcolor(6);
	outtextxy(240,90,"SYSTEM");
	settextstyle(3,0,1);
	setcolor(15);
	outtextxy(44,320,"MADE BY : TEAM TUSHAR");
	setcolor(15);
	outtextxy(44,350,"COLLEGE NAME : SVIIT");
	setcolor(15);
	settextstyle(3,0,2);
	outtextxy(380,200,"DEVELOPED BY:");
	outtextxy(380,220,"Tushar Singune(Leader)");
	outtextxy(380,240,"Yash Yadav");
	outtextxy(380,260,"Tanuj Choudhary");
	outtextxy(380,280,"Priyanshi Tandon");
	outtextxy(380,300,"Utkarsh Tiwari");
	outtextxy(380,320,"Shantanu Tyagi");
	outtextxy(380,340,"Shashwat Sharma");
	getch();
}

//    	ADMINISTRATOR MENU FUNCTION

void admin_menu()
{
	clrscr();
	cleardevice();
	int ch2;
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"c:\\TURBOC3\\BGI");
line(15,10,622,10);
line(15,10,15,466);
line(15,466,622,466);
line(622,466,622,10);
line(25,20,611,20);
line(25,20,25,455);
line(25,455,611,455);
line(611,455,611,20);
setbkcolor(CYAN);
/* settextstyle(1,0,1);
      setcolor(6);
      outtextxy(210,50,"ADMINISTRATOR MENU");
      settextstyle(3,0,2);
      setcolor(15); */

       cout<<"\n\n\n\tADMINISTRATOR MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORD";
	cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6.CREATE BOOK ";
	cout<<"\n\n\t7.DISPLAY ALL BOOKS ";
	cout<<"\n\n\t8.DISPLAY SPECIFIC BOOK ";
	cout<<"\n\n\t9.MODIFY BOOK ";
	cout<<"\n\n\t10.DELETE BOOK ";
	cout<<"\n\n\t11.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-11) ";
	cin>>ch2;
	switch(ch2)
	{
		case 1: clrscr();
			    write_student();break;
		case 2: display_alls();break;
		case 3:
			char num[6];
			clrscr();
			cout<<"\n\n\tPlease Enter The Admission No. ";
			cin>>num;
			display_sps(num);
			break;
		case 4: modify_student();break;
		case 5: delete_student();break;
		case 6: clrscr();
			write_book();break;
		case 7: display_allb();break;
		case 8: {
			char num[6];
			clrscr();
			cout<<"\n\n\tPlease Enter The book No. ";
			cin>>num;
			display_spb(num);
			break;
			}
		case 9: modify_book();break;
		case 10:delete_book();break;
		case 11: return;
		default:cout<<"\a";
	}
	admin_menu();
}

//    	THE MAIN FUNCTION OF PROGRAM

void main()
{
clrscr();
int gdriver=DETECT,gmode;
initgraph(&gdriver,&gmode,"c:\\TURBOC3\\BGI");
line(15,10,622,10);
line(15,10,15,466);
line(15,466,622,466);
line(622,466,622,10);
line(25,20,611,20);
line(25,20,25,455);
line(25,455,611,455);
line(611,455,611,20);
setbkcolor(CYAN);
	char ch;
	intro();
	do
	{       clrscr();
		cleardevice();
line(15,10,622,10);
line(15,10,15,466);
line(15,466,622,466);
line(622,466,622,10);
line(25,20,611,20);
line(25,20,25,455);
line(25,455,611,455);
line(611,455,611,20);
  setbkcolor(CYAN);
      settextstyle(1,0,4);
      setcolor(6);
      outtextxy(210,50,"MAIN MENU");
      settextstyle(3,0,2);
      setcolor(15);
      outtextxy(205,110,"01. BOOK ISSUE");
     // cout<<"\n\n\t01. BOOK ISSUE";
      setcolor(15);
      outtextxy(205,150,"02. BOOK DEPOSIT");
      setcolor(15);
      outtextxy(205,190,"03. ADMINISTRATOR MENU");
      setcolor(15);
       outtextxy(205,230,"04. EXIT");
       setcolor(15);
       outtextxy(205,270,"Please Select Your Option (1-4) ");
		ch=getch();
		switch(ch)
		{
			case '1':   clrscr();
				     book_issue();
				     break;
			case '2':book_deposit();
				 break;
			case '3':admin_menu();
				     break;
			case '4':exit(0);
			default :cout<<"\a";
		}
	}while(ch!='4');
getch();
}