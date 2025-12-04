#pragma once
#include "Matrix.h"
#include "Generator.h"
#include <memory>

namespace miit::algebra
{
    /**
    * @brief Абстрактный класс для выполнения заданий над матрицей
    */
    class Exercise
    {
    protected:
        std::unique_ptr<Matrix> matrix;
        std::unique_ptr<Generator> generator;

    public:
        /**
        * @brief Конструктор упражнения
        * @param matrix матрица для обработки
        * @param generator генератор значений
        */
        Exercise(std::unique_ptr<Matrix> matrix, std::unique_ptr<Generator> generator);

        /**
        * @brief Виртуальный деструктор
        */
        virtual ~Exercise() = default;

        /**
        * @brief Основная виртуальная функция выполнения задания
        */
        virtual void Task() = 0;
    };
}