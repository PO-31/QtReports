#!/bin/bash

cd "$HOME"
git clone -b $TRAVIS_OS_NAME https://github.com/PO-31/packages/ "$HOME/packages/"

cd "$TRAVIS_BUILD_DIR"