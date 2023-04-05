#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 用于存储所有的学生信息的类
class Student {
public:
    string name;
    int age;
    int score;
    Student(string name, int age, int score) {
        this->name = name;
        this->age = age;
        this->score = score;
    }
    // 打印学生信息
    void print() ;
    // 获取学生信息
    int get_age() ;
    // 修改学生信息
    void set(string name, int age, int score);
};

