﻿#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>

using namespace std;
const int MAX_NAME_LENGTH = 100;
const int MAX_GRADES = 5;   // Максимальное количество оценок
struct Student {
    char fullName[MAX_NAME_LENGTH];
    int groupNumber;
    int grades[MAX_GRADES];
    float averageGrade() const {
        int sum = 0;
        for (int i = 0; i < 5; ++i)
            sum += grades[i];
        return static_cast<float>(sum) / 5;
    }
};
// Функция для ввода данных о студентах
void inputStudents(bool isHuman, int n, Student students[]) {
    for (int i = 0; i < n; ++i) {
        if (isHuman) {
            cout << "Введите ФИО студента: ";
        }
        cin.ignore(); // Для игнорирования новой строки после предыдущего ввода
        cin.getline(students[i].fullName, MAX_NAME_LENGTH);

        if (isHuman) {
            cout << "Введите номер группы: ";
        }
        cin >> students[i].groupNumber;

        if (isHuman) {
            cout << "Введите успеваемость (5 оценок): ";
        }
        for (int j = 0; j < MAX_GRADES; j++) {
            cin >> students[i].grades[j];
        }
    }
}
// Сортировка студентов по номеру группы
void SortGroup(Student students[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (students[j].groupNumber > students[j + 1].groupNumber) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}
// Функция для печати данных о студентах
void printStudents(int n, Student students[]) {
    for (int i = 0; i < n; ++i) {
        cout << students[i].groupNumber << " - " << students[i].fullName << ": ";
        for (int j = 0; j < MAX_GRADES; j++) {
            cout << students[i].grades[j];
            if (j < MAX_GRADES - 1)
                cout << ", ";
        }
        cout << endl;
    }
}
// Сортировка по убыванию по среднему значению
void stableSortByAverageGrade(Student* students, int n) {
    for (int i = 1; i < n; ++i) {
        Student key = students[i];
        int j = i - 1;
        while (j >= 0 && students[j].averageGrade() < key.averageGrade()) {
            students[j + 1] = students[j];
            --j;
        }
        students[j + 1] = key;
    }
}
// Печать по убыванию средних значений
void printHighAverageStudents(const Student* students, int n) {
    for (int i = 0; i < n; ++i) {
        float avg = students[i].averageGrade();
        cout << students[i].groupNumber << ", " << students[i].fullName << " - " << avg << endl;
    }
}
// Функция для фильтрации студентов со средним баллом выше 4.0
int filterHighAverageStudents(const Student* students, int n, Student* filteredStudents) {
    int M = 0;
    for (int i = 0; i < n; ++i) {
        if (students[i].averageGrade() > 4.0) {
            filteredStudents[M++] = students[i];
        }
    }
    return M;
}
// Функция для группировки и агрегации данных по номеру группы
struct GroupStats {
    int group_number;
    int student_count;
    int bad_student_count;
};
// Функция для центровки текста в заданной ширине
string center(const string& str, int width) {
    int padding = width - str.length();
    int pad_left = padding / 2; // Левый отступ
    int pad_right = padding - pad_left; // Правый отступ
    return string(pad_left, ' ') + str + string(pad_right, ' ');
}
// Функция для оформления таблицы
void head(const GroupStats group_stats[], int unique_groups) {
    cout << "Группировка по номерам групп:\n";
    cout << "|" << setw(15) << center("Номер группы", 30) << "|"
        << setw(15) << center("Кол-во студентов", 30) << "|"
        << setw(15) << center("С плохими оценками", 30) << "|\n";
    cout << "----------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < unique_groups; i++) {
        cout << "|" << setw(15) << center(to_string(group_stats[i].group_number), 30) << "|"
            << setw(15) << center(to_string(group_stats[i].student_count), 30) << "|"
            << setw(15) << center(to_string(group_stats[i].bad_student_count), 30) << "|\n";
    }
}
// Функция для поиска группы
int findGroupIndex(GroupStats group_stats[], int unique_groups, int group_number) {
    for (int j = 0; j < unique_groups; j++) {
        if (group_stats[j].group_number == group_number) {
            return j; // Возвращаем индекс группы
        }
    }
    return -1; // Если группа не найдена
}
// Функция для сортировки групп по количеству двоечников
void sortGroupStats(GroupStats group_stats[], int unique_groups) {
    for (int i = 0; i < unique_groups - 1; ++i) {
        for (int j = 0; j < unique_groups - 1 - i; ++j) {
            if (group_stats[j].bad_student_count < group_stats[j + 1].bad_student_count ||
                (group_stats[j].bad_student_count == group_stats[j + 1].bad_student_count &&
                    group_stats[j].group_number > group_stats[j + 1].group_number)) {
                swap(group_stats[j], group_stats[j + 1]);
            }
        }
    }
}
// Функция для высчета уникальных групп и кол-ва двоечников
void groupStudents(const Student students[], int N, bool isHuman) {
    GroupStats* group_stats = new GroupStats[N];
    int unique_groups = 0;
    // Сбор данных по группам
    for (int i = 0; i < N; i++) {
        int group_index = findGroupIndex(group_stats, unique_groups, students[i].groupNumber);
        if (group_index == -1) {
            group_stats[unique_groups++] = { students[i].groupNumber, 1, 0 };
            group_index = unique_groups - 1;
        }
        else {
            group_stats[group_index].student_count++;
        }
        // Проверяем на наличие двоек
        for (int j = 0; j < MAX_GRADES; j++) {
            if (students[i].grades[j] == 2) {
                group_stats[group_index].bad_student_count++;
                break;  // Если есть хотя бы одна двойка, выходим из цикла
            }
        }
    }
    // Сортируем группы
    sortGroupStats(group_stats, unique_groups);
    // Выводим результаты
    if (isHuman)
    {
        head(group_stats, unique_groups);
    }
    else
    {
        for (int i = 0; i < unique_groups; i++)
            cout << group_stats[i].group_number << " - " << group_stats[i].student_count << " - " << group_stats[i].bad_student_count << endl;
    }
    delete[] group_stats; // Освобождаем память
}
int main(int argc, char* argv[]) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    bool isHuman = false;
    if (argc <= 1 || strcmp(argv[1], "false") != 0) {
        isHuman = true;
    }
    int n;
    if (isHuman) {
        cout << "Введите количество студентов: ";
    }
    cin >> n;
    Student* students = new Student[n];
    inputStudents(isHuman, n, students);
    SortGroup(students, n);
    printStudents(n, students);
    // Фильтрация по среднему балу
    Student* filteredStudents = new Student[n];
    int M = filterHighAverageStudents(students, n, filteredStudents);
    stableSortByAverageGrade(filteredStudents, M);
    if (M > 0) {
        if (isHuman) {
            cout << endl << "Студенты со средним баллом > 4.0, упорядоченные по убыванию среднего балла:" << endl;
        }
        printHighAverageStudents(filteredStudents, M);
    }
    else {
        cout << "NO" << endl;
    }
    groupStudents(students, n, isHuman);
    // Освобождение памяти
    delete[] students; // Освобождение памяти для массива студентов
    delete[] filteredStudents;
    return 0;
}