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
    boost::circular_buffer<long> *circularBuffer;

    long dataValue = *(long*)prec->a, bufferLen = *(long*)prec->b, reset= *(long*)prec->c, sum=0;

    if (prec->fta != menuFtypeLONG)
    {
        errlogSevPrintf(errlogMajor, "%s incorrect argument type A", prec->name);
        return 1;
    }
    if (prec->ftb != menuFtypeLONG)
    {
        errlogSevPrintf(errlogMajor, "%s incorrect argument type B", prec->name);
        return 1;
    }
    if (prec->ftc != menuFtypeLONG)
    {
        errlogSevPrintf(errlogMajor, "%s incorrect argument type C", prec->name);
        return 1;
    }

    try {

        if ( pvHistory.find(prec->name) == pvHistory.end() ) {
            // This PV has not called the aSub function before. Initialise.

            circularBuffer = new boost::circular_buffer<long>(bufferLen);
            pvHistory[prec->name] = circularBuffer;

        } else if (reset != 0) {
            // Replace the circular buffer in the map with a new, uninitialised one

            circularBuffer = pvHistory[prec->name];
            delete circularBuffer;

            circularBuffer = new boost::circular_buffer<long>(bufferLen);
            pvHistory[prec->name] = circularBuffer;

            // Rearm the reset window PV
            *(long*) prec->valb = 0;

        } else {
            // Recall circularBuffer from the map
            circularBuffer = pvHistory[prec->name];

        }

        // Add the new value to the circular buffer
        circularBuffer->push_back(dataValue);

        // Return the summed value of the buffer
        sum = std::accumulate(circularBuffer->begin(), circularBuffer->end(), 0);

        *(long*) prec->vala = sum;


    }
    catch (const std::exception& e) {
        errlogSevPrintf(errlogMajor, "%s exception %s", prec->name, e.what());

    }
    catch (...) {
        errlogSevPrintf(errlogMajor, "%s unknown exception", prec->name);
    }
    return 0; /* process output links */
}
