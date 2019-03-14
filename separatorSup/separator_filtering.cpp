#include <stdexcept>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <menuFtype.h>
#include <errlog.h>
#include <epicsString.h>
#include <epicsExport.h>
#include <iostream>

#include "separator.h"
#include "seprtr_gtest_fncts.h"

/**
* Calculates the moving average of the input array with a stride length of 1 (average i with i+1)
*
* Input: data_packet, An array of floats equivalent to data from a DAQ
* Input: data_len, The number of data points in the input array
* Output: filtered_data, Array of floats averaged to filter out noise.
*/
int perform_moving_average(const std::vector<double>& input_data, std::vector<double>& filtered_data) {

    for (int i = 0; i < input_data.size() - 1; ++i)
    {
        filtered_data.push_back(0.5 * (input_data[i] + input_data[i + 1]));
    }

    return 0;

}

long apply_filter_impl(aSubRecord *prec)
{
    if (prec->fta != menuFtypeDOUBLE)
    {
        errlogSevPrintf(errlogMajor, "%s incorrect argument type A", prec->name);
        return 1;
    }

    const int stride_length = 1;
    double* measured_data = (double*)prec->a;
    unsigned int data_length = prec->noa;
    std::vector<double> filtered_data;
    std::vector<double> input_data;

    for (int i = 0; i < data_length; ++i)
    {
        input_data.push_back(measured_data[i]);
    }
    

    try {
        perform_moving_average(input_data, filtered_data);
    }
    catch (std::out_of_range) {
        errlogSevPrintf(errlogMajor, "%s unknown exception", prec->name);
        return 1;
    }

    return 0;
}
