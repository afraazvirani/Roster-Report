//
// Name: Afraaz Virani
// Date: 6/18/26
// Course: COSC 1437 C++ Programming Fundamentals II
// Desc: Chapter 8 Lab - Roster Report Management
//

// Part 1 - Data Storage Constants & Structures
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

const int MAX_STUDENTS = 10;
const int NUM_TESTS = 4;


void readRoster(char names[][31], int scores[][NUM_TESTS], int& count);

void calcAverages(const int scores[][NUM_TESTS], double averages[], char grades[], int count); 

void sortRoster(char names[][31], int scores[][NUM_TESTS], double averages[], char grades[], int count);  

int searchRoster(const char names[][31], int count, const char target[]);

void printRoster(const char names[][31], const int scores[][NUM_TESTS], const double averages[], const char grades[], int count);

void printStats(const double averages[], int count); 

int main()
{
    char names[MAX_STUDENTS][31];
    int scores[MAX_STUDENTS][NUM_TESTS];
    double averages[MAX_STUDENTS];
    char grades[MAX_STUDENTS];

    int count = 0;
    int choice;
    char target[31];
    int studentIndex;

    bool rosterLoaded = false;
    bool averagesCalculated = false;

    do
    {
        cout << endl;
        cout << "===== Roster Report Menu =====" << endl;
        cout << "1. Load roster (enter data)" << endl;
        cout << "2. Calculate averages and grades" << endl;
        cout << "3. Sort roster alphabetically" << endl;
        cout << "4. Search for a student" << endl;
        cout << "5. Print roster" << endl;
        cout << "6. Print class statistics" << endl;
        cout << "7. Quit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 7)
        {
            cout << "Invalid choice. Please enter 1-7: ";

            cin.clear();
            cin.ignore(1000, '\n');

            cin >> choice;
        }

        if (choice == 1)
        {
            readRoster(names, scores, count);
            rosterLoaded = true;
            averagesCalculated = false;
        }

        else if (choice == 2)
        {
            if (rosterLoaded == true)
            {
                calcAverages(scores, averages, grades, count);
                averagesCalculated = true;
            }

            else
            {
                cout << "Please load the roster first." << endl;
            }
        }

        else if (choice == 3)
        {
            if (rosterLoaded == true)
            {
                sortRoster(names, scores, averages, grades, count);
            }

            else
            {
                cout << "Please load the roster first." << endl;
            }
        }

        else if (choice == 4)
        {
            if (rosterLoaded == true)
            {
                cin.ignore(1000, '\n');

                cout << "Enter student name to search: ";
                cin.getline(target, 31);

                studentIndex = searchRoster(names, count, target);

                if (studentIndex != -1)
                {
                    cout << "Student found at index: " << studentIndex << endl;
                    cout << "Student Name: " << names[studentIndex] << endl;
                }

                else
                {
                    cout << "Student was not found." << endl;
                }
            }

            else
            {
                cout << "Please load the roster first." << endl;
            }
        }

        else if (choice == 5)
        {
            if (rosterLoaded == true && averagesCalculated == true)
            {
                printRoster(names, scores, averages, grades, count);
            }

            else
            {
                cout << "Please load the roster and calculate averages first." << endl;
            }
        }

        else if (choice == 6)
        {
            if (rosterLoaded == true && averagesCalculated == true)
            {
                printStats(averages, count);
            }

            else
            {
                cout << "Please load the roster and calculate averages first." << endl;
            }
        }

        else if (choice == 7)
        {
            cout << endl;
            cout << "Goodbye!" << endl;
        }

    } while (choice != 7);

    return 0;
}

// Part 2a - readRoster
void readRoster(char names[][31], int scores[][NUM_TESTS], int& count)
{
    cout << "Enter number of students (1-10): ";
    cin >> count;

    while (cin.fail() || count < 1 || count > MAX_STUDENTS)
    {
        cout << "Invalid number. Enter number of students (1-10): ";
        
        cin.clear();
        cin.ignore(1000, '\n');

        cin >> count;
    }

    cin.ignore(1000, '\n');

    for (int i = 0; i < count; i = i + 1)
    {
        cout << endl;
        cout << "Enter name for student " << i + 1 << ": ";
        cin.getline(names[i], 31);

        for (int j = 0; j < NUM_TESTS; j = j + 1)
        {
            cout << "Enter test score " << j + 1 << " for " << names[i] << ": ";
            cin >> scores[i][j];

            while (cin.fail() || scores[i][j] < 0 || scores[i][j] > 100)
            {
                cout << "Invalid score. Enter score from 0 to 100: ";
                
                cin.clear();
                cin.ignore(1000, '\n');

                cin >> scores[i][j];
            }
        }

        cin.ignore(1000, '\n');
    }
}

