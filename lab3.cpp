#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>


int main()
{
    // задаём начальные параметры dt, h и прочие

    float h = 0.1;
    int N = 11;

    float dt = 0.1;
    int N_t = 11;

    float x_min = 0.0;
    float x_max = 1.0;
    float t_min = 0.0;
    float t_max = 1.0;


    // задаём пустой вектор необходимой величины

    std::vector<std::vector<float>> u;

    for (int k = 0; k < N_t; k++)
    {
        std::vector<float> tmp_vector(N + 1, -10000.0);
        u.push_back(tmp_vector);
    }

    // заполняем нулевые элементы вектора координатой по t

    for (int k = 0; k < N_t; k++)
    {
        u[k][0] = t_min + k * dt;
    }

    // задаём u[0][j] по начальному условию
    for (int j = 1; j <= N; j++)
    { 
        u[0][j] = (j - 1) * h;
    }

    // задаём n = 0;
    int n = 0;

    while (n < N_t - 1)
    {
        // ищем по граничным условиям

        u[n + 1][N] = std::exp((n + 1) * dt);
        std::cout << u[n + 1][N] << " ";

        // ищем по рекурентке
        for (int j = N - 1; j >= 1; j--)
        {
            u[n + 1][j] = (u[n][j] + dt / h * u[n + 1][j + 1]) / (1 + dt / h);
        }


        // увеличиваем n
        n++;
    }
    
    std::ofstream csv_out, txt_out;
    csv_out.open("./lab3/csv_out.csv");
    txt_out.open("./lab3/txt_out.txt");

    // выводим значения по x

    txt_out << "          ";

    std::string s = std::to_string(0.0);

    std::string x = ".", y = ",";
    size_t pos;
    while ((pos = s.find(x)) != std::string::npos) {
        s.replace(pos, 1, y);
    }

    csv_out << s << ".";

    float current_x = x_min;

    for (int n = 0; n < N; n++)
    {
        std::string s = std::to_string(current_x);

        std::string x = ".", y = ",";
        size_t pos;
        while ((pos = s.find(x)) != std::string::npos) {
            s.replace(pos, 1, y);
        }

        csv_out << s << ".";
        txt_out << std::setw(10) << s;

        current_x += h;
    }

    csv_out << "\n";
    txt_out << "\n";

    // вывод результата в файл

    for (int n = N_t - 1; n >= 0; n--)
    {
        for (int j = 0; j <= N; j++)
        {
            std::string s = std::to_string(u[n][j]);

            std::string x = ".", y = ",";
            size_t pos;
            while ((pos = s.find(x)) != std::string::npos) {
                s.replace(pos, 1, y);
            }

            csv_out << s << ".";
            txt_out << std::setw(10) << s;
        }

        csv_out << "\n";
        txt_out << "\n";
    }


    return 0;
}