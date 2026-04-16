# --- Proyecto TestMDF (aplicación cliente) ---
TEMPLATE = app
CONFIG += console c++17
CONFIG -= qt
CONFIG -= app_bundle

# --- Fuentes principales ---
SOURCES += main.cpp

# --- Headers del wrapper (API pública) ---
HEADERS += \
    $$files($$PWD/../mdflib/include/mdflibrary/*.h, true)

# --- Rutas de include ---
# Incluye tanto los headers del wrapper como los de la librería base
INCLUDEPATH += $$PWD/../mdflib/include

# --- Enlace con la librería base ---
LIBS += -L$$PWD/../lib -lmdflib
