#include <iostream>
#include "lab1.h"

/*
 Алгоритм 1 (Основний) -> [Помилка обчислень] -> Алгоритм 2 -> [Немає файлу] -> Алгоритм 3

 x = 2      (Програма візьме 1/x = 0.5, відкриє dat_X_1_00.dat)
 y = 1
 z = 1

26.516123

математична помилка в Алгоритмі 1.

 x = 5
 y = 0
 z = 1

Division by zero
Unknown error occurred.

перейменуй файл

 x = 2
 y = 0.5
 z = 1
*/

using namespace std;

int run_lab1() {
    double x, y, z;
    double result = 0;

    cout << "Enter x, y, z: ";
    cin >> x >> y >> z;

    try {

        try {
            // Внутрішній блок: слідкує за математикою в Алгоритмі 1
            cout << "Attempting Algorithm 1..." << endl;
            result = fun(x, y, z);
        }
        catch (ErrorMath& e) {
            // Крок 4.1: При помилці математики переходимо до Алгоритму
            e.Message();
            cout << "Switching to Algorithm 2 due to math error." << endl;
            result = fun_Algorithm2(x, y, z);
        }

    }
    catch (ErrorNoFile& e) {
        // Крок 6.4: При відсутності файлу переходимо до Алгоритму 3
        e.Message();
        cout << "Switching to Algorithm 3 due to file error." << endl;
        result = fun_Algorithm3(x, y, z);
    }
    catch (...) {
        cout << "Unknown error occurred." << endl;
        return 1;
    }

    cout << "\nFinal Result: " << result << endl;

    return 0;
}