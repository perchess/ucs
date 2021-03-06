#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <ros/ros.h>
#include <ros_wrapper.h>
#include <QQmlContext>
#include <QApplication>
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
    /// Init ROS
    ros::init(argc, argv, "DataHub_node");

    // Проверяем, запущен ли мастер, если нет - запускаем
    if (!ros::master::check())
        system("roscore &");

    ros::NodeHandle nh("~");

    ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("chatter", 1000);

    RosWrapper selfpub(&nh, &chatter_pub);
    CppWrapper cppWrapper;

    ros::AsyncSpinner spiner(0);
    spiner.start();
    /// ----------

    /// Init QT
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();

    ///RVIZ
    rviz::QuickVisualizationFrame::registerTypes();
    qmlRegisterType<SimpleGrid>("MyModule", 1, 0, "SimpleGrid");
    qmlRegisterType<DisplayConfig>("MyModule", 1, 0, "DisplayConfig");
//    qmlRegisterType<RobotModelType>("MyModule", 1, 0, "RobotModel");

    /* Загружаем объект класса в qml
     *
     * */
    context->setContextProperty("rosStringPub", &selfpub);
    context->setContextProperty("cppWrapper", &cppWrapper);
    context->setContextProperty("curPath", QString(CURRENT_DIR));

    /*
     *
     * */
    // RVIZ
//    MyViz myViz;
//    myViz.resize(200, 200);
//    myViz.show();
//    myViz.raise();

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    auto app_exec = app.exec();

    system("killall roscore");

    return app_exec;
}
