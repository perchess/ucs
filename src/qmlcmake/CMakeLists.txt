cmake_minimum_required(VERSION 3.10)
project(qmlcmake)

add_compile_options(-std=c++14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

# Qt5
find_package(Qt5 COMPONENTS
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
    include/ros_wrapper.h
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
  src/ros_wrapper.cpp
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
                    CACHE STRING "" FORCE)

qt5_add_resources(${PROJECT_NAME}_QML src/qml.qrc)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} helloworld_en.ts helloworld_de.ts)

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
  ${QM_FILES}
)

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  Qt5::Core
  Qt5::Qml
  Qt5::Quick
  Qt5::QuickControls2
  Qt5::Sql
  Qt5::WebView
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

