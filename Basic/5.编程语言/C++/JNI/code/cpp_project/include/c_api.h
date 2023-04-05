#include "string.h"

typedef void* INSTPTR;

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
};
