// ProcessSchedular.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ProcessScheduler.h"


int _tmain(int argc, _TCHAR* argv[])
{
	//Queue <int> q1;
	//q1.enqueue(1);
	//q1.enqueue(2);
	//q1.enqueue(3);
	//q1.enqueue(4);
	//q1.enqueue(5);
	//q1.displayQueue();
	//cout<<endl;
	//int a;
	//q1.dequeue(a);
	//cout<<a<<endl;
	//q1.displayQueue();
	//cout<<endl;
	//q1.enqueue(2);
	//q1.displayQueue();
	//cout<<endl;
	//int b;
	//q1.dequeue(b);
	//q1.displayQueue();

	//list <int> l1;
	//l1.insertAt(1,1);
	//l1.insertAt(2,2);
	//l1.insertAt(3,3);
	//l1.insertAt(4,4);
	//l1.insertAt(5,5);
	//l1.displayList();
	//l1.removeAt(3);
	//l1.displayList();
	//cout<<l1.removeAt(0)<<endl;
	//cout<<l1.removeAt(6)<<endl;
	//l1.insertAt(6,6);
	//l1.removeAt(4);
	//cout<<endl;
	//l1.displayList();
	//l1.removeAt(1);
	//l1.displayList();
	//l1.removeAt(2);
	//l1.displayList();
	//l1.insertAt(3,1);
	//l1.displayList();
 //   l1.insertAt(4,2);
	//l1.displayList();
	//l1.insertAt(5,4);
	//l1.displayList();
	//l1.insertAt(5,6);
	//l1.displayList();

	//list <int> l1;
	//for (int i=1;i<10;i++)
	//	l1.insertAt(i,i);

	//l1.displayList();

	//for (int i=1;i<10;i++)
	//l1.removeAt(1);

	//l1.displayList();


	//process p1("p0",1,2);

	runProcessScheduling("..\\ProcessScheduler\\job.txt",5);

	return 0;
}
