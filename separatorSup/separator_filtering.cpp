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

#include "separator.h"
#include "seprtr_gtest_fncts.h"

/**
* Applies a moving average to the data packet
*
* Input: data_packet, An array of floats equivalent to data from a DAQ
* Returns: filtered_data, Array of floats averaged to filter out noise.
*/
long perform_moving_average(double *data_packet, std::vector<double>& filtered_data, int arr_len) {
    const long packet_length = sizeof(data_packet);

    for (int i = 0; i < arr_len; ++i)
    {
        filtered_data[i] = 0.5 * (data_packet[i] + data_packet[i + 1]);
    }

    return 1;

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
