#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <conio.h>


#define KEY_LEFT 75 
#define KEY_RIGHT 77
#define KEY_ENTER 13

//sorting with rating-array
//sorting with rating 
using namespace std;

void mainMenu();
void addTutor();
void displayTutor();
void searchTutor();
void modifyTutor();
void deleteTutor();

void searchById();
void searchByRating();

void sortByID();
void sortByHourlyPay();
void sortByRating();
 
//for sorting id (insertion sort)
void insertionSort(struct Tutor** head_ref);
void sortedInsert(struct Tutor** head_ref, struct Tutor* newNode);


//for sorting hourly pay and rating (merge sort)
Tutor* mergeSort(Tutor* head, int type);
Tutor* split(Tutor* head);
Tutor* merge(Tutor* first, Tutor* second, int type);


void createList();
void writeToFile();
void readFromFile();
void display(vector<string>);
void insertToLinkedList(vector<string>);
void deleteLinkedList();

struct Tutor {
	int tutorID;
	string name;
	string date_joined;
	string date_terminated;
	int hourlyPayRate;
	string phoneNo;
	string address;
	int tuitionCentreCode;
	string tuitionCentreName;
	string subjectCode;
	string subjectName;
	float rating;

	Tutor* next;
	Tutor* prev;
} *head, * tail, * curr, * temp;


int main() {

	createList();
	readFromFile();
	mainMenu();

	return 0;
}

void mainMenu() {
	int option;
	cout << "\n\t*****************************************\n\t*\t\t WELCOME TO  \t\t*\n\t*\t   TUTOR MANAGEMENT SYSTEM   \t*\n\t*****************************************\n";
	cout << "\n\t\tMAIN MENU";
	cout << "\n\t1: ADD TUTOR RECORD\n\t2: DISPLAY RECORDS\n\t3: SEARCH TUTOR RECORD\n\t4: MODIFY TUTOR RECORD\n\t5: DELETE TUTOR RECORD\n\t6: EXIT SYSTEM";
	cout << "\n\n\tEnter an option:";
	cin >> option;
	switch (option) {
	case 1:
		addTutor();
		break;
	case 2:
		displayTutor();
		break;
	case 3:
		searchTutor();
		break;
	case 4:
		modifyTutor();
		break;
	case 5:
		deleteTutor();
		break;
	case 6:
		insertionSort(&head);
		writeToFile();
		exit(0);
	default:
		cout << "Invalid option. Please enter a valid option.";
		mainMenu();
		break;
	}
}


//************************************************************************************
// Create an empty Linked List
//***********************************************************************************
void createList() {
	head = NULL;
}

void addTutor() {
	system("cls");
	insertionSort(&head);
	curr = head;
	Tutor* newtutor = new Tutor;
	cout << "\n\tADD TUTOR RECORD" << endl << "\n\tPlease Enter Tutor's Information." << endl; 
	if (tail == NULL) {
		newtutor->tutorID = 1;
	}else{ 
		newtutor->tutorID = tail->tutorID + 1;
	}
	cout << "\tNew Tutor ID: " << newtutor->tutorID << endl;
	cout << "\tEnter Tutor's name:";
	cin.ignore();
	getline(cin, newtutor->name);
	cout << "\tEnter date joined:";
	getline(cin, newtutor->date_joined);
	cout << "\tEnter date terminated:";
	getline(cin, newtutor->date_terminated);
	cout << "\tEnter hourly pay rate:";
	cin >> newtutor->hourlyPayRate;
	cout << "\tEnter phone number:";
	cin.ignore();
	getline(cin, newtutor->phoneNo);
	cout << "\tEnter address:";
	getline(cin, newtutor->address);
	cout << "\tEnter tuition centre code:";
	cin >> newtutor->tuitionCentreCode;
	cout << "\tEnter tuition centre name:";
	cin.ignore();
	getline(cin, newtutor->tuitionCentreName);
	cout << "\tEnter subject code: ";
	cin >> newtutor->subjectCode;
	cout << "\tEnter subject name:";
	cin.ignore();
	getline(cin, newtutor->subjectName);
	cout << "\tEnter rating:";
	cin >> newtutor->rating;

	newtutor->next = NULL;
	newtutor->prev = NULL;

	if (head == NULL)
	{
		head = tail = newtutor;
	}
	else
	{
		newtutor->prev = tail;
		tail->next = newtutor;
		tail = newtutor;

	}
	cout << "\n\tTutor Record has been added!" << endl;
	mainMenu();
}


