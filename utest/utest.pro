TEMPLATE = app

CONFIG(debug, debug|release) {
  TARGET_SUFFIX = _d
} else {
  TARGET_SUFFIX =
}
TARGET = utest$$TARGET_SUFFIX

CONFIG += console
QT += testlib  script

HEADERS += \
    test_cpptools.h \
    test_qttools_core.h \
    test_qttools_script.h \
    \
    ../src/qttools/core/wait_loop.h \
    ../src/qttools/core/wait_loop_stop_condition.h \
    ../src/qttools/core/internal/wait_loop_p.h \
    ../src/qttools/core/internal/wait_loop_time_out_stop_condition.h \
    \
    ../src/qttools/script/calculator.h

SOURCES += \
    main.cpp \
    test_cpptools.cpp \
    test_qttools_core.cpp \
    test_qttools_script.cpp \
    \
    ../src/qttools/core/wait_loop.cpp \
    ../src/qttools/core/wait_loop_stop_condition.cpp \
    ../src/qttools/core/internal/wait_loop_p.cpp \
    ../src/qttools/core/internal/wait_loop_time_out_stop_condition.cpp \
    \
    ../src/qttools/script/calculator.cpp
