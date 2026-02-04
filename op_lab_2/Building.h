#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>

using namespace std;

//  для синхронізації
extern mutex printMutex;

enum BuildingType { CAPITAL, WOODEN };

class Building {
public:
    string name;
    double x, y;
    double targetX, targetY;
    double speed;
    BuildingType type;

    // Конструктор
    Building(string name, double x, double y, double speed, BuildingType type, int w, int h);


    void move();

private:
    // визначення випадкової цілі у потрібній чверті
    void setRandomTarget(int w, int h);
};


int run_lab2();