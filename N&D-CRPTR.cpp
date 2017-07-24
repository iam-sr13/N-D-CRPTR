/*
* Author: Shriraj Sawant aka SR13
* Description: This programe basically allows to encrypt a message and at the same time decrypt it thus acting as both.
*			   The technique is actually pretty simple, it just obfuscates the actual letters into binary characters.
* Status: Needs a lot of improvement in terms of effciency and security too. This was just my first attempt! 
*/

#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<string>
#include<cmath>
#include<cstdlib>
#include<conio.h>
#define sstream stringstream 
#define enc 1
#define dec 0
#define CLR (system("cls"))
using namespace std;

class file
{
	string fname,data,secured;		
	int int_(char a);	
	int binary(int a);		
	int decimal(int a);
	void store(float task);
	protected:
		void enc_func();
		void dec_func();
	public:	
		void getfname();
		void display();
		void create();		
		void retrieve();		
		void encrypt();		
		void decrypt();		
};
void file::display()
{	
	cout<<"\n\nYour data is:\n\n"<<data;
}
void file::create()
{
	fstream fout;
	string input;	
	fout.open(fname.c_str(), ios::out);
	if(!fout) {cerr<<"\n\n ERROR!! FILE CAN'T BE CREATED!!!"; exit(0);}
	cout<<"\n\n~Your Filespace:     ("<<fname<<")\n\n";
	cin.ignore();
	getline(cin,input);
	fout<<input;
	fout.close();
	cout<<"\nFile is closed.";
}
void file::getfname()
{ 
	data="";
	cout<<"\nPlease enter the respective filename: ";
	cin>>fname;					
}
int file::decimal(int a)
{
	int i,n=0;
	for(i=0;a!=0;a/=10,i++) n+=(a%10)*pow(2,i);
	return n;
}	
int file::binary(int a)
{
	int i,n=0;
	for(i=0;a!=0;a/=2,i++) n+=(a%2)*pow(10,i);
	return n;
}	
int file::int_(char a)
{
	int n=int(a);
	if(n<0) return 256+n;
	else return n;
}
void file::enc_func()
{
	int i,c,a,x;	
	sstream temp;	
	string t;
	for(i=0;i<data.size();i++) {		
		for(a=0,c=0;c<=127;c++,a++) if(data[i]==(char)c) {data[i]=(char)(2*a);x=1;break;}
		cout<<setprecision(2)<<setw(6)<<(((float)i/data.size())*100)<<"% complete.\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
		if(i==(data.size()-1)) cout<<"100.00% complete.";
		if(x) continue;
		for(a=0,c=128;c<=255;c++,a++) if(data[i]==(char)c) {data[i]=(char)(2*a+1);x=1;break;}							
	}	
	for(i=0;i<data.size();i++) {			
		temp<<(1000000000+binary(int_(data[i])));
		t+=temp.str();
		temp.str("");		
	}
	data=t;	
}
void file::dec_func()
{
	int i,c,a,x;
	long long int x1;	
	sstream temp;
	string t;
	for(i=0;i<data.size();) {
		for(c=1,x1=0;c<=10;c++,i++) {			
			a=data[i]-48;			
			x1=x1*10+a;			
		}		
		t+=char(decimal(x1-1000000000));
	}
	data=t;
	for(i=0;i<data.size();i++) {		
		for(a=0,c=0;c<=127;c++,a++) if(data[i]==(char)(2*a)) {data[i]=(char)c;x=1;break;}		
		cout<<setprecision(2)<<setw(6)<<(((float)i/data.size())*100)<<"% complete.\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
		if(i==(data.size()-1)) cout<<"100.00% complete.";		
		if(x) continue;
		for(a=0,c=128;c<=255;c++,a++) if(data[i]==(char)(2*a+1)) {data[i]=(char)c;x=1;break;}		
	}	
}
void file::encrypt()
{	
	char ch;	
	secured=data;	
	cout<<"\n\nENCRYPTING....";
	enc_func();	
	cout<<"\n\nENCRYPTION SUCCESSFULL!";	
	cout<<"\n\nYour encrypted DATA:=         (press any key)\n\n";
	getch();
	cout<<data;
	cout<<"\n\nWant to store the encrypted copy? (y/n)"<<"\nYour Choice: ";
	cin>>ch;
	if(ch=='y') this->store(enc);	
}		
void file::decrypt()
{	
	char ch;	
	secured=data;
	cout<<"\n\nDECRYPTING....";
	dec_func();		
	cout<<"\n\nDECRYPTION SUCCESSFULL!";			
	cout<<"\n\nYour decrypted DATA:=         (press any key)\n\n";
	getch();
	cout<<data;	
	cout<<"\n\nWant to store the decrypted copy? (y/n)"<<"\nYour Choice: ";
	cin>>ch;
	if(ch=='y') this->store(dec);	
}
void file::retrieve()
{
	cout<<"\n\nLOOKING FOR YOUR FILE....";	
	string tmp;  	    
	fstream fin;
	fin.open(fname.c_str(), ios::in);
	if(!fin) {cerr<<"\n\nFILE NOT FOUND!!!"; exit(0);}
	else cout<<"\n\nRETRIEVING DATA....";
	for(;;) {
		getline(fin,tmp);
		data+=tmp;
		if(fin.eof()) break;
		data+="\n";		
	}
	fin.close();
	cout<<"\n\nRETRIEVAL SUCCESSFUL!";
	cout<<"\n\nYour DATA:=         (press any key)\n\n";	
	getch();
	cout<<data<<"\n";	
}
void file::store(float task)
{	
	cout<<"\n\nCREATING YOUR FILE.....";
	string cryptname,tname=fname;			
	fstream fout;	
	if(task==1) {tname.erase(tname.find(".")); cryptname=tname+".enc.txt";}
	else {tname.erase(tname.find(".")); cryptname=tname+".dec.txt";}
	fout.open(cryptname.c_str(), ios::out);
	if(!fout) { cerr<<"\n\nERROR!\nFILE CAN'T BE OPENED!"; exit(0);}
	else cout<<"\n\nSTORING DATA....";
	fout<<data;		
	fout.close();
	cout<<"\n\nSTORAGE SUCCESSFULL!";	
}
int main()
{
	file encode;
	int ch;	
	cout<<"                                  WELCOME!\n                                 __________\n\n                        This is n&d-CRPTR v4.2\n\n{NOTE:- PLEASE place the file to be encrypted or decrypted in this software's directory!}\n\n";               
	for(;;) {
		cout<<"  MAIN-MENU\n ___________\n\n\nChoose your option :\n\n1. Create New File\n2. Open existing file\n3. Display Contents\n4. Encrypt\n5. Decrypt\n6. About\n7. Exit\n";
		
		cout<<"\nYour Choice: ";
		cin>>ch;
		switch(ch) {
			case 1: encode.getfname();
					encode.create();
					getch();
				break;
			case 2: encode.getfname();
					encode.retrieve();
					getch();
				break;
			case 3: encode.display();
					getch();
				break;
			case 4:	cout<<"Press enter to start encryption!";
					getch();
					encode.encrypt();						
				break;
			case 5: cout<<"\nPress enter to start decryption!";
					getch();
					encode.decrypt();									
				break;
			case 6: cout<<"\n\nSR Rocks!"; getch();
				break;
			case 7: exit(0);
			default:cout<<"\n\nINVALID INPUT!!!"; getch();			
		}		
		CLR;
	}
	return 0;
}

