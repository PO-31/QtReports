#!/bin/bash

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
