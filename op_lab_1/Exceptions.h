#pragma once
#include <iostream>
#include <string>

using namespace std;

// Базовий клас помилки
class ErrorCalculation {
public:
    string message;
    ErrorCalculation(string m) : message(m) {}
    virtual void Message() { cout << "Calculation Error: " << message << endl; }
};

class ErrorNoFile {
    string fileName;
public:
    ErrorNoFile(string s) : fileName(s) {}
    void Message() { cout << "ErrorNoFile: " << fileName << endl; }
};

// Помилка математична (ділення на нуль, корінь з від'ємного)
class ErrorMath : public ErrorCalculation {
public:
    double val;
    ErrorMath(string m, double v) : ErrorCalculation(m), val(v) {}
    void Message() override { cout << message << " at value: " << val << endl; }
};