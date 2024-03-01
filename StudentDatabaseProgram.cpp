#include <iostream>
using namespace std;

struct Student 
{
    Student *next = NULL;
    Student *prev = NULL ;

    string firstName;
    string lastName;
    int year;
    string section;
    string course;
};

void MainMenu(int& choice, int& currentPage);
Student* AddNewStudent();
void DisplayStudent(Student* head, Student* temp, int pageSize, int& currentPage);
void UpdateStudent(Student* head, int position);
void DeleteStudent(Student*& head, int position);

int main()
{
    int choice;
    int studentCount = 0;
    int position = 1;
    int pageSize = 5;
    int currentPage = 1;
    Student* head = NULL;
    Student* tail = NULL;
    Student* temp = NULL;

    do {
        MainMenu(choice, currentPage);
        switch(choice)
        {
            case 1:
                temp = AddNewStudent();
                if (studentCount) 
                {
                temp->prev = tail;
                temp->next = NULL;
                tail->next = temp;
                tail = temp;
                }
                else 
                {
                head = temp;
                head->prev = NULL;
                head->next = NULL;
                tail = head;
                }
                studentCount++;
                break;

            case 2:
                cout << "Read\n";
                DisplayStudent(head, temp, pageSize, currentPage);
                break;

            case 3:
                cout << "Update\n";
                UpdateStudent(head, 1);
                break;

            case 4:
                cout << "Delete\n";
                cout << "Enter the position of the student to delete: ";
                cin >> position;
                DeleteStudent(head, position);
                studentCount--;
                break;

            case 5:
                cout << "Exiting...\n";
                exit(0);
                break;

            default:
                break;
        }
    } while(true);
}

void MainMenu(int& choice, int& currentPage) 
{
    cout << "=============================\n";
    cout << "        STUDENT DATABASE      \n";
    cout << "=============================\n";
    cout << "1. Add Student\n";
    cout << "2. Check Student\n";
    cout << "3. Update Student\n";
    cout << "4. Delete Student\n";
    cout << "5. Exit\n";
    cout << "=============================\n";
    cout << "Enter your choice: ";
    cin >> choice;

    system("cls");
}

Student* AddNewStudent() 
{
    Student* studentInformation;
    studentInformation = new Student;
    cout << "-- Student Information Form --\n\n";
    
    cin.ignore();

    cout << "First Name: ";
    getline(cin, studentInformation->firstName);

    cout << "Last Name: ";
    getline(cin, studentInformation->lastName);

    while ((cout << "Student Year: ") && !(cin >> studentInformation->year)) 
    {
        cout << "Invalid input. Please enter a valid number for the year.\n";
        cin.clear();
        while (cin.get() != '\n');
    }

    cout << "Section: ";
    cin >> studentInformation->section;

    cout << "Course: ";
    cin >> studentInformation->course;

    studentInformation->next = nullptr;
    studentInformation->prev = nullptr;

    system("cls");

    cout << "Student added successfully!\n";

    return studentInformation;
}

void DisplayStudent(Student* head, Student* temp, int pageSize, int& currentPage) 
{
    int count = 0;
    int startIndex = (currentPage - 1) * pageSize;
    char choice;
    system("cls");

    temp = head;

    cout << "=============================\n";
    cout << "        DISPLAY STUDENT      \n";
    cout << "=============================\n";
    
    cout << "Current Page: " << currentPage << endl;
    cout << "========================================================================\n";

    for (int i = 0; i < startIndex && temp != nullptr; ++i)
    {
        temp = temp->next;
    }

    while (temp != nullptr && count < pageSize)
    {
        cout << "Student Number " << count + startIndex + 1 << ":\n";
        cout << "First Name: " << temp->firstName << endl;
        cout << "Last Name: " << temp->lastName << endl;
        cout << "Year: " << temp->year << endl;
        cout << "Section: " << temp->section << endl;
        cout << "Course: " << temp->course << endl;
        cout << "========================================================================\n";
        temp = temp->next;
        count++;
    }

    cout << "Press 'b' to go back..." << endl;
    cout << "Press 'n' to view the next page..." << endl;
    cout << "Press 'q' to go back..." << endl;
    cin >> choice;
    system("cls");

    switch (choice)
    {
        case 'b':
            if (currentPage > 1)
            {
                currentPage--;
            }
            break;
        case 'n':
            currentPage++;
            break;
        case 'q':
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }

    DisplayStudent(head, head, pageSize, currentPage);
}


void UpdateStudent(Student* head, int position) 
{
    int count = 1;
    Student* temp = head;

    while (temp != NULL && count < position) 
    {
        temp = temp->next;
        count++;
    }

    if (temp == NULL) {
        cout << "Invalid position. No student found at position " << position << endl;
        return;
    }

    cout << "-- Update Student Information --\n\n";
    cout << "Enter the position of the student to update: ";
    cin >> position;

    count = 1;
    temp = head;
    while (temp != NULL && count < position) 
    {
        temp = temp->next;
        count++;
    }

    if (temp == NULL) {
        cout << "Invalid position. No student found at position " << position << endl;
        return;
    }

    cin.ignore(); 

    cout << "First Name: ";
    getline(cin, temp->firstName);

    cout << "Last Name: ";
    getline(cin, temp->lastName);


    while ((cout << "Student Year: ") && !(cin >> temp->year)) 
    {
        cout << "Invalid input. Please enter a valid number for the year.\n";
        cin.clear();
        while (cin.get() != '\n');
    }

    cout << "Section: ";
    cin >> temp->section;

    cout << "Course: ";
    cin >> temp->course;

    cout << "Student information updated successfully!\n";
}

void DeleteStudent(Student*& head, int position)
{
    Student* temp = head;
    int count = 1;

    if (head == NULL) {
        cout << "No students in the database." << endl;
        return;
    }

    while (temp != NULL && count < position) 
    {
        temp = temp->next;
        count++;
    }

    if (temp == NULL) {
        cout << "Invalid position. No student found at position " << position << endl;
        return;
    }

    if (temp == head) 
    {
        head = temp->next;
        if (head != NULL) 
        {
            head->prev = NULL;
        }
        delete temp;
    } else if (temp->next == NULL) 
    {
        temp->prev->next = NULL;
        delete temp;
    } else 
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
    }

    cout << "Student at position " << position << " has been deleted." << endl;
}