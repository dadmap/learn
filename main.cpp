#include <cstdio>
#include <locale.h>
#include <windows.h>
#include <fstream>
const int nmax = 100;

int ArrayInput(int* n, double x[], char* fname) {
    FILE* file;
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");
    if ((file = fopen(fname, "r")) == NULL) {
        printf("Невозможно открыть файл '%s'\n", fname);
        return 0;
    }
    if (fscanf(file, "%d", n) < 1) {
        printf("Ошибка чтения из файла '%s'\n", fname);
        fclose(file);
        return 0;
    }
    if (*n < 0 || *n > nmax) {
        printf("Кол-во элементов массива должно быть от 1 до %d! (файл '%s')\n", nmax, fname);
        fclose(file);
        return 0;
    }
    for (int i = 0; i < *n; i++) {
        if (fscanf(file, "%lf", &x[i]) < 1) {
            printf("Ошибка чтения из файла '%s'\n", fname);
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}

double Sum(double x[], int n, double d1, double d2,int* cnt) {
    *cnt =0;
    double s = 0;
    for (int i = 0; i < n; i++)
        if (x[i] >= d1 && x[i] <= d2)
            s += x[i];
            (*cnt)++;
    return s;
}

void PrintArray(const char* name, double x[], int n) {
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");
    printf("Массив %s (%d элементов): ", name, n);
    for (int i = 0; i < n; i++)
        printf("%.2lf ", x[i]);
    printf("\n");
}

int main(int argc, char* argv[]) {
    double a[nmax], b[nmax], c[nmax];
    double suma, sumb, sumc, maxsum;
    int na, nb, nc;
    double d1, d2;
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");

   
    if (argc < 4) {
        printf("Недостаточно параметров!\n");
        return 1;
    }
    if (!ArrayInput(&na, a, argv[1])) return 1;
    if (!ArrayInput(&nb, b, argv[2])) return 1;
    if (!ArrayInput(&nc, c, argv[3])) return 1;

    printf("=== Исходные данные ===\n");
    PrintArray("A", a, na);
    PrintArray("B", b, nb);
    PrintArray("C", c, nc);
    printf("=======================");

    printf("Введите нижнюю границу диапазона: ");
    scanf("%lf", &d1);
    printf("Введите верхнюю границу диапазона, большую нижней: ");
    scanf("%lf", &d2);
    int ca =0, cb = 0, cc=0;
    suma = Sum(a, na, d1, d2, &ca);
    sumb = Sum(b, nb, d1, d2, &cb);
    sumc = Sum(c, nc, d1, d2, &cc);
    if (d1>d2) {
        printf("Не корректно введены границы ");
    }
    else{
    
    printf("\n--- Результаты ---\n");
    if (ca!=0) {
    printf("Сумма массива A: %.3lf\n", suma);
    }
    else{
    printf("элементы A не попадают в диапазон");}
    if (cb!=0) {
    printf("Сумма массива B: %.3lf\n", sumb); 
    }
    else{
    printf("элементы B не попадают в диапазон");
    }
    if (cc!=0){
    printf("Сумма массива C: %.3lf\n", sumc);
    }
    else{
    printf("элементы C не попадают в диапазон");
    }
    

    maxsum = suma;
    if (sumb > maxsum) maxsum = sumb;
    if (sumc > maxsum) maxsum = sumc;

    if (suma == maxsum && sumb == maxsum && sumc == maxsum)
        printf("Массивы A, B, C имеют одинаковую максимальную сумму: %.3lf\n", maxsum);
    else if (suma == maxsum && sumb == maxsum)
        printf("Массивы A и B имеют одинаковую максимальную сумму: %.3lf\n", maxsum);
    else if (suma == maxsum && sumc == maxsum)
        printf("Массивы A и C имеют одинаковую максимальную сумму: %.3lf\n", maxsum);
    else if (sumb == maxsum && sumc == maxsum)
        printf("Массивы B и C имеют одинаковую максимальную сумму: %.3lf\n", maxsum);
    else if (suma == maxsum)
        printf("Массив A имеет максимальную сумму: %.3lf\n", maxsum);
    else if (sumb == maxsum)
        printf("Массив B имеет максимальную сумму: %.3lf\n", maxsum);
    else
        printf("Массив C имеет максимальную сумму: %.3lf\n", maxsum);
}
}