#include <iostream>
#include <memory>
#include "../decesion/Exercise.h"
#include "../decesion/IStreamGenerator.h"
#include "../decesion/RandomGenerator.h"
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

    return (choice == 1) ? FillMethod::RANDOM : FillMethod::KEYBOARD;
}

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    try {
        std::cout << "=== Демонстрация работы с матрицей ===\n";

        // Ввод размера массива
        int size = input_int("Введите размер массива: ");
        if (size <= 0) {
            std::cout << "Размер массива должен быть положительным!\n";
            return 1;
        }

        // Создание матрицы
        auto matrix = std::make_unique<Matrix>(static_cast<size_t>(size));
        std::unique_ptr<Generator> generator;

        // Выбор способа заполнения
        FillMethod method = choose_fill_method();

        if (method == FillMethod::RANDOM) {
            int min_val = input_int("Введите минимальное значение: ");
            int max_val = input_int("Введите максимальное значение: ");

            if (min_val > max_val) {
                std::cout << "Минимальное значение не может быть больше максимального!\n";
                return 1;
            }

            generator = std::make_unique<RandomGenerator>(min_val, max_val);
        }
        else {
            std::cout << "Введите " << size << " целых чисел:\n";
            generator = std::make_unique<IStreamGenerator>();
        }

        // Заполнение матрицы
        matrix->fill(std::move(generator));

        std::cout << "\n=== Исходный массив ===\n";
        std::cout << matrix->to_string() << std::endl;

        // Задание 1
        std::cout << "\n=== Задание 1: Замена последнего отрицательного элемента ===\n";
        auto task1 = std::make_unique<Task1Exercise>(
            std::make_unique<Matrix>(*matrix),
            std::make_unique<RandomGenerator>(0, 0) // заглушка
        );

        std::cout << "До: " << task1->get_matrix_string() << std::endl;
        task1->Task1();
        std::cout << "После: " << task1->get_matrix_string() << std::endl;

        // Задание 2
        std::cout << "\n=== Задание 2: Удаление элементов с повторяющимися цифрами ===\n";
        auto task2 = std::make_unique<Task2Exercise>(
            std::make_unique<Matrix>(*matrix),
            std::make_unique<RandomGenerator>(0, 0) // заглушка
        );

        auto result2 = task2->Task2();
        std::cout << "Результат: " << result2->to_string() << std::endl;

        // Задание 3
        std::cout << "\n=== Задание 3: Преобразование массива ===\n";
        auto task3 = std::make_unique<Task3Exercise>(
            std::make_unique<Matrix>(*matrix),
            std::make_unique<RandomGenerator>(0, 0) // заглушка
        );

        auto result3 = task3->Task3();
        std::cout << "Результат: " << result3->to_string() << std::endl;

        // Демонстрация операторов
        std::cout << "\n=== Демонстрация операторов ===\n";

        // Оператор []
        std::cout << "matrix[0] = " << (*matrix)[0] << std::endl;

        // Оператор << (добавление в начало)
        *matrix << 999;
        std::cout << "После matrix << 999: " << matrix->to_string() << std::endl;

        // Оператор >> (извлечение из начала)
        int extracted;
        *matrix >> extracted;
        std::cout << "Извлеченный элемент: " << extracted << std::endl;
        std::cout << "После извлечения: " << matrix->to_string() << std::endl;

        // Оператор * (указатель на данные)
        const int* data_ptr = **matrix;
        std::cout << "Первый элемент через указатель: " << *data_ptr << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}