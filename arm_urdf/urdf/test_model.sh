#! /bin/bash

echo "ATTENTION: remember to start the ROSmaster first!"

set -e

rm -rf --force robot.pdf
# roscore &
rosrun xacro xacro main.xacro -o model.urdf
check_urdf model.urdf
urdf_to_graphiz model.urdf
rm --force robot.urdf robot.gv
firefox ./robot.pdf
