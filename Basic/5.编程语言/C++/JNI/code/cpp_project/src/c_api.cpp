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

// 使用student信息更新student_info
void update_student_info(INSTPTR student, StudentInfo* student_info) {
    Student* handle = (Student*)student;
    strcpy(student_info->name, handle->name.c_str());
    student_info->age = handle->age;
    student_info->score = handle->score;
    // 根据score设置课程表，简单实现用于测试，按照得分情况每门课都设置一个int值

    int class_num = 0;
    if (student_info->score < 60) //不及格
    {
        class_num = 6;
    }else if(student_info->score <= 80){ //良好
        class_num = 4;
    }else if(student_info->score < 95){ //优秀
        class_num = 2;
    }else{ // 牛逼
        class_num = 1;
    }
    // 确定安排课程数量
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < class_num; j++) {
            student_info->schedule[i][j] = 1;
        }
    }

    // 设置虚拟家庭住址
    for (size_t i = 0; i < 3; i++)
    {
        student_info->address[i].area = i*100 + 1;
        student_info->address[i].block = i*100 + 1;
        student_info->address[i].house_num = i*100 + 1;
    }
}