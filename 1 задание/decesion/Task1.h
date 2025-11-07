#pragma once
#include "Exercise.h"
#include <cmath>

namespace miit::algebra
{
    /**
    * @brief Реализация задания 1: замена последнего отрицательного элемента на модуль первого элемента
    */
    class Task1Exercise : public Exercise
    {
    public:
        /**
        * @brief Конструктор - явный вызов конструктора базового класса
        * @param matrix матрица для обработки
        * @param generator генератор значений
        */
        explicit Task1Exercise(std::unique_ptr<Matrix> matrix, std::unique_ptr<Generator> generator)
            : Exercise(std::move(matrix), std::move(generator)) {
        }

        /**
        * @brief Находит индекс последнего отрицательного элемента
        * @return индекс последнего отрицательного элемента или -1 если нет
        */
        int find_last_negative_index() const;

        /**
        * @brief Выполняет задание 1
        */
        void Task() override;

        /**
        * @brief Возвращает результат задания 1
        * @return уникальный указатель на результирующую матрицу
        */
        std::unique_ptr<Matrix> get_result() const;
    };
}