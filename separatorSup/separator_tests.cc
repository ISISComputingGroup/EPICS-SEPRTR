#include <epicsString.h>
#include "gtest/gtest.h"
#include "seprtr_gtest_fncts.h"

const int success_code = 0, fail_code = 1;
const int number_of_input_values = 4, too_many_values = number_of_input_values + 1;
std::vector<epicsFloat64> test_data { 1.0, 2.0, 3.0, 4.0 };
std::vector<epicsFloat64> expected_result = { 1.5, 2.5, 3.5 };

namespace {
    TEST(Separator, test_GIVEN_input_array_WHEN_moving_average_calculated_THEN_array_of_moving_averages_returned){
        // GIVEN
        int return_code;

        std::vector<epicsFloat64> returned_data;

        // WHEN
        return_code = perform_moving_average(test_data, returned_data);

        // THEN
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(returned_data.at(i), expected_result[i]);
        }

        EXPECT_EQ(return_code, success_code);

    }

} // namespace