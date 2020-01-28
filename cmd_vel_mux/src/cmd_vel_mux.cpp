#include "ros/ros.h"
#include <geometry_msgs/Twist.h>

class CmdVelMux
{
public:
	CmdVelMux(): n_()
	{
		vel_input_sub_ = n_.subscribe("/cmd_vel_mux", 1, &CmdVelMux::velCallback, this);
    vel_output_pub_ = n_.advertise<geometry_msgs::Twist>("/nav_vel", 1);
	}

	void velCallback(const geometry_msgs::Twist::ConstPtr& msg)
	{
    last_vel_ = *msg;
    last_msg_time_ = ros::Time::now();
	}

  void step()
	{
    if (ros::Time::now() - last_msg_time_ < ros::Duration(1))
      vel_output_pub_.publish(last_vel_);
  }

private:
	ros::NodeHandle n_;
	ros::Subscriber vel_input_sub_;
  ros::Publisher vel_output_pub_;
  geometry_msgs::Twist last_vel_;
  ros::Time last_msg_time_;
};

int main(int argc, char **argv)
{

  ros::init(argc, argv, "cmd_vel_mux_node");
  ros::NodeHandle n;

  CmdVelMux cmd_vel_mux;
  ros::Rate loop_rate(30);

  while (ros::ok())
  {
    cmd_vel_mux.step();
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
 }
