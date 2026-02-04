#pragma once
#include "Exceptions.h"

// Функції роботи з таблицями
double T(double x);
double U(double x);

// Алгоритм 1
double Glr(double x, double y);
double Gold(double x, double y);
double Srz(double x, double y, double z);
double Grs(double x, double y);
double fun(double x, double y, double z);

// Резервні алгоритми
double fun_Algorithm2(double x, double y, double z);
double fun_Algorithm3(double x, double y, double z);

double Glr1(double x, double y);
double Gold1(double x, double y);
double Grsl(double x, double y, double z); // Основна формула розрахунку коефіцієнтів

int run_lab1();
