#!/bin/bash

# Because of the problem with Qt described in "before_install.sh",
# we use these packages. Not all dependencies are listed, so be caution.
packages_list='qt512-meta-minimal qt512tools libgles2-mesa-dev libgl1-mesa-dev'

if [ "$BUILD_TYPE" = "doxygen" ]; then 
	packages_list+=' doxygen'
fi
sudo apt-get install -y $packages_list


if [ "$BUILD_TYPE" = "coverage" ]; then 
	gem install lcoveralls
fi

source /opt/qt512/bin/qt512-env.sh
	
if [ "$CC" = "gcc" ]; then
	export USING_QT_MKSPEC="linux-g++-64"
elif [ "$CC" = "clang" ]; then
	export USING_QT_MKSPEC="linux-clang"
else
	echo "Detected using unsupported compiler"
	exit 1
fi
