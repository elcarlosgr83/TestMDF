SOURCES += \
    $$files($$PWD/src/*.cpp, true) \
    $$files($$PWD/src/thirdparty/zlib/*.c, true) \
    $$files($$PWD/src/thirdparty/expat/*.c, true) \
    $$files($$PWD/include/mdflibrary/*.c, true) \
    $$PWD/mdflogger.cpp

HEADERS += \
    $$files($$PWD/include/mdf/*.h, true) \
    $$files($$PWD/include/mdflibrary/*.h, true) \
    $$files($$PWD/include/thirdparty/zlib/*.h, true) \
    $$files($$PWD/include/thirdparty/expat/*.h, true) \
    $$files($$PWD/include/thirdparty/ghc/*.hpp, true) \
    $$PWD/mdflogger.h

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/include/thirdparty/zlib
INCLUDEPATH += $$PWD/include/thirdparty/expat
INCLUDEPATH += $$PWD/include/thirdparty

DEFINES += MDFLIB_SUPPORT
