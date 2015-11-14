QT += core
QT -= gui

TARGET = psp
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    csimplesocket/ActiveSocket.cpp \
    csimplesocket/HTTPActiveSocket.cpp \
    csimplesocket/PassiveSocket.cpp \
    csimplesocket/SimpleSocket.cpp \
    model/Bonus.cpp \
    model/Car.cpp \
    model/CircularUnit.cpp \
    model/Game.cpp \
    model/Move.cpp \
    model/OilSlick.cpp \
    model/Player.cpp \
    model/PlayerContext.cpp \
    model/Projectile.cpp \
    model/RectangularUnit.cpp \
    model/Unit.cpp \
    model/World.cpp \
    MyStrategy.cpp \
    RemoteProcessClient.cpp \
    Runner.cpp \
    Strategy.cpp \
    mycode.cpp

DISTFILES +=

HEADERS += \
    csimplesocket/ActiveSocket.h \
    csimplesocket/Host.h \
    csimplesocket/HTTPActiveSocket.h \
    csimplesocket/PassiveSocket.h \
    csimplesocket/SimpleSocket.h \
    csimplesocket/StatTimer.h \
    model/Bonus.h \
    model/BonusType.h \
    model/Car.h \
    model/CarType.h \
    model/CircularUnit.h \
    model/Direction.h \
    model/Game.h \
    model/Move.h \
    model/OilSlick.h \
    model/Player.h \
    model/PlayerContext.h \
    model/Projectile.h \
    model/ProjectileType.h \
    model/RectangularUnit.h \
    model/TileType.h \
    model/Unit.h \
    model/World.h \
    MyStrategy.h \
    RemoteProcessClient.h \
    Runner.h \
    Strategy.h \
    mycode.h

