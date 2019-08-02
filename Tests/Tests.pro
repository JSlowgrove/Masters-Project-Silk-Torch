win32:include(gtest_dependency.pri)
unix:LIBS+= -lgtest

TARGET=Tests

SOURCES += \
    main.cpp \
    ../Masters_Project_Silk_Torch/src/Logging.cpp \
    ../Masters_Project_Silk_Torch/src/Utilities.cpp

INCLUDEPATH += \
    ../Masters_Project_Silk_Torch/include

win32:INCLUDEPATH += $$(SDKs)/glm-0.9.9.3
#unix:INCLUDEPATH += /usr/local/include
unix:INCLUDEPATH += /public/devel/2018/glm-0.9.9.2
