#! /bin/bash

echo "ATTENTION: remember to start the ROSmaster first!"

set -e

rm -rf --force ./model/robot.pdf ./model/model.urdf
# rm --force ./model/robot.urdf ./model/robot.gv
# roscore &
rosrun xacro xacro main.xacro -o ./model/model.urdf
check_urdf ./model/model.urdf
urdf_to_graphiz ./model/model.urdf
rm -rf ./robot.gv
mv robot.pdf ./model/robot.pdf
firefox ./model/robot.pdf
