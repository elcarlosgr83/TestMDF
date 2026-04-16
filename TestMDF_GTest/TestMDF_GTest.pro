TEMPLATE = app
CONFIG += console c++17
CONFIG -= qt
CONFIG -= app_bundle

TARGET = TestMDF_GTest

# --- Fuentes ---
SOURCES += \
    main.cpp \
    test_mdflib.cpp

# --- Headers de mdflib ---
INCLUDEPATH += $$PWD/../mdflib/include /usr/local/include

# --- Enlace con mdflib ---
LIBS += -L$$PWD/../lib -lmdflib

# --- Enlace con GTest ---
# Ajusta estas rutas según tu instalación de GTest
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lgtest -lgtest_main -lgmock -lgmock_main -lpthread
