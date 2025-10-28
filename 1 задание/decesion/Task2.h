#pragma once
#include "Exercise.h"

namespace miit::algebra
{
    /**
    * @brief Реализация задания 2: удаление элементов с повторяющимися цифрами
    */
    class Task2Exercise : public Exercise
    {
    public:
        using Exercise::Exercise;

        /**
        * @brief Проверяет есть ли в числе повторяющиеся цифры
        * @param number число для проверки
        * @return true если есть повторяющиеся цифры, иначе false
        */
        static bool has_repeating_digits(int number);

        /**
        * @brief Подсчитывает количество элементов без повторяющихся цифр
        * @return количество элементов без повторяющихся цифр
        */
        size_t count_elements_without_repeats() const;

        /**
        * @brief Создает новую матрицу без элементов с повторяющимися цифрами
        * @return новая матрица
        */
        std::unique_ptr<Matrix> Task2() override;

        void Task1() override {}
        std::unique_ptr<Matrix> Task3() override { return nullptr; }
    };
}