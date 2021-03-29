#include "Header.h"


using namespace std;

int main()
{
    int l = 1;
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    while (l != 0)
    {
        cout << endl << "Введите необходимый пункт: ";
        cout << endl << "1 - генерация секретного ключа методом Диффи-Хелмана ";
        cout << endl << "2 - алгоритм RSA";
        cout << endl << "3 - алгоритм Эль-Гамаля" << endl;
        cout << endl << "0 - выход" << endl;
        cin >> l;
        system("cls");
     

        switch (l)
        {
        case 1: {
            int p, g, a, b, A, B, S1, S2;
            cout << "Введите первое простое число: "; cin >> p;
            cout << "Введите второе простое число: "; cin >> g;
            cout << "Введите секретный ключ 1-го человека: "; cin >> a;
            cout << "Введите секретный ключ 2-го человека: "; cin >> b;
            A = power(g, a, p);
            B = power(g, b, p);
            cout << "Открытый ключ 1-го человека: "; cout << A;
            cout << endl << "Открытый ключ 2-го человека: "; cout << B;
            S1 = power(A, b, p);
            S2 = power(A, b, p);
            cout << endl << "Секретный ключ, полученный 1-м человеком: "; cout << S1;
            cout << endl << "Секретный ключ, полученный 2-м человеком: "; cout << S2;
            break;
            }
        case 2: {
            int e, n, d; int text; int output, result;
            e = 17;
            cout << "Введите число для шифрования: "; cin >> text;
            n = 493;
            d = 369;
            cout << "-------------------------" << endl;
            cout << "Открытая экспонента: "; cout << e << endl;
            cout << "Секретная экспонента: "; cout << d << endl;
            cout << "Модуль: "; cout << n << endl;
            cout << "-------------------------" << endl;
            output = modpow(text, e, n);
            cout << "Зашифрованный текст: "; cout << output << endl;
            result = modpow(output,d,n);
            cout << "Расшифрованный текст: "; cout << result << endl;
            break;
        }
        case 3: {
            int p, g, x, b;
            string inFileName = "D:\\ALEX\\STUDY\\4SEM_2COURSE\\Основы защиты информации\\ОЗИ\\Лабораторные работы\\6\\OSI_6\\OSI_6\\test.txt";
            string outFileName = "D:\\ALEX\\STUDY\\4SEM_2COURSE\\Основы защиты информации\\ОЗИ\\Лабораторные работы\\6\\OSI_6\\OSI_6\\out.txt";
            string result = "D:\\ALEX\\STUDY\\4SEM_2COURSE\\Основы защиты информации\\ОЗИ\\Лабораторные работы\\6\\OSI_6\\OSI_6\\result.txt";
            srand(time(0));
            p = 11;
            g = 2;
            cout << "Первый ключ p: "; cout << p << endl;
            cout << "Второй ключ g : "; cout << g << endl;
            x = 8 ;
            cout << "Случайное число x (1<x<p): " << x << endl;
            crypt(p, g, x, inFileName, outFileName);
            decrypt(p, x, outFileName, result);
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

int mul(int a, int b, int n) 
{// a*b mod n 
    int sum = 0;

    for (int i = 0; i < b; i++) {
        sum += a;

        if (sum >= n) {
            sum -= n;
        }
    }

    return sum;
}

void crypt(int p, int g, int x, string inFileName, string outFileName) {
    ifstream inf(inFileName.c_str());
    ofstream outf(outFileName.c_str());

    int y = power(g, x, p);

    cout << "Открытый ключ (p,g,y)=" << "(" << p << "," << g << "," << y << ")" << endl;
    cout << "Закрытый ключ x=" << x << endl;

    cout << "\nШифруемый текст:" << endl;

    while (inf.good()) {
        int m = inf.get();
        if (m > 0) {
            cout << (char)m;
            int k = 9; // 1 < k < (p-1) 
            int a = power(g, k, p);
            int b = ((int)(pow(y,k) * (m - 48))) % p;
            cout << "(" << a << "," << b << ")" << endl;
            outf <<  a << " " << b << " " ;
        }
    }

    wcout << endl;

    inf.close();
    outf.close();
}

void decrypt(int p, int x, string inFileName, string outFileName) {
    ifstream inf(inFileName.c_str());
    ofstream outf(outFileName.c_str());

    cout << "\nДешифрованый текст:" << endl;
    while (inf.good()) {
        int a = 0;
        int b = 0;
        inf >> a;
        inf >> b;

        if (a != 0 && b != 0) {
            //wcout<<a<<" "<<b<<endl; 

            int deM = mul(b, power(a, p - 1 - x, p), p);// m=b*(a^x)^(-1)mod p =b*a^(p-1-x)mod p - трудно было  найти нормальную формулу, в ней вся загвоздка 
            char m = static_cast<char>(deM + 48);
            outf << m;
            cout << m;
        }
    }

    wcout << endl;

    inf.close();
    outf.close();
}