void displayTutor() {
	int sort;
	cout << "\n\tDISPLAY TUTOR RECORD";
	cout << "\n\t1: SORT BY TUTOR ID\n\t2: SORT BY HOURLY PAY RATE\n\t3: SORT BY TUTOR OVERALL PERFORMANCE\n\t4: RETURN TO MAIN MENU";
	cout << "\n\n\tEnter an option:";
	cin >> sort;
	if (sort == 1)
		sortByID();
	else if (sort == 2)
		sortByHourlyPay();
	else if (sort == 3)
		sortByRating();
	else if (sort == 4)
		mainMenu();
	else {
		cout << "Invalid Option. Please choose again.";
		displayTutor();
	}
}



void sortedInsert(struct Tutor** head_ref, struct Tutor* newNode)
{
	struct Tutor* current;
	// if list is empty 
	if (*head_ref == NULL)
		*head_ref = newNode;

	// if the tutor is inserted at the beginning of the doubly linked list 
	else if ((*head_ref)->tutorID >= newNode->tutorID) {
		newNode->next = *head_ref;
		newNode->next->prev = newNode;
		*head_ref = newNode;
	}
	else {
		current = *head_ref;

		// locate the node after which the new node 
		// is to be inserted 
		while (current->next != NULL &&
			current->next->tutorID < newNode->tutorID)
			current = current->next;

		/*Make the appropriate links */
		newNode->next = current->next;

		// if the new node is not inserted at the end of the list 
		if (current->next != NULL)
			newNode->next->prev = newNode;

		current->next = newNode;
		newNode->prev = current;
	}
}

void insertionSort(struct Tutor** head_ref)
{
	// Initialize 'sorted' - a sorted doubly linked list 
	struct Tutor* sorted = NULL;

	// Traverse the given doubly linked list and 
	// insert every node to 'sorted' 
	struct Tutor* current = *head_ref;
	while (current != NULL) {

		// Store next for next iteration 
		struct Tutor* next = current->next;

		// removing all the links so as to create 'current' 
		// as a new node for insertion 
		current->prev = current->next = NULL;

		// insert current in 'sorted' doubly linked list 
		sortedInsert(&sorted, current);

		// Update current 
		current = next;
	}

	// Update head_ref to point to sorted doubly linked list 
	*head_ref = sorted;
}

Tutor* merge(Tutor* first, Tutor* second, int type) {
	if (!first)
		return second;

	if (!second)
		return first;

	if (type == 1) {
		if (first->hourlyPayRate < second->hourlyPayRate)
		{
			first->next = merge(first->next, second, type);
			first->next->prev = first;
			first->prev = NULL;
			return first;
		}
		else
		{
			second->next = merge(first, second->next, type);
			second->next->prev = second;
			second->prev = NULL;
			return second;
		}
	}
	else {
		if (first->rating < second->rating)
		{
			first->next = merge(first->next, second, type);
			first->next->prev = first;
			first->prev = NULL;
			return first;
		}
		else
		{
			second->next = merge(first, second->next, type);
			second->next->prev = second;
			second->prev = NULL;
			return second;
		}
	}


}

//splitting array into half
Tutor* split(Tutor* head) {
	Tutor* fast = head;
	Tutor* slow = head;
	while (fast->next != NULL && fast->next->next != NULL) {
		fast = fast->next->next;
		slow = slow->next; //slow node is right at the middle
	}
	Tutor* secondHead = slow->next; //second head starts after node slow
	slow->next = NULL; //slow is the last node for the first head therefore its next becomes null
	return secondHead;

}

Tutor* mergeSort(Tutor* head, int type) {

	//if list is empty or there is only one node
	if (head == NULL || head->next == NULL)
		return head;
	Tutor* second = split(head); //get the split second node's head
	//recursion
	//recurse first segment (head is always first node)
	head = mergeSort(head, type);
	// recurse the second segment
	second = mergeSort(second, type);

	return merge(head, second, type); //sort the nodes  

}


