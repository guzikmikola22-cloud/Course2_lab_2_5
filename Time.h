#pragma once
#include "Triad.h"

class Time {
private:
    Triad timeFields;                        // КОМПОЗИЦІЯ: об'єкт класу Triad як поле класу Time!
    // first = години, second = хвилини, third = секунди

    void normalize();                        // Допоміжний метод: перетворює 65 сек у 1 хв 5 сек

public:
    // ================= КОНСТРУКТОРИ =================
    Time();
    Time(int h, int m, int s);
    Time(const Time& other);
    ~Time();

    // ================= МЕТОДИ ДОСТУПУ =================
    int getHours() const;                    // Читає timeFields.getFirst()
    int getMinutes() const;                  // Читає timeFields.getSecond()
    int getSeconds() const;                  // Читає timeFields.getThird()

    void setHours(int h);
    void setMinutes(int m);
    void setSeconds(int s);

    // ================= БІЗНЕС-ЛОГІКА (Варіант 15) =================
    void incHours();                         // Перевизначене збільшення години на 1
    void incMinutes();                       // Перевизначене збільшення хвилини на 1
    void incSeconds();                       // Перевизначене збільшення секунди на 1

    void addMinutes(int n);                  // Додати n хвилин
    void addSeconds(int n);                  // Додати n секунд

    // ================= ПЕРЕВАНТАЖЕННЯ ОПЕРАЦІЙ =================
    Time& operator=(const Time& other);
    operator string() const;

    Time& operator++();                      // Префіксний інкремент (години)
    Time operator++(int);                    // Постфіксний інкремент (хвилини)
    Time& operator--();                      // Префіксний декремент (години)
    Time operator--(int);                    // Постфіксний декремент (хвилини)

    friend ostream& operator<<(ostream& out, const Time& t); // Дружня функція для виведення в потік cout << t
    friend istream& operator>>(istream& in, Time& t);        // Дружня функція для введення з потоку cin >> t
};