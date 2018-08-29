/**
 * @file mavros_service_client.cpp
 * @brief 
 * Testing mavros position command as a ROS service server with this client node
 */

#include <ros/ros.h>
#include "mavros_test/mavros_cmd.h"
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
	if (argc != 5)
  {
    ROS_INFO("usage: motion_control_client x y z z_rotation");
    return 1;
  }
  ros::init(argc, argv, "mavros_service_client");
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<mavros_test::mavros_cmd>("mavros_service");
  mavros_test::mavros_cmd srv;
  srv.request.x_pos = atof(argv[1]);
  srv.request.y_pos = atof(argv[2]);
  srv.request.z_pos = atof(argv[3]);
  srv.request.z_rot = atof(argv[4]);
  
  double rate_l = 1;

  ros::Rate loopRate(rate_l);	// Hz
  //create instance of ar_drone_move to drive AR DRone
	while(ros::ok())
	{
		if (client.call(srv))
		  {
			ROS_INFO("Response: %d", srv.response.started);
		  }
		else
		  {
			ROS_ERROR("Failed to call mavros_test_node_server");
			return 1;
		  }
		loopRate.sleep();
		ros::spinOnce();
	}
  return 0;
}
