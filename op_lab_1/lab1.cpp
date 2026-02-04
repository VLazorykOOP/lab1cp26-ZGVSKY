#include "lab1.h"    // заголовок
#include <fstream>   // роботa з файлами
#include <cmath>     // Для abs

//(не обов'язково виносити в header)
double getTableValue(const double x, const int column) {
    string fileName;
    double currentX = x;

    if (abs(x) <= 1) {
        fileName = "dat_X_1_1.dat";
    } else if (x < -1) {
        currentX = 1.0 / x;
        fileName = "dat_X_00_1.dat";
    } else {
        currentX = 1.0 / x;
        fileName = "dat_X_1_00.dat";
    }

    ifstream file(fileName);
    if (!file) throw ErrorNoFile(fileName); // Викидаємо помилку

    double x_prev, t_prev, u_prev;
    double x_next, t_next, u_next;

    if (!(file >> x_prev >> t_prev >> u_prev)) return 0; // Файл пустий або помилка читання

    // Інтерполяція
    while (file >> x_next >> t_next >> u_next) {
        if (currentX >= x_prev && currentX <= x_next) {
            file.close();
            double y_prev = (column == 1) ? t_prev : u_prev;
            double y_next = (column == 1) ? t_next : u_next;
            return y_prev + (y_next - y_prev) * (currentX - x_prev) / (x_next - x_prev);
        }
        x_prev = x_next; t_prev = t_next; u_prev = u_next;
    }
    file.close();
    return (column == 1) ? t_prev : u_prev;
}

// Реалізація функцій, оголошених у Lab1.h
double T(double x) { return getTableValue(x, 1); }
double U(double x) { return getTableValue(x, 2); }

double Glr(double x, double y) {
    // 1. Якщо |x| < 1
    if (abs(x) < 1) {
        return x;
    }

    // 2. Якщо |x| >= 1 і |y| < 1
    if (abs(x) >= 1 && abs(y) < 1) {
        return y;
    }

    // 3. Інакше обчислюємо корінь
    double temp = x * x + y * y - 4;
    double rootVal = sqrt(temp);

    // "при sqrt(...) < 0.1 перерахувати"
    if (rootVal < 0.1) {
        throw ErrorMath("Glr: sqrt(x^2+y^2-4) < 0.1", rootVal);
    }

    return y / rootVal;
}

double Gold(double x, double y) {
    // Випадок 1: x > y
    if (x > y) {
        if (y == 0) {

            throw ErrorMath("Gold: Division by zero (x > y, y == 0)", y);
        }
        return x / y;
    }
    // Випадок 2: x < y
    else if (x < y) {
        if (x == 0) {

            throw ErrorMath("Gold: Division by zero (x < y, x == 0)", x);
        }
        return y / x;
    }

    // Якщо x == y ( повертаємо 1 )
    return 1.0;
}

double Srz(double x, double y, double z) {
    if (x > y) {
        return T(x) + U(z) - T(y);
    } else {
        return T(y) + U(y) - U(z);
    }
}

double Grs(double x, double y) {


    // Частина 1: 0.1389 * Srz(x+y, Gold(x,y), Glr(x, x*y))
    double part1 = 0.1389 * Srz(x + y, Gold(x, y), Glr(x, x * y));

    // Частина 2: 1.8389 * Srz(x-y, Gold(y, x/5), Glr(5x, x*y))
    double part2 = 1.8389 * Srz(x - y, Gold(y, x / 5.0), Glr(5 * x, x * y));

    // Частина 3: 0.83 * Srz(x-0.9, Glr(y, x/5), Gold(5y, y))
    double part3 = 0.83 * Srz(x - 0.9, Glr(y, x / 5.0), Gold(5 * y, y));

    return part1 + part2 + part3;
}

double fun(double x, double y, double z) {
    // Формула: x^2*Grs(y,z) + y^2*Grs(x,z) + 0.33*x*y*Grs(x,z)
    // Останній доданок використовує Grs(x,z)

    return x * x * Grs(y, z)
         + y * y * Grs(x, z)
         + 0.33 * x * y * Grs(x, z);
}

// Алгоритм 3 (Використовується при помилці файлу)
// 1.3498*z + 2.2362*y - 2.348*x*y
double fun_Algorithm3(double x, double y, double z) {
    cout << "   [INFO] Calculating using Algorithm 3..." << endl;
    return 1.3498 * z + 2.2362 * y - 2.348 * x * y;
}

double Glr1(double x, double y) {
    if (abs(x) < 1) {
        return x;
    } else {
        return y; // для |x| >= 1
    }
}


double Gold1(double x, double y) {
    // Умова 4: y = 0 -> 0.1
    if (y == 0) {
        return 0.1;
    }

    // Умова 1: x > y і |y| > 0.1
    if (x > y && abs(y) > 0.1) {
        return x / y;
    }

    // Умова 2: x < y і |y| > 0.1
    if (x < y && abs(y) > 0.1) {
        if (x == 0) throw ErrorMath("Gold1: Division by zero (x=0)", 0);
        return y / x;
    }

    // Умова 3: x < y і |x| > 0.1 -> 0.15
    if (x < y && abs(x) > 0.1) {
        return 0.15;
    }

    // якщо жодна умова не виконалася
    return 1.0;
}

// Функція Grsl (аналог Grs, але для Алгоритму 2)
double Grsl(double x, double y) {

    //  0.14 * Srz(x+y, Gold1(x,y), Glr1(x, x*y))
    double part1 = 0.14 * Srz(x + y, Gold1(x, y), Glr1(x, x * y));

    //  1.83 * Srz(x-y, Gold1(y, x/5), Glr1(4x, x*y))
    double part2 = 1.83 * Srz(x - y, Gold1(y, x / 5.0), Glr1(4 * x, x * y));

    //  0.83 * Srz(x, Glr1(y, x/4), Gold1(4y, y))
    //0.83Srz(x, Glrl(y,x/4), Gold1(4y, y))
    double part3 = 0.83 * Srz(x, Glr1(y, x / 4.0), Gold1(4 * y, y));

    return part1 + part2 + part3;
}

// Algorithm 2
double fun_Algorithm2(double x, double y, double z) {
    cout << "   [INFO] Calculating using Algorithm 2..." << endl;

    // x*Grsl(x,y) + y*Grsl(y,z) + z*Grsl(z,x) [cite: 359]

    return x * Grsl(x, y)
         + y * Grsl(y, z)
         + z * Grsl(z, x);
}

// Created by User on 02.02.2026.
//
