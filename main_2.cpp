#include <iostream>
#include <fstream>
#include <locale>
#include <windows.h>
#include <cstdio>
using namespace std;

const int nmax = 100;
bool ArrayInput(int* n, double x[], char* fname);
double Sum(double x[], int n, double d1, double d2);
void PrintArray(const char* name, double x[], int n);
int main(int argc, char* argv[]) {
    double a[nmax], b[nmax], c[nmax];
    double suma, sumb, sumc, maxsum;
    int na, nb, nc;
    double d1, d2;

    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    if (argc < 4) {
        cout << "Недостаточно параметров!\n";
        return 1;
    }

    if (!ArrayInput(&na, a, argv[1])) return 1;
    if (!ArrayInput(&nb, b, argv[2])) return 1;
    if (!ArrayInput(&nc, c, argv[3])) return 1;

    cout << "\n=== Исходные данные ===\n";
    PrintArray("A", a, na);
    PrintArray("B", b, nb);
    PrintArray("C", c, nc);
    cout << "=======================\n\n";

    cout << "Введите нижнюю границу диапазона: ";
    cin >> d1;

    cout << "Введите верхнюю границу диапазона, большую нижней: ";
    cin >> d2;

    suma = Sum(a, na, d1, d2);
    sumb = Sum(b, nb, d1, d2);
    sumc = Sum(c, nc, d1, d2);
    if (d1>d2) {
        printf("Не корректно введены границы ");
    }
    else{
    cout << "\n--- Результаты ---\n";
    cout << "Сумма массива A: " << suma << endl;
    cout << "Сумма массива B: " << sumb << endl;
    cout << "Сумма массива C: " << sumc << endl;

    maxsum = suma;
    if (sumb > maxsum) maxsum = sumb;
    if (sumc > maxsum) maxsum = sumc;

    if (suma == maxsum && sumb == maxsum && sumc == maxsum) {
        cout << "Массивы A, B, C имеют одинаковую максимальную сумму элементов: "
             << maxsum << endl;
    } 
    else if (suma == maxsum && sumb == maxsum) {
        cout << "Массивы A и B имеют одинаковую максимальную сумму элементов: "
             << maxsum << endl;
    } 
    else if (suma == maxsum && sumc == maxsum) {
        cout << "Массивы A и C имеют одинаковую максимальную сумму элементов: "
             << maxsum << endl;
    } 
    else if (sumb == maxsum && sumc == maxsum) {
        cout << "Массивы B и C имеют одинаковую максимальную сумму элементов: "
             << maxsum << endl;
    } 
    else if (suma == maxsum) {
        cout << "Массив A имеет максимальную сумму элементов: " << maxsum << endl;
    } 
    else if (sumb == maxsum) {
        cout << "Массив B имеет максимальную сумму элементов: " << maxsum << endl;
    } 
    else if (sumc == maxsum) {
        cout << "Массив C имеет максимальную сумму элементов: " << maxsum << endl;
    }
}}
bool ArrayInput(int* n, double x[], char* fname) {
    FILE* file;
    if ((file = fopen(fname, "r")) == NULL) {
        cout << "Невозможно открыть файл '" << fname << "'\n";
        return false;
    }

    if (fscanf(file, "%d", n) < 1) {
        cout << "Ошибка чтения размера массива из файла '" << fname << "'\n";
        fclose(file);
        return false;
    }

    if (*n <= 0 || *n > nmax) {
        cout << "Количество элементов массива должно быть от 1 до " << nmax
             << " (файл '" << fname << "')\n";
        fclose(file);
        return false;
    }

    for (int i = 0; i < *n; i++) {
        if (fscanf(file, "%lf", &x[i]) < 1) {
            cout << "Ошибка чтения элемента №" << i + 1 << " из файла '" << fname << "'\n";
            fclose(file);
            return false;
        }
    }

    fclose(file);
    return true;
}

double Sum(double x[], int n, double d1, double d2) {
    double s = 0;
    for (int i = 0; i < n; i++) {
        if (x[i] >= d1 && x[i] <= d2) {
            s += x[i];
        }
    }
    return s;
}

void PrintArray(const char* name, double x[], int n) {
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    cout << "Массив " << name << " (" << n << " элементов): ";
    for (int i = 0; i < n; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
}

