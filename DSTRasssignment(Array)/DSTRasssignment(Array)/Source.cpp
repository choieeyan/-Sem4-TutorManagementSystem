#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <conio.h>


#define KEY_LEFT 75 
#define KEY_RIGHT 77
#define KEY_ENTER 13

using namespace std;
#define MAX 100	//define the length for array
int tutorNo = 0;	//read the number of lines stored in file to know the tutor number

struct Tutor {		//structure for storing tutor information
	int TutorID;
	string TutorName;
	string DateJoined;
	string DateTerminated;
	double HourlyPay;
	string phoneNo;
	string Address;
	int TuitionCode;
	string TuitionName;
	string SubjectCode;
	string SubjectName;
	float rating;
} tutor[MAX];

void menu();
void insertTutor();
void displayTutor();
void deleteTutor();
void modifyInfo();

void sortByHourlyPay();
void sortByID();
void sortByRating();

void searchTutor();
void searchByID();
void searchByRating();
int binarySearch(struct Tutor arr[], int left, int right, int TutorID);

void readFile();
void insertToArray(vector<string> v);
void writeFile();

void searchByRating() {	//search tutor rating function using linear search
	float rate;
	int found = 0;
	cout << "\n\tSearching Tutor Information By Rating" << endl;
	cout << "\n\tPlease enter the rating:";
	cin >> rate;
	for (int i = 0; i < tutorNo; i++) {
		if (tutor[i].rating == rate) {
			found = 1;
			cout << "\n\tTutor ID:" << tutor[i].TutorID << endl << "\tTutor Name:" << tutor[i].TutorName << endl
				<< "\tDate Joined:" << tutor[i].DateJoined << endl << "\tDate Terminated:" << tutor[i].DateTerminated << endl
				<< "\tHourly Pay Rate:" << tutor[i].HourlyPay << endl << "\tPhone Number:" << tutor[i].phoneNo << endl
				<< "\tAddress:" << tutor[i].Address << endl << "\tTuition Centre Code:" << tutor[i].TuitionCode << endl
				<< "\tTution Centre Name:" << tutor[i].TuitionName << endl << "\tSubject Code:" << tutor[i].SubjectCode << endl
				<< "\tSubject Name:" << tutor[i].SubjectName << endl << "\tRating:" << tutor[i].rating << endl;
		}
	}
	if (found == 0)
		cout << "\n\tNo record is found." << endl;
	cout << "\n\tPlease enter any key to return back searching page." << endl;
	getchar();
	getchar();
	searchTutor();
}

void searchByID() {	//search tutor ID function using binary search
	int id;
	cout << "\n\tSearching Tutor Information By ID" << endl;
	cout << "\tEnter Tutor ID:";
	cin >> id;
	int index = binarySearch(tutor, 0, tutorNo, id);	//return the array index of the matched tutor ID
	if (index == -1) {
		cout << "\n\tTutor Record cannot be found." << endl;
	}
	else {
		cout << "\n\tTutor ID:" << tutor[index].TutorID << endl << "\tTutor Name:" << tutor[index].TutorName << endl
			<< "\tDate Joined:" << tutor[index].DateJoined << endl << "\tDate Terminated:" << tutor[index].DateTerminated << endl
			<< "\tHourly Pay Rate:" << tutor[index].HourlyPay << endl << "\tPhone Number:" << tutor[index].phoneNo << endl
			<< "\tAddress:" << tutor[index].Address << endl << "\tTuition Centre Code:" << tutor[index].TuitionCode << endl
			<< "\tTution Centre Name:" << tutor[index].TuitionName << endl << "\tSubject Code:" << tutor[index].SubjectCode << endl
			<< "\tSubject Name:" << tutor[index].SubjectName << endl << "\tRating:" << tutor[index].rating << endl;
	}
	cout << "\n\tPlease enter any key to return back searching page." << endl;
	getchar();
	getchar();
	searchTutor();
}

int binarySearch(struct Tutor arr[], int left, int right, int TutorID)	//binary search algorithm
{
	while (left <= right) {
		int mid = left + (right - left) / 2;

		// Check if Tutor iD is present at middle of tutor array
		if (arr[mid].TutorID == TutorID)
			return mid;

		// If tutor id in struct tutor is smaller, ignore right half 
		if (TutorID > arr[mid].TutorID)
			left = mid + 1;

		// If tutor id in struct tutor greater, ignore left half 		
		else
			right = mid - 1;
	}
	// if element was not present 
	return -1;
}

