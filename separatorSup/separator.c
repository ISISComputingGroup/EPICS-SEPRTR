#include <stdlib.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <epicsExport.h>

#include "separator.h"

static long parse_stability(aSubRecord *prec)
{
    return parse_stability_impl(prec);
}

epicsRegisterFunction(parse_stability);
