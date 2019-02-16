# ATTENTION
# Если ты не drclaws и ошибка при push Travis'ом
# ПОМЕНЯЙ GITHUB_API_KEY в Travis на свой,
# так как возможно, что я, drclaws, удалю его у себя

# Exit if any command returns fail (non-zero)

# Auto documentation generation
if [ "$BUILD_TYPE" = "doxygen" ]; then
	cd "$TRAVIS_BUILD_DIR"
	cd ..
	# Clone repository and update doc
	git clone https://github.com/PO-31/PO-31.github.io 
	cd PO-31.github.io
	rm -d -f -r html
	doxygen Doxyfile
	
	# Push changes to remote repository
	git config --global user.name "travis"
	git config --global user.email "travis@travis.org"
	git add -A

	git commit -am "Update doc from Travis CI"
	git config --global push.default simple
	
	git push -f -q https://drclaws:$GITHUB_API_KEY@github.com/PO-31/PO-31.github.io > /dev/null
	exit
fi

cd "$TRAVIS_BUILD_DIR/qtreports"
qmake -spec ${USING_QT_MKSPEC} "CONFIG+=${BUILD_TYPE}" qtreports.pro
make -j $(nproc)
sudo make install

if [ "$BUILD_TYPE" = "coverage" ]; then	
	cd "$TRAVIS_BUILD_DIR/qtreports-tests"
	qmake -spec ${USING_QT_MKSPEC} "CONFIG+=${BUILD_TYPE}" qtreports-tests.pro
	make -j $(nproc)
	./qtreports-tests

	cd "$TRAVIS_BUILD_DIR"
	git clone https://github.com/linux-test-project/lcov
	cd lcov
	sudo make install
	cd ..
	lcov --version
	lcov --capture --directory "$TRAVIS_BUILD_DIR/qtreports" --output-file coverage.info
	lcov --remove coverage.info --output-file coverage.info "*moc_*.cpp"
	lcov --remove coverage.info --output-file coverage.info "*/usr/*"
	cd "$TRAVIS_BUILD_DIR"
	git clone  -b gh-pages https://github.com/PO-31/QtReports ../gh_pages
	rm -r ../gh_pages/${TRAVIS_BRANCH}
	genhtml coverage.info --output-directory ../gh_pages/${TRAVIS_BRANCH}
	cd ../gh_pages
	git config --global user.name "travis"
	git config --global user.email "travis@travis.org"
	git add -A
	git commit -a -m "Update coverage from Travis CI"
	git config --global push.default simple
    git push -f -q https://drclaws:$GITHUB_API_KEY@github.com/PO-31/QtReports HEAD:gh-pages > /dev/null
fi
