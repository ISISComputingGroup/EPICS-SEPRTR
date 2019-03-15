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
* Calculates the moving average of the input array with a stride length of 1 (average i with i+1)
*
* Input: data_packet, An array of floats equivalent to data from a DAQ
* Input: data_len, The number of data points in the input array
* Output: filtered_data, Array of floats averaged to filter out noise.
*/
int perform_moving_average(const std::vector<epicsFloat64>& input_data, std::vector<epicsFloat64>& filtered_data) {

    std::cout << "Function run" << std::endl;
    for (int i = 0; i < input_data.size() - 1; ++i)
    {
        filtered_data.push_back(0.5 * (input_data[i] + input_data[i + 1]));
        //filtered_data.at(i) = (0.5 * (input_data[i] + input_data[i + 1]));
        std::cout << "value:" << input_data[i] << std::endl;
        // This might be adding the data on the end of nonsense
    }

    return 0;

}

long apply_filter_impl(aSubRecord *prec)
{

    std::cout << "Enter C++" << std::endl;
    if (prec->fta != menuFtypeDOUBLE)
    {
        errlogSevPrintf(errlogMajor, "%s incorrect argument type A", prec->name);

        return 0;
    }

    const int stride_length = 1;
    epicsFloat64* measured_data = (epicsFloat64*)prec->a;
    unsigned int data_length = prec->nea;

    std::cout << "data_length " << data_length << std::endl;

    if (data_length < 1) {
        return 1;
    }
    
    // This is defining a vector with a start point defined by the prec->vala pointer location
    //std::vector<double> filtered_data(data_length - 1);
    std::vector<double> filtered_data;
    std::vector<epicsFloat64> input_data;

    //epicsFloat64* arr_out = 
    
    prec->neva = data_length - 1;
    //prec->nova = data_length - 1;

    std::cout << "Defined arrays" << std::endl;
    for (unsigned int i = 0; i < data_length; ++i)
    {
        input_data.push_back(measured_data[i]);
    }

    try {
        std::cout << "Function called" << std::endl;
        perform_moving_average(input_data, filtered_data);
        
        for (unsigned int i = 0; i < filtered_data.size(); ++i)
        {
            std::cout << i << std::endl;
            std::cout << "Final value :" << filtered_data[i] << std::endl;
        }

        std::copy(filtered_data.begin(), filtered_data.end(), (epicsFloat64*) prec->vala);

    }

    catch (...) {
        errlogSevPrintf(errlogMajor, "%s unknown exception", prec->name);
        return 1;
    }

    return 0;
}
