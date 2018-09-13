#include <string.h>
#include <stdlib.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <menuFtype.h>
#include <errlog.h>
#include <epicsString.h>
#include <epicsExport.h>
#include <boost/circular_buffer.hpp>

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <numeric>
#include <map>

#include "separator.h"

static std::map<std::string, boost::circular_buffer<long>*> pvHistory;

long parse_stability_impl(aSubRecord *prec)
{
//    static std::map<std::string, boost::circular_buffer<long>*> pvHistory;
    boost::circular_buffer<long> *circularBuffer;

    long dataValue = *(long*)prec->a, bufferLen = *(long*)prec->b, reset= *(long*)prec->c, sum=0;

    std::cout << "Name " <<  prec->name << std::endl;

    //std::cout << pvHistory.find(prec->name)->first << pvHistory.end()->first << std::endl;

    // Type/value checking on input variables here

    if ( pvHistory.find(prec->name) == pvHistory.end() ) {
        /* This PV has not called the aSub function before. Initialise. */

        circularBuffer = new boost::circular_buffer<long>(bufferLen);

        //std::cout << prec->name << " A Buffer Length " << std::endl;
        std::cout << prec->name << " A Buffer Length " << bufferLen << std::endl;

        //pvHistory.insert(std::make_pair(prec->name, &circularBuffer) );
        pvHistory[prec->name] = circularBuffer;

    } else if (reset != 0) {

        std::cout << prec->name << " B" << std::endl;

        circularBuffer = new boost::circular_buffer<long>(bufferLen);

        pvHistory[prec->name] = circularBuffer;

    }

    else {
        std::cout << prec->name << " C" << std::endl;
        circularBuffer = pvHistory[prec->name];

    }

    std::cout << "Data" << dataValue << std::endl;

    std::cout << "Before push back" << std::endl;
    circularBuffer->push_back(dataValue);

    std::cout << "Before sum" << std::endl;
    sum = std::accumulate(circularBuffer->begin(), circularBuffer->end(), 0);

    std::cout << "Sum value " << sum << std::endl;

    /* Returns the first input value back */
    *(long*) prec->vala = 0;//sum;
    *(long*) prec->valb = 0;
    return 0; /* process output links */
}
