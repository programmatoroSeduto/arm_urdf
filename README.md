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
- [ ] :sparkle: working on the manipulator of the robot
- [ ] test in Gazebo of the chassis alongside with the robot
- [ ] setting up Gazebo plugins
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

--

# TroubleShooting

## WARN -- root lik with Inertia

This (neglectable) warning is caused by assigning an <ineritial> tag to the so called *root link* i.e. the very first link defined in the URDF model. When trying to run Gazebo, an error message could appear such like this one:


```
[ WARN] [1653916723.536752700]: The root link base_link has an inertia specified in the URDF, but KDL does not support a root link with an inertia.  As a workaround, you can add an extra dummy link to your URDF.
```

For further informations, see this interesting post from the [official ROS1 community](https://answers.ros.org/question/192817/error-msg-the-root-link_base-has-an-inertia-specified-in-the-urdf-but-kdl/).

The error should be alreaty solved: see the `main.xacro` which includes a dummy link before defining every other component of the robot. 

