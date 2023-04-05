package com;
public class Student {
    public static void main(String[] args) {
        System.out.println("Hello World!");
    }
    // 加载jni库
    static {
        try {
            System.loadLibrary("jnilib");
        }
        catch(UnsatisfiedLinkError e) {
			System.err.println(">>> Can not load library: " + e.toString());
		}
    }
    // 声明native方法
    public native long create_student(String name, int age, int score);

    public native void print_student(long student);

    public native int get_student_age(long student);

    public native void set_student(long student, String name, int age, int score);
}