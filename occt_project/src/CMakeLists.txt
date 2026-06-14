cmake_minimum_required(VERSION 3.19)
project(occt_project LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

# 设置输出到位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin/$<CONFIG>)

qt_add_executable(occt_project
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(occt_project
    PRIVATE
        Qt::Core
        Qt::Widgets
)

# 集成 OCCT
set(OCCT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../3rdpatry/occt)
# 头文件
target_include_directories(occt_project PRIVATE ${OCCT_ROOT}/inc)
# 库搜索路径
target_link_directories(occt_project PRIVATE ${OCCT_ROOT}/lib)
file(GLOB OCCT_LIBS_DEBUG "${OCCT_ROOT}/libd/*.lib")
file(GLOB OCCT_LIBS_RELEASE "${OCCT_ROOT}/lib/*.lib")
target_link_libraries(occt_project PRIVATE
    $<$<CONFIG:Debug>:${OCCT_LIBS_DEBUG}>
    $<$<NOT:$<CONFIG:Debug>>:${OCCT_LIBS_RELEASE}>
)

install(TARGETS occt_project
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET occt_project
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
