#include "Building.h"
#include <iomanip> // Для setprecision
#include <cmath>

mutex printMutex;

Building::Building(string name, double x, double y, double speed, BuildingType type, int w, int h)
    : name(name), x(x), y(y), speed(speed), type(type) {

    setRandomTarget(w, h);

    lock_guard<mutex> lock(printMutex);
    cout << "[Spawn] " << name << " created at (" << x << ", " << y
         << ") targeting (" << targetX << ", " << targetY << ")" << endl;
}

void Building::setRandomTarget(int w, int h) {
    random_device rd;
    mt19937 gen(rd());

    if (type == CAPITAL) {
        // Ліва верхня чверть: x [0, w/2], y [0, h/2]
        uniform_real_distribution<> disX(0, w / 2.0);
        uniform_real_distribution<> disY(0, h / 2.0);
        targetX = disX(gen);
        targetY = disY(gen);
    } else {
        // Нижня права чверть: x [w/2, w], y [h/2, h]
        uniform_real_distribution<> disX(w / 2.0, w);
        uniform_real_distribution<> disY(h / 2.0, h);
        targetX = disX(gen);
        targetY = disY(gen);
    }
}



void Building::move() {
    string zoneName = (type == CAPITAL) ? "Ліва Верхня" : "Нижня Права";

    while (true) {
        double dx = targetX - x;
        double dy = targetY - y;
        double distance = sqrt(dx * dx + dy * dy);

        // Перевірка прибуття
        if (distance <= speed) {
            x = targetX;
            y = targetY;
            {
                lock_guard<mutex> lock(printMutex);
                cout << "[!] " << name << " ПРИБУВ у зону: " << zoneName << endl;
            }
            break;
        }

        x += (dx / distance) * speed;
        y += (dy / distance) * speed;

        {
            // Використовуємо м'ютекс ТІЛЬКИ на час виводу рядка
            lock_guard<mutex> lock(printMutex);

            // Очищення екрана для Windows
            // Щоб уникнути мерехтіння, ми просто виводимо статус
            cout << setw(12) << left << name
                 << " -> Поз: (" << setw(3) << (int)x << "," << setw(3) << (int)y << ")"
                 << " Ціль: " << zoneName << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}