#!/bin/bash

# Requirements QtBase package
# Has been gotten from https://launchpad.net/~beineri repo
packages_list+='libgles2-mesa-dev libgl1-mesa-dev fontconfig libc6 libcups2 libdbus-1-3 libdrm2 libfontconfig1 libfreetype6 libgcc1 libgl1-mesa-glx libglib2.0-0 libgtk-3-0 libice6 libicu55 libmtdev1 libpango-1.0-0 libpng12-0 libsm6 libstdc++6 libudev1 libx11-6 libx11-xcb1 libxcb-glx0 libxcb-icccm4 libxcb-image0 libxcb-keysyms1 libxcb-randr0 libxcb-render-util0 libxcb-render0 libxcb-shape0 libxcb-shm0 libxcb-sync1 libxcb-xfixes0 libxcb-xinerama0 libxcb-xkb1 libxcb1 libxkbcommon-x11-0 libxkbcommon0 libxrender1 zlib1g'

# Packages for doxygen run
if [ "$BUILD_TYPE" = "doxygen" ]; then
	packages_list+=' doxygen graphviz'
fi

sudo apt-get install -y $packages_list

# Builds and installs lcov and other for coverage run
if [ "$BUILD_TYPE" = "coverage" ]; then
	# gem install lcoveralls FOR COVERALLS.IO
	cd "$HOME/lcov/"
	sudo make install
	if [[ $? -ne 0 ]]; then
		exit 1
	fi
	cd "$TRAVIS_BUILD_DIR"
fi

# Extract self-made QtBase package and enabled his environment
sudo tar -xf "$HOME/packages/qtbase-build.tar.gz" -C "/opt/"
source /opt/qtbase-build/bin/qtbase-env.sh

# Sets using compiler for qmake
if [ "$CC" = "gcc" ]; then
	export USING_QT_MKSPEC="linux-g++-64"
elif [ "$CC" = "clang" ]; then
	export USING_QT_MKSPEC="linux-clang"
fi
