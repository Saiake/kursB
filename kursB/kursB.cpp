#include <iostream>
#include <iomanip>
#include <math.h>

int main()
{
    system("chcp 1251");

    const double E = 0.0001;

    int size;
    
    bool metka = true;
    char in;

    while (metka) {
        std::cout << "Введите размер системы уравнений: ";

        if ((std::cin >> in).good() && isdigit(in)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            size = in - '0';

            metka = false;
        }
    }

    double** a = new double* [size];
    double** x = new double* [size];

    for (int i = 0; i < size; i++) {
        a[i] = new double[size + 1];
        x[i] = new double[2];
    }

    bool usl = true;
    
    while (usl) {
        std::cout << "Введите коэффициенты уравнений построчно" << std::endl;

        for (int i = 0; i < size; i++) {
            std::cout << i + 1 << ": ";

            for (int j = 0; j <= size; j++) {
                std::cin >> a[i][j];
            }
        }

        for (int i = 0; i < size; i++) {
            double max = a[i][0];
            int index = 0;
            double sum = 0;

            for (int j = 0; j < size; j++) {
                if (max < a[i][j]) {
                    max = a[i][j];
                    index = j;
                }
            }

            std::swap(a[i], a[index]);

            for (int j = 0; j < size; j++) {
                if (j != index) {
                    sum += a[i][j];
                }

                if (max <= sum) {
                    std::cout << "Не выполняется условие сходимости" << std::endl;
                }

                else {
                    usl = false;
                }
            }
        }
    }

    for (int i = 0; i < size; i++) {
        x[i][0] = 0;
        
        std::cout << std::setw(9) << 'x' << i + 1;
    }

    std::cout << std::endl;

    bool isWorking = true;
    int index = 1;
    
    while (isWorking) {
        std::cout << index << ":";
       
        for (int i = 0; i < size; i++) {
            x[i][1] = a[i][size];
            
            for (int j = 0; j < size; j++) {
                if (i != j) {
                    x[i][1] = x[i][1] - (a[i][j] * x[j][0]);
                }
            }

            x[i][1] = x[i][1] / a[i][i];
            x[i][1] = floor(x[i][1] * 100000) / 100000;

            std::cout << std::setw(10) << x[i][1];
        }

        std::cout << std::endl;

        for (int i = 0; i < size; i++) {
            if (x[i][0] - x[i][1] < E && x[i][1] - x[i][0] < E) {
                isWorking = false;
            }

            x[i][0] = x[i][1];
        }

        index++;
    }

    std::cout << "Ответ:" << std::endl;
    
    for (int i = 0; i < size; i++) {
        std::cout << 'x' << i << '=' << x[i][1] << std::endl;
    }
    
    std::cout << "Количество итераций: " << index - 1 << std::endl;

    return 0;
}