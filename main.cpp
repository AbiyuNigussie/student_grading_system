#include <iostream>
#include <sstream>
#include <string.h>
#include <bits/stdc++.h>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

void getGradeReport(string studs[][12], int &curStuds);
void CalculateGrade(float results[], string stud[], int &curStuds, string studs[][12]);
void displayClassTable(string sec, int curStuds, string studs[][12]);
void displayStudTable(int curStuds, string id, string studs[][12]);
void removeDuplicateSecs(int curStuds, string studs[][12], string (&sects)[], int &secslen);
void saveRecord(string studs[][12], int curStuds);
void readRecord(int &curStud, string studs[][12]);

int main()
{
    float results[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int opt;
    int currentStuds = 0;
    bool loop = true;
    string student[12];
    string students[200][12];

    while (loop)
    {
        readRecord(currentStuds, students);
        system("cls");
        cout << "*********************** STUDENT GRADING SYSTEM ***************************" << endl;
        cout << "     1. Get Grade Report\n     2. Calculate Grade\n     3. Exit";
        cout << "\nPlease Enter your option: ";
        cin >> opt;
        switch (opt)
        {
        case 1:
            getGradeReport(students, currentStuds);
            break;
        case 2:
            CalculateGrade(results, student, currentStuds, students);
            break;
        case 3:
            loop = false;
        }
    }
}

void CalculateGrade(float results[], string stud[], int &curStuds, string studs[][12])
{
    string firstName, lastName;
    system("cls");
    cout << "# Notice: This Menu helps u to calculate a Student Grade\n"
         << endl;
    cout << "\nFirst Name: ";
    cin >> firstName;
    cout << "Last Name: ";
    cin >> lastName;
    stud[0] = firstName + " " + lastName;
    cout << "ID: ";
    cin >> stud[1];
    cout << "Section: ";
    cin >> stud[2];

    cout << "\n# Please fill out the subject values(100%)\n"
         << endl;

    cout << "\nMathimatics: ";
    cin >> results[0];
    cout << "English: ";
    cin >> results[1];
    cout << "Physics: ";
    cin >> results[2];
    cout << "Biology: ";
    cin >> results[3];
    cout << "Chemistry: ";
    cin >> results[4];
    cout << "Civic: ";
    cin >> results[5];
    cout << "Amharic: ";
    cin >> results[6];
    for (int i = 0; i <= 6; i++)
    {
        results[7] += results[i];
    }
    results[8] = results[7] / 7;
    for (int i = 0; i <= 8; i++)
    {
        stringstream stream;
        stream << results[i];
        stream >> stud[i + 3];
    }
    results[7] = 0;
    for (int i = 0; i <= 11; i++)
    {
        transform(stud[i].begin(), stud[i].end(), stud[i].begin(), ::toupper);
        studs[curStuds][i] = stud[i];
    }

    curStuds += 1;
    saveRecord(studs, curStuds);
    cout << "\nRecord Successfully Added!\n"
         << endl;
    system("pause");
}

void getGradeReport(string studs[][12], int &curStuds)
{
    system("cls");
    int opt;
    int secslen;
    string id;
    string sections[curStuds];

    cout
        << "\n     1. Class Grade report" << endl;
    cout << "     2. Student Grade report\n"
         << endl;
    cout << "\nPlease choose from the options: ";
    cin >> opt;
    system("cls");

    switch (opt)
    {
    case 1:
        removeDuplicateSecs(curStuds, studs, sections, secslen);
        if (secslen == 0)
        {
            cout << "No Section Available...\n\n";
        }
        else
        {
            cout << "# Available Sections\n"
                 << endl;
            for (int i = 0; i < secslen; i++)
            {
                cout << "     " << i + 1 << ". " << sections[i] << endl;
            }

            cout << "choose section: ";
            cin >> opt;
            displayClassTable(sections[opt - 1], curStuds, studs);
        }

        system("pause");
        break;
    case 2:
        cout << "\nPlease Enter ID: ";
        cin >> id;
        displayStudTable(curStuds, id, studs);
    }
}

void removeDuplicateSecs(int curStuds, string studs[][12], string (&sects)[], int &secslen)
{
    int i, j, k, n = curStuds;
    string arr[curStuds];
    for (int q = 0; q < n; q++)
    {
        arr[q] = studs[q][2];
    }

    for (i = 0; i < n; ++i)
        for (j = i + 1; j < n;)
        {
            if (arr[i] == arr[j])
            {
                for (k = j; k < n - 1; ++k)
                    arr[k] = arr[k + 1];
                --n;
            }
            else
                ++j;
        }
    for (int k = 0; k < n; k++)
    {
        sects[k] = arr[k];
    }
    secslen = n;
}

void displayClassTable(string sec, int curStuds, string studs[][12])
{
    string cols[] = {"NAME", "ID", "TOTAL", "AVERAGE"};
    cout << "\n************************ SECTION " << sec << " RESULT ************************\n"
         << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << left << setw(20) << cols[i];
    }
    cout << "\n"
         << endl;
    for (int i = 0; i < curStuds; i++)
    {

        if (studs[i][2] != sec)
            continue;
        cout << left << setw(20) << studs[i][0] << setw(20) << studs[i][1] << setw(20) << studs[i][10] << setw(20) << studs[i][11] << "\n"
             << endl;
    }
}

void displayStudTable(int curStuds, string id, string studs[][12])
{
    string firstColumn[9] = {"Mathimatics", "English", "Physics", "Biology", "Chemistry", "Civic", "Amharic", "Total", "Average"};
    bool match = false;
    transform(id.begin(), id.end(), id.begin(), ::toupper);
    for (int i = 0; i < curStuds; i++)
    {
        if (id != studs[i][1])
        {
            continue;
        }
        cout << "\nName: " << studs[i][0] << endl;
        cout << "ID: " << studs[i][1] << endl;
        cout << "Section: " << studs[i][2] << "\n"
             << endl;
        cout << "******* RESULT *******\n"
             << endl;
        for (int i = 3; i < 12; i++)
        {
            cout << left << setw(20) << firstColumn[i - 3] << setw(20) << studs[0][i] << endl;
            cout << endl;
        }
        match = true;
    }
    if (!match)
    {
        cout << "ID not Found!\n"
             << endl;
    }
    system("pause");
}

void saveRecord(string studs[][12], int curStuds)
{
    string text = "";
    for (int i = 0; i < curStuds; i++)
    {
        for (int x = 0; x < 12; x++)
        {
            text += " " + studs[i][x];
        }
        text += "\n";
    }
    ofstream save;
    save.open("records.txt");
    save << text;
    save.close();
}

void readRecord(int &curStuds, string studs[][12])
{
    string line;
    string word;
    int x = 0;
    int temp = 0;
    int line_len = 0;
    vector<string> lines;

    fstream read;
    read.open("records.txt", ios::in);
    while (getline(read, line))
    {
        lines.push_back(line);
        line_len++;
    }
    curStuds = line_len;

    for (int i = 0; i < line_len; i++)
    {
        stringstream ss(lines[i]);
        while (ss >> word)
        {
            if (temp == 1)
            {
                studs[i][temp - 1] += " " + word;
                temp++;
                continue;
            }
            studs[i][x] = word;
            x++;
            temp++;
        }
        x = 0;
        temp = 0;
    }
}