#include "c_api.h"
#include "student.h"
INSTPTR create_student(const char * name, int age, int score) {
    return new Student(name, age, score);
}


// 打印学生信息
void print_student(INSTPTR student) {
    Student* handle = (Student*)student;
    handle->print();
}

// 获取学生年龄信息
int get_student_age(INSTPTR student) {
    Student* handle = (Student*)student;
    return handle->get_age();
}

// 修改学生信息

void set_student(INSTPTR student, const char * name, int age, int score) {
    Student* handle = (Student*)student;
    handle->set(name, age, score);
}