void displayList() {
	curr = head;
	int i = 1;
	char option = 0;
	while (curr != NULL)
	{ 
		system("cls");
		cout << "\n\tTutor ID:" << curr->tutorID << "\n\tTutor Name:" << curr->name << "\n\tDate Joined:" << curr->date_joined << "\n\tDate Terminated: " << curr->date_terminated
			<< "\n\tHourly Pay Rate: " << curr->hourlyPayRate << "\n\tPhone: " << curr->phoneNo << "\n\tAddress: " << curr->address << "\n\tentre Code: " << curr->tuitionCentreCode
			<< "\n\tCentre Name: " << curr->tuitionCentreName << "\n\tSubject Code: " << curr->subjectCode << "\n\tSubject Name: " << curr->subjectName << "\n\tRating: " << curr->rating << endl;

		if (curr->prev == NULL && curr->next == NULL) { //if there is only one record
			cout << "\n\t\t Page " << i << "\n\tEnter to exit to main menu";
			option = _getch();
			if (option == KEY_ENTER)
				break;
		}

		else if (curr->prev == NULL) { //if first record
			cout << "\n\t\t Page " << i << " >" << "\n\tEnter to exit to main menu";
			option = _getch();
			if (option == KEY_RIGHT) {
				curr = curr->next;
				i++;
			}
			else if (option == KEY_ENTER)
				break;
		}
		else if (curr->next == NULL) { //if last record
			cout << "\n\t\t< Page " << i << "\n\tEnter to exit to main menu";
			option = _getch();
			if (option == KEY_LEFT) {
				curr = curr->prev;
				i--;
			}
			else if (option == KEY_ENTER)
				break;
			
		}
		else { //if center
			cout << "\n\t\t< Page " << i << " >" << "\n\tEnter to exit to main menu";
			option = _getch();
			if (option == KEY_LEFT) {
				curr = curr->prev;
				i--;
			}
			else if (option == KEY_RIGHT) {
				curr = curr->next;
				i++;
			}
			else if (option == KEY_ENTER)
				break;
			
		}  
	}
	system("cls");
	mainMenu();
}

void sortByID() {
	if (head == NULL) { 
		cout << "\n\tNo Tutor Record exist...\n";
		mainMenu();
	}
	else{
		insertionSort(&head);
		cout << "\n\tTutors' Information after sorting ID:\n";
		displayList();
	}
}

void sortByHourlyPay() {
	if (head == NULL) {
		cout << "\n\tNo Tutor Record exist...\n";
		mainMenu();
	}
	else{
		head = mergeSort(head, 1);
		cout << "\n\tTutors' Information after sorting Hourly Pay Rate:\n";
		displayList(); 
	}
}

void sortByRating() {
	if (head == NULL) {
		cout << "\n\tNo Tutor Record exist...\n";
		mainMenu();
	}
	else {
		head = mergeSort(head, 2);
		cout << "\n\tTutors' Record sorted by Overall Performance:\n";
		displayList(); 
	}

}

void searchTutor() {
	int option;
	cout << "\n\tSEARCH TUTOR RECORD";
	cout << "\n\t1: SEARCH BY TUTOR ID\n\t2: SEARCH BY TUTOR OVERALL PERFORMANCE\n\t3: RETURN TO MAIN MENU";
	cout << "\n\n\tEnter an option:";
	cin >> option;
	if (option == 1)
		searchById();
	else if (option == 2)
		searchByRating();
	else if (option == 3)
		mainMenu();
	else {
		cout << "\tInvalid Option. Please choose again.";
		searchTutor();
	}
}

void searchByRating() {
	int found = 0;
	int rating;
	cout << "\n\tEnter Tutor Overall Performance:";
	cin >> rating;
	curr = head;
	while (curr != NULL) {
		if (curr->tutorID == rating) {
			found = 1;
			cout << "\n\tTutor ID: " << curr->tutorID << "\n\tName: " << curr->name << "\n\tDate Joined: " << curr->date_joined << "\n\tDate Terminated: " << curr->date_terminated
				<< "\n\tHourly Pay Rate: " << curr->hourlyPayRate << "\n\tPhone: " << curr->phoneNo << "\n\tAddress: " << curr->address << "\n\tCentre Code: " << curr->tuitionCentreCode
				<< "\n\tCentre Name: " << curr->tuitionCentreName << "\n\tSubject Code: " << curr->subjectCode << "\n\tSubject Name: " << curr->subjectName << "\n\tRating: " << curr->rating << endl;
			break;
		}
		else
			curr = curr->next;
	}
	if (found == 0) {
		cout << "\n\tTutor Record cannot be found.";
	}
	searchTutor();
}

