#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <ros/ros.h>
#include <qml_wrapper.h>
#include <QQmlContext>

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

#include "simplegrid.h"
#include "displayconfig.h"

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


    QLocale::setDefault(QLocale("ru_RU"));
    /// Init ROS
    ros::init(argc, argv, "DataHub_node");

    // Проверяем, запущен ли мастер, если нет - запускаем
    if (!ros::master::check()){
      ROS_WARN("No rosmaster detected. Launching roscore ...");
      system("roscore &");
    }


    ros::NodeHandle nh("~");

    ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("gui_output", 1000);

    RosWrapper rosWrapper(&nh, &chatter_pub);



    ros::AsyncSpinner spiner(0);
    spiner.start();
    /// ----------

    /// Init QT
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);



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
    context->setContextProperty("rosWrapper", &rosWrapper);
    context->setContextProperty("cppWrapper", &cppWrapper);
    context->setContextProperty("curPath", QString(ros::package::getPath("gui_control_system").c_str()));

    /*
     *
     * */
    qDebug() << "App path : " << qApp->applicationDirPath();
    qDebug() << QDir().relativeFilePath("main.cpp");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    auto app_exec = app.exec();

    system("killall roscore &");

    return app_exec;
}
