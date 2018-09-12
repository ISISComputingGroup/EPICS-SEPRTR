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

typedef boost::circular_buffer<long> circbuffer;

static boost::circular_buffer<long>* initCircularBuffer(long& bufferLen)
{
    /* Initialise a new circular buffer */
    boost::circular_buffer<long> circularBuffer(bufferLen, bufferLen, long(0));

    return &circularBuffer;
}

long parse_stability_impl(aSubRecord *prec)
{
    static std::map<std::string, boost::circular_buffer<long>*> pvHistory;
    circbuffer* circularBuffer;

    long dataValue = *(long*)prec->a, bufferLen = *(long*)prec->b, sum=0;
    //long bufferLen = *(long*)prec->b;

    if ( pvHistory.find(prec->name) == pvHistory.end() ) {
        /* This PV has not called the aSub function before. Initialise. */
        //boost::circular_buffer<long>* circularBuffer = initCircularBuffer(bufferLen);
        circularBuffer = initCircularBuffer(bufferLen);

        pvHistory.insert(std::make_pair(prec->name, circularBuffer));

    } else {
        circularBuffer = pvHistory[prec->name];
        //boost::circular_buffer<long>* circularBuffer = pvHistory[prec->name];
    }

    (*circularBuffer).push_back(dataValue);

    sum = std::accumulate((*circularBuffer).begin(), (*circularBuffer).end(), 0);

    /* Returns the first input value back */
    *(long*) prec->vala = sum;
    return 0; /* process output links */
}