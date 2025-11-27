#pragma once
#include "Exercise.h"
#include <array>

namespace miit::algebra
{
    /**
    * @brief Реализация задания 2: удаление элементов с повторяющимися цифрами
    */
    class Task2Exercise : public Exercise
    {
    public:
        /**
        * @brief Конструктор - явный вызов конструктора базового класса
        * @param matrix матрица для обработки
        * @param generator генератор значений
        */
        explicit Task2Exercise(std::unique_ptr<Matrix> matrix, std::unique_ptr<Generator> generator);

        /**
        * @brief Выполняет задание 2
        */
        void Task() override;

        /**
        * @brief Возвращает результат задания 2
        * @return уникальный указатель на результирующую матрицу
        */
        std::unique_ptr<Matrix> get_result() const;

    private:
        /**
        * @brief Проверяет есть ли в числе повторяющиеся цифры
        * @param number число для проверки
        * @return true если есть повторяющиеся цифры, иначе false
        */
        static bool has_repeating_digits(int number);

        std::unique_ptr<Matrix> result;
    };
}