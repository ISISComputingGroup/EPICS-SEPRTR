#include "gtest/gtest.h"
#include "seprtr_gtest_fncts.h"


/**
 * Mimics the expected behaviour of the filtering required of the aSub record
 * 
 * Input: data_packet, An array of floats equivalent to data from a DAQ
 * Returns: filtered_data, Array of floats averaged to filter out noise.
 *
static double apply_filter_to_test_data(static double data_packet) {
    double filtered_data[sizeof(data_packet) - 1];

    for (unsigned int i = 0; i < (sizeof(data_packet) - 1); ++i)
    {
      filtered_data[i] = 0.5 * (data_packet[i] + data_packet[i + 1]);
    }

}
*/

namespace {
    TEST(Separator, test_GIVEN_input_array_WHEN_array_processed_THEN_array_of_moving_averages_returned){
        // GIVEN
        const int number_of_values_per_packet = 4;
        //double test_data[number_of_values_per_packet] returned_data[number_of_values_per_packet];
        double test_data[number_of_values_per_packet] = {10.0, 20.0, 10.0, 20.0}, expected_result[3] = {15.0, 15.0, 15.0};

        std::vector<double> returned_data(number_of_values_per_packet);

        // WHEN
        perform_moving_average(test_data, returned_data, number_of_values_per_packet);

        // THEN
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(returned_data[i], expected_result[i]);
        }


        //ASSERT_EQ(returned_data, expected_result);

    }
} // namespace