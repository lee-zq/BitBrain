
export LD_LIBRARY_PATH=/root/project/lzq/jni_demo/cpp_project/build/bin:$LD_LIBRARY_PATH
# 生成jni接口头文件
javac  -encoding  utf8  -h ./ com/Student.java

# 编译java文件
javac -encoding utf8 com/Test.java -d bin

# 运行java文件
java -Djava.library.path=/root/project/lzq/jni_demo/cpp_project/build/bin -cp bin com.Test

# # 打包成jar文件
# jar -cvf Test.jar -C bin/ .

# #打包aar文件
# jar -cvf Test.aar -C bin/ .
