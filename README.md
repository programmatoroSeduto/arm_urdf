# Arm Urdf

*Francesco Ganci* - 4143910 - 2021/2022

> Compatible With:
> - ROS1 (Noetic)
> 
> Starting from this project:
> - [CarmineD8/robot_urdf on GitHub](https://github.com/CarmineD8/robot_urdf)

## What is this?

This ROS package contains a *xacro* description for a robot made up of

- a mobile base with two wheels
- and a manipulator on the chassis of the robot

THe robot also supports some other functionalities such as laser scan and others. 

## Structure of the repository

This repository contains a ROS1 package *arm_urdf* ready to be copied inside a workspace and then used. Here are the main files inside the folder:

```
.
├── arm_urdf
│   ├── config
│   │   └── motors_config.yaml	<> motors configuration
│   │
│   ├── launch
│   │   ├── run.launch	<> launch the entire model
│   │	│
│   │   ├── gazebo.launch	<> launch Gazebo only with the model
│   │   ├── rviz.launch	<> launch RViz only
│   │	│
│   │   └── cubes_example.launch	<> a little example about URDF
│   │
│   └── urdf
│       ├── test_model.sh	<> helpful for syntax checking, with visual schema
│    	│
│       ├── main.xacro	<> this XACRO contains the entire model, chassis + manipulator
│       ├── macros.xacro	<> main macros
│       ├── params.xacro	<> main parameters of the model
│    	│
│       ├── arm.xacro	<> the XACRO of the manipulator only
│       ├── chassis.xacro	<> the XACRO of the chassis only
│    	│
│       ├── gazebo.gazebo	<> plugins and materials for Gazebo
│       ├── materials.xacro	<> RViz materials data
│       ├── transmission.xacro	<> data about the motorization of the robot
│    	│
│       └── cubes.xacro	<> a very simple model, for understading
└──
```

# How to inspect and test the model

## Inspecting the model -- slow way

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
	
	```bash
	urdf_to_graphiz model.urdf
	# firefox ./robot.pdf
	```
	
	the command `urdf_to_graphviz` makes two files when launched: *robot.pdf* and *robot.gv*. 

## Inspecting the model -- fast way

In order to make a quick syntax check, I wrote a small script which does every abovementioned step. This script is located into the package folder *urdf* alongside with the xacro model. The script checks the syntax of the model and tries to build a graphical representation of the robot structure; if everything works fine, Firefox will show up the generated graph from the urdf/xacro model.

Here are the steps for executing the script:

1. from inside the package folder *urdf*, run a new shell

2. then, `roscore &`

3. and finally, `./test_model.sh`
	
	first remember to check if the script is set executable. If not, use this: `chmod +x ./test_model.sh`.

## Launch files

The main launch file is `run.launch` which runs both Gazebo (paused) and RViz. 

If you just want to see the model in Gazebo, run the model with the launch file `gazebo.launch`. Or, in case you want to run RViz only, the launch file is `rviz.launch`. 

# TroubleShooting

Here are some well known errors and troubles with this model 

## WARN -- root lik with Inertia

This (neglectable) warning is caused by assigning an <ineritial> tag to the so called *root link* i.e. the very first link defined in the URDF model. When trying to run Gazebo, an error message could appear such like this one:


```
[ WARN] [1653916723.536752700]: The root link base_link has an inertia specified in the URDF, but KDL does not support a root link with an inertia.  As a workaround, you can add an extra dummy link to your URDF.
```

For further informations, see this interesting post from the [official ROS1 community](https://answers.ros.org/question/192817/error-msg-the-root-link_base-has-an-inertia-specified-in-the-urdf-but-kdl/).

The error should be alreaty solved: see the `main.xacro` which includes a dummy link before defining every other component of the robot. 

## WARN -- ignoring data with redundant timestamp

Another warning that sometimes appears in the console, especially while executing the entire model with `run.launch` is the following:

```
[ WARN] [1654443200.004133200, 6.204000000]: TF_REPEATED_DATA ignoring data with redundant timestamp for frame link_left_wheel at time 6.200000 according to authority unknown_publisher
```

There are a lot of discussions about it, but no real solution. However, this error can be ignored. It is caused bu the Gazebo plugin `differential_drive_controller`. 
