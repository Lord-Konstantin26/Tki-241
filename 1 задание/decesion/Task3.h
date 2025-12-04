#pragma once
#include "Exercise.h"

namespace miit::algebra
{
    /**
    * @brief Реализация задания 3: преобразование массива по правилу
    */
    class Task3Exercise : public Exercise
    {
    public:
        /**
        * @brief Конструктор - явный вызов конструктора базового класса
        * @param matrix матрица для обработки
        * @param generator генератор значений
        */
        explicit Task3Exercise(std::unique_ptr<Matrix> matrix, std::unique_ptr<Generator> generator)
            : Exercise(std::move(matrix), std::move(generator)) {
        }

        /**
        * @brief Выполняет задание 3
        */
        void Task() override;

        /**
        * @brief Возвращает результат задания 3
        * @return уникальный указатель на результирующую матрицу
        */
        std::unique_ptr<Matrix> get_result() const;

    private:
        std::unique_ptr<Matrix> result;
    };
}