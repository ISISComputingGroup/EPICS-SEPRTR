TOP=..
include $(TOP)/configure/CONFIG
#=======================================

# Install .dbd and .db files
DB += separator.db
DB += separator_power_status.db
DB += separator_voltage.db
DB += separator_current.db
DB += separator_stability.db

#protocol files
DATA += separator.proto

LIBRARY_IOC += SEPRTR

DBD += separator.dbd

SEPRTR_SRCS += separator.c separator_impl.cpp

SEPRTR_DBD += asyn.dbd
SEPRTR_DBD += asubFunctions.dbd

SEPRTR_LIBS += $(EPICS_BASE_IOC_LIBS)
SEPRTR_LIBS += asyn utilities
SEPRTR_LIBS += asubFunctions


#=======================================
include $(TOP)/configure/RULES
