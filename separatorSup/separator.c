#include <stdlib.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <epicsExport.h>

#include "separator.h"

static long parse_stability(aSubRecord *prec)
{
    return parse_stability_impl(prec);
}

static long apply_filter(aSubRecord *prec)
{
    return apply_filter_impl(prec);
}

epicsRegisterFunction(parse_stability);
epicsRegisterFunction(apply_filter);
