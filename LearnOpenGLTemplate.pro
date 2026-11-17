TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lassimp

SOURCES += \
        glad.c \
        main.cpp \
        src/common/camera.cpp \
        src/common/mesh.cpp \
        src/common/model.cpp \
        src/common/shader.cpp \
        src/common/window.cpp \
        src/util/controller_util.cpp \
        src/util/file_util.cpp

HEADERS += \
    includes/stb_image.h \
    src/common/camera.h \
    src/common/macro.h \
    src/common/mesh.h \
    src/common/model.h \
    src/common/shader.h \
    src/common/singleton.h \
    src/common/window.h \
    src/util/controller_util.h \
    src/util/file_util.h

DISTFILES += \
    resource/shaders/fragment.fsh \
    resource/shaders/vertex.vsh
