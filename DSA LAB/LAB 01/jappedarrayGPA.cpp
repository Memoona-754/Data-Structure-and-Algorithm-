#include <iostream>
using namespace std;

int main() {
    const int numStudents = 5;
    string names[numStudents] = {"Ali", "Hiba", "Asma", "Zain", "Faisal"};
    int courses[numStudents] = {5, 4, 3, 3, 5};   

    float **grades = new float*[numStudents];

    // Allocate each student's row based on their course count
    for (int i = 0; i < numStudents; i++) {
        grades[i] = new float[courses[i]];
    }

    float allGrades[5][5] = {
        {3.66, 3.33, 4.0, 3.0, 2.66},
        {3.33, 3.0, 3.66, 3.0},
        {4.0, 3.66, 2.66},
        {2.66, 2.33, 4.0},
        {3.33, 3.66, 4.0, 3.0, 3.33}
    };
    for (int i = 0; i < numStudents; i++)
        for (int j = 0; j < courses[i]; j++)
            grades[i][j] = allGrades[i][j];

    // Compute and print GPA for each student
    for (int i = 0; i < numStudents; i++) {
        float sum = 0;                          // reset per student
        for (int j = 0; j < courses[i]; j++) {
            sum += grades[i][j];                
        }
        float gpa = sum / courses[i];           
        cout << names[i] << "'s GPA: " << gpa << endl;
    }

    for (int i = 0; i < numStudents; i++)
        delete[] grades[i];
    delete[] grades;

    return 0;
}