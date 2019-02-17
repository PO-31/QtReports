#!/bin/bash

packages_list=''
if [ "${CC}" = "clang" ]; then
	sudo add-apt-repository -y ppa:beineri/opt-qt-5.12.0-xenial
	packages_list='qt512-meta'
else
	packages_list='qt5-default qttools5-dev-tools'
fi

if [ "$BUILD_TYPE" = "doxygen" ]; then 
	packages_list+=' doxygen'
elif [ "$BUILD_TYPE" = "coverage" ]; then
	packages_list+=' libqt5sql5-sqlite'
fi

sudo apt-get update -qq
