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
    if (c_name == NULL) {
        return 0;
    }
    INSTPTR student = create_student(c_name, age, score);
    env->ReleaseStringUTFChars(name, c_name);
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
    if (c_name == NULL) {
        return;
    }
    set_student(handle, c_name, age, score);
    env->ReleaseStringUTFChars(name, c_name);
  }

/*
 * Class:     com_Student
 * Method:    update_student_info
 * Signature: (JLcom/StudentInfo;)V
 */
JNIEXPORT void JNICALL Java_com_Student_update_1student_1info
  (JNIEnv * env, jobject obj, jlong student, jobject student_info){
  // 1. 获取StudentInfo类
  jclass student_info_class = env->GetObjectClass(student_info);
  // 2. 获取StudentInfo类中的name字段
  jfieldID name_field = env->GetFieldID(student_info_class, "name", "Ljava/lang/String;");
  // 3. 获取StudentInfo类中的age字段
  jfieldID age_field = env->GetFieldID(student_info_class, "age", "I");
  // 4. 获取StudentInfo类中的score字段
  jfieldID score_field = env->GetFieldID(student_info_class, "score", "I");
  // 5. 获取StudentInfo类中的schedule字段
  jfieldID schedule_field = env->GetFieldID(student_info_class, "schedule", "[[I");
  // 6. 获取StudentInfo类中的name字段的值
  jstring name = (jstring)env->GetObjectField(student_info, name_field);
  // 7. 获取StudentInfo类中的age字段的值

  // 创建一个C++类型的StudentInfo对象
  StudentInfo student_info_cpp;
  // 将Java类型的StudentInfo对象的值赋值给C++类型的StudentInfo对象
  // 8. 将Java类型的StudentInfo对象的name字段的值赋值给C++类型的StudentInfo对象的name字段
  const char* c_name = env->GetStringUTFChars(name, 0);
  if (c_name == NULL) {
      return;
  }
  strcpy(student_info_cpp.name, c_name);
  env->ReleaseStringUTFChars(name, c_name);
  // 9. 将Java类型的StudentInfo对象的age字段的值赋值给C++类型的StudentInfo对象的age字段
  student_info_cpp.age = env->GetIntField(student_info, age_field);
  // 10. 将Java类型的StudentInfo对象的score字段的值赋值给C++类型的StudentInfo对象的score字段
  student_info_cpp.score = env->GetIntField(student_info, score_field);
  // 11. 将Java类型的StudentInfo对象的schedule字段的值赋值给C++类型的StudentInfo对象的schedule字段
  jobjectArray schedule = (jobjectArray)env->GetObjectField(student_info, schedule_field);
  int schedule_len = env->GetArrayLength(schedule);
  for (int i = 0; i < schedule_len; i++) {
      jintArray schedule_item = (jintArray)env->GetObjectArrayElement(schedule, i);
      int schedule_item_len = env->GetArrayLength(schedule_item);
      jint* schedule_item_data = env->GetIntArrayElements(schedule_item, 0);
      for (int j = 0; j < schedule_item_len; j++) {
          student_info_cpp.schedule[i][j] = schedule_item_data[j];
      }
      env->ReleaseIntArrayElements(schedule_item, schedule_item_data, 0);
  }

  // 调用c接口修改C++类型的StudentInfo对象
  INSTPTR handle = (INSTPTR)student;
  update_student_info(handle, &student_info_cpp);

  // 将C++类型的StudentInfo对象的值赋值给Java类型的StudentInfo对象
  // 8. 将C++类型的StudentInfo对象的name字段的值赋值给Java类型的StudentInfo对象的name字段
  env->SetObjectField(student_info, name_field, env->NewStringUTF(student_info_cpp.name));
  // 9. 将C++类型的StudentInfo对象的age字段的值赋值给Java类型的StudentInfo对象的age字段
  env->SetIntField(student_info, age_field, student_info_cpp.age);
  // 10. 将C++类型的StudentInfo对象的score字段的值赋值给Java类型的StudentInfo对象的score字段
  env->SetIntField(student_info, score_field, student_info_cpp.score);
  // 11.1 将C++类型的StudentInfo对象的schedule字段的值赋值给Java类型的StudentInfo对象的schedule字段
  // 11.2 遍历C++类型的StudentInfo对象的schedule字段的值
  for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 6; j++) {
          // 11.3 获取Java类型的StudentInfo对象的schedule字段的值的第i行第j列的值
          jintArray schedule_row = (jintArray)env->GetObjectArrayElement(schedule, i);
          jint* schedule_row_ptr = env->GetIntArrayElements(schedule_row, 0);
          // 11.4 将C++类型的StudentInfo对象的schedule字段的值的第i行第j列的值赋值给Java类型的StudentInfo对象的schedule字段的值的第i行第j列的值
          schedule_row_ptr[j] = student_info_cpp.schedule[i][j];
          // 11.5 释放Java类型的StudentInfo对象的schedule字段的值的第i行第j列的值
          env->ReleaseIntArrayElements(schedule_row, schedule_row_ptr, 0);
      }
  }

  // 设置家庭住址
  // 12. 获取StudentInfo类中的address字段
  jfieldID address_field = env->GetFieldID(student_info_class, "address", "J[Lcom/StudentInfo/Address;");
  // 13. 获取StudentInfo类中的address字段的值
  jobjectArray address = (jobjectArray)env->GetObjectField(student_info, address_field); 
  // 14. 将C++类型的StudentInfo对象的address字段的值赋给Java类型的StudentInfo对象的address字段的值
  // 14.1 遍历C++类型的StudentInfo对象的address字段的值
  // for (int i = 0; i < 2; i++) {
  //     // 14.2 获取Java类型的StudentInfo对象的address字段的值的第i个元素
  //     jobject address_item = env->GetObjectArrayElement(address, i);
  //     // 14.3 获取Address类
  //     jclass address_class = env->GetObjectClass(address_item);
  //     jfieldID area_field = env->GetFieldID(address_class, "area", "I");
  //     jfieldID block_field = env->GetFieldID(address_class, "block", "I");
  //     jfieldID house_num_field = env->GetFieldID(address_class, "house_num", "I");

  //     jstring area = (jstring)env->GetObjectField(address_item, area_field);
  //     jstring block = (jstring)env->GetObjectField(address_item, block_field);
  //     jstring house_num = (jstring)env->GetObjectField(address_item, house_num_field);

  //     // 14.4 将C++类型的StudentInfo对象的字段赋值给Java类型的StudentInfo对象的address字段
  //     env->SetIntField(address_item, area_field, student_info_cpp.address[i].area);
  //     env->SetIntField(address_item, block_field, student_info_cpp.address[i].block);
  //     env->SetIntField(address_item, house_num_field, student_info_cpp.address[i].house_num);
  //     // 释放局部引用
  //     env->DeleteLocalRef(address_item);
  // }
  // 释放局部引用
  env->DeleteLocalRef(student_info_class);
  env->DeleteLocalRef(student_info);
  env->DeleteLocalRef(schedule);
  env->DeleteLocalRef(address);

}
