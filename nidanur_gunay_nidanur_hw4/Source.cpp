#include<iostream>
#include<string>
#include<fstream>
#include <sstream>
#include "Heap.h"


using namespace std;
// this  function  for ordering that 3 number in ascending order
void order(int & a, int & b, int &  c)
{
	int max,min,med;

	if(a<=c && a<=b)
	{
		min=a;
		if(b>=c)
		{
			max=b;med=c;
		}
		else
		{
			max=c;med=b;
		}

	}
	else if(b<=c && b<= a)
	{	
		min=b;
		if(a>=c)
		{
			max=a;med=c;
		}
		else
		{
			max=c;med=a;
		}
	}
	else 
	{	
		min=c;
		if(a>=b)
		{
			max=a;med=b;
		}
		else
		{
			max=b;med=a;
		}
	}
	a=max;
	b=med;
	c=min;

}
//it is the function that calculates the median
double med (PriorityQueue<int> min, maxheap<int> max)//since it can be rayional, return is double
{
	int maxsize=max.getTotalElements();
	int minsize=min.getTotalElements();
	double med;
	int maximum=max.pop();
	int minimum=min.pop();
	if(minsize>maxsize)// if min contains more element then the root of the min is median
		med=minimum*1.0;
	else if(maxsize>minsize)// if max contains more elements then the root of the max is median
		med=maximum*1.0;
	else// else their sizes are equal to eacj other
		med=(maximum+minimum)*1.0/2;//median is half of their roots
	return med;
}
int main()
{
	string filename;
	cout<<"Please enter the next file name that contains integer stream: ";
		PriorityQueue<int> min;//created min and max heaps
		maxheap<int> max; 
	while(getline(cin,filename))
	{
		ifstream infile;
		infile.open(filename.c_str());
		string a;
	
		while(getline(infile,a))
		{
			int c=0;
			stringstream ss(a);
			ss>>c;//c is integer

			int maxsize=max.getTotalElements();
			int minsize=min.getTotalElements();
			if(maxsize==0)//insertion of the first 2 elemets toheaps
				max.push(c);
			else if(minsize==0 )
				min.push(c);
			else
			{
				int a=max.pop();//popped the max of the inputs that less than median
				int b=min.pop();//popped the min of the inputs that greater than median
				order(a,b,c);// i ordered them by ascendig order
				max.push(c);// pushed the min 
				min.push(a);//pushed the max
				if(maxsize==minsize)//pushed the median one min and one max by this way the difference of heap size kept in 1 and 0
					max.push(b);
				else
					min.push(b);
			
			}
			
		}
		
		double median = med(min, max);
	cout<<"current median : "<< median<<endl;
	cout<<"Please enter the next file name that contains integer stream: ";
	}
	
	
	return 0;
}


