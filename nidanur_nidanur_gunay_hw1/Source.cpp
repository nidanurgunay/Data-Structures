#include <iostream>
#include <fstream>
#include "stack.h"
#include <string>
#include <sstream>

using namespace std;

//i created a struct as coordinate to keep two info at the same time
struct coordinate
{
	int x;
	int y;
	coordinate (int a, int b) :x(a),y(b)
	{};
	coordinate() {};
};


// function returns if the given coordinate had been already visited or not
bool ifexist(Stack<coordinate> & s, coordinate c)
{
	Stack<coordinate> temp;// create a temp struct to keep the data while popping 
	while(!s.isEmpty())
	{
		coordinate t;
		s.pop(t);
		if(t.x==c.x && t.y==c.y)//checked if the coordinates are equal or not
		{
			s.push(t);
			return true;
		}
		temp.push(t);
	}
	if(s.isEmpty())//if all the stacks in s is checked so there isnt exist the coordinate in
	{
		while(!temp.isEmpty())
		{
			coordinate n;
			temp.pop(n);
			s.push(n);
		}
	}
			return false;
}

int main()
{
	ifstream input;
	string filename;
	cout <<"Please enter the input file: ";
	cin>> filename;
	input.open(filename.c_str());

	while(input.fail())//if the given input is wrong
	{
		cout<<"Unable to open file please enter a different file name. \n\n"<<"Please enter a different filename: ";
		cin>> filename;
		input.open(filename.c_str());
	}

	Stack <coordinate> s;

	coordinate salesman (0,0);//initial coordinate of the salesman
	int a, b;
	string line;
	while(getline(input,line))
	{
		istringstream iss(line);
		iss>>a>>b;// read the given input as integer
		coordinate adress(a,b);//created the target coordinate to move
		
		if(!ifexist(s,adress))// if teh target coordinate had not been visited already
		{
			cout<<"Moving to (" <<a<<","<<b<<")"<<endl;
			while(salesman.x!=a && salesman.x<a )// if the targets x is greater than salemans x
			{
 				salesman.x++;
				if(salesman.y!=b || salesman.x!=a)
				cout<<"("<<salesman.x<<","<<salesman.y<<")"<<endl;
				coordinate step(salesman.x,salesman.y);
				s.push(step);
			}

				while(a<salesman.x && salesman.x!=a)// if the targets x is smaller that the salesmans x
			{
				salesman.x--;
				if(salesman.y!=b || salesman.x!=a)
				cout<<"("<<salesman.x<<","<<salesman.y<<")"<<endl;
				coordinate step(salesman.x,salesman.y);
				s.push(step);
			}
				
			while( salesman.y!= b && salesman.y<b)//if the salesmans y is smaller than the targets y
			{
				salesman.y++;
				if(salesman.y!=b || salesman.x!=a)
				cout<<"("<<salesman.x<<","<<salesman.y<<")"<<endl;
				coordinate step(salesman.x,salesman.y);
				s.push(step);
				
			}
			
				while(b<salesman.y && salesman.y!=b)//if the salesmans y is greater than the targets y
			{
				salesman.y--;
				if(salesman.y!=b || salesman.x!=a)
				cout<<"("<<salesman.x<<","<<salesman.y<<")"<<endl;
				
				coordinate step(salesman.x,salesman.y);
				s.push(step);
			}
			cout<<"Arrived to ("<<salesman.x<<","<<salesman.y<<")"<<endl;

		}
		else
			cout<<"Time travel back to ("<< adress.x<<","<<adress.y<<")"<<endl;
	//before going out of the loop make equal to tarets adress
		salesman.x=adress.x;
		salesman.y=adress.y;
	}
	cout<<"Back to (0.0)"<<endl;
	coordinate o;
	s.pop(o);// before going  back to home popping the coordinate that salesman location
	while(!s.isEmpty())//while stack become empty, emty the stack and  print the coordinate
	{		
		coordinate t ;
		s.pop(t);
		cout<<"("<<t.x<<","<<t.y<<")"<<endl;
	}
	cout<<"Home sweet home!"<<endl;

	system("pause");
	return 0;
}