#pragma once

namespace miit::algebra
{
    /**
    * @brief Абстрактный генератор значений для заполнения матрицы
    */
    class Generator
    {
    public:
        /**
        * @brief Виртуальный деструктор
        */
        virtual ~Generator() = default;

        /**
        * @brief Генерирует следующее значение
        * @return сгенерированное значение
        */
        virtual int generate() = 0;
    };

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
        explicit ConstantGenerator(int constant_value) : value(constant_value) {}

        /**
        * @brief Генерирует константное значение
        * @return заданное константное значение
        */
        int generate() override
        {
            return value;
        }
    };
}