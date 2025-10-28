#pragma once
#include "Exercise.h"

namespace miit::algebra
{
    /**
    * @brief Реализация задания 1: замена последнего отрицательного элемента на модуль первого элемента
    */
    class Task1Exercise : public Exercise
    {
    public:
        using Exercise::Exercise;

        /**
        * @brief Находит индекс последнего отрицательного элемента
        * @return индекс последнего отрицательного элемента или -1 если нет
        */
        int find_last_negative_index() const;

        /**
        * @brief Замена последнего отрицательного элемента на модуль первого элемента
        */
        void Task1() override;

        std::unique_ptr<Matrix> Task2() override { return nullptr; }
        std::unique_ptr<Matrix> Task3() override { return nullptr; }
    };
}