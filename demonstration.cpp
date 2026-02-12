#include "matrix_library.h"

// تابع اصلی برنامه => منوی اصلی
int main(){

    int MainChoice;

    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "       MATRIX & VECTOR CALCULATOR";
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    do{ // نمایش منوی اصلی
        while(1){
            cout << "\n   ~~~ Main Menu ~~~\n";
            cout << "1. Matrix Operations\n";
            cout << "2. Vector Operations\n";
            cout << "0. Exit\n";
            cout << "Choose: ";
            cin >> MainChoice;

            // در صورتیکه کاربر مقدار غیرصحیح وارد کند
            if (cin.fail()){
                cout << "\nERROR: Invalid input!\nTry again.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }else{
                break;
            }
        }

        switch(MainChoice){
            case 1:
                MatrixOperations();
                break;

            case 2:
                VectorOperations();
                break;

            case 0:
                cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                cout << "     Thank you for using this calculator!";
                cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    }while(MainChoice != 0);

    return 0;
}