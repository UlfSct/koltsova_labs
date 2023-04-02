#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>


int main()
{
    // ����� ��������� ��������� dt, h � ������

    float h = 0.1;
    int N = 11;

    float dt[2] = {0.1, 0.001};
    int N_t[2] = {11, 1001};

    float x_min = 0.0;
    float x_max = 1.0;
    float t_min = 0.0;
    float t_max = 1.0;
    

    // ���� �� dt
    for (int i = 0; i < 2; i++)
    {
        // ��������� ������� ������������
        if (dt[i] / h / h > 0.5)
        {
            std::cout << "stability condition is not met" << std::endl;
            continue;
        }


        // ����� ������ ������ ����������� ��������

        std::vector<std::vector<float>> u;

        for (int k = 0; k < N_t[i]; k++)
        {
            std::vector<float> tmp_vector(N + 1, -10000.0);
            u.push_back(tmp_vector);
        }

        // ��������� ������� �������� ������� ����������� �� t

        for (int k = 0; k < N_t[i]; k++)
        {
            u[k][0] = t_min + k * dt[i];
        }

        // ����� u[0][j] �� ���������� �������
        for (int j = 1; j <= N; j++)
        { 
            u[0][j] = (j - 1) * h * (j - 1) * h;
        }

        // ����� n = 0;
        int n = 0;

        while (n < N_t[i] - 1)
        {
            // ���� �� ����������
            for (int j = 2; j < N; j++)
            {
                u[n + 1][j] = u[n][j] + dt[i] / h / h * (u[n][j + 1] - 2 * u[n][j] + u[n][j - 1]) - dt[i];
            }

            // ���� �� ��������� ��������

            u[n + 1][1] = (n + 1) * dt[i];
            u[n + 1][N] = (n + 1) * dt[i] + 1;

            // ����������� n
            n++;
        }
        
        std::ofstream csv_out, txt_out;
        csv_out.open("./lab1/csv_out" + std::to_string(i) + ".csv");
        txt_out.open("./lab1/txt_out" + std::to_string(i) + ".txt");

        // ������� �������� �� x

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

        // ����� ���������� � ����

        for (int n = N_t[i] - 1; n >= 0; n--)
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
    }


    return 0;
}