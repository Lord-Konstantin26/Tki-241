#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <random>
#include <iostream>
#include <cmath>

#include "CppUnitTest.h"
#include "../decesion/Exercise.h"
#include "../decesion/IStreamGenerator.h"
#include "../decesion/RandomGenerator.h"
#include "../decesion/Task1.h"
#include "../decesion/Task2.h"
#include "../decesion/Task3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixTests
{
    TEST_CLASS(MatrixTests)
    {
    public:

        TEST_METHOD(MatrixConstructor_ValidSize)
        {
            miit::algebra::Matrix matrix(5);
            Assert::IsTrue(matrix.size() == 5);
        }

        TEST_METHOD(MatrixConstructor_FromVector)
        {
            std::vector<int> data = { 1, 2, 3, 4, 5 };
            miit::algebra::Matrix matrix(data);
            Assert::IsTrue(matrix.size() == data.size());
            Assert::IsTrue(matrix[2] == 3);
        }

        TEST_METHOD(MatrixToString_ValidFormat)
        {
            miit::algebra::Matrix matrix(std::vector<int>{1, 2, 3});
            std::string result = matrix.to_string();
            std::string expected = "[1, 2, 3]";
            Assert::IsTrue(result == expected);
        }

        TEST_METHOD(MatrixToString_EmptyMatrix)
        {
            miit::algebra::Matrix matrix(0);
            std::string result = matrix.to_string();
            std::string expected = "[]";
            Assert::IsTrue(result == expected);
        }

        TEST_METHOD(MatrixIndexOperator_ValidAccess)
        {
            miit::algebra::Matrix matrix(std::vector<int>{10, 20, 30});
            Assert::IsTrue(matrix[1] == 20);
            matrix[1] = 25;
            Assert::IsTrue(matrix[1] == 25);
        }

        TEST_METHOD(MatrixIndexOperator_OutOfRange)
        {
            miit::algebra::Matrix matrix(std::vector<int>{10, 20, 30});

            // Проверка выхода за границы
            auto func = [&]() { matrix[5]; };
            Assert::ExpectException<std::out_of_range>(func);
        }

        TEST_METHOD(MatrixIndexOperator_ConstAccess)
        {
            const miit::algebra::Matrix matrix(std::vector<int>{10, 20, 30});
            Assert::IsTrue(matrix[1] == 20);
        }

        TEST_METHOD(MatrixShiftLeftOperator_ValidBehavior)
        {
            miit::algebra::Matrix matrix(std::vector<int>{1, 2, 3});
            matrix << 0;
            Assert::IsTrue(matrix.size() == 4);
            Assert::IsTrue(matrix[0] == 0);
            Assert::IsTrue(matrix[1] == 1);
        }

        TEST_METHOD(MatrixShiftRightOperator_ValidBehavior)
        {
            miit::algebra::Matrix matrix(std::vector<int>{1, 2, 3});
            int value;
            matrix >> value;
            Assert::IsTrue(value == 1);
            Assert::IsTrue(matrix.size() == 2);
            Assert::IsTrue(matrix[0] == 2);
        }

        TEST_METHOD(MatrixShiftRightOperator_EmptyMatrix)
        {
            miit::algebra::Matrix matrix(0);
            int value = 0;

            // Извлечение из пустой матрицы не должно изменять значение
            matrix >> value;
            Assert::IsTrue(value == 0);
            Assert::IsTrue(matrix.size() == 0);
        }

        TEST_METHOD(MatrixDereferenceOperator_ValidPointer)
        {
            miit::algebra::Matrix matrix(std::vector<int>{10, 20, 30});
            const int* data = *matrix;
            Assert::IsTrue(data[0] == 10);
            Assert::IsTrue(data[1] == 20);
            Assert::IsTrue(data[2] == 30);
        }

        TEST_METHOD(MatrixAssignmentOperator_ValidCopy)
        {
            miit::algebra::Matrix matrix1(std::vector<int>{1, 2, 3});
            miit::algebra::Matrix matrix2 = matrix1;
            Assert::IsTrue(matrix1.size() == matrix2.size());
            Assert::IsTrue(matrix1[0] == matrix2[0]);
            Assert::IsTrue(matrix1[1] == matrix2[1]);
            Assert::IsTrue(matrix1[2] == matrix2[2]);
        }

        TEST_METHOD(MatrixFill_RandomGenerator)
        {
            miit::algebra::Matrix matrix(5);
            auto generator = std::make_unique<miit::algebra::RandomGenerator>(1, 10);
            matrix.fill(std::move(generator));

            for (size_t i = 0; i < matrix.size(); i++) {
                Assert::IsTrue(matrix[i] >= 1 && matrix[i] <= 10);
            }
        }
    };

    TEST_CLASS(GeneratorTests)
    {
    public:

        TEST_METHOD(RandomGenerator_ValidRange)
        {
            miit::algebra::RandomGenerator generator(5, 15);
            for (int i = 0; i < 100; i++) {
                int value = generator.generate();
                Assert::IsTrue(value >= 5 && value <= 15);
            }
        }

        TEST_METHOD(RandomGenerator_SingleValueRange)
        {
            miit::algebra::RandomGenerator generator(7, 7);
            Assert::IsTrue(generator.generate() == 7);
            Assert::IsTrue(generator.generate() == 7);
        }

        TEST_METHOD(IStreamGenerator_MockInput)
        {
            std::istringstream input("10 20 30 40 50");
            miit::algebra::IStreamGenerator generator(input);

            Assert::IsTrue(generator.generate() == 10);
            Assert::IsTrue(generator.generate() == 20);
            Assert::IsTrue(generator.generate() == 30);
        }
    };

    TEST_CLASS(Task1Tests)
    {
    public:

        TEST_METHOD(Task1_LastNegativeReplacedWithFirstAbsolute)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{5, -3, 8, -2, 10});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            task->Task1();
            auto data = task->get_data();

            Assert::IsTrue(data[3] == 5); // -2 заменен на |5| = 5
            Assert::IsTrue(data[1] == -3); // -3 остается
        }

        TEST_METHOD(Task1_NoNegative_NoChanges)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{1, 2, 3, 4});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            task->Task1();
            auto data = task->get_data();

            Assert::IsTrue(data[0] == 1);
            Assert::IsTrue(data[1] == 2);
            Assert::IsTrue(data[2] == 3);
            Assert::IsTrue(data[3] == 4);
        }

        TEST_METHOD(Task1_SingleNegativeElement)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{-5});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            task->Task1();
            auto data = task->get_data();

            Assert::IsTrue(data[0] == 5); // |-5| = 5
        }

        TEST_METHOD(Task1_FirstElementNegative)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{-10, 5, -3});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            task->Task1();
            auto data = task->get_data();

            Assert::IsTrue(data[2] == 10); // -3 заменен на | -10 | = 10
            Assert::IsTrue(data[0] == -10); // первый элемент не меняется
        }

        TEST_METHOD(Task1_AllNegativeElements)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{-1, -2, -3, -4});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            task->Task1();
            auto data = task->get_data();

            Assert::IsTrue(data[3] == 1); // последний отрицательный (-4) заменен на | -1 | = 1
            Assert::IsTrue(data[0] == -1);
            Assert::IsTrue(data[1] == -2);
            Assert::IsTrue(data[2] == -3);
        }

        TEST_METHOD(Task1_FindLastNegativeIndex_Valid)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{1, -2, 3, -4, 5});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            int index = task->find_last_negative_index();
            Assert::IsTrue(index == 3); // индекс -4
        }

        TEST_METHOD(Task1_FindLastNegativeIndex_NoNegative)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{1, 2, 3, 4, 5});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            int index = task->find_last_negative_index();
            Assert::IsTrue(index == -1); // нет отрицательных
        }
    };

    TEST_CLASS(Task2Tests)
    {
    public:

        TEST_METHOD(Task2_RemoveElementsWithRepeatingDigits)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{122, 123, 111, 456, 789});
            auto task = std::make_unique<miit::algebra::Task2Exercise>(
                std::move(matrix), nullptr);

            auto result = task->Task2();
            auto result_data = result->get_data();

            Assert::IsTrue(result->size() == 3); // 122, 111 удалены
            Assert::IsTrue(result_data[0] == 123);
            Assert::IsTrue(result_data[1] == 456);
            Assert::IsTrue(result_data[2] == 789);
        }

        TEST_METHOD(Task2_NoRepeatingDigits_NoChanges)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{123, 456, 789});
            auto task = std::make_unique<miit::algebra::Task2Exercise>(
                std::move(matrix), nullptr);

            auto result = task->Task2();

            Assert::IsTrue(result->size() == 3);
        }

        TEST_METHOD(Task2_AllElementsWithRepeatingDigits)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{111, 222, 333});
            auto task = std::make_unique<miit::algebra::Task2Exercise>(
                std::move(matrix), nullptr);

            auto result = task->Task2();

            Assert::IsTrue(result->size() == 0); // все элементы удалены
        }

        TEST_METHOD(Task2_SingleElementWithRepeatingDigits)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{121});
            auto task = std::make_unique<miit::algebra::Task2Exercise>(
                std::move(matrix), nullptr);

            auto result = task->Task2();

            Assert::IsTrue(result->size() == 0); // элемент удален
        }

        TEST_METHOD(Task2_NegativeNumbersWithRepeatingDigits)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{-121, -123, -111});
            auto task = std::make_unique<miit::algebra::Task2Exercise>(
                std::move(matrix), nullptr);

            auto result = task->Task2();
            auto result_data = result->get_data();

            Assert::IsTrue(result->size() == 1); // только -123 остается
            Assert::IsTrue(result_data[0] == -123);
        }

        TEST_METHOD(Task2_HasRepeatingDigits_ValidCases)
        {
            Assert::IsTrue(miit::algebra::Task2Exercise::has_repeating_digits(122)); // повторяющиеся
            Assert::IsTrue(miit::algebra::Task2Exercise::has_repeating_digits(111)); // все одинаковые
            Assert::IsFalse(miit::algebra::Task2Exercise::has_repeating_digits(123)); // все разные
            Assert::IsFalse(miit::algebra::Task2Exercise::has_repeating_digits(456)); // все разные
        }

        TEST_METHOD(Task2_HasRepeatingDigits_Zero)
        {
            Assert::IsFalse(miit::algebra::Task2Exercise::has_repeating_digits(0)); // 0 не имеет повторяющихся цифр
        }

        TEST_METHOD(Task2_CountElementsWithoutRepeats)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{122, 123, 111, 456});
            auto task = std::make_unique<miit::algebra::Task2Exercise>(
                std::move(matrix), nullptr);

            size_t count = task->count_elements_without_repeats();
            Assert::IsTrue(count == 2); // 123 и 456
        }
    };

    TEST_CLASS(Task3Tests)
    {
    public:

        TEST_METHOD(Task3_CreateModifiedMatrix)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{1, 2, 3, 4, 5});
            auto task = std::make_unique<miit::algebra::Task3Exercise>(
                std::move(matrix), nullptr);

            auto result = task->Task3();
            auto result_data = result->get_data();

            Assert::IsTrue(result->size() == 5);
            Assert::IsTrue(result_data[0] == 0);   // 0 * 1 = 0 (четный индекс)
            Assert::IsTrue(result_data[1] == -2);  // -2 (нечетный индекс)
            Assert::IsTrue(result_data[2] == 6);   // 2 * 3 = 6 (четный индекс)
            Assert::IsTrue(result_data[3] == -4);  // -4 (нечетный индекс)
            Assert::IsTrue(result_data[4] == 16);  // 4 * 4 = 16 (четный индекс)
        }

        TEST_METHOD(Task3_EmptyMatrix)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{});
            auto task = std::make_unique<miit::algebra::Task3Exercise>(
                std::move(matrix), nullptr);

            auto result = task->Task3();

            Assert::IsTrue(result->size() == 0);
        }

        TEST_METHOD(Task3_SingleElement)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{10});
            auto task = std::make_unique<miit::algebra::Task3Exercise>(
                std::move(matrix), nullptr);

            auto result = task->Task3();
            auto result_data = result->get_data();

            Assert::IsTrue(result->size() == 1);
            Assert::IsTrue(result_data[0] == 0); // 0 * 10 = 0
        }

        TEST_METHOD(Task3_TwoElements)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{1, 2});
            auto task = std::make_unique<miit::algebra::Task3Exercise>(
                std::move(matrix), nullptr);

            auto result = task->Task3();
            auto result_data = result->get_data();

            Assert::IsTrue(result->size() == 2);
            Assert::IsTrue(result_data[0] == 0); // 0 * 1 = 0
            Assert::IsTrue(result_data[1] == -2); // -2
        }

        TEST_METHOD(Task3_ThreeElements)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{1, 2, 3});
            auto task = std::make_unique<miit::algebra::Task3Exercise>(
                std::move(matrix), nullptr);

            auto result = task->Task3();
            auto result_data = result->get_data();

            Assert::IsTrue(result->size() == 3);
            Assert::IsTrue(result_data[0] == 0);  // 0 * 1 = 0
            Assert::IsTrue(result_data[1] == -2); // -2
            Assert::IsTrue(result_data[2] == 6);  // 2 * 3 = 6
        }

        TEST_METHOD(Task3_NegativeValues)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{-1, -2, -3});
            auto task = std::make_unique<miit::algebra::Task3Exercise>(
                std::move(matrix), nullptr);

            auto result = task->Task3();
            auto result_data = result->get_data();

            Assert::IsTrue(result->size() == 3);
            Assert::IsTrue(result_data[0] == 0);   // 0 * (-1) = 0
            Assert::IsTrue(result_data[1] == 2);   // -(-2) = 2
            Assert::IsTrue(result_data[2] == -6);  // 2 * (-3) = -6
        }
    };

    TEST_CLASS(ExerciseTests)
    {
    public:

        TEST_METHOD(Exercise_GetMatrixString)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{1, 2, 3});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            std::string result = task->get_matrix_string();
            std::string expected = "[1, 2, 3]";
            Assert::IsTrue(result == expected);
        }

        TEST_METHOD(Exercise_GetData)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{10, 20, 30});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            const auto& data = task->get_data();
            Assert::IsTrue(data.size() == 3);
            Assert::IsTrue(data[0] == 10);
            Assert::IsTrue(data[1] == 20);
            Assert::IsTrue(data[2] == 30);
        }

        TEST_METHOD(Exercise_Size)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{1, 2, 3, 4, 5});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            Assert::IsTrue(task->size() == 5);
        }

        TEST_METHOD(Exercise_EmptyMatrix)
        {
            auto matrix = std::make_unique<miit::algebra::Matrix>(
                std::vector<int>{});
            auto task = std::make_unique<miit::algebra::Task1Exercise>(
                std::move(matrix), nullptr);

            Assert::IsTrue(task->size() == 0);
            Assert::IsTrue(task->get_matrix_string() == "[]");
        }
    };
}