void insertTutor() { //insert new tutor 
	int opt;
	if (tutorNo < 100) {
		for (int i = 0; i < 100; i++) {
			system("cls");
			cout << "\tADD TUTOR RECORD" << endl << "Please Enter Tutors' Information:" << endl;
			tutor[tutorNo].TutorID = tutor[tutorNo - 1].TutorID + 1;	// the tutorID can reuse the latest one ID even it is deleted
			cout << "\nNew Tutor ID: " << tutor[tutorNo].TutorID << endl;
			cin.ignore();
			cout << "Enter Tutor's name:";
			getline(cin, tutor[tutorNo].TutorName);
			cout << "Enter date joined:";
			getline(cin, tutor[tutorNo].DateJoined);
			cout << "Enter date terminated:";
			getline(cin, tutor[tutorNo].DateTerminated);
			cout << "Enter hourly pay rate:";
			cin >> tutor[tutorNo].HourlyPay;
			cout << "Enter phone number:";
			cin.ignore();
			getline(cin, tutor[tutorNo].phoneNo);
			cout << "Enter address:";
			getline(cin, tutor[tutorNo].Address);
			cout << "Enter tuition centre code:";
			cin >> tutor[tutorNo].TuitionCode;
			cout << "Enter tuition centre name:";
			cin.ignore();
			getline(cin, tutor[tutorNo].TuitionName);
			cout << "Enter subject code:";
			getline(cin, tutor[tutorNo].SubjectCode);
			cout << "Enter subject name:";
			getline(cin, tutor[tutorNo].SubjectName);
			cout << "Enter rating:";
			cin >> tutor[tutorNo].rating;
			cout << "Tutor Record has been added!" << endl;
			tutorNo++;
			cout << "Please enter 0 to continue adding, else press 1 to stop." << endl;
			cin >> opt;
			if (opt)
				break;
		}
	}
	else {	//if meet the array limit
		cout << "\tNo record can be inserted anymore. The array is overflow." << endl;
	}
	menu();
}

void displayTutor() {	//display tutor functions
	int option;
	cout << "\n\tSORT AND DISPLAY TUTOR RECORDS";
	cout << "\n\t1: SORT BY TUTOR ID\n\t2: SORT BY TUTOR HOURLY PAY RATE\n\t3: SORT BY TUTOR OVERALL PERFORMANCE\n\t4: RETURN TO MAIN MENU";
	cout << "\n\n\tEnter an option:";
	cin >> option;
	if (option == 1)
		sortByID();
	else if (option == 2)
		sortByHourlyPay();
	else if (option == 3)
		sortByRating();
	else if (option == 4)
		menu();
	else {
		cout << "\tInvalid Option. Please choose again." << endl;
		displayTutor();
	}
}

