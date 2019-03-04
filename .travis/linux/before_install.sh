#!/bin/bash

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