#include "Exercise.h"
#include <sstream>

namespace miit::algebra
{
    Exercise::Exercise(std::unique_ptr<Matrix> matrix, std::unique_ptr<Generator> generator)
        : matrix(std::move(matrix)), generator(std::move(generator))
    {
        // Заполняем матрицу значениями из генератора
        if (this->matrix && this->generator) {
            for (size_t i = 0; i < this->matrix->size(); i++) {
                (*this->matrix)[i] = this->generator->generate();
            }
        }
    }
}