void modifyInfo() {	//modify or update the tutor information
	int ID, choice;
	cout << "\n\tModify Tutor Information" << endl;
	cout << "\n\tPlease enter Tutor ID:";
	cin >> ID;
	for (int i = 0; i < tutorNo; i++) {
		if (tutor[i].TutorID == ID) {
			cout << "\tTutor ID:" << tutor[i].TutorID << endl << "\tTutor Name:" << tutor[i].TutorName << endl
				<< "\tDate Joined:" << tutor[i].DateJoined << endl << "\tDate Terminated:" << tutor[i].DateTerminated << endl
				<< "\tHourly Pay Rate:" << tutor[i].HourlyPay << endl << "\tPhone Number:" << tutor[i].phoneNo << endl
				<< "\tAddress:" << tutor[i].Address << endl << "\tTuition Centre Code:" << tutor[i].TuitionCode << endl
				<< "\tTution Centre Name:" << tutor[i].TuitionName << endl << "\tSubject Code:" << tutor[i].SubjectCode << endl
				<< "\tSubject Name:" << tutor[i].SubjectName << endl << "\tRating:" << tutor[i].rating << endl;
			cout << "\n\t1. Date Terminated" << endl << "\t2. Hourly Pay Rate" << endl << "\t3. Phone Number" << endl
				<< "\t4. Address" << endl << "\t5. Rating\n\n";
			cout << "\tPlease select the information you want to modify:";
			cin >> choice;
			switch (choice) {
			case 1: cout << "\tPlease enter the date terminated:"; cin >> tutor[i].DateTerminated; break;
			case 2: cout << "\tPlease enter new hourly pay rate:"; cin >> tutor[i].HourlyPay; break;
			case 3: cout << "\tPlease enter new phone number:"; cin >> tutor[i].phoneNo; break;
			case 4: cout << "\tPlease enter new address:"; cin.ignore(); getline(cin, tutor[i].Address); break;
			case 5: cout << "\tPlease enter new rating:"; cin >> tutor[i].rating; break;
			default: cout << "\tInvalid input." << endl; modifyInfo(); break;
			}
			cout << "\n\tTutor ID:" << tutor[i].TutorID << endl << "\tTutor Name:" << tutor[i].TutorName << endl
				<< "\tDate Joined:" << tutor[i].DateJoined << endl << "\tDate Terminated:" << tutor[i].DateTerminated << endl
				<< "\tHourly Pay Rate:" << tutor[i].HourlyPay << endl << "\tPhone Number:" << tutor[i].phoneNo << endl
				<< "\tAddress:" << tutor[i].Address << endl << "\tTuition Centre Code:" << tutor[i].TuitionCode << endl
				<< "\tTution Centre Name:" << tutor[i].TuitionName << endl << "\tSubject Code:" << tutor[i].SubjectCode << endl
				<< "\tSubject Name:" << tutor[i].SubjectName << endl << "\tRating:" << tutor[i].rating << endl;
			cout << "\nPlease enter any key to return back main menu." << endl;
			getchar();
			getchar();
			menu();
		}
	}
}

void deleteTutor() {	//delete tutor function
	int ID;
	char response;
	cout << "\n\tDelete Tutor Information" << endl;
	cout << "\tDeletion of tutors' information is only applicable for those who have left 6 months ago." << endl;
	cout << "\n\tPlease enter Tutor ID:";
	cin >> ID;
	for (int i = 0; i < tutorNo; i++) {
		if (tutor[i].TutorID == ID) {
			cout << "\n\tTutor ID:" << tutor[i].TutorID << endl << "\tTutor Name:" << tutor[i].TutorName << endl
				<< "\tDate Joined:" << tutor[i].DateJoined << endl << "\tDate Terminated:" << tutor[i].DateTerminated << endl
				<< "\tHourly Pay Rate:" << tutor[i].HourlyPay << endl << "\tPhone Number:" << tutor[i].phoneNo << endl
				<< "\tAddress:" << tutor[i].Address << endl << "\tTuition Centre Code:" << tutor[i].TuitionCode << endl
				<< "\tTution Centre Name:" << tutor[i].TuitionName << endl << "\tSubject Code:" << tutor[i].SubjectCode << endl
				<< "\tSubject Name:" << tutor[i].SubjectName << endl << "\tRating:" << tutor[i].rating << endl;
			cout << "\tPlease confirm the deletion of Tutor Information. (Y/N)";
			cin >> response;
			if (response == 'Y' || response == 'y') {
				for (int j = i; j < tutorNo; j++) {
					tutor[j] = tutor[j + 1];
					tutorNo--;
					cout << "\n\tTutor is deleted successfully." << endl;
				}
			}
			else if (response == 'N' || response == 'n') {
				break;
			}
			else {
				cout << "Invalid input." << endl;
				break;
			};
		}
	}
	cout << "\tPlease enter any key to return back main menu." << endl;
	getchar();
	getchar();
	menu();
}

void exit() {	//exit system function
	char response;
	cout << "\n\tAre you sure to quit this system? (Y/N): ";
	cin >> response;
	if (response == 'Y' || response == 'y') {
		writeFile();
		exit(0);
	}
	else if (response == 'N' || response == 'n') {
		menu();
	}
	else {
		cout << "Invalid input." << endl;
		exit();
	};
}

void writeFile() {
	//write array data to file top to bottom
	ofstream fout("TutorData.txt", ofstream::trunc);

	for (int i = 0; i < tutorNo; i++) {
		fout << tutor[i].TutorID << "," << tutor[i].TutorName << "," << tutor[i].DateJoined << "," << tutor[i].DateTerminated
			<< "," << tutor[i].HourlyPay << "," << tutor[i].phoneNo << "," << tutor[i].Address << "," << tutor[i].TuitionCode
			<< "," << tutor[i].TuitionName << "," << tutor[i].SubjectCode << "," << tutor[i].SubjectName << "," << tutor[i].rating << endl;
	}
	fout.close();
}

