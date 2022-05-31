#include <ros/ros.h>

// MoveIt
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_state/robot_state.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "robot_model_and_robot_state_tutorial");
  ros::AsyncSpinner spinner(1);
  spinner.start();
  
  // We start by instantiating a
  // `RobotModelLoader`_
  // object, which will look up
  // the robot description on the ROS parameter server and construct a
  // :moveit_core:`RobotModel` for us to use.
  //
  // .. _RobotModelLoader:
  //     http://docs.ros.org/noetic/api/moveit_ros_planning/html/classrobot__model__loader_1_1RobotModelLoader.html
  
  robot_model_loader::RobotModelLoader robot_model_loader("robot_description");
  const moveit::core::RobotModelPtr& kinematic_model = robot_model_loader.getModel();
  ROS_INFO("Model frame: %s", kinematic_model->getModelFrame().c_str());

  // Using the :moveit_core:`RobotModel`, we can construct a
  // :moveit_core:`RobotState` that maintains the configuration
  // of the robot. We will set all joints in the state to their
  // default values. We can then get a
  // :moveit_core:`JointModelGroup`, which represents the robot
  // model for a particular group, e.g. the "panda_arm" of the Panda
  // robot.
  
  moveit::core::RobotStatePtr kinematic_state(new moveit::core::RobotState(kinematic_model));
  kinematic_state->setToDefaultValues();
  const moveit::core::JointModelGroup* joint_model_group = kinematic_model->getJointModelGroup("arm");
  moveit::planning_interface::MoveGroupInterface group("arm");
  const std::vector<std::string>& joint_names = joint_model_group->getVariableNames();

  
  //kinematic_state->setToRandomPositions(joint_model_group);
  //const Eigen::Isometry3d& pose1 = kinematic_state->getGlobalLinkTransform("arm_link_04");
  geometry_msgs::Pose pose1;
	
  pose1.orientation.w = 0.70;
  pose1.orientation.x = -0.00;
  pose1.orientation.y = 0.00;
  pose1.orientation.z = -0.71;
  pose1.position.x =  0.50;
  pose1.position.y =  0.00;
  pose1.position.z =  1.15;
  
  
  // Inverse Kinematics
  // ^^^^^^^^^^^^^^^^^^
  // We can now solve inverse kinematics (IK) for the Panda robot.
  // To solve IK, we will need the following:
  //
  //  * The desired pose of the end-effector 
  //  * The timeout: 0.1 s
  
  group.setStartStateToCurrentState();
  group.setApproximateJointValueTarget(pose1, "arm_link_04");
  std::vector<double> joint_values;
  double timeout = 0.1;
  bool found_ik = kinematic_state->setFromIK(joint_model_group, pose1, timeout);

  // Now, we can print out the IK solution (if found):
  if (found_ik)
  {
    kinematic_state->copyJointGroupPositions(joint_model_group, joint_values);
    for (std::size_t i = 0; i < joint_names.size(); ++i)
    {
      ROS_INFO("Joint %s: %f", joint_names[i].c_str(), joint_values[i]);
    }
  }
  else
  {
    ROS_INFO("Did not find IK solution");
  }
  
  
  group.setJointValueTarget(joint_values);
  group.setStartStateToCurrentState();
  group.setGoalOrientationTolerance(0.01);
  group.setGoalPositionTolerance(0.01);

  // Plan and execute
  moveit::planning_interface::MoveGroupInterface::Plan my_plan;
  group.plan(my_plan); 
  group.execute(my_plan);
  
  std::cout << "Position 1 -> IK + setJointValue" << std::endl;
  sleep(5.0);
  
  // Move to default positions
  
	group.setNamedTarget("zero");
	group.move();  
	
   std::cout << "Position 2 -> Zero" << std::endl;
   sleep(5.0);
	
	group.setNamedTarget("pose1");
	group.move();   
	
   std::cout << "Position 3 -> Pose1" << std::endl;
   sleep(5.0);
	
  pose1.orientation.w = 0.00;
  pose1.orientation.x = -0.00;
  pose1.orientation.y = 0.00;
  pose1.orientation.z = 1.00;
  pose1.position.x =  0.50;
  pose1.position.y =  0.50;
  pose1.position.z =  1.00;
  
  group.setStartStateToCurrentState();
  group.setApproximateJointValueTarget(pose1, "arm_link_04");
  found_ik = kinematic_state->setFromIK(joint_model_group, pose1, timeout);

  if (found_ik)
  {
    kinematic_state->copyJointGroupPositions(joint_model_group, joint_values);
    for (std::size_t i = 0; i < joint_names.size(); ++i)
    {
      ROS_INFO("Joint %s: %f", joint_names[i].c_str(), joint_values[i]);
    }
  }
  else
  {
    ROS_INFO("Did not find IK solution");
  }
  
  
  group.setJointValueTarget(joint_values);
  group.setStartStateToCurrentState();
  group.setGoalOrientationTolerance(0.01);
  group.setGoalPositionTolerance(0.01);

  // Plan and execute
  group.plan(my_plan); 
  group.execute(my_plan);
  
  std::cout << "Position 4 -> IK + setJointValue" << std::endl;
  sleep(5.0);
  

  ros::shutdown();
  return 0;
}
