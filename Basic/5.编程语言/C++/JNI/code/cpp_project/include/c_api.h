#include "string.h"

typedef void* INSTPTR;

typedef struct{
    int area;
    int block;
    int house_num;
} Address;

typedef struct StudentInfo
{
    char name[32];
    int id;
    int age;
    int score;
    int schedule[5][6]; //课程表 一周5天每天6节课；语1，数2，外3，物4，化5，体6
    Address address[3]; // 3个常用家庭住址
} StudentInfo;

// c++库导出c接口
extern "C"
{
    INSTPTR create_student(const char *name, int age, int score);
    // 打印学生信息
    void print_student(INSTPTR student);
    // 获取学生信息
    int get_student_age(INSTPTR student);
    // 修改学生信息
    void set_student(INSTPTR student, const char *name, int age, int score);


    // 独立接口，测试JNI传入复杂结构体并修改后返回的情况
    void update_student_info(INSTPTR student, StudentInfo * student_info);
};
