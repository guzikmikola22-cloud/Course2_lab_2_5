#include <iostream>
#include <Windows.h>
#include "Time.h"

using namespace std;

// Структура для демонстрації розмірів з пакуванням пам'яті
#pragma pack(push, 1)
class TimePacked {
    Triad t;
};
#pragma pack(pop)

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    cout << "Розмір класу Time без #pragma pack(1): " << sizeof(Time) << " байт" << endl;
    cout << "Розмір класу з #pragma pack(1): " << sizeof(TimePacked) << " байт" << endl;
    cout << "-------------------------------------------------" << endl;

    cout << "1. Демонстрація класу Triad (Допоміжний клас):" << endl;
    Triad tr(1, 2, 3);
    cout << "Початкова тріада: " << tr << endl;
    tr.incFirst();
    cout << "Після incFirst(): " << tr << endl;
    cout << "-------------------------------------------------" << endl;

    cout << "2. Демонстрація класу Time (Композиція):" << endl;
    Time t1(23, 59, 50);
    cout << "Створено час t1: " << t1 << endl;

    t1.incSeconds();
    cout << "Після incSeconds(): " << t1 << " (Зверніть увагу: секунди стали 51)" << endl;

    t1.addSeconds(15);
    cout << "Додали 15 секунд : " << t1 << " (51+15=66 с -> 1 хв 6 с -> Години перейшли через 23->0)" << endl;

    t1.addMinutes(125);
    cout << "Додали 125 хвилин: " << t1 << " (+2 години 5 хвилин)" << endl;
    cout << "-------------------------------------------------" << endl;

    cout << "3. Введення масиву часу:" << endl;
    Time arr[2];
    for (int i = 0; i < 2; i++) {
        cout << "Введіть час [" << i << "]:" << endl;
        cin >> arr[i];
    }

    cout << "\nВаш масив часу:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }

    return 0;
}