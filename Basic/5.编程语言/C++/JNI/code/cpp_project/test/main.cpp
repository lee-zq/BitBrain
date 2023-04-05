#include <iostream>
#include "c_api.h"

using namespace std;

int main() {
    void* student = create_student("张三", 18, 100);
    print_student(student);
    cout << "1.get student age: "<<get_student_age(student) << endl;
    set_student(student, "李四", 20, 99);
    print_student(student);
    cout << "2.get student age: "<< get_student_age(student) << endl;
    return 0;
}
