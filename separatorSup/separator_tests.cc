#include "gtest/gtest.h"
#include "seprtr_gtest_fncts.h"

const int success_code = 0, fail_code = 1;
const int number_of_input_values = 4, too_many_values = number_of_input_values + 1;
double test_data[number_of_input_values] = { 1.0, 2.0, 3.0, 4.0 }, expected_result[3] = { 1.5, 2.5, 3.5 };

namespace {
    TEST(Separator, test_GIVEN_input_array_WHEN_moving_average_calculated_THEN_array_of_moving_averages_returned){
        // GIVEN
        int return_code;

        std::vector<double> returned_data(number_of_input_values - 1);

        // WHEN
        return_code = perform_moving_average(test_data, returned_data, number_of_input_values);

        // THEN
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(returned_data[i], expected_result[i]);
        }

        EXPECT_EQ(return_code, success_code);

    }

    TEST(Separator, test_GIVEN_input_array_of_different_length_to_data_len_WHEN_moving_average_calculated_THEN_function_returns_fail){
        // GIVEN
        int return_code;

        std::vector<double> returned_data(number_of_input_values - 1);

        // WHEN
        return_code = perform_moving_average(test_data, returned_data, too_many_values);

        // THEN
        EXPECT_EQ(return_code, fail_code);

    }
} // namespace