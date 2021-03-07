cmake_minimum_required(VERSION 3.1)
project(qmlcmake)

add_compile_options(-std=c++14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(Qt5Core_DIR "/home/den/Qt5-12/5.12.2/gcc_64/lib/cmake/Qt5Core")
set(Qt5_DIR "/home/den/Qt5-12/5.12.2/gcc_64/lib/cmake/Qt5")
#set(QT_QMAKE_EXECUTABLE "/home/den/Qt5-12/5.12.2/gcc_64/bin/qmake")
#set(LD_LIBRARY_PATH $ENV{LD_LIBRARY_PATH}:/home/den/Qt5-12/5.12.2/gcc_64/lib)

message($ENV{LD_LIBRARY_PATH})
#message(STATUS "Qt version: ${QT_VERSION}")

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
  std_msgs
  rviz2
)
find_package(yaml_cpp)

# Qt5
find_package(Qt5 5.12.2 COMPONENTS
  Core
  Qml
  Quick
  WebView
  Widgets
  QuickControls2
  Sql
  LinguistTools
  REQUIRED
)

set(TARGET_HDR
    include/qml_wrapper.h
    include/simplegrid.h
    include/displayconfig.h
    include/robot_model.h
    #    include/my_rviz.h
#    src/log_model.h
#    src/base_module.h
#    src/weight_module.h
#    src/festo_module.h
#    src/flexbe_module.h
#    src/model.h
#    src/scenario_model.h
#    src/stz_module.h
#    src/manipulator_module.h
#    src/scenarioparser.h
)

set(TARGET_SRC
#  src/log_model.cpp
#  src/base_module.cpp
  src/main.cpp
  src/qml_wrapper.cpp
  src/simplegrid.cpp
  src/displayconfig.cpp
  src/robot_model.cpp
#  src/my_rviz.cpp
#  src/weight_module.cpp
#  src/festo_module.cpp
#  src/flexbe_module.cpp
#  src/model.cpp
#  src/scenario_model.cpp
#  src/stz_module.cpp
#  src/manipulator_module.cpp
#  src/scenarioparser.cpp
)

set(RESOURCES
  src/qml.qrc
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

qt5_add_resources(${PROJECT_NAME}_QML src/qml.qrc)

#################
## Translation ##
#################

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} helloworld_en.ts helloworld_de.ts)

add_app_translations_resource(APP_RES ${QM_FILES})

set(TS_FILES
    helloworld_en.ts helloworld_de.ts
)

qt5_add_translation(QM_FILES ${TS_FILES})

configure_file(translations.qrc ${CMAKE_BINARY_DIR} COPYONLY)

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
  ${CMAKE_BINARY_DIR}/translations.qrc
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

