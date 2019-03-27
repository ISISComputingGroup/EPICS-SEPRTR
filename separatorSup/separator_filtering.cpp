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
#include <algorithm>

#include "separator.h"
#include "seprtr_gtest_fncts.h"

/**
* Calculates the moving average of the input array with a given stride length (average i with i+stride_len)
*
* Input: data_packet, An array of floats equivalent to data from a DAQ
* Input: stride_length, The number of indices to skip over to perform the two-point average
* Output: filtered_data, Array of floats averaged to filter out noise.
*/
int perform_moving_average(const std::vector<epicsFloat64>& input_data, std::vector<epicsFloat64>& filtered_data, const int stride_len) {

    for (int i = 0; i < input_data.size() - stride_len; ++i)
    {
        filtered_data.push_back(0.5 * (input_data[i] + input_data[i + stride_len]));
    }

    return 0;

}

long apply_filter_impl(aSubRecord *prec)
{
    const int stride_len = 1;
    epicsFloat64* measured_data = (epicsFloat64*)prec->a;
    unsigned int data_length = prec->nea;
    std::vector<epicsFloat64> filtered_data;
    std::vector<epicsFloat64> input_data;

    if (prec->fta != menuFtypeDOUBLE)
    {
        errlogSevPrintf(errlogMajor, "%s incorrect argument type A", prec->name);

        return 1;
    }

    if (data_length < stride_len) {
        errlogSevPrintf(errlogMajor, "%s input data too short for stride length", prec->name);
        return 1;
    }

    // Write the number of elements in output array to NEVA field
    prec->neva = data_length - stride_len;

    for (unsigned int i = 0; i < data_length; ++i)
    {
        input_data.push_back(measured_data[i]);
    }

    try {
        perform_moving_average(input_data, filtered_data, stride_len);

        // Move the filtered data from the working vector to the epics aSub array
        std::copy(filtered_data.begin(), filtered_data.end(), (epicsFloat64*) prec->vala);

    }

    catch (...) {
        errlogSevPrintf(errlogMajor, "%s unknown exception", prec->name);
        return 1;
    }

    return 0;
}
