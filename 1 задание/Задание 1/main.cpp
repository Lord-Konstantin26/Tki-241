#include <iostream>
#include <memory>
#include <limits>
#include "../decesion/Exercise.h"
#include "../decesion/IStreamGenerator.h"
#include "../decesion/RandomGenerator.h"
#include "../decesion/ConstantGenerator.h"
#include "../decesion/Task1.h"
#include "../decesion/Task2.h"
#include "../decesion/Task3.h"

namespace miit::algebra
{
    // Функция для безопасного ввода целых чисел
    int input_int(const std::string& prompt)
    {
        int value;
        while (true)
        {
            std::cout << prompt;
            if (std::cin >> value)
            {
                break;
            }
            else
            {
                std::cout << "Ошибка ввода! Пожалуйста, введите целое число.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        return value;
    }

    // Функция для выбора метода заполнения
    int choose_fill_method()
    {
        std::cout << "\n=== Выбор метода заполнения матрицы ===\n";
        std::cout << "1 - Заполнить случайными числами\n";
        std::cout << "2 - Ввести значения с клавиатуры\n";

        int choice;
        do
        {
            choice = input_int("Ваш выбор (1 или 2): ");
            switch (choice)
            {
            case 1:
            case 2:
                return choice;
            default:
                std::cout << "Неверный выбор! Пожалуйста, введите 1 или 2.\n";
                break;
            }
        } while (true);
    }

    // Функция для выбора задания
    int choose_task()
    {
        std::cout << "\n=== Выбор задания ===\n";
        std::cout << "1 - Задание 1 (замена последнего отрицательного)\n";
        std::cout << "2 - Задание 2 (удаление с повторяющимися цифрами)\n";
        std::cout << "3 - Задание 3 (преобразование по правилу)\n";
        std::cout << "0 - Выход\n";

        int choice;
        do
        {
            choice = input_int("Ваш выбор (0-3): ");
            switch (choice)
            {
            case 0:
            case 1:
            case 2:
            case 3:
                return choice;
            default:
                std::cout << "Неверный выбор! Пожалуйста, введите число от 0 до 3.\n";
                break;
            }
        } while (true);
    }

    // Основная функция приложения
    void run_application()
    {
        std::cout << "=== Система выполнения заданий над матрицами ===\n";

        while (true)
        {
            int task_choice = choose_task();

            if (task_choice == 0)
            {
                std::cout << "Выход из программы.\n";
                break;
            }

            // Ввод размера матрицы
            int size;
            do
            {
                size = input_int("Введите размер матрицы (1-100): ");
                if (size >= 1 && size <= 100)
                {
                    break;
                }
                std::cout << "Неверный размер! Пожалуйста, введите число от 1 до 100.\n";
            } while (true);

            // Создание матрицы
            auto matrix = std::make_unique<Matrix>(static_cast<size_t>(size));
            std::unique_ptr<Generator> generator;

            // Выбор метода заполнения
            int fill_method = choose_fill_method();

            switch (fill_method)
            {
            case 1:
                generator = std::make_unique<RandomGenerator>(-100, 100);
                break;
            case 2:
                std::cout << "Введите " << size << " элементов матрицы:\n";
                generator = std::make_unique<IStreamGenerator>();
                break;
            }

            // Заполнение матрицы
            matrix->fill(std::move(generator));
            std::cout << "Исходная матрица: " << matrix->to_string() << "\n";

            // Выполнение выбранного задания
            std::unique_ptr<Matrix> result;

            switch (task_choice)
            {
            case 1:
            {
                auto task1 = std::make_unique<Task1Exercise>(std::move(matrix), nullptr);
                task1->Task();
                result = task1->get_result();
                break;
            }
            case 2:
            {
                auto task2 = std::make_unique<Task2Exercise>(std::move(matrix), nullptr);
                task2->Task();
                result = task2->get_result();
                break;
            }
            case 3:
            {
                auto task3 = std::make_unique<Task3Exercise>(std::move(matrix), nullptr);
                task3->Task();
                result = task3->get_result();
                break;
            }
            }

            if (result)
            {
                std::cout << "Результат: " << result->to_string() << "\n";
            }

            std::cout << "\n" << std::string(50, '=') << "\n";
        }
    }
}

int main()
{
    miit::algebra::run_application();
    return 0;
}