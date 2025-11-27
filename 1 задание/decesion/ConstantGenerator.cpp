#include "ConstantGenerator.h"

namespace miit::algebra
{
    ConstantGenerator::ConstantGenerator(int constant_value)
        : value(constant_value)
    {
    }

    int ConstantGenerator::generate()
    {
        return value;
    }
}