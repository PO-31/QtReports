#!/bin/bash

# Because of the problem with Qt described in "before_install.sh",
# we use these packages. Not all dependencies are listed, so be caution.
# packages_list='qt512-meta-minimal qt512tools libgles2-mesa-dev libgl1-mesa-dev'

# if [ "$BUILD_TYPE" = "doxygen" ]; then 
	# packages_list+=' doxygen'
# fi
# sudo apt-get install -y $packages_list


# if [ "$BUILD_TYPE" = "coverage" ]; then 
	# gem install lcoveralls
# fi

# source /opt/qt512/bin/qt512-env.sh

packages_list+='libgles2-mesa-dev libgl1-mesa-dev'
packages_list+=' fontconfig libc6 libcups2 libdbus-1-3 libdrm2 libfontconfig1 libfreetype6 libgcc1 libgl1-mesa-glx libglib2.0-0 libgtk-3-0 libice6 libicu55 libmtdev1 libpango-1.0-0 libpng12-0 libsm6 libstdc++6 libudev1 libx11-6 libx11-xcb1 libxcb-glx0 libxcb-icccm4 libxcb-image0 libxcb-keysyms1 libxcb-randr0 libxcb-render-util0 libxcb-render0 libxcb-shape0 libxcb-shm0 libxcb-sync1 libxcb-xfixes0 libxcb-xinerama0 libxcb-xkb1 libxcb1 libxkbcommon-x11-0 libxkbcommon0 libxrender1 zlib1g'

if [ "$BUILD_TYPE" = "doxygen" ]; then
	packages_list+=' doxygen'
fi

sudo apt-get install -y $packages_list

if [ "$BUILD_TYPE" = "coverage" ]; then 
	gem install lcoveralls
	cd "$HOME/lcov/"
	sudo make install
	if [[ $? -ne 0 ]]; then
		exit 1
	fi
	cd "$TRAVIS_BUILD_DIR"
fi

sudo tar -xf "$HOME/packages/qtbase-build.tar.gz" -C "/opt/"
source /opt/qtbase-build/bin/qtbase-env.sh


if [ "$CC" = "gcc" ]; then
	export USING_QT_MKSPEC="linux-g++-64"
elif [ "$CC" = "clang" ]; then
	export USING_QT_MKSPEC="linux-clang"
elif [ "$BUILD_TYPE" != "None" ]; then
	echo "Detected using unsupported compiler"
	exit 1
fi
