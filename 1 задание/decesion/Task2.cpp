#include "Task2.h"
#include <vector>
#include <cmath>

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

    void Task2Exercise::Task()
    {
        const auto& data = matrix->get_data();
        std::vector<int> result_data;

        for (int value : data)
        {
            if (!has_repeating_digits(value))
            {
                result_data.push_back(value);
            }
        }

        result = std::make_unique<Matrix>(result_data);
    }

    std::unique_ptr<Matrix> Task2Exercise::get_result() const
    {
        return std::make_unique<Matrix>(*result);
    }
}