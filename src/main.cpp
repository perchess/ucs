#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <ros/ros.h>
#include <ros_wrapper.h>
#include <QQmlContext>


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

    /* Загружаем объект класса в qml
     *
     * */
    context->setContextProperty("rosStringPub", &selfpub);
    context->setContextProperty("cppWrapper", &cppWrapper);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
