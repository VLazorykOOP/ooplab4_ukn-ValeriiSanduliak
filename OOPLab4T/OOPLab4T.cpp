// OOPLab4T.cpp : Цей файл містить є шаблоном для 
// виконання лаб. роботи №4. 
// Він містинь функцію "main" з якої починається та закінчується виконання програми.
//


#include <iostream>
using namespace std;
// Ваші файли загловки 
//
#include "Lab4Exmaple.h"
int main()
{
    cout << " Lab #4  !\n";
    char ch = '5';
    do {

        MenuTask();
        cout << " >>> ";
        ch = cin.get();

        cin.get();

        switch (ch) {
        case '1': task1();  break;
        case '2': task2();  break;
        case '3': task3();  break;
        case '4': return 0;
        }
        cout << " Press any key and enter\n";
        ch = cin.get();
    } while (ch != '5');

    return 0;

}