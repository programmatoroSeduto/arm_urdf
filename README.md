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
- [x] create missing links and very first test in Gazebo
- [x] working on the chassis of the robot
- [x] test in Gazebo of the chassis only
- [x] working on the manipulator of the robot
- [x] test in Gazebo of the chassis alongside with the robot
- [ ] :sparkle: setting up Gazebo plugins
- [ ] controllers!
- [ ] end up the writing of the readme
- [ ] deployment

## What is this?

This ROS package contains a *xacro* description for a robot made up of

- a mobile base with two wheels
- and a manipulator on the chassis of the robot

THe robot also supports some other functionalities such as laser scan and others. 

## Structure of the repository

--

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

## Visualize the model in Gazebo

--

# Structure of the model

## A fundamental observation about the origin

The first link is spawned with its center of mass as origin. To understand the position of the center for a second link, imagine that it appears by default with the origin located at the one of the jint linking the two links. If the origin of the joint is 0,0,0 then the center of the second link will be the same of the first one.

The tag `\<origin>` always specifies not the coordinates of the origin of the second link, but instead the transform of the origin of the second link, which has a different meaning: it specifies the offset with respect to the previous joint origin. Let's suppose for example a structure like this:

- cube A of height La
- cube B of height Lb put on the cube A

to model this situation, the correct code to use is the following:

```xml
<?xml version="1.0"?>

<robot name="cubebot" xmlns:xacro="http://www.ros.org/wiki/xacro">

<xacro:property name="La" value="0.5" />
<xacro:property name="Lb" value="0.2" />

<link name="A">
	<origin xyz="0 0 0" rpy="0 0 0" /> 
	
	<inertial>
		<mass value="0.1"/>
  		<origin xyz="0 0 0" rpy="0 0 0" />
  		<inertia 
			ixx="0.0000416666667" iyy="0.0000416666667" izz="0.0000416666667" 
			iyz="0" ixy="0" ixz="0" />
	</inertial>
	
	<collision>
		<origin xyz="0 0 0" rpy="0 0 0"/>
		<geometry>
			<box size="${La} ${La} ${La}" />
		</geometry>
  	</collision>
	
	<visual name="cubeA">
		<origin xyz="0 0 0" rpy="0 0 0"/>
		<geometry>
			<box size="${La} ${La} ${La}" />
		</geometry>
	</visual>
</link>

<joint name="joint_A_B" type="fixed">
	<parent link="A" />
	<child link="B" />
	
	<origin xyz="0 0 0" rpy="0 0 0" />
</joint>

<link name="B">
	<origin xyz="0 0 0" rpy="0 0 0" />
	
	<inertial>
		<mass value="0.1"/>
  		<origin xyz="0 0 0" rpy="0 0 0" />
  		<inertia 
			ixx="0.0000416666667" iyy="0.0000416666667" izz="0.0000416666667" 
			iyz="0" ixy="0" ixz="0" />
	</inertial>
	
	<collision>
		<origin xyz="0 0 0" rpy="0 0 0"/>
		<geometry>
			<box size="${Lb} ${Lb} ${Lb}" />
		</geometry>
  	</collision>
	
	<visual name="cubeB">
		<origin xyz="0 0 0" rpy="0 0 0"/>
		<geometry>
			<box size="${Lb} ${Lb} ${Lb}" />
		</geometry>
	</visual>
</link>

</robot>
```

Tests:

- with each origin to zero, both the cubes have the same origin, i.e. the one of the world frame
- let's set the `origin` of the first cube to `0 0 ${La/2}`: nothing happens
- let's set also the other origins for the link A: **now the cube appears on the floor** but the cube B has the same origin of the world frame
- let's delete the other origins except for the main one, inside the very first scope of the `link` tag A: the cubes return below the floor
- let's set the origin of the joint to `0 0 ${La/2}`: now both A and B have the same origin (strange...)
- let's change the origin of the joint to `0 0 ${La + Lb/2}`: now the cube B is on the cube A as we want!



# TroubleShooting

## WARN -- root lik with Inertia

This (neglectable) warning is caused by assigning an <ineritial> tag to the so called *root link* i.e. the very first link defined in the URDF model. When trying to run Gazebo, an error message could appear such like this one:


```
[ WARN] [1653916723.536752700]: The root link base_link has an inertia specified in the URDF, but KDL does not support a root link with an inertia.  As a workaround, you can add an extra dummy link to your URDF.
```

For further informations, see this interesting post from the [official ROS1 community](https://answers.ros.org/question/192817/error-msg-the-root-link_base-has-an-inertia-specified-in-the-urdf-but-kdl/).

The error should be alreaty solved: see the `main.xacro` which includes a dummy link before defining every other component of the robot. 

