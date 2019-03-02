#!/bin/bash

echo
echo "Building and passing tests"

cd "$TRAVIS_BUILD_DIR/qtreports-tests"
qmake -spec ${USING_QT_MKSPEC} "CONFIG+=${BUILD_TYPE}" qtreports-tests.pro
mingw32-make -j$(nproc)
if [[ $? -ne 0 ]]; then
	echo
	echo "Building tests program FAILED"
	exit 1
fi

echo
echo "Tests program has been built"

# At this time (02.03.2019) it's impossible to run tests
# due to Git Bash problems with locating libs.
# After a lot of tries the best solution is
# to wait for Travis-CI compatibility with PowerShell.

# OR MOVE Windows building TO AppVeyor
# It supports PowerShell and Qt out of box

# ./qtreports-tests
# if [[ $? -ne 0 ]]; then
	# echo "Some of the tests FAILED"
	# exit 1
# fi
# echo "Tests PASSED"

cd "$TRAVIS_BUILD_DIR"
