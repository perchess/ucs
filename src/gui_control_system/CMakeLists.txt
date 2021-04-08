cmake_minimum_required(VERSION 3.13)
project(gui_control_system)

add_compile_options(-std=c++14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(FeatureSummary)

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Qt version: ${QT_VERSION}")
message(STATUS "Qt spec: ${QT_MKSPEC}")



function(ADD_APP_TRANSLATIONS_RESOURCE res_file)
    set(_qm_files ${ARGN})
    set(_res_file ${CMAKE_CURRENT_BINARY_DIR}/app_translations.qrc)

    file(WRITE ${_res_file} "<!DOCTYPE RCC><RCC version=\"1.0\">\n <qresource prefix=\"/\">\n")
    foreach(_lang ${_qm_files})
        get_filename_component(_filename ${_lang} NAME)
        file(APPEND ${_res_file} "  <file>${_filename}</file>\n")
    endforeach()
    file(APPEND ${_res_file} " </qresource>\n</RCC>\n")

    set(${res_file} ${_res_file} PARENT_SCOPE)
endfunction()



###################################
# Attention! Need use gold linker #
# to avoid multiple definition    #
# '__bss_start' in QQuickStyle    #
###################################
if (UNIX)
    execute_process(COMMAND ${CMAKE_C_COMPILER} -fuse-ld=gold -Wl,--version ERROR_QUIET OUTPUT_VARIABLE ld_version)
    if ("${ld_version}" MATCHES "GNU gold")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold -Wl,--disable-new-dtags")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=gold -Wl,--disable-new-dtags")
    endif()
endif()
###################################


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    rosbag
    rosbag_storage
    std_msgs
    rviz
    )
find_package(yaml_cpp)

# Qt5
find_package(Qt5 ${QT_VERSION}
    COMPONENTS
    Core
    Qml
    Quick
    WebView
    Widgets
    QuickControls2
    Sql
    LinguistTools
    REQUIRED
    HINTS
    ${QT_LIBRARY_HINTS}
    )

message("Qt5Core_VERSION_MAJOR: " ${Qt5Core_VERSION_MAJOR})
message("Qt5Core_VERSION_MINOR: " ${Qt5Core_VERSION_MINOR})


set(TARGET_HDR
    include/qml_wrapper.h
    include/ros_wrapper.h
    include/simplegrid.h
    include/displayconfig.h
    include/robot_model.h
    include/logs_table_model.h
    include/modelfilter.h
    )

set(TARGET_SRC
    src/main.cpp
    src/qml_wrapper.cpp
    src/ros_wrapper.cpp
    src/simplegrid.cpp
    src/displayconfig.cpp
    src/robot_model.cpp
    src/logs_table_model.cpp
    src/modelfilter.cpp
    )

set(RESOURCES
    qml.qrc
    #  src/imports/FalloutTheme/qmldir
    #  src/imports/FalloutTheme/FalloutTheme.qml
    )
###################################
## catkin specific configuration ##
###################################
catkin_package(
    INCLUDE_DIRS
    src
    include
    CATKIN_DEPENDS
    roscpp
    std_msgs
    )

###########
## Build ##
###########

qt5_wrap_cpp(${PROJECT_NAME}_MOCS ${TARGET_HDR})

set(QML_IMPORT_PATH ${CMAKE_SOURCE_DIR}/src/imports
    ${CMAKE_SOURCE_DIR}/src/CustomItems
    #                    /opt/Qt5_15/5.15.0
    #                    CACHE STRING "" FORCE
    )

qt5_add_resources(${PROJECT_NAME}_QML ${RESOURCES})

#################
## Translation ##
#################

set(TS_FILES
    translations/main_en.ts
    translations/main_de.ts
    )


qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR}
    ${TS_FILES})

add_app_translations_resource(APP_RES ${QM_FILES})


#qt5_add_translation(QM_FILES ${TS_FILES})

#configure_file(app_translations.qrc ${CMAKE_BINARY_DIR} COPYONLY)

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}
    ${Qt5Widgets_INCLUDE_DIRS}
    #  ${CMAKE_SOURCE_DIR}/src/imports/FalloutTheme/
    #  ${CMAKE_SOURCE_DIR}/src/CustomItems/
    )

add_executable(${PROJECT_NAME}
    ${TARGET_SRC}
    ${QT_RESOURCES_CPP}
    ${${PROJECT_NAME}_MOCS}
    ${${PROJECT_NAME}_QML}
    ${RESOURCES}
    ${TARGET_HDR}
    ${APP_RES}
    )

target_link_libraries(${PROJECT_NAME}
    ${catkin_LIBRARIES}
    Qt5::Core
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickControls2
    Qt5::Sql
    Qt5::WebView
    yaml-cpp
    )
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
get_target_property(QtCore_location Qt5::Core LOCATION)

# Копироваие скрипта с для поиска по сценариям
#configure_file(${CMAKE_SOURCE_DIR}/src/find_scenarios.py
#    ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_BIN_DESTINATION}/find_scenarios.py
#    COPYONLY)
#configure_file(${CMAKE_SOURCE_DIR}/src/find_scenarios.py
#    $ENV{HOME}/.ros/find_scenarios.py
#    COPYONLY)

