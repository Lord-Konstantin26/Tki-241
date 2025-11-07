#include "Task1.h"

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

    void Task1Exercise::Task()
    {
        const auto& data = matrix->get_data();
        int last_negative_index = find_last_negative_index();

        if (last_negative_index != -1 && !data.empty())
        {
            // Модифицируем матрицу
            (*matrix)[last_negative_index] = std::abs(data[0]);
        }
    }

    /**
    * @brief Возвращает результат задания 1
    * @return уникальный указатель на результирующую матрицу
    */
    std::unique_ptr<Matrix> Task1Exercise::get_result() const
    {
        return std::make_unique<Matrix>(*matrix);
    }
}