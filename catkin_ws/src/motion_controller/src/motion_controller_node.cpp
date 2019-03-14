#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <termios.h>

int main( int argc, char *argv[] ) {
	ros::NodeHandle *nh = NULL;
	ros::NodeHandle *nh_priv = NULL;

	ros::init( argc, argv, "motion_controller_node" );

	nh = new ros::NodeHandle( );
	if( !nh )
	{
		ROS_FATAL( "Failed to initialize NodeHanlde" );
		ros::shutdown( );
		return -1;
	}
	nh_priv = new ros::NodeHandle( "~" );
	if( !nh_priv )
	{
		ROS_FATAL( "Failed to initialize private NodeHanlde" );
		delete nh;
		ros::shutdown( );
		return -2;
	}
	qik = new pololu_qik::pololu_qik( *nh, *nh_priv );
	if( !qik )
	{
		ROS_FATAL( "Failed to initialize driver" );
		delete nh_priv;
		delete nh;
		ros::shutdown( );
		return -3;
	}
	if( !qik->start( ) )
		ROS_ERROR( "Failed to start the driver" );

	ros::Rate rate(20);
	while(1) {
          rate.sleep();
	  ros::spinOnce();
          qik->spin_once();
	}

	delete qik;
	delete nh_priv;
	delete nh;

	return 0;
}
