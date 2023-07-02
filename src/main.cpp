

#include <QApplication> 
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QTimer>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <veh_interfaces/msg/message.hpp>
#include <veh_interfaces/msg/degradation_info.hpp>
#include <veh_interfaces/msg/obj.hpp>

int main(int argc, char *argv[])
{
  // Initialize the Qt application and create the main window
  QApplication app(argc, argv);
  QWidget window;
  window.setWindowTitle("ROS2 Publisher");

  // Create a vertical layout and add a label and line edit for each message
  QVBoxLayout *layout = new QVBoxLayout(&window);
  QLabel *label1 = new QLabel("message 1:");
  QLineEdit *lineEdit1 = new QLineEdit();

  QLabel *label2 = new QLabel("message 2:");
  QLineEdit *lineEdit2 = new QLineEdit();

  QLabel *label3 = new QLabel("crit_impct :");
  QLineEdit *lineEdit3 = new QLineEdit();

  QLabel *label4 = new QLabel("low_impct:");
  QLineEdit *lineEdit4 = new QLineEdit();


  QLabel *label5 = new QLabel("rt_obj:");
  QLineEdit *lineEdit5 = new QLineEdit();

  QLabel *label6 = new QLabel("lt_obj:");
  QLineEdit *lineEdit6 = new QLineEdit();


  layout->addWidget(label1);
  layout->addWidget(lineEdit1);

  layout->addWidget(label2);
  layout->addWidget(lineEdit2);

    layout->addWidget(label3);
  layout->addWidget(lineEdit3);

     layout->addWidget(label4);
  layout->addWidget(lineEdit4);

       layout->addWidget(label5);
  layout->addWidget(lineEdit5);

        layout->addWidget(label6);
  layout->addWidget(lineEdit6);

   


  // Create a button to publish both messages
  QPushButton *button = new QPushButton("Publish Messages");
  layout->addWidget(button);

  // Initialize ROS2 and create a node and a single publisher
  rclcpp::init(argc, argv);
  rclcpp::QoS qos(10);
  rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("qt_publisher");
  auto pub = node->create_publisher<veh_interfaces::msg::Message>(std::string("custom_message"), qos);
  auto pub_dow = node->create_publisher<veh_interfaces::msg::DegradationInfo>(std::string("Degradation_info"), qos);
  auto pub_thrt = node->create_publisher<veh_interfaces::msg::Obj>(std::string("Object_Info"), qos);

  QTimer *timer = new QTimer();
  timer->setInterval(1000); // publish messages every 1000 ms (1 second)
  timer->start();


  // Connect the button's clicked signal to a slot function that will publish both messages
 // QObject::connect(button, &QPushButton::clicked, [&]() {
 QObject::connect(timer, &QTimer::timeout, [&]() {
    veh_interfaces::msg::Message msg;
    veh_interfaces::msg::DegradationInfo msg2;
    veh_interfaces::msg::Obj msg3;

    msg.message1 = lineEdit1->text().toStdString();
    msg.message2 = lineEdit2->text().toStdString();

    msg2.crit_impct = lineEdit3->text() == "true";
    msg2.low_impct = lineEdit4->text() == "true";

   
    msg3.rt_obj = lineEdit5->text() == "true";
    msg3.lt_obj = lineEdit6->text() == "true";
    

    
    pub->publish(msg);
    pub_dow->publish(msg2);
    pub_thrt->publish(msg3);
  });

  // Show the main window and run the Qt application
     window.show();
  return app.exec();
}
