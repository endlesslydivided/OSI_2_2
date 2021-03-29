#pragma once
#include <string>
#include <iostream>
#include <time.h>
#include <fstream>
#include <Windows.h>
#include <iostream>

int power(int a, int b, int n);
template <typename T>
T modpow(T base, T exp, T modulus);

using namespace std;

int main()
{
    int e, n, d; int text; int output, result;
    int l = 1;
    e = 17;
    n = 493;
    d = 369;
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    while (l != 0)
    {
        cout << endl << "Введите необходимый пункт: ";
        cout << endl << "1 - генерация ЭЦП";
        cout << endl << "0 - выход" << endl;
        cin >> l;
        system("cls");


        switch (l)
        {
        case 1: {
           
            cout << "Введите число для шифрования: "; cin >> text;
            cout << "-------------------------" << endl;
            cout << "Открытая экспонента: "; cout << e << endl;
            cout << "Секретная экспонента: "; cout << d << endl;
            cout << "Модуль: "; cout << n << endl;
            cout << "-------------------------" << endl;
            int   S1, S2;
            int N = 250; double A = 0.618033;
            int h = N * fmod(text * A, 2);
            cout << "Хеш-образ: "; cout << h << endl;
            S1 = power(h, d, n);
            cout << "Сообщение для 2-го человека (исходное сообщение; ЭЦП): "; cout << '(' << text << ';' << S1 << ')' << endl;
            S2 = power(S1, e, n);
            cout << "Вычисленное значение из хеш-образа: "; cout << S2 << endl;
            break;
        }
        default: break;
        }
    }
}

int power(int a, int b, int n)
{// a^b mod n
    int tmp = a;
    int sum = tmp;
    for (int i = 1; i < b; i++) {
        for (int j = 1; j < a; j++) {
            sum += tmp;
            if (sum >= n) {
                sum -= n;
            }
        }
        tmp = sum;
    }
    return tmp;
}

template <typename T>
T modpow(T base, T exp, T modulus) {
    base %= modulus;
    T result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}
