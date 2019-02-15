#!/bin/bash

packages_list='qt5-default qttools5-dev-tools'
if [ "$BUILD_TYPE" = "doxygen" ]; then 
  packages_list+=' doxygen'
elif [ "$BUILD_TYPE" = "coverage" ]; then
  packages_list+=' libqt5sql5-sqlite'
fi

sudo apt-get update
sudo apt-get install -y $packages_list

if [ "$BUILD_TYPE" = "coverage" ]; then 
  gem install lcoveralls
fi