//Rough work:=
//char alpha,numer,auth,schar;line 31,57.
/*for(alpha='A',auth=1,j=1;j<=26;j++,alpha++,auth++) if(data[i]==alpha) {data[i]=(2*auth);x=1;break;}
		if(x) continue;
		for(alpha='a',auth=1,j=1;j<=26;j++,alpha++,auth++) if(data[i]==alpha) {data[i]=(2*auth-1);x=1;break;}
		if(x) continue;
		for(numer='0',j=1;j<=10;j++,numer++,auth++) if(data[i]==numer) {data[i]=(2*auth);x=1;break;}
		if(x) continue;
		cout<<"\n...."<<setw(3)<<((i/data.size())*100)<<"% complete."<<"\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
		for(schar=32;schar<=47;schar++,auth++) if(data[i]==schar) {data[i]=(2*auth-1);x=1;break;}
		if(x) continue;
		for(schar=58;schar<=64;schar++,auth++) if(data[i]==schar) {data[i]=(2*auth);x=1;break;}
		if(x) continue;
		for(schar=91;schar<=96;schar++,auth++) if(data[i]==schar) {data[i]=(2*auth-1);x=1;break;}
		if(x) continue;
		for(schar=123;schar<=126;schar++,auth++) if(data[i]==schar) {data[i]=(2*auth);x=1;break;}*/	//line 32
/*for(alpha='A',auth=1,j=1;j<=26;j++,alpha++,auth++) if(data[i]==(2*auth)) {data[i]=alpha;x=1;break;}
		if(x) continue;
		for(alpha='a',auth=1,j=1;j<=26;j++,alpha++,auth++) if(data[i]==(2*auth-1)) {data[i]=alpha;x=1;break;}
		if(x) continue;
		for(numer='0',j=1;j<=10;j++,numer++,auth++) if(data[i]==(2*auth)) {data[i]=numer;x=1;break;}
		if(x) continue;
		cout<<"\n...."<<setw(3)<<((i/data.size())*100)<<"% complete."<<"\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
		for(schar=32;schar<=47;schar++,auth++) if(data[i]==(2*auth-1)) {data[i]=schar;x=1;break;}
		if(x) continue;
		for(schar=58;schar<=64;schar++,auth++) if(data[i]==(2*auth)) {data[i]=schar;x=1;break;}
		if(x) continue;
		for(schar=91;schar<=96;schar++,auth++) if(data[i]==(2*auth-1)) {data[i]=schar;x=1;break;}
		if(x) continue;
		for(schar=123;schar<=126;schar++,auth++) if(data[i]==(2*auth)) {data[i]=schar;x=1;break;}*/	//line 47
/*if(i) {	     	
		for(;;) {
			getline(fin,tmp);
			data+=tmp+"\n";
			if(fin.eof()) break;		
		}		
		cout<<"\n\nRETRIEVAL SUCCESSFUL!";
		cout<<"\n\nYour DATA to be encrypted:=         (press any key)\n\n";		
	}
	else {		 	
		getline(fin,tmp);
		data=tmp;		
		cout<<"\n\nRETRIEVAL SUCCESSFUL!";
		cout<<"\n\nYour encrypted DATA:=         (press any key)\n\n";		
	}
	fin.close();
	getch();
	cout<<data<<"\n";
	*/

