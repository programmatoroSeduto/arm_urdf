# Arm Urdf


*Francesco Ganci* - 4143910 - 2021/2022

> Compatible With:
> - ROS1 (Noetic)
> 
> Starting from this project:
> - [CarmineD8/robot_urdf on GitHub](https://github.com/CarmineD8/robot_urdf)

## Roadmap

- [x] first structure of the code and the repo
- [x] import already implemented macros from the original source file
- [ ] create missing links and very first test in Gazebo
- [ ] working on the chassis of the robot
- [ ] test in Gazebo of the chassis only
- [ ] working on the manipulator of the robot
- [ ] test in Gazebo of the chassis alongside with the robot
- [ ] end up the writing of the readme
- [ ] final debug of the model (deploy)

## What is this?

This ROS package contains a *xacro* description for a robot made up of

- a mobile base with two wheels
- and a manipulator on the chassis of the robot

THe robot also supports some other functionalities such as laser scan and others. 

## Structure of the repository

--

# How to inspect and test the model

## Inspect the model

Here are the steps to check the structure and the syntax of the model:

1. go inside the folder *urdf* in the package, and open up a shell from there

2. build the URDF file from XACRO; you can use these commands here:
	
	```
	roscore &
	
	rosrun xacro xacro main.xacro -o model.urdf
	```

3. for checking the structure of the robot on the console, run this: 
	
	```
	check_urdf model.urdf
	```
	
	a text screen showing the structure of the robot should appear. Otherwise, the program will complain with some syntax error. 

4. (optional) build a graph from the model by the command
	
	```
	urdf_to_graphiz model.urdf
	# firefox ./model.pdf
	```

## Visualize the model in Gazebo

--

# Structure of the model

--
