/*
 * Created By: Gareth Ellis
 * Created On: July 16th, 2016
 * Description: An example node that subscribes to a topic publishing strings,
 *              and re-publishes everything it receives to another topic with
 *              a "!" at the end
 */

#include <MyNode.h>

MyClass::MyClass(int argc, char **argv, std::string node_name) {
    // Setup NodeHandles
    ros::init(argc, argv, node_name);
    ros::NodeHandle nh;
    ros::NodeHandle private_nh("~");

    // Setup Subscriber(s)
    std::string topic_to_subscribe_to = "/scan";
    int refresh_rate = 10;
    my_subscriber = nh.subscribe(topic_to_subscribe_to, refresh_rate, &MyClass::subscriberCallBack, this);

    // Setup Publisher(s)
    std::string topic = private_nh.resolveName("cmd_vel");
    uint32_t queue_size = 1;
    my_publisher = private_nh.advertise<geometry_msgs::Twist>(topic, queue_size);
}

void MyClass::subscriberCallBack(const sensor_msgs::LaserScan::ConstPtr& msg) {
    ROS_INFO("Received message");

    int total_data_points = (msg->angle_max - msg->angle_min) / msg->angle_increment;
    int total_considered_data_points = 1.85/msg->angle_increment;
    int total_points_in_section = total_considered_data_points/10.0;

    double sections[10];
    int start = ( - 1.85 / 2 - msg->angle_min) / msg->angle_increment;
    double sum;

    for (int i = 0; i < 10; i++) {
        sum = 0;
        for (int j = 0; j < total_points_in_section; j++) {
            sum += msg->ranges[start];
            start++;
        }
        sections[i] = sum / total_points_in_section;
    }

    int max = sections[0];
    int max_index = 0;
    for (int i = 1; i < 10; i++) {
        if (sections[i] > max) {
            max = sections[i];
            max_index = i;
        }
    }

    float linear_x = 1; // 0.5 - 1.5
    float angular_z = 1; // 2

    int centre = start + total_points_in_section *( max_index + 0.5);
    for (int i = 0; i <  max_index; i++) {
        centre += total_points_in_section;
    }
    centre += total_points_in_section / 2;


    angular_z = msg->angle_min;
    angular_z += centre * msg->angle_increment;


    geometry_msgs::Twist message;
    message.linear.x = linear_x;
    message.angular.z = angular_z;

    my_publisher.publish(message);
    /*
     * std::
     */
}

std::string MyClass::addCharacterToString(std::string input_string, std::string suffix) {
    return input_string.append(suffix);
}

void MyClass::republishMsg(std::string msg_to_publish) {
    std_msgs::String string_to_publish;
    string_to_publish.data = msg_to_publish;
    my_publisher.publish(string_to_publish);
    ROS_INFO("Published message");
}

/*
 * void MyClass::republishMsg() {
 *      my_publisher.publish();
 *      ROS_INFO("Published message");
 */
