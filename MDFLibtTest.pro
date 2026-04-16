TEMPLATE = subdirs

SUBDIRS += \
    mdflib \
    TestMDF

TestMDF.depends = mdflib
