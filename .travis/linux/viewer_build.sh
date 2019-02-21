cd "$TRAVIS_BUILD_DIR/qtreports-viewer"
qmake qtreports-viewer.pro
make -j$(nproc)
if [[ $? -ne 0 ]]; then
	exit 1
fi

cd "$TRAVIS_BUILD_DIR"
