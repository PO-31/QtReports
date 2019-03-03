#!/bin/bash

# Because Xenial's repo doesn't have relatively new version
# of Qt5 (since july 2015!) we have to use this repo.

# sudo add-apt-repository -y ppa:beineri/opt-qt-5.12.0-xenial

# sudo apt-get update


git clone -b linux https://github.com/PO-31/packages/ "$HOME/packages/" --single-branch --depth 1

if [[ $? -ne 0 ]]; then
	exit 1
fi

if [ "$BUILD_TYPE" = "coverage" ]; then 
	git clone https://github.com/linux-test-project/lcov "$HOME/lcov/"
	if [[ $? -ne 0 ]]; then
		exit 1
	fi
fi

sudo apt-get update