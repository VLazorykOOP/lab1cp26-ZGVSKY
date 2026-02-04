#include "Building.h"
#include <vector>

int run_lab2() {
    const int W = 100;
    const int H = 40;
    const double V = 2.5;

    system("cls"); // Початкове очищення екрана


    vector<Building> town;
    town.emplace_back("Мерія", 90, 35, V, CAPITAL, W, H);
    town.emplace_back("Склад", 10, 5, V, WOODEN, W, H);
    town.emplace_back("Школа", 80, 5, V, CAPITAL, W, H);
    town.emplace_back("Дача", 20, 30, V, WOODEN, W, H);

    vector<thread> threads;

    // Створення потоків
    for (int i = 0; i < town.size(); ++i) {
        threads.emplace_back(&Building::move, &town[i]);
    }

    // Очікування завершення
    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }

    cout << "\n[КІНЕЦЬ] Симуляція завершена." << endl;
    return 0;
}