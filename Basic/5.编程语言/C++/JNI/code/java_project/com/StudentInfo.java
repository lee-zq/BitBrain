package com;

public class StudentInfo {
    public String name;
    public int id;
    public int age;
    public int score;
    public int[][] schedule = new int[5][6];
    public Address[] address = new Address[3];

    public class Address {
        public int area;
        public int block;
        public int house_num;
    }

    public StudentInfo() {
        name = "None";
        id = 0;
        age = 0;
        score = 0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 6; j++) {
                schedule[i][j] = 0;
            }
        }
        for (int i = 0; i < 3; i++) {
            address[i] = new Address();
            address[i].area = 0;
            address[i].block = 0;
            address[i].house_num = 0;
        }
    }
    // 打印学生信息
    public void print_student_info() {
        System.out.println("==============");
        System.out.println("name: " + name);
        System.out.println("id: " + id);
        System.out.println("age: " + age);
        System.out.println("score: " + score);
        System.out.println("schedule: ");
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 6; j++) {
                System.out.print(schedule[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println("address: ");
        for (int i = 0; i < 3; i++) {
            System.out.println(address[i].area + " " + address[i].block + " " + address[i].house_num);
        }
        System.out.println("==============");
    }

}
