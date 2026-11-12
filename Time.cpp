#include "Time.h"
#include <sstream>
#include <iomanip>

// Метод нормалізації часу (щоб не було 90 секунд або 25 годин)
void Time::normalize() {
    int s = timeFields.getThird();           // Отримуємо поточні секунди з допоміжного об'єкта
    int m = timeFields.getSecond();          // Отримуємо поточні хвилини
    int h = timeFields.getFirst();           // Отримуємо поточні години

    // Переводимо зайві секунди у хвилини
    if (s >= 60) {
        m += s / 60;                         // Ділення націло дає кількість нових хвилин (напр. 130 / 60 = +2 хв)
        s %= 60;                             // Залишок від ділення - це правильні секунди в межах 0-59
    }
    else if (s < 0) {
        int borrow = (-s + 59) / 60;         // Обчислюємо, скільки хвилин треба "позичити", щоб секунди стали додатними
        m -= borrow;                         // Віднімаємо позичені хвилини
        s += borrow * 60;                    // Компенсуємо від'ємні секунди (наприклад, -10 сек стане 50 сек)
    }

    // Переводимо зайві хвилини у години
    if (m >= 60) {
        h += m / 60;                         // Додаємо цілі години, що утворилися з надлишку хвилин
        m %= 60;                             // Залишаємо тільки хвилини в межах 0-59
    }
    else if (m < 0) {
        int borrow = (-m + 59) / 60;         // Скільки годин треба "позичити" для компенсації
        h -= borrow;                         // Зменшуємо години
        m += borrow * 60;                    // Робимо хвилини додатними
    }

    // Години завжди в межах 0-23
    if (h >= 24) {
        h %= 24;                             // Перехід через північ (наприклад, 26 годин -> 2 година ночі)
    }
    else if (h < 0) {
        h = (h % 24 + 24) % 24;              // Коректна обробка від'ємних годин (перехід назад у часі)
    }

    // Зберігаємо нормалізовані значення назад у тріадy
    timeFields.setFirst(h);                  // Записуємо правильні години у Triad
    timeFields.setSecond(m);                 // Записуємо правильні хвилини у Triad
    timeFields.setThird(s);                  // Записуємо правильні секунди у Triad
}

Time::Time() : timeFields(0, 0, 0) {}                                  // Делегуємо створення порожнього часу конструктору Triad

Time::Time(int h, int m, int s) : timeFields(h, m, s) { normalize(); } // Записуємо дані в Triad і одразу виправляємо переповнення

Time::Time(const Time& other) : timeFields(other.timeFields) {}        // Копіюємо всі поля внутрішнього об'єкта Triad

Time::~Time() {}                                                       // Порожній, бо немає динамічної пам'яті (new/delete)

int Time::getHours() const { return timeFields.getFirst(); }           // Отримуємо години (перше поле) з об'єкта Triad
int Time::getMinutes() const { return timeFields.getSecond(); }        // Отримуємо хвилини (друге поле) з об'єкта Triad
int Time::getSeconds() const { return timeFields.getThird(); }         // Отримуємо секунди (третє поле) з об'єкта Triad

void Time::setHours(int h) { timeFields.setFirst(h); normalize(); }    // Передаємо години в Triad і викликаємо нормалізацію
void Time::setMinutes(int m) { timeFields.setSecond(m); normalize(); } // Передаємо хвилини в Triad і виправляємо формат
void Time::setSeconds(int s) { timeFields.setThird(s); normalize(); }  // Передаємо секунди в Triad і виправляємо формат

// Перевизначені методи (використовують методи Triad + нормалізація)
void Time::incHours() { timeFields.incFirst(); normalize(); }          // Збільшуємо 1-ше поле (години) в Triad + корекція 24->0
void Time::incMinutes() { timeFields.incSecond(); normalize(); }       // Збільшуємо 2-ге поле (хвилини) + корекція 60->0
void Time::incSeconds() { timeFields.incThird(); normalize(); }        // Збільшуємо 3-тє поле (секунди) + корекція 60->0

// Додавання довільної кількості хвилин та секунд
void Time::addMinutes(int n) {
    timeFields.setSecond(timeFields.getSecond() + n);                  // Додаємо число до поточних хвилин (може вийти > 60)
    normalize();                                                       // Метод normalize автоматично перекине зайве в години
}

void Time::addSeconds(int n) {
    timeFields.setThird(timeFields.getThird() + n);                    // Додаємо число до секунд (наприклад, + 150)
    normalize();                                                       // Перетворюємо зайві секунди на хвилини і години
}

Time& Time::operator=(const Time& other) {
    if (this != &other) timeFields = other.timeFields;                 // Захист від самоприсвоєння (a = a). Копіюємо Triad
    return *this;                                                      // Повертаємо поточний об'єкт для ланцюжків (a = b = c)
}

Time::operator string() const {
    stringstream ss;                                                   // Створюємо потік для зручного форматування тексту
    // Виводимо красиво: додаємо нулі попереду (наприклад 09:05:03 замість 9:5:3)
    ss << setfill('0') << setw(2) << getHours() << ":"                 // setw(2) виділяє 2 позиції, setfill('0') заповнює порожнечу нулями
        << setfill('0') << setw(2) << getMinutes() << ":"
        << setfill('0') << setw(2) << getSeconds();
    return ss.str();                                                   // Конвертуємо потік у стандартний рядок (string)
}

Time& Time::operator++() { incHours(); return *this; }                 // Префіксний (++t): викликає метод для годин і повертає змінений стан

Time Time::operator++(int) {
    Time temp(*this); incMinutes(); return temp;                       // Постфіксний (t++): зберігає старий стан, збільшує хвилини, повертає старий стан
}

Time& Time::operator--() {
    timeFields.setFirst(timeFields.getFirst() - 1); normalize(); return *this; // Префіксний (--t): зменшує години і виправляє, якщо стало < 0
}

Time Time::operator--(int) {
    Time temp(*this); timeFields.setSecond(timeFields.getSecond() - 1); normalize(); return temp; // Постфіксний (t--): зменшує хвилини і повертає копію
}

ostream& operator<<(ostream& out, const Time& t) { out << string(t); return out; } // Виведення: делегуємо роботу оператору приведення до string

istream& operator>>(istream& in, Time& t) {
    int h, m, s;
    cout << " Години: "; in >> h;                                      // Просимо користувача ввести години
    cout << " Хвилини: "; in >> m;                                     // Просимо користувача ввести хвилини
    cout << " Секунди: "; in >> s;                                     // Просимо користувача ввести секунди
    t.setHours(h); t.setMinutes(m); t.setSeconds(s);                   // Сеттери самі викличуть normalize(), якщо ввели напр. "90 хвилин"
    return in;                                                         // Повертаємо потік in для множинного введення (cin >> a >> b)
}