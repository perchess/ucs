#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <ros/ros.h>
#include <wrappers/qml_wrapper.h>
#include <wrappers/ros_wrapper.h>
#include <QQmlContext>
#include <QProcess>

#include <QDir>
//#include <my_rviz.h>

#include <experimental/filesystem>

#include "rviz/quick_visualizer_app.h"
#include "rviz/quick_visualization_frame.h"

#include "rviz/visualization_manager.h"
#include "rviz/render_panel.h"
#include "rviz/displays_panel.h"
#include "rviz/default_plugin/robot_model_display.h"
#include <ros/package.h>

#include "custom_rviz/simplegrid.h"
#include "custom_rviz/displayconfig.h"

#include "rosbag_parser/logs_table_model.h"

//#include "robot_model.h"



//! @brief Шаблоннная функция для чтения параметров
template <typename T>
void readParam(const std::string param_name, T& param_value,
               const T default_value) {
    if (!ros::param::get(param_name, param_value)) {
        ROS_WARN_STREAM("Parameter \""
                        << param_name << "\" didn' find in Parameter Server."
                        << "\nSetting default value: " << &default_value);
        param_value = default_value;
    }
}




int main(int argc, char *argv[]){
    ///
    ///  Инциализация переменных окружения
    ///
    qputenv("QSG_RENDER_LOOP", "basic");
    qputenv("TURTLEBOT3_MODEL", "waffle");
    ///
    ///  Инциализация ROS
    ///
    ros::init(argc, argv, "DataHub_node");
    QProcess rosTerminal;
    // Проверяем, запущен ли мастер, если нет - запускаем
    if (!ros::master::check())
    {
      ROS_WARN("No rosmaster detected. Launching roscore ...");
      rosTerminal.start("roscore", QStringList());
      rosTerminal.waitForStarted();
    }

    RosWrapper rosWrapper;
    ///
    ///  ----------
    ///

    ///
    ///  Инциализация QT
    ///
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setOrganizationName("SPBSTU");
    app.setOrganizationDomain("SPBSTU");



    QQmlApplicationEngine engine;
    CppWrapper cppWrapper(&engine);

    qDebug() << "Qt version : " << QT_VERSION_STR;

    QQmlContext *context = engine.rootContext();

    ///RVIZ
    rviz::QuickVisualizationFrame::registerTypes();
    qmlRegisterType<SimpleGrid>("MyModule", 1, 0, "SimpleGrid");
    qmlRegisterType<DisplayConfig>("MyModule", 1, 0, "DisplayConfig");
//    qmlRegisterType<RosWrapper>("RosWrapper", 1, 0, "ROS");
//    qmlRegisterType<RobotModelType>("MyModule", 1, 0, "RobotModel");

    /* Загружаем объект класса в qml
     *
     * */
    context->setContextProperty("rosbagTableModel", rosWrapper.getTableModel());
    context->setContextProperty("rosWrapper", &rosWrapper);
    context->setContextProperty("cppWrapper", &cppWrapper);
    context->setContextProperty("curPath", QString(ros::package::getPath("gui_control_system").c_str()));


    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    auto app_exec = app.exec();

    rosTerminal.terminate();
    rosTerminal.waitForFinished();

    return app_exec;
}
