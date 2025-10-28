#include "Task2.h"
#include <vector>
#include <cmath>
#include <array>

namespace miit::algebra
{
    bool Task2Exercise::has_repeating_digits(int number)
    {
        std::array<int, 10> count = { 0 };
        int num = std::abs(number);

        // Обработка нуля
        if (num == 0)
        {
            count[0]++;
            return count[0] > 1;
        }

        while (num > 0)
        {
            int digit = num % 10;
            count[digit]++;
            if (count[digit] > 1)
            {
                return true;
            }
            num /= 10;
        }

        return false;
    }

    size_t Task2Exercise::count_elements_without_repeats() const
    {
        const auto& data = matrix->get_data();
        size_t count = 0;

        for (int value : data)
        {
            if (!has_repeating_digits(value))
            {
                count++;
            }
        }

        return count;
    }

    std::unique_ptr<Matrix> Task2Exercise::Task2()
    {
        const auto& data = matrix->get_data();
        std::vector<int> result;
        result.reserve(count_elements_without_repeats());

        for (int value : data)
        {
            if (!has_repeating_digits(value))
            {
                result.push_back(value);
            }
        }

        return std::make_unique<Matrix>(result);
    }
}