// Part 2b - calcAverages
void calcAverages(const int scores[][NUM_TESTS], double averages[], char grades[], int count) 
{
    int total;

    for (int i = 0; i < count; i = i + 1)
    {
        total = 0;

        for (int j = 0; j < NUM_TESTS; j = j + 1)
        {
            total = total + scores[i][j];
        }

        averages[i] = static_cast<double>(total) / NUM_TESTS;

        if (averages[i] >= 90)
        {
            grades[i] = 'A';
        }

        else if (averages[i] >= 80)
        {
            grades[i] = 'B';
        }

        else if (averages[i] >= 70)
        {
            grades[i] = 'C';
        }

        else if (averages[i] >= 60)
        {
            grades[i] = 'D';
        }

        else
        {
            grades[i] = 'F';
        }
    }

    cout << "Averages and grades calculated." << endl;
}

// Part 2c - sortRoster (Selection Sort)
void sortRoster(char names[][31], int scores[][NUM_TESTS], double averages[], char grades[], int count)
{
    int minIndex;

    char tempName[31];
    int tempScore;
    double tempAverage;
    char tempGrade;

    for (int start = 0; start < count - 1; start = start + 1)
    {
        minIndex = start;

        for (int i = start + 1; i < count; i = i + 1)
        {
            if (strcmp(names[i], names[minIndex]) < 0)
            {
                minIndex = i;
            }
        }

        if (minIndex != start)
        {
            strcpy(tempName, names[start]);
            strcpy(names[start], names[minIndex]);
            strcpy(names[minIndex], tempName);

            for (int j = 0; j < NUM_TESTS; j = j + 1)
            {
                tempScore = scores[start][j];
                scores[start][j] = scores[minIndex][j];
                scores[minIndex][j] = tempScore;
            }

            tempAverage = averages[start];
            averages[start] = averages[minIndex];
            averages[minIndex] = tempAverage;

            tempGrade = grades[start];
            grades[start] = grades[minIndex];
            grades[minIndex] = tempGrade;
        }
    }

    cout << "Roster sorted alphabetically." << endl;
}

// Part 2d - searchRoster (Sequential Search)
int searchRoster(const char names[][31], int count, const char target[])
{
    for (int i = 0; i < count; i = i + 1)
    {
        if (strcmp(names[i], target) == 0)
        {
            return i;
        }
    }

    return -1;
}

// Part 2e - printRoster
void printRoster(const char names[][31], const int scores[][NUM_TESTS], const double averages[], const char grades[], int count)  
{
    cout << fixed << setprecision(2);

    cout << endl;
    cout << "============================ Roster Report ============================" << endl;

    cout << left << setw(20) << "Name";
    cout << left << setw(8) << "Test 1";
    cout << left << setw(8) << "Test 2";
    cout << left << setw(8) << "Test 3";
    cout << left << setw(8) << "Test 4";
    cout << right << setw(8) << "Average";
    cout << right << setw(8) << "Grade" << endl;

    cout << "-----------------------------------------------------------------------" << endl;

    for (int i = 0; i < count; i = i + 1)
    {
        cout << left << setw(20) << names[i];

        for (int j = 0; j < NUM_TESTS; j = j + 1)
        {
            cout << left << setw(8) << scores[i][j];
        }

        cout << right << setw(8) << averages[i];
        cout << right << setw(8) << grades[i] << endl;
    }

    cout << "-----------------------------------------------------------------------" << endl;
}


// Part 2f - printStats
void printStats(const double averages[], int count)
{
    double validAverages[MAX_STUDENTS]; //local copy of the valid data
    double highScore;
    double lowScore;
    double total;
    double classAverage;
    int processedStudents;

    for (int i = 0; i < count; i = i + 1)
    {
        validAverages[i] = averages[i];
    }

    highScore = validAverages[0];
    lowScore = validAverages[0];
    total = 0.0;
    processedStudents = 0;

    for (auto average : validAverages)
    {
        if (processedStudents == count)     // processedStudents is how many enteries/students we have processed yet, while count is how many students were initially entered.
        {                                   // this condition makes sure that we only cycle through how many students were entered and not through the entire limit of the array (10).  
            break;
        }

        if (average > highScore)
        {
            highScore = average;
        }

        if (average < lowScore)
        {
            lowScore = average;
        }

        total = total + average;
        processedStudents = processedStudents + 1;
    }

    classAverage = total / count;

    cout << fixed << setprecision(2);

    cout << endl;
    cout << "===== Class Statistics =====" << endl;
    cout << "Class High Average: " << highScore << endl;
    cout << "Class Low Average: " << lowScore << endl;
    cout << "Class Average: " << classAverage << endl;
}