void readFile() { //make it readable for array of structure
	vector <string> record;
	ifstream fin("TutorData.txt");

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
	insertToArray(record);
}

void insertToArray(vector<string> v)	//insert the lines of file into array function
{
	int i = 0, size;
	string tmp;

	size = v.size();
	while (i < size) {
		if (i % 12 == 0) {	//insert the tutor info
			tutor[tutorNo].TutorID = stoi(v[i]);
			tutor[tutorNo].TutorName = v[i + 1];
			tutor[tutorNo].DateJoined = v[i + 2];
			tutor[tutorNo].DateTerminated = v[i + 3];
			tutor[tutorNo].HourlyPay = stoi(v[i + 4]);
			tutor[tutorNo].phoneNo = v[i + 5];
			tutor[tutorNo].Address = v[i + 6];
			tutor[tutorNo].TuitionCode = stoi(v[i + 7]);
			tutor[tutorNo].TuitionName = v[i + 8];
			tutor[tutorNo].SubjectCode = v[i + 9];
			tutor[tutorNo].SubjectName = v[i + 10];
			tutor[tutorNo].rating = stof(v[i + 11]);
		}
		tutorNo++;
		i = i + 12;
	}
}

void menu() {	//main menu of the tutor management system
	int option, i = 0;
	cout << "\n\t*****************************************\n\t*\t\t WELCOME TO  \t\t*\n\t*\t   TUTOR MANAGEMENT SYSTEM   \t*\n\t*****************************************\n";
	cout << "\n\t\tMAIN MENU" << endl;
	cout << "\t1. Add New Tutor Record " << endl;
	cout << "\t2. Display the Tutor Record " << endl;
	cout << "\t3. Search Tutor Record " << endl;
	cout << "\t4. Modify Tutor Record " << endl;
	cout << "\t5. Delete Tutor Record " << endl;
	cout << "\t6. Exit System" << endl;
	cout << "\tSelect a choice:";
	cin >> option;
	switch (option) {
	case 1: insertTutor(); break;
	case 2: displayTutor(); break;
	case 3: searchTutor(); break;
	case 4: modifyInfo(); break;
	case 5: deleteTutor(); break;
	case 6: exit(); break;
	default: cout << "\tInvalid input." << endl; break;
	}
}

void searchTutor() {	//searching menu
	int option;
	cout << "\n\tSEARCH TUTOR RECORD";
	cout << "\n\t1: SEARCH BY TUTOR ID\n\t2: SEARCH BY TUTOR OVERALL PERFORMANCE (Rating)\n\t3: RETURN TO MAIN MENU";
	cout << "\n\n\tEnter an option:";
	cin >> option;
	if (option == 1)
		searchByID();
	else if (option == 2)
		searchByRating();
	else if (option == 3)
		menu();
	else {
		cout << "\tInvalid Option. Please choose again." << endl;
		searchTutor();
	}
}

void insertionSort(struct Tutor arr[], int n)	//insertion sort algorithm for Tutor ID
{
	int i, key, j;
	struct Tutor temp[1];
	for (i = 1; i < n; i++)
	{
		key = arr[i].TutorID;
		j = i - 1;

		/* Move and swap elements of tutor[0..i-1], that are
		greater than key Tutor ID, to one position ahead of their current position*/
		while (j >= 0 && arr[j].TutorID > key)
		{
			temp[0] = arr[j + 1];
			arr[j + 1] = arr[j];
			arr[j] = temp[0];
			j = j - 1;
		}
		arr[j + 1].TutorID = key;
	}
}

