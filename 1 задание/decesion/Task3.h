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
        using Exercise::Exercise;

        /**
        * @brief Создает новую матрицу: M[i] = i*P[i] для четных индексов, M[i] = -P[i] для нечетных
        * @return новая матрица
        */
        std::unique_ptr<Matrix> Task3() override;

        void Task1() override {}
        std::unique_ptr<Matrix> Task2() override { return nullptr; }
    };
}