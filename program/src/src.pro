TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    market.cpp \
    agent.cpp


HEADERS += \
    market.h \
    agent.h


##MPI OSX
#INCLUDEPATH += /usr/local/include
##INCLUDEPATH += /usr/local/Cellar/open-mpi/2.0.1/include

#LIBS += -L/usr/local/opt/libevent/lib -L/usr/local/Cellar/open-mpi/2.0.1/lib -lmpi


## MPI Settings UBUNTU
#QMAKE_CXX = mpicxx
#QMAKE_CXX_RELEASE = $$QMAKE_CXX
#QMAKE_CXX_DEBUG = $$QMAKE_CXX
#QMAKE_LINK = $$QMAKE_CXX
#QMAKE_CC = mpicc

#QMAKE_CFLAGS += $$system(mpicc --showme:compile)
#QMAKE_LFLAGS += $$system(mpicxx --showme:link)
#QMAKE_CXXFLAGS += $$system(mpicxx --showme:compile) -DMPICH_IGNORE_CXX_SEEK
#QMAKE_CXXFLAGS_RELEASE += $$system(mpicxx --showme:compile) -DMPICH_IGNORE_CXX_SEEK
