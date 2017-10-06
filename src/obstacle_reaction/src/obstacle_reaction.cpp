#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <string>

// TODO: Define a callback here which does all the reacting!

int main(int argc, char **argv){
    std::string node_name = "olaf_brain";
    ros::init(argc, argv, node_name);
    ros::NodeHandle nh;

    ros::Rate loop_rate=10;

    while(ros::ok()){


        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