void searchById() {
	int found = 0;
	int id;
	cout << "\n\tEnter Tutor ID:";
	cin >> id;
	curr = head;
	while (curr != NULL) {
		if (curr->tutorID == id) {
			found = 1;
			cout << "\n\tTutor ID: " << curr->tutorID << "\n\tName: " << curr->name << "\n\tDate Joined: " << curr->date_joined << "\n\tDate Terminated: " << curr->date_terminated
				<< "\n\tHourly Pay Rate: " << curr->hourlyPayRate << "\n\tPhone: " << curr->phoneNo << "\n\tAddress: " << curr->address << "\n\tCentre Code: " << curr->tuitionCentreCode
				<< "\n\tCentre Name: " << curr->tuitionCentreName << "\n\tSubject Code: " << curr->subjectCode << "\n\tSubject Name: " << curr->subjectName << "\n\tRating: " << curr->rating << endl;
			break;
		}
		else
			curr = curr->next;
	}
	if (found == 0) {
		cout << "\n\tTutor Record cannot be found.";
	}
	system("PAUSE");
	system("CLS");
	cout << flush;
	searchTutor();
}

void modifyTutor() {
	int id, opt;
	int found = 0;
	cout << "\n\tEnter Tutor ID :";
	cin >> id;
	curr = head;
	while (curr != NULL) {
		if (curr->tutorID == id) {
			found = 1;
			cout << "\n\tTutor ID: " << curr->tutorID << "\n\tName: " << curr->name << "\n\tDate Joined: " << curr->date_joined << "\n\tDate Terminated: " << curr->date_terminated
				<< "\n\tHourly Pay Rate: " << curr->hourlyPayRate << "\n\tPhone: " << curr->phoneNo << "\n\tAddress: " << curr->address << "\n\tCentre Code: " << curr->tuitionCentreCode
				<< "\n\tCentre Name: " << curr->tuitionCentreName << "\n\tSubject Code: " << curr->subjectCode << "\n\tSubject Name: " << curr->subjectName << "\n\tRating: " << curr->rating << endl;
			cout << "\n\tWhat detail do u want to update\n";
			cout << "\t1. Termination date\n";
			cout << "\t2. Phone No.\n";
			cout << "\t3. Hourly pay rate\n";
			cout << "\t4. Address\n";
			cout << "\t5. Rating\n\t";
			cin >> opt;
			if (opt == 1) {
				cout << "\tEnter new termination date: ";
				cin.ignore();
				getline(cin, curr->date_terminated);
			}
			else if (opt == 2) {
				cout << "\tEnter new Phone Number: ";
				cin.ignore();
				getline(cin, curr->phoneNo);
			}
			else if (opt == 3) {
				cout << "\tEnter new Hourly pay rate: ";
				cin.ignore();
				cin >> curr->hourlyPayRate;
			}
			else if (opt == 4) {
				cout << "\tEnter new Address: ";
				cin.ignore();
				getline(cin, curr->address);
			}
			else if (opt == 5) {
				cout << "\tEnter new Rating: ";
				cin.ignore();
				cin >> curr->rating;
			}
			else {
				cout << "\n\tTry again bro: ";
				modifyTutor();
			}
			cout << "\n\tTutor ID: " << curr->tutorID << "\n\tName: " << curr->name << "\n\tDate Joined: " << curr->date_joined << "\n\tDate Terminated: " << curr->date_terminated
				<< "\n\tHourly Pay Rate: " << curr->hourlyPayRate << "\n\tPhone: " << curr->phoneNo << "\n\tAddress: " << curr->address << "\n\tCentre Code: " << curr->tuitionCentreCode
				<< "\n\tCentre Name: " << curr->tuitionCentreName << "\n\tSubject Code: " << curr->subjectCode << "\n\tSubject Name: " << curr->subjectName << "\n\tRating: " << curr->rating << endl;
			break;
		}
		else
			curr = curr->next;
	}
	if (found == 0) {
		cout << "\n\tTutor Record cannot be found.";
	}
	system("PAUSE");
	system("CLS");
	cout << flush;
	mainMenu();
}


