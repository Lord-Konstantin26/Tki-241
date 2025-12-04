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
    enum class TaskChoice {
        EXIT = 0,
        TASK1 = 1,
        TASK2 = 2,
        TASK3 = 3
    };

    enum class FillMethod {
        RANDOM = 1,
        KEYBOARD = 2
    };

    const int MIN_SIZE = 1;
    const int MAX_SIZE = 100;
    const int MIN_RANDOM = -100;
    const int MAX_RANDOM = 100;


    int input_int(const std::string& prompt)
    {
        int value;
        std::cout << prompt;
        if (std::cin >> value)
        {
            return value;
        }
        else
        {
            std::cout << "Ошибка ввода! Программа завершена.\n";
            std::exit(1);
        }
    }

    // Функция для выбора метода заполнения
    FillMethod choose_fill_method()
    {
        std::cout << "\n=== Выбор метода заполнения матрицы ===\n";
        std::cout << static_cast<int>(FillMethod::RANDOM) << " - Заполнить случайными числами\n";
        std::cout << static_cast<int>(FillMethod::KEYBOARD) << " - Ввести значения с клавиатуры\n";

        int choice = input_int("Ваш выбор (1 или 2): ");

        switch (choice)
        {
        case static_cast<int>(FillMethod::RANDOM):
            return FillMethod::RANDOM;
        case static_cast<int>(FillMethod::KEYBOARD):
            return FillMethod::KEYBOARD;
        default:
            std::cout << "Неверный выбор! Программа завершена.\n";
            std::exit(1);
        }
    }

    // Функция для выбора задания
    TaskChoice choose_task()
    {
        std::cout << "\n=== Выбор задания ===\n";
        std::cout << static_cast<int>(TaskChoice::TASK1) << " - Задание 1 (замена последнего отрицательного)\n";
        std::cout << static_cast<int>(TaskChoice::TASK2) << " - Задание 2 (удаление с повторяющимися цифрами)\n";
        std::cout << static_cast<int>(TaskChoice::TASK3) << " - Задание 3 (преобразование по правилу)\n";
        std::cout << static_cast<int>(TaskChoice::EXIT) << " - Выход\n";

        int choice = input_int("Ваш выбор (0-3): ");

        switch (choice)
        {
        case static_cast<int>(TaskChoice::EXIT):
            return TaskChoice::EXIT;
        case static_cast<int>(TaskChoice::TASK1):
            return TaskChoice::TASK1;
        case static_cast<int>(TaskChoice::TASK2):
            return TaskChoice::TASK2;
        case static_cast<int>(TaskChoice::TASK3):
            return TaskChoice::TASK3;
        default:
            std::cout << "Неверный выбор! Программа завершена.\n";
            std::exit(1);
        }
    }

    // Основная функция приложения
    void run_application()
    {
        std::cout << "=== Система выполнения заданий над матрицами ===\n";

        while (true)
        {
            TaskChoice task_choice = choose_task();

            if (task_choice == TaskChoice::EXIT)
            {
                std::cout << "Выход из программы.\n";
                break;
            }

            // Ввод размера матрицы
            int size = input_int("Введите размер матрицы (1-100): ");
            if (size < MIN_SIZE || size > MAX_SIZE)
            {
                std::cout << "Неверный размер! Программа завершена.\n";
                std::exit(1);
            }

            // Создание матрицы
            auto matrix = std::make_unique<Matrix>(static_cast<size_t>(size));
            std::unique_ptr<Generator> generator;

            // Выбор метода заполнения
            FillMethod fill_method = choose_fill_method();

            switch (fill_method)
            {
            case FillMethod::RANDOM:
                generator = std::make_unique<RandomGenerator>(MIN_RANDOM, MAX_RANDOM);
                break;
            case FillMethod::KEYBOARD:
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
            case TaskChoice::TASK1:
            {
                auto task1 = std::make_unique<Task1Exercise>(std::move(matrix), nullptr);
                task1->Task();
                result = task1->get_result();
                break;
            }
            case TaskChoice::TASK2:
            {
                auto task2 = std::make_unique<Task2Exercise>(std::move(matrix), nullptr);
                task2->Task();
                result = task2->get_result();
                break;
            }
            case TaskChoice::TASK3:
            {
                auto task3 = std::make_unique<Task3Exercise>(std::move(matrix), nullptr);
                task3->Task();
                result = task3->get_result();
                break;
            }
            default:
                break;
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