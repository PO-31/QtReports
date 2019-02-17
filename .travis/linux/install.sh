#!/bin/bash

packages_list=''
if [ "${CC}" = "clang" ]; then
	packages_list='qt512-meta-minimal qt512tools'
else
	packages_list='qt5-default qttools5-dev-tools'
fi

if [ "$BUILD_TYPE" = "doxygen" ]; then 
	packages_list+=' doxygen'
elif [ "$BUILD_TYPE" = "coverage" ]; then
	packages_list+=' libqt5sql5-sqlite'
fi
sudo apt-get install -y $packages_list


if [ "$BUILD_TYPE" = "coverage" ]; then 
	gem install lcoveralls
fi


if [ "$CC" = "gcc" ]; then
	export USING_QT_MKSPEC="linux-g++-64"
elif [ "$CC" = "clang" ]; then
	source /opt/qt512/bin/qt512-env.sh
	export USING_QT_MKSPEC="linux-clang"
else
	echo "Detected using unsupported compiler"
	exit 1
fi