void deleteTutor() {
	int id;
	int pos = 0;
	cout << "\n\tTutor detail can be deleted after 6 months from date terminated" << endl;
	cout << "\n\tEnter Tutor Id : " << endl;
	cin >> id;
	struct Tutor* pre_node = NULL;

	if (head == NULL) {
		printf("\n\tLinked List not initialized");
		return;
	}

	if (head->tutorID == id) {
		if (head->next != NULL) {
			head->next->prev = NULL;
			head = head->next;
			return;
		}
		else {
			head = NULL;
			cout << "\n\tList is empty now";
			return;
		}
	}
	else if (head->tutorID != id && head->next == NULL) {
		cout << head->tutorID << "\n\tNot found in the list\n";
		return;
	}

	curr = head;

	while (curr->next != NULL && curr->tutorID != id) {
		pre_node = curr;
		curr = curr->next;
	}
	if (curr->tutorID == id) {
		pre_node->next = pre_node->next->next;

		if (pre_node->next != NULL) {          // link back
			pre_node->next->prev = pre_node;
		}
		else
			tail = pre_node;

		free(curr);
	}
	else
		cout << head->tutorID << "\n\tNot found in the list\n";
	cout << "\n\tTutor detail is deleted." << endl;
	system("PAUSE");
	system("CLS");
	cout << flush;
	mainMenu();
}


//************************************************************************************
// write the Linked List Data To a File
//*********************************************************************************** 
void writeToFile() {
	//write list data to file top to bottom
	ofstream fout("listData.txt", ofstream::trunc);
	curr = head;

	while (curr != NULL)
	{
		fout << curr->tutorID << "," << curr->name << "," << curr->date_joined << "," << curr->date_terminated << ","
			<< curr->hourlyPayRate << "," << curr->phoneNo << "," << curr->address << "," << curr->tuitionCentreCode
			<< "," << curr->tuitionCentreName << "," << curr->subjectCode << "," << curr->subjectName << ","
			<< curr->rating << endl;
		curr = curr->next;
	}

	fout.close();
}

//************************************************************************************
// read the data in a file and put it back to the Linked List
//*********************************************************************************** 
void readFromFile() {
	// vector <vector <string> > data;
	vector <string> record;

	ifstream fin("listData.txt");
	Tutor* newHead = NULL;

	while (fin)
	{
		string s;
		if (!getline(fin, s)) break;

		istringstream ss(s);

		while (ss)
		{
			string s;
			if (!getline(ss, s, ',')) break;
			record.push_back(s);
		}
	}
	if (!fin.eof())
	{
		cerr << "End of File...!\n";
	}

	fin.close();

	//display(record);
	//cout << "Insert into List..." << endl;
	insertToLinkedList(record);
}


//************************************************************************************
// Display data in the the Vector
//***********************************************************************************
void display(vector<string> v)
{
	int i;
	for (i = 0; i < v.size(); i++) {
		if (i % 2 == 0) cout << endl;
		cout << v[i] << " ";
	}
}

//************************************************************************************
// Insert Data into the Linked List
//*********************************************************************************** 
void insertToLinkedList(vector<string> v)
{
	int i = 0, size;
	string tmp;

	size = v.size();
	while (i < size) {
		if (i % 12 == 0) {
			curr = head;
			//declare a new node to add to list
			Tutor* newTutor = new Tutor;
			//initialize members of new node
			newTutor->tutorID = stoi(v[i]);
			newTutor->name = v[i + 1];
			newTutor->date_joined = v[i + 2];
			newTutor->date_terminated = v[i + 3];
			newTutor->hourlyPayRate = stoi(v[i + 4]);
			newTutor->phoneNo = v[i + 5];
			newTutor->address = v[i + 6];
			newTutor->tuitionCentreCode = stoi(v[i + 7]);
			newTutor->tuitionCentreName = v[i + 8];
			newTutor->subjectCode = v[i + 9];
			newTutor->subjectName = v[i + 10];
			newTutor->rating = stof(v[i + 11]);

			newTutor->next = NULL;
			newTutor->prev = NULL;
			if (head == NULL)//this is first node in list
			{
				head = tail = newTutor;
			}
			else
			{
				newTutor->prev = tail;
				tail->next = newTutor;
				tail = newTutor;
			}
		}
		i = i + 12;
	}
}

//************************************************************************************
// Delete the Linked List
//***********************************************************************************
void deleteLinkedList()
{

	/* deref head_ref to get the real head */
	curr = head;

	while (curr != NULL)
	{
		temp = curr->next;
		free(curr);
		curr = temp;
	}

	/* deref head_ref to affect the real head back
		in the caller. */
	head = NULL;
}


 