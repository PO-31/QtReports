#!/bin/bash

# This repo contains self-made lite builds of QtBase
# Also you can get lite builds of Qt from https://launchpad.net/~beineri repo
git clone -b linux https://github.com/PO-31/packages/ "$HOME/packages/" --single-branch --depth 1

if [[ $? -ne 0 ]]; then
	exit 1
fi

# Required for collecting coverage info
if [ "$BUILD_TYPE" = "coverage" ]; then 
	git clone https://github.com/linux-test-project/lcov "$HOME/lcov/"
	if [[ $? -ne 0 ]]; then
		exit 1
	fi
fi

sudo apt-get update