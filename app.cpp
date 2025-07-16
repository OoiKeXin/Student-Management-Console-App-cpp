#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(const char *, BST *);
int menu();

int main() 
{
	const char* filename = "student.txt";
	BST t1, t2;
	Student s1;
	int id;
	int height = 0;
	int cont = 1;
	int order, source;
	while (cont == 1)
	{
		system("cls");
		int choice = menu();
		switch (choice)
		{
		case 1:
			if (readFile(filename, &t1))
				cout << "Successfully read." << endl << endl;
			else
				cout << "Cannot read in the student.txt." << endl << endl;
			break;
		
		case 2:
			if (t1.deepestNodes())
				cout << "\nSuccessfully displayed.\n\n";
			else
				cout << "\nEmpty tree.\n\n";
			break;
		
		case 3:
			cout << endl;
			cout << "Where do you want to print in ascending or descending order according to id (1 - Ascending / 2 - Descending): ";
			cin >> order;
			cout << endl;
			cout << "Where do you want to print the output? (1 - Print to screen / 2 - Print to file): ";
			cin >> source;
			cout << endl;

			if (t1.display(order, source))
				cout << "\nSuccessfully display output.\n" << endl;
			else
				cout << "\nUnable to display output.\n" << endl;

			break;
		
		case 4:
			cout << "Please enter the student ID: ";
			cin >> id;
			s1.id = id;
			if (t2.CloneSubtree(t1, s1))
			{
				cout << "\n\nClone successfully.\n\n";
			}

			else
				cout << "Cannot clone the subtree." << endl;
			break;
		
		case 5:
			if (t1.printLevelNodes())
				cout << "\nDisplayed the nodes in level." << endl << endl;
			else
				cout << "The tree is empty." << endl << endl;
			break;
		
		case 6:
			if (t1.printPath())
				cout << "\nDisplayed the external path." << endl << endl;
			else
				cout << "Tree is empty." << endl << endl;
			break;
		
		default:
			break;
		}
		cout << "Do you want to continue? (0 - NO, 1 - YES): ";
		cin >> cont;
	}

	system("pause");
	return 0;
}

bool readFile(const char* filename, BST* t1)
{
	char c[20];
	Student student;
	fstream inFile;
	inFile.open("Student.txt");

	if (!inFile.is_open()) 
	{
		cout << "Failed to open file." << endl;
		return false;
	}

	if (inFile.is_open())
	{
		int count = 0;
		while (inFile >> c && c != " ")
		{
			// Assuming the file structure is in a fixed format
			inFile >> c >> c;	// Skip labels or extra text
			inFile >> student.id;
			inFile >> c >> c;
			inFile.getline(student.name, 30);
			inFile >> c >> c;
			inFile.getline(student.address, 100);
			inFile >> c >> c;
			inFile >> student.DOB;
			inFile >> c >> c >> c;
			inFile >> student.phone_no;
			inFile >> c >> c;
			inFile >> student.course;
			inFile >> c >> c;
			inFile >> student.cgpa;
			if (!t1->empty())
			{
				if (t1->searching(student))
					cout << "Duplication found." << endl;
				else
				{
					t1->insert(student);
					count++;
				}
			}
			else
			{
				t1->insert(student);
				count++;
			}
		}
		cout << endl;
		cout << count << " number of student records successfully read." << endl << endl;
		return true;
	}
	else
		return false;
}

int menu()
{
	int choice;
	cout << "(1) Read Data to BST" << '\n';
	cout << "(2) Print Deepest Nodes" << "\n";
	cout << "(3) Display Student" << "\n";
	cout << "(4) Clone Subtree" << "\n";
	cout << "(5) Print Level Nodes" << "\n";
	cout << "(6) Print Path" << "\n";
	cout << "(7) Exit" << "\n";
	cout << "Enter a number: ";
	cin >> choice;
	return choice;
}