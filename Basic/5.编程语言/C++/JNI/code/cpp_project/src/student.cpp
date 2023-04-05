#include <iostream>
#include "student.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 打印学生信息
void Student::print() {
    cout << "name: " << name << ", age: " << age << ", score: " << score << endl;
}

// 获取学生信息
int Student::get_age() {
    return age;
}

// 修改学生信息
void Student::set(string name, int age, int score) {
    this->name = name;
    this->age = age;
    this->score = score;
}
