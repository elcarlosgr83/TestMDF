# --- Proyecto configurado como librería estática ---
TEMPLATE = lib
CONFIG += staticlib c++17
CONFIG -= qt
CONFIG -= app_bundle

# --- Fuentes principales ---
SOURCES += \
    $$files($$PWD/src/*.cpp, true) \
    $$files($$PWD/src/thirdparty/zlib/*.c, true) \
    $$files($$PWD/src/thirdparty/expat/*.c, true) \
    $$files($$PWD/include/mdflibrary/*.c, true) \

# --- Headers principales ---
HEADERS += \
    $$files($$PWD/include/mdf/*.h, true) \
    $$files($$PWD/include/mdflibrary/*.h, true) \
    $$files($$PWD/include/thirdparty/zlib/*.h, true) \
    $$files($$PWD/include/thirdparty/expat/*.h, true) \
    $$files($$PWD/include/thirdparty/ghc/*.hpp, true)

# --- Rutas de include ---
INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/include/thirdparty/zlib
INCLUDEPATH += $$PWD/include/thirdparty/expat
INCLUDEPATH += $$PWD/include/thirdparty

# --- Flags de compilación estática ---
win32-g++ {
    QMAKE_LFLAGS += -static -static-libgcc -static-libstdc++
}

# --- Entropy source for embedded Expat ---
DEFINES += XML_DEV_URANDOM

# --- Directorio de salida fijo ---
DESTDIR = $$PWD/../lib
