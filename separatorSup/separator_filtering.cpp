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
int perform_moving_average(double *data_packet, std::vector<double>& filtered_data, int data_len) {

    try {

        for (int i = 0; i < data_len; ++i)
        {
            filtered_data[i] = 0.5 * (data_packet[i] + data_packet[i + 1]);
        }

    }
    catch (std::out_of_range) {
        errlogSevPrintf(errlogMajor, "Caught of of range error, input data too short?");
        std::cout<< "Caught of of range error, input data too short?" <<std::endl;
        return 1;
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
    int data_length = (int)prec->noa;
    std::vector<double> filtered_data(data_length);

    try {
        perform_moving_average(measured_data, filtered_data, data_length);
    }
    catch (std::out_of_range) {
        errlogSevPrintf(errlogMajor, "Caught of of range error, input data too short?");
    }
}
