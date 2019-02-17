#!/bin/bash

if [ "$CC" = "gcc" ]; then
  export USING_QT_MKSPEC="linux-g++-64"
elif [ "$CC" = "clang" ]; then
  export USING_QT_MKSPEC="linux-clang"
else
  echo "Detected using unsupported compiler"
  exit 1
fi
