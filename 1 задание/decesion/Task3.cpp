#include "Task3.h"
#include <vector>

namespace miit::algebra
{
    std::unique_ptr<Matrix> Task3Exercise::Task3()
    {
        const auto& data = matrix->get_data();
        std::vector<int> result(data.size());

        for (size_t i = 0; i < data.size(); i++)
        {
            if (i % 2 == 0)
            {
                result[i] = static_cast<int>(i) * data[i];
            }
            else
            {
                result[i] = -data[i];
            }
        }

        return std::make_unique<Matrix>(result);
    }
}