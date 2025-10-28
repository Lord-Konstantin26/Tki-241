#include "Task1.h"
#include <cmath>

namespace miit::algebra
{
    int Task1Exercise::find_last_negative_index() const
    {
        const auto& data = matrix->get_data();
        int last_negative = -1;

        for (size_t i = 0; i < data.size(); i++)
        {
            if (data[i] < 0)
            {
                last_negative = static_cast<int>(i);
            }
        }

        return last_negative;
    }

    void Task1Exercise::Task1()
    {
        const auto& data = matrix->get_data();
        int last_negative_index = find_last_negative_index();

        if (last_negative_index != -1 && !data.empty())
        {
            // Модифицируем матрицу
            (*matrix)[last_negative_index] = std::abs(data[0]);
        }
    }
}