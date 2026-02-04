#include <iostream>



#include "op_lab_1/lab1.h"
#include "op_lab_2/building.h"

using namespace std;

int main() {
    int choice;
    system("chcp 65001");
    while (true) {
        cout << "\n===== ======= =====" << endl;
        cout << "1. Run  #1" << endl;
        cout << "2. Run  #2" << endl;
        cout << "1. Run  #3" << endl;
        cout << "2. Run  #4" << endl;
        cout << "1. Run  #5" << endl;
        cout << "0. Exit" << endl;
        cout << "::: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1:
                   run_lab1();
                   break;
            case 2:
                    run_lab2();
                    break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}