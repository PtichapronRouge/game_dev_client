TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L"/home/thelistener/cpp/libs/SFML/SFML-2.4.1/lib"

CONFIG(release, debug|release): LIBS += -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += "/home/thelistener/cpp/libs/SFML/SFML-2.4.1/include"
DEPENDPATH += "/home/thelistener/cpp/libs/SFML/SFML-2.4.1/include"

SOURCES += main.cpp \
    sources/statestack.cpp \
    sources/state.cpp \
    sources/application.cpp \
    sources/initstate.cpp

HEADERS +=  headers/statestack.hpp \
    headers/displaymanager.hpp \
    headers/state.hpp \
    headers/stateidentifiers.hpp \
    headers/application.hpp \
    headers/initstate.hpp \
    headers/resourceholder.hpp

