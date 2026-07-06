#include <iostream>
#include <vector>


using namespace std;

// 6. Refactoring
// process of changing a software system in such a way it does not alter the external behavior of code 
// yet it improves the internal structure
// also its making changes to a body of code to improve its internal structure without changing its external behavior


#include <iostream>
#include <vector>
#include <string>
#include <numeric> // For std::accumulate

using namespace std;

class GradeReporter {
public:
    void printReport(const vector<string>& students, const vector<int>& grades) {
        printDivider();
        cout << "      STUDENT GRADE REPORT    " << endl;
        printDivider();

        printStudentGrades(students, grades);

        printDivider();
        cout << "Class Average: " << calculateAverage(grades) << endl;
        printDivider();
    }

private:
    // Refactored out duplicated code into a reusable function
    void printDivider() {
        cout << "==============================" << endl;
    }

    // Refactored calculation logic away from presentation logic
    double calculateAverage(const vector<int>& grades) {
        if (grades.empty()) return 0.0;
        
        // Using a safe, modern algorithm instead of a manual loop
        double sum = accumulate(grades.begin(), grades.end(), 0.0);
        return sum / grades.size();
    }

    // Refactored the printing loop into its own focused method
    void printStudentGrades(const vector<string>& students, const vector<int>& grades) {
        for (size_t i = 0; i < students.size(); ++i) {
            cout << students[i] << ": " << grades[i] << endl;
        }
    }
};

int main() {
    vector<string> students = {"Alice", "Bob", "Charlie"};
    vector<int> grades = {85, 92, 78};

    GradeReporter reporter;
    reporter.printReport(students, grades);

    return 0;
}


/* 
------------------------------------------------------------
   code before refactoring:
-------------------------------------------------------------

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<string> students = {"Alice", "Bob", "Charlie"};
    vector<int> grades = {85, 92, 78};

    // Calculate average and print report
    cout << "==============================" << endl;
    cout << "      STUDENT GRADE REPORT    " << endl;
    cout << "==============================" << endl;

    double total = 0;
    for (size_t i = 0; i < grades.size(); i++) {
        cout << students[i] << ": " << grades[i] << endl;
        total += grades[i];
    }

    cout << "==============================" << endl;
    double average = total / grades.size();
    cout << "Class Average: " << average << endl;
    cout << "==============================" << endl;

    return 0;
}




*/