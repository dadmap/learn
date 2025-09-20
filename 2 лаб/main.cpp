#include <iostream>
#include <cstdio>
#include <locale>
#include <windows.h>

using namespace std;

const int NMAX = 100;

// --- Функция чтения матрицы ---
bool ReadMatrixFromFile(const char* fname, int mat[NMAX][NMAX], int &n, int &m) {
    FILE* f = fopen(fname, "r");
    if (!f) {
        cout << "Ошибка: невозможно открыть файл '" << fname << "'\n";
        return false;
    }

    if (fscanf(f, "%d %d", &n, &m) != 2) {
        cout << "Ошибка: неверный формат в файле '" << fname << "'\n";
        fclose(f);
        return false;
    }

    if (n <= 0 || m <= 0 || n > NMAX || m > NMAX) {
        cout << "Ошибка: неверные размеры матрицы в файле '" << fname << "'\n";
        fclose(f);
        return false;
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (fscanf(f, "%d", &mat[i][j]) != 1) {
                cout << "Ошибка: недостаточно данных в файле '" << fname << "'\n";
                fclose(f);
                return false;
            }

    fclose(f);
    cout << "Файл '" << fname << "' успешно прочитан. Размер: " << n << "x" << m << "\n";
    return true;
}

// --- Функция проверки строки на отрицательные ---
bool RowHasNegative(const int row[], int m) {
    bool hasNeg = false;
    int j = 0;
    while (j < m && !hasNeg) {
        if (row[j] < 0) hasNeg = true;
        ++j;
    }
    return hasNeg;
}

// --- Функция проверки матрицы на ноль ---
bool HasZeroInMatrix(const int mat[NMAX][NMAX], int n, int m) {
    bool hasZero = false;
    int i = 0;
    while (i < n && !hasZero) {
        int j = 0;
        while (j < m && !hasZero) {
            if (mat[i][j] == 0) hasZero = true;
            ++j;
        }
        ++i;
    }
    return hasZero;
}

// --- Функция вывода матрицы ---
void PrintMatrix(const int mat[NMAX][NMAX], int n, int m, const char* name) {
    cout << "Матрица " << name << " (" << n << "x" << m << "):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }
}

// --- Функция вывода результата проверки строки ---
void PrintRowCheck(int rowIndex, bool hasNeg) {
    cout << "Строка " << rowIndex + 1 << ": " 
         << (hasNeg ? "содержит отрицательные элементы" : "не содержит отрицательных элементов") 
         << "\n";
}

// --- Главная функция обработки матрицы ---
void ProcessMatrix(const int mat[NMAX][NMAX], int n, int m, const char* name) {
    PrintMatrix(mat, n, m, name);

    bool hasZero = HasZeroInMatrix(mat, n, m);
    if (!hasZero) {
        cout << "В матрице " << name << " нет элементов, равных 0.\n\n";
        return;
    }

    cout << "В матрице " << name << " найдены элементы, равные 0.\n";
    cout << "Проверка каждой строки на наличие отрицательных элементов:\n";
    for (int i = 0; i < n; ++i) {
        bool hasNeg = RowHasNegative(mat[i], m);
        PrintRowCheck(i, hasNeg);
    }
    cout << "\n";
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    if (argc < 3) {
        cout << "Недостаточно параметров!\n";
        cout << "Использование: " << argv[0] << " <файл_матрицы_1> <файл_матрицы_2>\n";
        return 1;
    }

    int n1=0, m1=0, n2=0, m2=0;

    if (!ReadMatrixFromFile(argv[1], A, n1, m1)) return 2;
    if (!ReadMatrixFromFile(argv[2], B, n2, m2)) return 3;

    cout << "\n=== Обработка матриц ===\n\n";

    ProcessMatrix(A, n1, m1, "A");
    ProcessMatrix(B, n2, m2, "B");


    return 0;
}
