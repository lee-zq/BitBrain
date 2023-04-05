#include "com_Student.h"
#include "c_api.h"

/*
 * Class:     com_Student
 * Method:    create_student
 * Signature: (Ljava/lang/String;II)J
 */
JNIEXPORT jlong JNICALL Java_com_Student_create_1student
  (JNIEnv * env, jobject obj, jstring name, jint age, jint score){
    const char* c_name = env->GetStringUTFChars(name, 0);
    INSTPTR student = create_student(c_name, age, score);
    return (jlong)student;
  }

/*
 * Class:     com_Student
 * Method:    print_student
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_Student_print_1student
  (JNIEnv * env, jobject obj, jlong student){
    INSTPTR handle = (INSTPTR)student;
    print_student(handle);
  }

/*
 * Class:     com_Student
 * Method:    get_student_age
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_Student_get_1student_1age
  (JNIEnv * env, jobject, jlong student){
    INSTPTR handle = (INSTPTR)student;
    return get_student_age(handle);
  }

/*
 * Class:     com_Student
 * Method:    set_student
 * Signature: (JLjava/lang/String;II)V
 */
JNIEXPORT void JNICALL Java_com_Student_set_1student
  (JNIEnv * env, jobject obj, jlong student, jstring name, jint age, jint score){
    INSTPTR handle = (INSTPTR)student;
    const char* c_name = env->GetStringUTFChars(name, 0);
    set_student(handle, c_name, age, score);
  }
