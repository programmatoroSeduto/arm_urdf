
#include <ros/ros.h>

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

int main( int argc, char* argv[] )
{
	// init ROS node
	ros::init( argc, argv );
	ros::NodeHandle nh;
	
	// init as required by MoveIt framework
	ros::AsyncSpinner spinner( n_threads );
	spinner.start();
	
	// init MoveIt
	static const std::string PLANNING_GROUP = "my_arm";
	moveit::planning_interface::MoveGroupInterface move_group_interface( PLANNING_GROUP );
	move_group_interface.setPlanningTime(10.0);
	
	// set final pose
	geometry_msgs::Pose target_pose1;
	target_pose1.orientation.w = 1.0;
	target_pose1.position.x = 0.28;
	target_pose1.position.y = -0.2;
	target_pose1.position.z = 0.5;
	move_group_interface.setPoseTarget(target_pose1);
	
	// plan 
	moveit::planning_interface::MoveGroupInterface::Plan my_plan;
	move_group_interface.plan(my_plan);
	/*
	bool success = (
		move_group_interface.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
	*/
	
	// execute the plan
	move_group_interface.execute(my_plan);
	
	return 0;
}
