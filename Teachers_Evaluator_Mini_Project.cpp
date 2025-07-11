#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

const int MAX_TEACHERS = 10;
const int PARAMETERS = 3;
const int ALERT_THRESHOLD = 60;

struct TeacherRecord {
    string name;
    string department;
    string date;
    int scores[PARAMETERS];
    double average;
};

void inputTeachers(vector<TeacherRecord>& records, int& teacherCount);
void evaluateTeachers(vector<TeacherRecord>& records, int teacherCount, string parameters[]);
void displayResults(const vector<TeacherRecord>& records, int teacherCount, string parameters[]);
void alertLowPerformers(const vector<TeacherRecord>& records, int teacherCount);
void filterRecords(const vector<TeacherRecord>& records);

int main() {
    vector<TeacherRecord> records;
    string parameters[PARAMETERS] = {"Teaching Quality", "Communication", "Punctuality"};
    int teacherCount = 0;

    cout << "Welcome to the Enhanced Teacher Evaluator Program!\n";

    inputTeachers(records, teacherCount);
    evaluateTeachers(records, teacherCount, parameters);
    displayResults(records, teacherCount, parameters);
    alertLowPerformers(records, teacherCount);
    filterRecords(records);

    return 0;
}

void inputTeachers(vector<TeacherRecord>& records, int& teacherCount) {
    cout << "Enter the number of teachers to evaluate (max " << MAX_TEACHERS << "): ";
    cin >> teacherCount;

    if (teacherCount > MAX_TEACHERS || teacherCount <= 0) {
        cout << "Invalid number of teachers. Exiting program.\n";
        exit(1);
    }

    cin.ignore();
    for (int i = 0; i < teacherCount; i++) {
        TeacherRecord record;
        cout << "Enter the name of teacher " << i + 1 << ": ";
        getline(cin, record.name);
        cout << "Enter the department of " << record.name << ": ";
        getline(cin, record.department);
        cout << "Enter the evaluation date (e.g., YYYY-MM-DD): ";
        getline(cin, record.date);

        records.push_back(record);
    }
}

void evaluateTeachers(vector<TeacherRecord>& records, int teacherCount, string parameters[]) {
    cout << "\nTeacher Evaluation (Scores from 0 to 100):\n";
    for (int i = 0; i < teacherCount; i++) {
        cout << "\nEvaluating " << records[i].name << " (" << records[i].department << " on " << records[i].date << "):\n";
        int totalScore = 0;
        for (int j = 0; j < PARAMETERS; j++) {
            do {
                cout << parameters[j] << ": ";
                cin >> records[i].scores[j];
                if (records[i].scores[j] < 0 || records[i].scores[j] > 100) {
                    cout << "Invalid score. Please enter a score between 0 and 100.\n";
                }
            } while (records[i].scores[j] < 0 || records[i].scores[j] > 100);
            totalScore += records[i].scores[j];
        }
        records[i].average = static_cast<double>(totalScore) / PARAMETERS;
    }
}

void displayResults(const vector<TeacherRecord>& records, int teacherCount, string parameters[]) {
    cout << "\nEvaluation Results:\n";
    cout << left << setw(20) << "Teacher" << setw(20) << "Department" << setw(15) << "Date";
    for (int j = 0; j < PARAMETERS; j++) {
        cout << setw(20) << parameters[j];
    }
    cout << setw(15) << "Average" << endl;
    for (int i = 0; i < teacherCount; i++) {
        cout << left << setw(20) << records[i].name << setw(20) << records[i].department << setw(15) << records[i].date;
        for (int j = 0; j < PARAMETERS; j++) {
            cout << setw(20) << records[i].scores[j];
        }
        cout << setw(15) << fixed << setprecision(2) << records[i].average << endl;
    }
}

void alertLowPerformers(const vector<TeacherRecord>& records, int teacherCount) {
    cout << "\nLow-Performance Alert (Scores below " << ALERT_THRESHOLD << "):\n";
    bool found = false;
    for (int i = 0; i < teacherCount; i++) {
        if (records[i].average < ALERT_THRESHOLD) {
            cout << records[i].name << " from " << records[i].department << " scored an average of "
                 << fixed << setprecision(2) << records[i].average << ".\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No teachers scored below the threshold.\n";
    }
}

void filterRecords(const vector<TeacherRecord>& records) {
    cout << "\nFilter Records:\n";
    cout << "1. By Department\n2. By Date\n3. By Performance Score\n";
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    cin.ignore();
    switch (choice) {
        case 1: {
            string department;
            cout << "Enter department: ";
            getline(cin, department);
            cout << "\nTeachers in " << department << ":\n";
            for (const auto& record : records) {
                if (record.department == department) {
                    cout << record.name << " (Average Score: " << fixed << setprecision(2) << record.average << ")\n";
                }
            }
            break;
        }
        case 2: {
            string date;
            cout << "Enter date (YYYY-MM-DD): ";
            getline(cin, date);
            cout << "\nTeachers evaluated on " << date << ":\n";
            for (const auto& record : records) {
                if (record.date == date) {
                    cout << record.name << " (Average Score: " << fixed << setprecision(2) << record.average << ")\n";
                }
            }
            break;
        }
        case 3: {
            double minScore;
            cout << "Enter minimum performance score: ";
            cin >> minScore;
            cout << "\nTeachers with performance scores above " << minScore << ":\n";
            for (const auto& record : records) {
                if (record.average >= minScore) {
                    cout << record.name << " (Average Score: " << fixed << setprecision(2) << record.average << ")\n";
                }
            }
            break;
        }
        default:
            cout << "Invalid choice.\n";
    }
}