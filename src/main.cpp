#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <ros/ros.h>
#include <std_msgs/String.h>


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

class Publisher{
    Q_OBJECT
public:
    Publisher(ros::NodeHandle * nh, ros::Publisher * pub)
        : msg_(std::string())
        , nh_(nh)
        , pub_(pub)
    {}

public slots:
    void setValue(std::string str){
        if (str != msg_) {
        msg_=str;
        std_msgs::String ros_msg;
        ros_msg.data = msg_;
        pub_->publish(ros_msg);

        emit valueChanged(msg_);
        }

    }


signals:
   void valueChanged(std::string newValue);

private:
    std::string msg_;
    ros::NodeHandle * nh_;
    ros::Publisher * pub_;
};


int main(int argc, char *argv[]){
    /// Init ROS
    ros::init(argc, argv, "DataHub_node");
    ros::NodeHandle nh("~");

    ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("chatter", 1000);

    Publisher selfpub(&nh, &chatter_pub);

    ros::AsyncSpinner spiner(0);
    spiner.start();
    /// ----------

    /// Init QT
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
