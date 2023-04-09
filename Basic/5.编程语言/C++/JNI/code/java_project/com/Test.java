package com;
// 创建一个java类，名为Test，包含对应的main方法
import com.Student;
public class Test {
    public static void main(String[] args) {
        System.out.println("Unit Test!");
        com.Student student = new com.Student();
        long stu = student.create_student("lzq", 21, 100);
        student.print_student(stu);
        System.out.println("1.age: " + student.get_student_age(stu));
        student.set_student(stu, "gyq", 18, 59);
        
        student.print_student(stu);
        System.out.println("2.age: " + student.get_student_age(stu));

        StudentInfo student_info = new StudentInfo();
        System.out.println("复杂接口测试：");
        student_info.print_student_info();
        student.update_student_info(stu, student_info);
        student_info.print_student_info();

        // while(true) {
        //     student.update_student_info(stu, student_info);
        // }
        System.out.println("Unit Test End!");
    }
}