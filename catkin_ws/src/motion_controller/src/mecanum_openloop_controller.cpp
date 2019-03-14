#include "mecanum_openloop_controller/mecanum_openloop_controller.hpp"

#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <termios.h>

namespace mecanum_openloop_controller {

mecanum_openloop_controller::mecanum_openloop_controller(
  ros::NodeHandle &_nh, ros::NodeHandle &_nh_priv):
    nh(_nh),
    nh_priv(_nh_priv),
    front_right_out(0.0),
    front_left_out(0.0) {
      ROS_INFO("initializing");
      nh_priv.param("ns_motor", ns_motor, (std::string)"/motor");
      nh_priv.param("ns_motion", ns_motion, (std::string)"/motion");
      nh_priv.param("wheel_base_x", wheel_base_x, (double)0.137);
      nh_priv.param("wheel_base_y", wheel_base_y, (double)0.183);
      nh_priv.param("wheel_radius", wheel_radius, (double)0.03);
      nh_priv.param("openloop_gain", openloop_gain, (double)0.03);
      nh_priv.param("limit_linear", limit_linear, (double)0.5);
      nh_priv.param("limit_angular", limit_angular, (double)1.0);
      nh_priv.param("level_expiry", level_expiry, (double)1.0);
      nh_priv.param("num_levels", num_levels, (int)5);
}

void mecanum_openloop_controller::start() {
    ROS_INFO("starting");

    sub_level = nh.subscribe("/motion/level0", 1, &mecanum_openloop_controller::command_callback, this);
}

void mecanum_openloop_controller::spin_once( ) {
  ros::spin_once();

  ros::Time time = ros::Time::now();
  uint64_t t = 1000 * (uint64_t)time.sec + (uint64_t)time.nsec / 1e6;
  int i;

  return true;    
}

void mecanum_openloop_controller::stop() {
    ROS_INFO("stopping");
    sub_command.shutdown( );
}

void mecanum_openloop_controller::command_callback(const geometry_msgs::TwistPtr &msg) {

}

}
