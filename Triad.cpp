#include "Triad.h"
#include <sstream>

// Конструктор за умовчанням
Triad::Triad() : first(0), second(0), third(0) {}           // Список ініціалізації: задаємо нулі при створенні порожнього об'єкта

// Конструктор ініціалізації з параметрами
Triad::Triad(int f, int s, int t) {
    setFirst(f);                                            // Використовуємо сеттери замість прямого присвоєння,
    setSecond(s);                                           // щоб працювала логіка перевірок (якщо вона буде додана в майбутньому)
    setThird(t);
}

// Конструктор копіювання
Triad::Triad(const Triad& other) {                          // Викликається при створенні нового об'єкта як копії іншого (Triad t2 = t1)
    first = other.first;                                    // Просто поелементно копіюємо всі три поля
    second = other.second;
    third = other.third;
}

Triad::~Triad() {}                                          // Деструктор порожній, бо ми не виділяли динамічної пам'яті (через new)

int Triad::getFirst() const { return first; }               // Повертає значення першого поля (константний метод, не змінює об'єкт)
int Triad::getSecond() const { return second; }             // Повертає значення другого поля
int Triad::getThird() const { return third; }               // Повертає значення третього поля

void Triad::setFirst(int f) { first = f; }                  // Встановлює нове значення для першого поля
void Triad::setSecond(int s) { second = s; }                // Встановлює нове значення для другого поля
void Triad::setThird(int t) { third = t; }                  // Встановлює нове значення для третього поля

void Triad::incFirst() { first++; }                         // Просте збільшення першого поля на 1
void Triad::incSecond() { second++; }                       // Просте збільшення другого поля на 1
void Triad::incThird() { third++; }                         // Просте збільшення третього поля на 1

Triad& Triad::operator=(const Triad& other) {
    if (this != &other) {                                   // Перевірка адрес: чи не намагаємося ми присвоїти об'єкт самому собі (t = t)
        first = other.first;                                // Якщо все ок — копіюємо поля
        second = other.second;
        third = other.third;
    }
    return *this;                                           // Повертаємо поточний об'єкт за посиланням для ланцюжків (a = b = c)
}

Triad::operator string() const {
    stringstream ss;                                        // Створюємо потік для зручного "склеювання" рядка і чисел
    ss << "(" << first << ", " << second << ", " << third << ")"; // Форматуємо вивід у вигляді: (1, 2, 3)
    return ss.str();                                        // Конвертуємо потік у фінальний string
}

Triad& Triad::operator++() {
    incFirst();                                             // Префіксний інкремент (++t): за умовою змінює перше поле (години у класі Time)
    return *this;                                           // Одразу повертає змінений стан об'єкта
}

Triad Triad::operator++(int) {
    Triad temp(*this);                                      // Постфіксний інкремент (t++): зберігаємо копію старого стану
    incSecond();                                            // Збільшуємо друге поле (хвилини у класі Time)
    return temp;                                            // Повертаємо копію ДО збільшення
}

Triad& Triad::operator--() {
    first--;                                                // Префіксний декремент (--t): зменшує перше поле
    return *this;
}

Triad Triad::operator--(int) {
    Triad temp(*this);                                      // Постфіксний декремент (t--): створює копію
    second--;                                               // Зменшує друге поле
    return temp;                                            // Повертає збережену копію
}

ostream& operator<<(ostream& out, const Triad& t) {
    out << string(t);                                       // Викликаємо наш operator string() для форматування і записуємо в потік out
    return out;
}

istream& operator>>(istream& in, Triad& t) {
    int f, s, tr;
    cout << " Введіть три числа через пробіл: ";            // Підказуємо користувачу, що треба ввести
    in >> f >> s >> tr;                                     // Зчитуємо 3 числа
    t.setFirst(f); t.setSecond(s); t.setThird(tr);          // Записуємо їх через сеттери для безпеки
    return in;                                              // Повертаємо потік для можливості множинного введення (cin >> t1 >> t2)
}