#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

// =========================================================================
// БАЗОВИЙ КЛАС: Liquid (Рідина)
// =========================================================================
class Liquid
{
protected:
    string name;      // Назва рідини
    double density;   // Щільність (кг/м3)

public:
    // Конструктор
    Liquid(string n = "Вода", double d = 1000.0) : name(n), density(d) {}

    virtual ~Liquid() = default;

    // Методи отримання значень
    string getName() const { return name; }
    double getDensity() const { return density; }

    // Методи перепризначення й зміни щільності
    void setName(string new_name) { name = new_name; }
    void setDensity(double new_density) { density = new_density; }

    // Віртуальний метод для виведення інформації
    virtual void display() const
    {
        cout << "Рідина: " << name << " | Щільність: " << density << " кг/м³";
    }
};

// =========================================================================
// ПОХІДНИЙ КЛАС: Alcohol (Спирт)
// =========================================================================
class Alcohol : public Liquid
{
private:
    double strength; // Міцність у відсотках (%)

public:
    // Конструктор
    Alcohol(string n = "Етанол", double d = 789.0, double s = 40.0)
        : Liquid(n, d), strength(s) {
    }

    // Методи отримання та зміни міцності
    double getStrength() const { return strength; }
    void setStrength(double new_strength) { strength = new_strength; }

    // Перевизначення методу виведення інформації
    void display() const override
    {
        Liquid::display();
        cout << " | Міцність: " << strength << "%";
    }
};

// =========================================================================
// ФУНКЦІЯ ДЛЯ ДЕМОНСТРАЦІЇ ПРИНЦИПУ ПІДСТАНОВКИ
// Функція приймає покажчик на базовий клас і повертає покажчик на базовий клас
// =========================================================================
Liquid* transformLiquid(Liquid* obj)
{
    cout << "\n[Всередині функції transformLiquid]:" << endl;
    cout << "Вхідні дані об'єкта: ";
    obj->display();
    cout << endl;

    // Змінюємо назву (метод перепризначення)
    obj->setName(obj->getName() + " (Модифікована)");

    // Збільшуємо щільність на 10%
    obj->setDensity(obj->getDensity() * 1.1);

    cout << "Дані після модифікації: ";
    obj->display();
    cout << endl;

    return obj; // Повертаємо об'єкт базового класу
}


// =========================================================================
// ГОЛОВНА ФУНКЦІЯ
// =========================================================================
int main()
{
    // Налаштування укр. мови в консолі
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "=== Лабораторна робота № 8: Спадкування ===" << endl;
    cout << "Варіант 3: Класи Liquid та Alcohol" << endl << endl;

    cout << "--- 1. Робота з базовим класом Liquid ---" << endl;
    Liquid* water = new Liquid("Дистильована вода", 1000.0);
    water->display(); cout << endl;

    // Зміна щільності вручну
    water->setDensity(997.0);
    cout << "Після зміни щільності: ";
    water->display(); cout << endl << endl;

    cout << "--- 2. Робота з похідним класом Alcohol ---" << endl;
    Alcohol* vodka = new Alcohol("Горілка", 950.0, 40.0);
    vodka->display(); cout << endl;

    // Зміна міцності вручну
    vodka->setStrength(45.0);
    cout << "Після зміни міцності: ";
    vodka->display(); cout << endl << endl;

    cout << "--- 3. Демонстрація принципу підстановки (Liskov Substitution) ---" << endl;
    cout << "Передаємо базовий клас (Liquid):" << endl;
    Liquid* result1 = transformLiquid(water);

    cout << "\nПередаємо ПОХІДНИЙ клас (Alcohol) замість базового:" << endl;
    // ПРИНЦИП ПІДСТАНОВКИ: функція чекає Liquid*, але ми можемо абсолютно безпечно передати Alcohol*
    Liquid* result2 = transformLiquid(vodka);

    // Очищення пам'яті
    delete water;
    delete vodka;

    cout << "\nНатисніть Enter для завершення...";
    cin.get();
    return 0;
}
