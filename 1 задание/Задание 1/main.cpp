#include <iostream>
#include <memory>
#include "../decesion/Exercise.h"
#include "../decesion/IStreamGenerator.h"
#include "../decesion/RandomGenerator.h"
#include "../decesion/ConstantGenerator.h"
#include "../decesion/Task1.h"
#include "../decesion/Task2.h"
#include "../decesion/Task3.h"

using namespace miit::algebra;

/**
* @brief Перечисление для выбора способа заполнения массива
*/
enum class FillMethod {
    RANDOM,
    KEYBOARD
};

/**
* @brief Функция для безопасного ввода целого числа
* @param prompt сообщение для пользователя
* @return введенное число
*/
int input_int(const std::string& prompt) {
    std::cout << prompt;
    int value;
    while (!(std::cin >> value)) {
        std::cout << "Ошибка ввода! Пожалуйста, введите целое число: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return value;
}

/**
* @brief Функция для выбора способа заполнения
* @return выбранный способ заполнения
*/
FillMethod choose_fill_method() {
    std::cout << "\nВыберите способ заполнения массива:\n";
    std::cout << "1 - Случайные числа\n";
    std::cout << "2 - Ввод с клавиатуры\n";

    int choice;
    do {
        choice = input_int("Ваш выбор (1 или 2): ");
    } while (choice != 1 && choice != 2);

    // Убрана строка с тернарным оператором
    if (choice == 1) {
        return FillMethod::RANDOM;
    }
    else {
        return FillMethod::KEYBOARD;
    }
}

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    try {
        std::cout << "=== Демонстрация работы с матрицей ===\n";

        int size = input_int("Введите размер массива: ");
        if (size <= 0) {
            std::cout << "Размер массива должен быть положительным!\n";
            return 1;
        }

        // Создание матрицы
        auto matrix = std::make_unique<Matrix>(static_cast<size_t>(size));
        std::unique_ptr<Generator> generator;

        // Выбор способа заполнения с использованием switch case
        FillMethod method = choose_fill_method();

        switch (method) {
        case FillMethod::RANDOM: {
            int min_val = input_int("Введите минимальное значение: ");
            int max_val = input_int("Введите максимальное значение: ");

            if (min_val > max_val) {
                std::cout << "Минимальное значение не может быть больше максимального!\n";
                return 1;
            }

            generator = std::make_unique<RandomGenerator>(min_val, max_val);
            break;
        }
        case FillMethod::KEYBOARD: {
            std::cout << "Введите " << size << " целых чисел:\n";
            generator = std::make_unique<IStreamGenerator>();
            break;
        }
        default: {
            std::cout << "Неизвестный метод заполнения!\n";
            return 1;
        }
        }

        // Заполнение матрицы
        matrix->fill(std::move(generator));

        std::cout << "\n=== Исходный массив ===\n";
        std::cout << matrix->to_string() << std::endl;

        // Задание 1
        std::cout << "\n=== Задание 1: Замена последнего отрицательного элемента ===\n";
        auto task1_matrix = std::make_unique<Matrix>(*matrix);
        auto task1 = std::make_unique<Task1Exercise>(
            std::move(task1_matrix),
            std::make_unique<ConstantGenerator>(0)
        );
        std::cout << "До: " << matrix->to_string() << std::endl;
        task1->Task();
        auto result1 = task1->get_result();
        std::cout << "После: " << result1->to_string() << std::endl;

        // Задание 2
        std::cout << "\n=== Задание 2: Удаление элементов с повторяющимися цифрами ===\n";
        auto task2_matrix = std::make_unique<Matrix>(*matrix);
        auto task2 = std::make_unique<Task2Exercise>(
            std::move(task2_matrix),
            std::make_unique<ConstantGenerator>(0)
        );
        std::cout << "До: " << matrix->to_string() << std::endl;
        task2->Task();
        auto result2 = task2->get_result();
        std::cout << "После: " << result2->to_string() << std::endl;

        // Задание 3
        std::cout << "\n=== Задание 3: Преобразование массива ===\n";
        auto task3_matrix = std::make_unique<Matrix>(*matrix);
        auto task3 = std::make_unique<Task3Exercise>(
            std::move(task3_matrix),
            std::make_unique<ConstantGenerator>(0)
        );
        std::cout << "До: " << matrix->to_string() << std::endl;
        task3->Task();
        auto result3 = task3->get_result();
        std::cout << "После: " << result3->to_string() << std::endl;

        // Демонстрация операторов
        std::cout << "\n=== Демонстрация операторов ===\n";
        auto matrix_ops = std::make_unique<Matrix>(*matrix);

        if (matrix_ops->size() > 0) {
            std::cout << "matrix[0] = " << (*matrix_ops)[0] << std::endl;
        }

        *matrix_ops << 999;
        std::cout << "После matrix << 999: " << matrix_ops->to_string() << std::endl;

        int extracted;
        *matrix_ops >> extracted;
        std::cout << "Извлеченный элемент: " << extracted << std::endl;
        std::cout << "После извлечения: " << matrix_ops->to_string() << std::endl;

        if (matrix_ops->size() > 0) {
            const int* data_ptr = **matrix_ops;
            std::cout << "Первый элемент через указатель: " << *data_ptr << std::endl;
        }

        std::cout << "\n=== Программа завершена успешно ===\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Неизвестная ошибка!" << std::endl;
        return 1;
    }

    return 0;
}