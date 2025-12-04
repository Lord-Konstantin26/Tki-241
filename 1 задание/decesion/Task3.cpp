#include "Task3.h"
#include <vector>

namespace miit::algebra
{
    void Task3Exercise::Task()
    {
        const auto& data = matrix->get_data();
        std::vector<int> result_data(data.size());

        for (size_t i = 0; i < data.size(); i++)
        {
            if (i % 2 == 0)
            {
                result_data[i] = static_cast<int>(i) * data[i];
            }
            else
            {
                result_data[i] = -data[i];
            }
        }

        result = std::make_unique<Matrix>(result_data);
    }

    std::unique_ptr<Matrix> Task3Exercise::get_result() const
    {
        return std::make_unique<Matrix>(*result);
    }
}