#pragma once
#include "Generator.h"

namespace miit::algebra
{
    /**
    * @brief Константный генератор, всегда возвращающий заданное значение
    */
    class ConstantGenerator : public Generator
    {
    private:
        int value;

    public:
        /**
        * @brief Конструктор константного генератора
        * @param constant_value значение, которое будет возвращаться при генерации
        */
        explicit ConstantGenerator(int constant_value);

        /**
        * @brief Генерирует константное значение
        * @return заданное константное значение
        */
        int generate() override;
    };
}