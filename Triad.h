#pragma once
#include <iostream>
#include <string>

using namespace std;

class Triad {
private:
    int first;                               // Перше число
    int second;                              // Друге число
    int third;                               // Третє число

public:
    // ================= КОНСТРУКТОРИ =================
    Triad();                                 // За умовчанням (без аргументів)
    Triad(int f, int s, int t);              // Ініціалізації (з аргументами)
    Triad(const Triad& other);               // Копіювання
    ~Triad();                                // Деструктор

    // ================= МЕТОДИ ДОСТУПУ =================
    int getFirst() const;                    // Читання першого поля
    int getSecond() const;                   // Читання другого поля
    int getThird() const;                    // Читання третього поля

    void setFirst(int f);                    // Запис першого поля
    void setSecond(int s);                   // Запис другого поля
    void setThird(int t);                    // Запис третього поля

    // ================= БІЗНЕС-ЛОГІКА =================
    void incFirst();                         // Збільшити перше поле на 1
    void incSecond();                        // Збільшити друге поле на 1
    void incThird();                         // Збільшити третє поле на 1

    // ================= ПЕРЕВАНТАЖЕННЯ ОПЕРАЦІЙ =================
    Triad& operator=(const Triad& other);    // Присвоєння
    operator string() const;                 // Приведення до літерного рядка

    Triad& operator++();                     // Префіксний інкремент (++t) - збільшує first
    Triad operator++(int);                   // Постфіксний інкремент (t++) - збільшує second
    Triad& operator--();                     // Префіксний декремент (--t) - зменшує first
    Triad operator--(int);                   // Постфіксний декремент (t--) - зменшує second

    // ================= ДРУЖНІ ФУНКЦІЇ =================
    friend ostream& operator<<(ostream& out, const Triad& t); // Виведення
    friend istream& operator>>(istream& in, Triad& t);        // Введення
};