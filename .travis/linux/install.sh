#!/bin/bash

# old stuff for qtreportslib_test

# export DISPLAY=:99.0
# cat /etc/init.d/xvfb
# sh -e /etc/init.d/xvfb start
# sleep 3 # give xvfb some time to start

if [ "$CC" = "gcc" ]; then
  export USING_QT_MKSPEC="linux-g++-64"
elif [ "$CC" = "clang" ]; then
  export USING_QT_MKSPEC="linux-clang"
else
  echo "Detected using unsupported compiler"
  exit 1
fi
