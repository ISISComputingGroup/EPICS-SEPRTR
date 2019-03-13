TOP=..
include $(TOP)/configure/CONFIG
#=======================================

# Install .dbd and .db files
DB += separator.db
DB += separator_power_status.db
DB += separator_voltage.db
DB += separator_current.db
DB += separator_stability.db

LIBRARY_IOC += SEPRTR

DBD += separator.dbd

SEPRTR_SRCS += separator.c separator_impl.cpp separator_filtering.cpp

SEPRTR_DBD += asyn.dbd
SEPRTR_DBD += asubFunctions.dbd

SEPRTR_LIBS += $(EPICS_BASE_IOC_LIBS)
SEPRTR_LIBS += asyn utilities
SEPRTR_LIBS += asubFunctions

#=======================================
# googleTest Runner

TESTPROD_HOST += runner
USR_CPPFLAGS += -I$(GTEST)/googletest/include
runner_SRCS += run_all_tests.cc

runner_SRCS += separator_tests.cc separator_filtering.cpp
runner_LIBS += gtest $(SEPRTR_LIBS)

#=======================================
include $(TOP)/configure/RULES
