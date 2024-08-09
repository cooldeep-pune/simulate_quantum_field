#include <iostream>
#include "SingleFieldTypeUniverse.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

void clrscr()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}


int main(int argc, char** argv) {
	UniverseInterface * uptr = NULL;
	int choice = 0;
	do {
		clrscr();
		cout<<endl<<"Welcome to Universe Simulation Program"<<endl;
		cout<<endl<<"Select Type of Universe to Simulate"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"1) SingleFieldTypeUniverse"<<endl;
		cout<<"2) Display 2D intersection"<<endl;
		cout<<"3) Exit Program"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"Enter Your Choice:";
		cin>>choice;
		switch(choice){
			case 1: uptr = SingleFieldTypeUniverse::instance();
			uptr->InitializeUniverse();
			uptr->SimulateUniverse();
			int ch = 0;
			cin>>choice;
			break;
		}
	}while(choice!=3);
	
	if(uptr!=NULL)
		delete uptr;

	return 0;
}