void printInfo(struct Tutor tutor[], int n)		//print tutor Info function
{
	int i=0;
	char option =0;
	while (i<n) {
		system("cls");
		cout << "\n\tTutor ID:" << tutor[i].TutorID << endl << "\tTutor Name:" << tutor[i].TutorName << endl
			<< "\tDate Joined:" << tutor[i].DateJoined << endl << "\tDate Terminated:" << tutor[i].DateTerminated << endl
			<< "\tHourly Pay Rate:" << tutor[i].HourlyPay << endl << "\tPhone Number:" << tutor[i].phoneNo << endl
			<< "\tAddress:" << tutor[i].Address << endl << "\tTuition Centre Code:" << tutor[i].TuitionCode << endl
			<< "\tTution Centre Name:" << tutor[i].TuitionName << endl << "\tSubject Code:" << tutor[i].SubjectCode << endl
			<< "\tSubject Name:" << tutor[i].SubjectName << endl << "\tRating:" << tutor[i].rating << endl;

		if (i==0) {
			cout << "\n\t\t Page " << i+1 << " >" << "\n\tEnter to exit to main menu";
			option = _getch();
			if (option == KEY_RIGHT) { 
				i++;
			}
			else if (option == KEY_ENTER)
				break;
		}
		else if (i==n-1) {
			cout << "\n\t\t< Page " << i+1 << "\n\tEnter to exit to main menu";
			option = _getch();
			if (option == KEY_LEFT) { 
				i--;
			}
			else if (option == KEY_ENTER)
				break; 
		}
		else {
			cout << "\n\t\t< Page " << i+1 << " >" << "\n\tEnter to exit to main menu";
			option = _getch();
			if (option == KEY_LEFT) { 
				i--;
			}
			else if (option == KEY_RIGHT) { 
				i++;
			}
			else if (option == KEY_ENTER)
				break; 
		}
	}
	system("cls");
	menu();
}

void swap(struct Tutor* a, struct Tutor* b)
{
	struct Tutor* t;
	t = a;
	a = b;
	b = t;
}

//partition- assigning a pivot and moving items so all items lesser at at left and greater is at right (returns the index of partition (where pivot is after partition arrangement)
int partition(struct Tutor* tutor, int start, int end, int type) {
	int pivot = end; //assign pivot as the pivot
	int pIndex = start; //partition index
	//swapping for numbers before the pivot
	if (type == 1) {
		for (int i = start; i < end; i++) {
			//if the rating is smaller or equal than rating at pivot
			if (tutor[i].HourlyPay <= tutor[pivot].HourlyPay) {
				//we swap the tutor record with the partition index
				swap(tutor[i], tutor[pIndex]);
				pIndex++; //after swapping pindex will increment to the next index
			}
		}
	}
	else {
		for (int i = start; i < end; i++) {
			//if the rating is smaller or equal than rating at pivot
			if (tutor[i].rating <= tutor[pivot].rating) {
				//we swap the tutor record with the partition index
				swap(tutor[i], tutor[pIndex]);
				pIndex++; //after swapping pindex will increment to the next index
			}
		}
	}

	//now pindex which is bigger than pivot will swap with pivot so that it is between smaller and larger numbers
	swap(tutor[pIndex], tutor[pivot]);
	return pIndex;//now pIndex is where pivot is
	return 0;
}


//sending the array, the start of the array and the end and returning the index of the pivot
void quickSort(struct Tutor* tutor, int start, int end, int type) {


	//using pivot: first assign pivot. all item to left are smaller than pivot and right are larger
	//after sorting, we have left (smaller items) and right (bigger items) -subarrays
	//recurse partinoning until there is only 1 element left

	//if segment has one element left or no segment

	if (start < end) {
		int partitionIndex = partition(tutor, start, end, type);
		//recursion
		//sort segment left (of current pivot)
		quickSort(tutor, start, partitionIndex - 1, type);
		//sort segment right (of current pivot)
		quickSort(tutor, start + 1, end, type);
	}
}

void sortByID() {	//sorting tutor ID function
	insertionSort(tutor, tutorNo);
	printInfo(tutor, tutorNo);
	getchar();
	displayTutor();
}

void sortByRating() {		//sorting tutor rating
	quickSort(tutor, 0, tutorNo - 1, 2);
	printInfo(tutor, tutorNo);
	getchar();
	displayTutor();
}

void sortByHourlyPay() {	//sorting tutor hourly pay rate
	quickSort(tutor, 0, tutorNo - 1, 1);
	printInfo(tutor, tutorNo);
	displayTutor();
}

int main() {	//main function to read file and start the system
	readFile();
	menu();
	return 0;
}
//sorting sequence might affect the way of tutor info writing into file
//better sort id before exit the system