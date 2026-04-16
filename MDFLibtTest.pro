TEMPLATE = subdirs

SUBDIRS += \
    mdflib \
    TestMDF \
    TestMDF_GTest

TestMDF.depends = mdflib
TestMDF_GTest.depends = mdflib
