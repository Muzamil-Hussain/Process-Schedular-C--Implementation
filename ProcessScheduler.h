#pragma once 
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int GlobalTime = -1;

template<class T>
class QNode {
public:
	T value;
	QNode<T> *Next;
	QNode() {
		value = 0;
		Next = NULL;
	}
};
template<class T>
class Queue {
private:
	QNode<T> *Front;
	QNode<T> *Rear;
	int noOfItems;
public:
	Queue() {
		Front = NULL;
		Rear = NULL;
		noOfItems = 0;
	}
	bool isEmpty() {
		if (noOfItems == 0)
			return true;
		return false;
	}
	void enqueue(T nValue) {
		QNode<T> *newNode = new QNode<T>;
		newNode->value = nValue;
		newNode->Next = NULL;
		if (isEmpty()) {
			Rear = newNode;
			Front = newNode;
		} else {
			newNode->Next = Rear->Next;
			Rear->Next = newNode;
			Rear = newNode;
		}
		noOfItems += 1;
	}
	bool dequeue(T &nValue) {
		if (isEmpty())
			return false;
		else {
			QNode<T> *temp;
			nValue = Front->value;
			temp = Front->Next;
			delete[] Front;
			Front = temp;
			noOfItems--;
			return true;
		}
	}
	QNode<T> * getRear() const {
		return Rear;
	}
	QNode<T> *getFront() const {
		return Front;
	}
	void displayQueue() {
		if (!isEmpty()) {
			QNode<T> *currentQueue = Front;
			while (currentQueue != NULL) {
				cout << currentQueue->value << " ";
				currentQueue = currentQueue->Next;
			}
		} else
			cout << "Queue is Empty" << endl;
	}
	void makeNull() {
		T value;
		while (!isEmpty())
			dequeue(value);
	}
	~Queue() {
		makeNull();
	}
};
template <typename T,typename U>
class process {
public:
	T name;
	U index;
	T state;
	U arrivalTime;
	T *listOfInstructions;
	T currentQueue;
	U size;
	U time;
	U currentInstruction;
	U readyToWaitingQueueArrivalTime;
	T previousQueue;
	process() {
		name = "";
		index = -1;
		state = "";
		arrivalTime = -1;
		listOfInstructions = NULL;
		currentQueue = "";
		size = -1;
		time = -1;
		currentInstruction = 0;
	}
	process(T pFName, U pIndex, U pArrivalTime) {
		name = pFName;
		index = pIndex;
		state = "New";
		arrivalTime = pArrivalTime;
		currentQueue = "";
		currentInstruction = 0;
		previousQueue = "";

		size = 0;
		ifstream readFile("..\\ProcessScheduler\\" + pFName + ".txt");
		string line;
		if (readFile.is_open()) {
			while (!readFile.eof()) {
				line = "";
				getline(readFile, line);
				if (line != "Start" && line != "End")
					size++;
			}
			readFile.close();

			listOfInstructions = new string[size];
			readFile.open("..\\ProcessScheduler\\" + pFName + ".txt");

			int i = 0;
			while (i < size) {
				line = "";
				getline(readFile, line);
				if (line != "Start" && line != "End") {
					listOfInstructions[i] = line;
					i++;
				}
			}
		} else
			cout << "File Couldn't Be Opened!" << endl;
	}
	void display() {
		cout << "Name: " << name << endl;
		cout << "Index: " << index << endl;
		cout << "State: " << state << endl;
		cout << "Arrival Time: " << arrivalTime << endl;
		cout << "Displaying process instructions: " << endl;
		for (int i = 0; i < size; i++) {
			cout << listOfInstructions[i] << endl;
		}
		cout << "Current Instruction: " << currentInstruction << endl;
		cout << "Current Queue: " << currentQueue << endl << endl;
	}
};
template<typename T>
class Node {
public:
	T data;
	Node<T> *Next;
	Node<T> *Prev;
	Node() {
		Next = NULL;
		Prev = NULL;
	}
};
template<class T>
class list {
private:
	Node<T> *Head;
	Node<T> *Cursor;
public:
	list() {
		Head = NULL;
	}
	bool isEmpty() {
		if (Head == NULL)
			return true;
		else
			return false;
	}
	void insertAt(const T &newDataItem, int index) {
		Node<T> *newNode = new Node<T>;
		newNode->data = newDataItem;
		if (index > 1 && isEmpty())
			cout << "index out of range";
		else {
			Node<T> *currNode = Head;
			int currIndex = 2;
			while (currNode && index > currIndex) {
				currNode = currNode->Next;
				currIndex++;
			}
			if (index > currIndex - 1 && !currNode)
				cout << "index out of range";
			else {
				if (index == 1 && isEmpty()) {
					newNode->Next = NULL;
					newNode->Prev = NULL;
					Head = newNode;
					Cursor = newNode;
				} else if (index == 1) {
					newNode->Next = currNode;
					Head = newNode;
					Cursor = newNode;
				} else if (currNode->Next == NULL) {
					newNode->Next = currNode->Next;
					newNode->Prev = currNode;
					currNode->Next = newNode;
				} else {
					newNode->Next = currNode->Next;
					currNode->Next = newNode;
					newNode->Next->Prev = newNode;
					newNode->Prev = currNode;
				}
			}
		}
	}
	bool removeAt(int index) {
		if (index <= 0) {
			cout << "Can't remove at this index " << endl;
			return false;
		}
		if (isEmpty()) {
			cout << "List is already empty" << endl;
			return false;
		} else {
			Node<T> *currNode = Head;
			int currIndex = 1;
			while (currNode && index > currIndex) {
				currIndex++;
				currNode = currNode->Next;
			}
			if (index > currIndex && !currNode) {
				cout << "Index out of range" << endl;
				return false;
			} else {
				if (index == 1
						&& (currNode->Next == NULL && currNode->Prev == NULL)) {
					delete[] Head;
					Head = NULL;
					return true;
				} else if (currNode->Next == NULL && currNode->Prev != NULL) {
					currNode->Prev->Next = NULL;
					delete[] currNode;
					return true;
				} else if (currNode->Prev == NULL && currNode->Next != NULL) {
					currNode->Next->Prev = NULL;
					Head = currNode->Next;
					delete[] currNode;
					return true;
				} else {
					currNode->Prev->Next = currNode->Next;
					currNode->Next->Prev = currNode->Prev;
					return true;
				}
			}
		}
	}
	bool moveCursorToNext() {
		if (Cursor->Next != NULL) {
			Cursor = Cursor->Next;
			return true;
		}
		return false;
	}
	Node<T> * getCursor() const {
		return Cursor;
	}
	Node<T> * getHead() const {
		return Head;
	}
	void displayList() {
		if (!isEmpty()) {
			Node<T> *currNode = Head;
			while (currNode) {
				currNode->data.display();
				currNode = currNode->Next;
			}
			cout << endl;
		} else
			cout << "List is already Empty";
	}
};
template<typename T>
bool isAllTerminated(list<T> &l1) {
	Node<T> *currNode = l1.getHead();
	while (currNode != NULL) {
		if (currNode->data.state != "Terminated")
			return false;
		currNode = currNode->Next;
	}
	return true;
}
template<typename T,typename U>
void incrementGlobalTime(list<T> &l1, Queue<U> &q, Queue<U> &q1,
		Queue<U> &q2, Queue<U> &HardDiskQueue, Queue<U> &NetworkQueue,
		Queue<U> &DeviceQueue, ofstream &cpufile, int &globalTick,
		ofstream &processfile, ofstream &queuefile) {
	if (GlobalTime >= 0) {
		Node<T> *currNode = l1.getHead();
		while (currNode->data.state != "Running" )
			currNode = currNode->Next;
		if (cpufile.is_open()) {
			cpufile << "Time " << GlobalTime;
			if (GlobalTime < globalTick)
				cpufile << endl << currNode->data.name << " "
						<< currNode->data.listOfInstructions[currNode->data.currentInstruction]
						<< endl;
			else
				cpufile << endl << currNode->data.name << " "
						<< currNode->data.listOfInstructions[currNode->data.currentInstruction];
		} else
			cout << "Couldn't Open File!";
	}
	if (GlobalTime >= 0) {
		Node<T> *currNode = l1.getHead();
		processfile << "Time " << GlobalTime << endl;
		if (GlobalTime < globalTick) {
			while (currNode != NULL) {
				if (processfile.is_open()) {
					if (currNode->data.state != "New" && currNode->data.state!="Terminated")
						processfile << currNode->data.name << " "
								<< currNode->data.state << " "
								<< currNode->data.currentQueue << endl;
				}
				currNode = currNode->Next;
			}
		} else {
			while (currNode->Next != NULL) {
				if (processfile.is_open()) {
					if (currNode->data.state != "New" && currNode->data.state!="Terminated")
						processfile << currNode->data.name << " "
								<< currNode->data.state << " "
								<< currNode->data.currentQueue << endl;
				}
				currNode = currNode->Next;
			}
			processfile << currNode->data.name << " " << currNode->data.state
					<< " " << currNode->data.currentQueue;
		}
	}
	if (GlobalTime >= 0) {
		if (GlobalTime == 0)
			queuefile << "Time " << GlobalTime << endl;
		else
			queuefile << "\nTime " << GlobalTime << endl;
		if (GlobalTime <= globalTick) {
			if (processfile.is_open()) {
				QNode<int> *currQueue = q.getFront();
				queuefile << "FCFS-1:";
				while (currQueue != NULL) {
					Node<T> *currNode = l1.getHead();
					while (currNode != NULL) {
						if (currNode->data.index == currQueue->value
								&& currNode->data.currentQueue != "CPU")
							queuefile << " " << currNode->data.name;
						currNode = currNode->Next;
					}
					currQueue = currQueue->Next;
				}
			}
		}
	}
	if (GlobalTime >= 0) {
		if (GlobalTime <= globalTick) {
			if (processfile.is_open()) {
				QNode<int> *currQueue = q1.getFront();
				queuefile << "\nFCFS-2:";
				while (currQueue != NULL) {
					Node<T> *currNode = l1.getHead();
					while (currNode != NULL) {
						if (currNode->data.index == currQueue->value
								&& currNode->data.currentQueue != "CPU")
							queuefile << " " << currNode->data.name;
						currNode = currNode->Next;
					}
					currQueue = currQueue->Next;
				}
			}
		}
	}
	if (GlobalTime >= 0) {
		if (GlobalTime <= globalTick) {
			if (processfile.is_open()) {
				QNode<int> *currQueue = q2.getFront();
				queuefile << "\nSJF:";
				while (currQueue != NULL) {
					Node<T> *currNode = l1.getHead();
					while (currNode != NULL) {
						if (currNode->data.index == currQueue->value
								&& currNode->data.currentQueue != "CPU")
							queuefile << " " << currNode->data.name;
						currNode = currNode->Next;
					}
					currQueue = currQueue->Next;
				}
			}
		}
	}
	if (GlobalTime >= 0) {
		if (GlobalTime <= globalTick) {
			if (processfile.is_open()) {
				QNode<int> *currQueue = HardDiskQueue.getFront();
				queuefile << "\nHardDisk:";
				while (currQueue != NULL) {
					Node<T> *currNode = l1.getHead();
					while (currNode != NULL) {
						if (currNode->data.index == currQueue->value
								&& currNode->data.currentQueue != "CPU")
							queuefile << " " << currNode->data.name;
						currNode = currNode->Next;
					}
					currQueue = currQueue->Next;
				}
			}
		}
	}
	if (GlobalTime >= 0) {
		if (GlobalTime <= globalTick) {
			if (processfile.is_open()) {
				QNode<int> *currQueue = NetworkQueue.getFront();
				queuefile << "\nNetwork:";
				while (currQueue != NULL) {
					Node<T> *currNode = l1.getHead();
					while (currNode != NULL) {
						if (currNode->data.index == currQueue->value
								&& currNode->data.currentQueue != "CPU")
							queuefile << " " << currNode->data.name;
						currNode = currNode->Next;
					}
					currQueue = currQueue->Next;
				}
			}
		}
	}
	if (GlobalTime >= 0) {
		if (GlobalTime <= globalTick) {
			if (processfile.is_open()) {
				QNode<int> *currQueue = DeviceQueue.getFront();
				queuefile << "\nDevice:";
				while (currQueue != NULL) {
					Node<T> *currNode = l1.getHead();
					while (currNode != NULL) {
						if (currNode->data.index == currQueue->value
								&& currNode->data.currentQueue != "CPU")
							queuefile << " " << currNode->data.name;
						currNode = currNode->Next;
					}
					currQueue = currQueue->Next;
				}
			}
		}
	}
	GlobalTime++;
	if (l1.getCursor()->data.arrivalTime == GlobalTime) {
		l1.getCursor()->data.state = "Ready";
		l1.getCursor()->data.currentQueue = "FCFS-1";
		l1.getCursor()->data.time = 3;
		q.enqueue(l1.getCursor()->data.index);
		l1.moveCursorToNext();
	}
	if (!HardDiskQueue.isEmpty()) {
		Node<T> *currNode = l1.getHead();
		while (currNode->data.index != HardDiskQueue.getFront()->value)
			currNode = currNode->Next;
		currNode->data.time -= 1;
		if (currNode->data.time == 0) {
			if (currNode->data.currentInstruction + 1 < currNode->data.size) {
				int saveIndex = 0;
				HardDiskQueue.dequeue(saveIndex);
				q.enqueue(saveIndex);
				currNode->data.state = "Ready";
				currNode->data.currentQueue = "FCFS-1";
				currNode->data.time = 3;
				currNode->data.currentInstruction += 1;
			} else {
				int saveIndex = 0;
				HardDiskQueue.dequeue(saveIndex);
				currNode->data.state = "Terminated";
			}
		}
	}
	if (!NetworkQueue.isEmpty()) {
		Node<T> *currNode = l1.getHead();
		while (currNode->data.index != NetworkQueue.getFront()->value)
			currNode = currNode->Next;
		currNode->data.time -= 1;
		if (currNode->data.time == 0) {
			if (currNode->data.currentInstruction + 1 < currNode->data.size) {
				int saveIndex = 0;
				NetworkQueue.dequeue(saveIndex);
				q.enqueue(saveIndex);
				currNode->data.state = "Ready";
				currNode->data.currentQueue = "FCFS-1";
				currNode->data.time = 3;
				currNode->data.currentInstruction += 1;
			} else {
				int saveIndex = 0;
				NetworkQueue.dequeue(saveIndex);
				currNode->data.state = "Terminated";
			}
		}
	}
	if (!DeviceQueue.isEmpty()) {
		Node<T> *currNode = l1.getHead();
		while (currNode->data.index != DeviceQueue.getFront()->value)
			currNode = currNode->Next;
		currNode->data.time -= 1;
		if (currNode->data.time == 0) {
			if (currNode->data.currentInstruction + 1 < currNode->data.size) {
				int saveIndex = 0;
				DeviceQueue.dequeue(saveIndex);
				q.enqueue(saveIndex);
				currNode->data.state = "Ready";
				currNode->data.currentQueue = "FCFS-1";
				currNode->data.time = 3;
				currNode->data.currentInstruction += 1;
			} else {
				int saveIndex = 0;
				DeviceQueue.dequeue(saveIndex);
				currNode->data.state = "Terminated";
			}
		}
	}
}
template<typename T>
class CPU {
private:
	int runningTime;
public:
	CPU() {
		runningTime = 0;
	}
	int getTime(string instruction) {
		string storeNum = "";
		int i = 0;
		int count = 0;
		while (count != 2) {
			i++;
			if (instruction[i] == ' ')
				count++;
		}
		i++;
		while (instruction[i] != ' ') {
			storeNum += instruction[i];
			i++;
		}
		return stoi(storeNum);
	}
	string getType(string instruction) {
		string storeType = "";
		int i = 0;
		int count = 0;
		while (count != 1) {
			i++;
			if (instruction[i] == ' ')
				count++;
		}
		i++;
		while (instruction[i] != ' ') {
			storeType += instruction[i];
			i++;
		}
		return storeType;
	}
	int checkDeviceType(string type) {
		if (type.compare("DISK") == 0)
			return 0;
		else if (type.compare("NETWORK") == 0)
			return 1;
		else
			return 2;
	}
	void runProcess(list<T> &l1, Queue<int> &rFCFS1, Queue<int> &rFCFS2,
			Queue<int> &rSFJ, Queue<int> &HardDiskQueue,
			Queue<int> &NetworkQueue, Queue<int> &DeviceQueue, int globalTick,
			ofstream &out, ofstream &out1, ofstream &out2) {
		if (!rFCFS1.isEmpty()) {
			bool flag = false;
			Node<T> *currNode = l1.getHead();
			while (currNode->data.index != rFCFS1.getFront()->value)
				currNode = currNode->Next;
			runningTime = currNode->data.time;
			currNode->data.state = "Running";
			currNode->data.currentQueue = "CPU";
			while (runningTime != 0 && !flag
					&& currNode->data.currentInstruction
							<= (currNode->data.size) - 1
					&& globalTick >= GlobalTime) {
				if (currNode->data.listOfInstructions[currNode->data.currentInstruction]
						!= "COMPUTE") {
					flag = true;
					break;
				}
				incrementGlobalTime(l1, rFCFS1, rFCFS2, rSFJ, HardDiskQueue,
						NetworkQueue, DeviceQueue, out, globalTick, out1, out2);
				currNode->data.currentInstruction += 1;
				runningTime--;
			}
			if (currNode->data.currentInstruction > (currNode->data.size) - 1)
				currNode->data.state = "Terminated";
			if (flag == false && runningTime == 0
					&& currNode->data.state == "Terminated") {
				int value;
				rFCFS1.dequeue(value);
			}
			if (flag == false && runningTime == 0
					&& currNode->data.state != "Terminated") {
				int saveIndex = 0;
				rFCFS1.dequeue(saveIndex);
				rFCFS2.enqueue(saveIndex);
				currNode->data.time = 6;
				currNode->data.currentQueue = "FCFS-2";
				currNode->data.state = "Ready";
			}
			if (flag == true) {
				if (checkDeviceType(
						getType(
								currNode->data.listOfInstructions[currNode->data.currentInstruction]))
						== 0) {
					incrementGlobalTime(l1, rFCFS1, rFCFS2, rSFJ, HardDiskQueue,
							NetworkQueue, DeviceQueue, out, globalTick, out1,
							out2);

					currNode->data.state = "Waiting";
					currNode->data.currentQueue = "HardDisk";
					currNode->data.time =
							getTime(
									currNode->data.listOfInstructions[currNode->data.currentInstruction]);

					int saveIndex = 0;
					rFCFS1.dequeue(saveIndex);
					HardDiskQueue.enqueue(saveIndex);
				} else if (checkDeviceType(
						getType(
								currNode->data.listOfInstructions[currNode->data.currentInstruction]))
						== 1) {
					incrementGlobalTime(l1, rFCFS1, rFCFS2, rSFJ, HardDiskQueue,
							NetworkQueue, DeviceQueue, out, globalTick, out1,
							out2);

					currNode->data.state = "Waiting";
					currNode->data.currentQueue = "Network";
					currNode->data.time =
							getTime(
									currNode->data.listOfInstructions[currNode->data.currentInstruction]);

					int saveIndex = 0;
					rFCFS1.dequeue(saveIndex);
					NetworkQueue.enqueue(saveIndex);
				} else if (checkDeviceType(
						getType(
								currNode->data.listOfInstructions[currNode->data.currentInstruction]))
						== 2) {
					incrementGlobalTime(l1, rFCFS1, rFCFS2, rSFJ, HardDiskQueue,
							NetworkQueue, DeviceQueue, out, globalTick, out1,
							out2);

					currNode->data.state = "Waiting";
					currNode->data.currentQueue = "Device";
					currNode->data.time =
							getTime(
									currNode->data.listOfInstructions[currNode->data.currentInstruction]);

					int saveIndex = 0;
					rFCFS1.dequeue(saveIndex);
					DeviceQueue.enqueue(saveIndex);
				} else
					cout << "No Such Device";
			}
		} else if (!rFCFS2.isEmpty()) {
			bool flag = false;
			Node<T> *currNode = l1.getHead();
			while (currNode->data.index != rFCFS2.getFront()->value)
				currNode = currNode->Next;
			runningTime = currNode->data.time;
			currNode->data.state = "Running";
			currNode->data.currentQueue = "CPU";

			while (runningTime != 0 && !flag
					&& currNode->data.currentInstruction
							<= (currNode->data.size) - 1
					&& globalTick >= GlobalTime) {
				if (currNode->data.listOfInstructions[currNode->data.currentInstruction]
						!= "COMPUTE") {
					flag = true;
					break;
				}
				incrementGlobalTime(l1, rFCFS1, rFCFS2, rSFJ, HardDiskQueue,
						NetworkQueue, DeviceQueue, out, globalTick, out1, out2);
				currNode->data.currentInstruction += 1;
				runningTime--;
			}
			if (currNode->data.currentInstruction > (currNode->data.size) - 1)
				currNode->data.state = "Terminated";
			if (flag == false && runningTime == 0
					&& currNode->data.state == "Terminated") {
				int value;
				rFCFS1.dequeue(value);
			}
			if (flag == false && runningTime == 0
					&& currNode->data.state != "Terminated") {
				int saveIndex = 0;
				rFCFS2.dequeue(saveIndex);
				rSFJ.enqueue(saveIndex);
				currNode->data.time = 6;
				currNode->data.currentQueue = "SJF";
				currNode->data.state = "Ready";
			}
			if (flag == true) {
				if (checkDeviceType(
						getType(
								currNode->data.listOfInstructions[currNode->data.currentInstruction]))
						== 0) {

					incrementGlobalTime(l1, rFCFS1, rFCFS2, rSFJ, HardDiskQueue,
							NetworkQueue, DeviceQueue, out, globalTick, out1,
							out2);

					currNode->data.state = "Waiting";
					currNode->data.currentQueue = "HardDisk";
					currNode->data.time =
							getTime(
									currNode->data.listOfInstructions[currNode->data.currentInstruction]);

					int saveIndex = 0;
					rFCFS2.dequeue(saveIndex);
					HardDiskQueue.enqueue(saveIndex);
				} else if (checkDeviceType(
						getType(
								currNode->data.listOfInstructions[currNode->data.currentInstruction]))
						== 1) {
					incrementGlobalTime(l1, rFCFS1, rFCFS2, rSFJ, HardDiskQueue,
							NetworkQueue, DeviceQueue, out, globalTick, out1,
							out2);

					currNode->data.state = "Waiting";
					currNode->data.currentQueue = "Network";
					currNode->data.time =
							getTime(
									currNode->data.listOfInstructions[currNode->data.currentInstruction]);

					int saveIndex = 0;
					rFCFS2.dequeue(saveIndex);
					NetworkQueue.enqueue(saveIndex);
				} else if (checkDeviceType(
						getType(
								currNode->data.listOfInstructions[currNode->data.currentInstruction]))
						== 2) {
					incrementGlobalTime(l1, rFCFS1, rFCFS2, rSFJ, HardDiskQueue,
							NetworkQueue, DeviceQueue, out, globalTick, out1,
							out2);

					currNode->data.state = "Waiting";
					currNode->data.currentQueue = "Device";
					currNode->data.time =
							getTime(
									currNode->data.listOfInstructions[currNode->data.currentInstruction]);

					int saveIndex = 0;
					rFCFS2.dequeue(saveIndex);
					DeviceQueue.enqueue(saveIndex);
				} else
					cout << "No Such Device";
			}
		} else if (!rSFJ.isEmpty()) {
			Node<T> *currNode = l1.getHead();
			int minInstructionsvalue = 99999;
			int minInstructionsIndex = 1;
			while (currNode != NULL) {
				if (currNode->data.currentQueue != "SJF") {
					currNode = currNode->Next;
				} else if (currNode->data.size
						- currNode->data.currentInstruction
						< minInstructionsvalue) {
					minInstructionsvalue = currNode->data.size
							- currNode->data.currentInstruction;
					minInstructionsIndex = currNode->data.index;
					currNode = currNode->Next;
				}

			}

			bool flag = false;
			currNode = l1.getHead();
			while (currNode->data.index != minInstructionsIndex) {
				currNode = currNode->Next;
			}
			currNode->data.state = "Running";

			currNode->data.currentQueue = "CPU";

			while (!flag
					&& currNode->data.currentInstruction
							<= (currNode->data.size) - 1
					&& globalTick >= GlobalTime) {
				if (currNode->data.listOfInstructions[currNode->data.currentInstruction]
						!= "COMPUTE") {
					flag = true;
					break;
				}

				incrementGlobalTime(l1, rFCFS1, rFCFS2, rSFJ, HardDiskQueue,
						NetworkQueue, DeviceQueue, out, globalTick, out1, out2);
				currNode->data.currentInstruction += 1;

			}
			if (currNode->data.currentInstruction > (currNode->data.size) - 1
					&& globalTick >= GlobalTime) {

				currNode->data.state = "Terminated";
				int saveValue = 0;
				rSFJ.dequeue(saveValue);
			}
			if (flag == true) {
				if (checkDeviceType(
						getType(
								currNode->data.listOfInstructions[currNode->data.currentInstruction]))
						== 0) {
					incrementGlobalTime(l1, rFCFS1, rFCFS2, rSFJ, HardDiskQueue,
							NetworkQueue, DeviceQueue, out, globalTick, out1,
							out2);

					currNode->data.state = "Waiting";
					currNode->data.currentQueue = "HardDisk";
					currNode->data.time =
							getTime(
									currNode->data.listOfInstructions[currNode->data.currentInstruction]);

					int saveIndex = 0;
					rSFJ.dequeue(saveIndex);
					HardDiskQueue.enqueue(saveIndex);
				} else if (checkDeviceType(
						getType(
								currNode->data.listOfInstructions[currNode->data.currentInstruction]))
						== 1) {

					incrementGlobalTime(l1, rFCFS1, rFCFS2, rSFJ, HardDiskQueue,
							NetworkQueue, DeviceQueue, out, globalTick, out1,
							out2);

					currNode->data.state = "Waiting";
					currNode->data.currentQueue = "Network";
					currNode->data.time =
							getTime(
									currNode->data.listOfInstructions[currNode->data.currentInstruction]);

					int saveIndex = 0;
					rSFJ.dequeue(saveIndex);
					NetworkQueue.enqueue(saveIndex);

				} else if (checkDeviceType(
						getType(
								currNode->data.listOfInstructions[currNode->data.currentInstruction]))
						== 2) {

					incrementGlobalTime(l1, rFCFS1, rFCFS2, rSFJ, HardDiskQueue,
							NetworkQueue, DeviceQueue, out, globalTick, out1,
							out2);

					currNode->data.state = "Waiting";
					currNode->data.currentQueue = "Device";
					currNode->data.time =
							getTime(
									currNode->data.listOfInstructions[currNode->data.currentInstruction]);

					int saveIndex = 0;
					rSFJ.dequeue(saveIndex);
					DeviceQueue.enqueue(saveIndex);
				} else {
					cout << "No Such Device";
				}
			}
		}
	}
};
template <typename T,typename U,typename V>
void runProcessScheduling(const U* PathofJobFile, V globalTick) {
	if (GlobalTime == -1) {
		string *processFileNames;
		int *processFilesArrivalTime;
		int size = 0;

		ifstream readFile(PathofJobFile);
		string line;

		if (readFile.is_open()) {
			while (!readFile.eof()) {
				line = "";
				getline(readFile, line);
				size++;
			}
			readFile.close();
			processFileNames = new string[size];
			processFilesArrivalTime = new int[size];

			readFile.open(PathofJobFile);

			int i = 0;
			while (i < size) {
				line = "";
				getline(readFile, line);
				line += '\n';
				int j = 0;
				while (line[j] != '\n') {
					while (line[j] != ' ') {
						processFileNames[i] += line[j];
						j++;
					}
					if (line[j] == ' ')
						j++;

					string strToNum = "";
					while (line[j] != '\n') {
						strToNum += line[j];
						j++;
					}
					processFilesArrivalTime[i] = stoi(strToNum);
					i++;
				}
			}
			for (int i = 1; i < size; i++) {
				for (int j = 0; j < size - i; j++) {
					if (processFilesArrivalTime[j]
							> processFilesArrivalTime[j + 1]) {
						int temp = processFilesArrivalTime[j];
						processFilesArrivalTime[j] = processFilesArrivalTime[j
								+ 1];
						processFilesArrivalTime[j + 1] = temp;

						string tempString = processFileNames[j];
						processFileNames[j] = processFileNames[j + 1];
						processFileNames[j + 1] = tempString;
					}
				}
			}
			list<process<string,int>> l1;
			for (int i = 0; i < size; i++)
				l1.insertAt(
						process<string,int>(processFileNames[i], i + 1,
								processFilesArrivalTime[i]), i + 1);

			Queue<T> rFCFS1;
			Queue<T> rFCFS2;
			Queue<T> rSJF;
			Queue<T> wFCFS1;
			Queue<T> wFCFS2;
			Queue<T> wFCFS3;
			ofstream out("..\\ProcessScheduler\\CPU.txt");
			ofstream out1("..\\ProcessScheduler\\Process.txt");
			ofstream out2("..\\ProcessScheduler\\Queue.txt");

			incrementGlobalTime(l1, rFCFS1, rFCFS2, rSJF, wFCFS1, wFCFS2,
					wFCFS3, out, globalTick, out1, out2);

			CPU<process<string,int>> c1;
			while (!isAllTerminated(l1) && globalTick >= GlobalTime) {
				c1.runProcess(l1, rFCFS1, rFCFS2, rSJF, wFCFS1, wFCFS2, wFCFS3,
						globalTick, out, out1, out2);
			}

			while (GlobalTime <= globalTick) {
				if (GlobalTime < globalTick){
					out << "Time " << GlobalTime << endl;
					out1 << "Time " << GlobalTime << endl;
				}
				else{
					out << "Time " << GlobalTime;
					out1 << "Time " << GlobalTime;
				}
				out2<< "\nTime " << GlobalTime;
				out2<<"\nFCFS-1:";
				out2<<"\nFCFS-2:";
				out2<<"\nSJF:";
				out2<<"\nHardDisk:";
				out2<<"\nNetwork:";
				out2<<"\nDevice:";

				GlobalTime++;
			}
			out.close();
			out1.close();
			out2.close();
		}
	}
}
void runProcessScheduling(const char* PathofJobFile, int globalTick){
	runProcessScheduling<int>(PathofJobFile, globalTick);
}
