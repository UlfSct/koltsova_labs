#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <iomanip>


int main()
{
    // h и прочие

    double h[2] = {0.1, 0.01};
    int N[2] = {11, 101};
    double eps = 0.0001;


    double x_min = 0.0;
    double x_max = 1.0;
    double t_min = 0.0;
    double t_max = 1.0;
    double norm = eps + 1;

    

    // цикл по h
    for (int i = 0; i < 2; i++)
    {
        std::vector<double> u_prev(N[i] + 1, -10000.0);
        std::vector<double> u_curr(N[i] + 1, -10000.0);

        // задаём начальные значения
        int n = 0;
        for (int j = 1; j <= N[i]; j++)
        {
            u_prev[j] = 4 * (j - 1) * h[i] - 1;
        }
        u_prev[0] = n;

        // настройка вывода данных в файл
        std::ofstream fout;
        fout.open("out" + std::to_string(i) + ".txt");

        do
        {
            // рекурентное соотношение
            for (int j = 2; j <= N[i] - 1; j++)
            {
                u_curr[j] = (u_prev[j + 1] + (h[i] + 1) * u_prev[j - 1] + 4 * (j - 1) * h[i] * h[i] * h[i] - h[i] * h[i]) / (h[i] + 2);
            }

            // граничные условия
            u_curr[1] = 0;
            u_curr[N[i]] = 5;

            // счётчик по приколу
            u_curr[0] = n + 1;

            // считаем норму и сравниваем
            norm = 0;
            for (int j = 1; j <= N[i]; j++)
            {
                norm += (u_curr[j] - u_prev[j]) * (u_curr[j] - u_prev[j]);
            }
            norm *= h[i];
            norm = std::sqrt(norm);

            // выводим результаты
            for (int j = 0; j <= N[i]; j++)
            {
                if (i == 0 || (i == 1 && (j == 0 || j % 10 == 1)))
                {
                    fout << std::setw(10) << u_prev[j] << " ";
                }
            }
            fout << "\n";

            // переводим результаты на следующий шаг
            for (int j = 0; j <= N[i]; j++)
            {
                u_prev[j] = u_curr[j];
            }

            // переходим на следующий шаг
            n++;
        } 
        while (norm > eps);
    }


    return 0;
}