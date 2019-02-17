#!/bin/bash

echo "\nBuild and run tests"
cd "$TRAVIS_BUILD_DIR/qtreports-tests"
qmake -spec ${USING_QT_MKSPEC} "CONFIG+=${BUILD_TYPE}" qtreports-tests.pro
make -j $(nproc)
if [[ $? -ne 0 ]]; then
	exit 1
fi
./qtreports-tests

echo "\nCollect coverage data"
cd "$TRAVIS_BUILD_DIR"
git clone https://github.com/linux-test-project/lcov
cd lcov
sudo make install
cd ..
lcov --version
lcov --capture --directory "$TRAVIS_BUILD_DIR/qtreports" --output-file coverage.info
lcov --remove coverage.info --output-file coverage.info "*moc_*.cpp"
lcov --remove coverage.info --output-file coverage.info "*/usr/*"

echo "\nGenerating html view of coverage data"
cd "$TRAVIS_BUILD_DIR"
git clone  -b gh-pages https://github.com/PO-31/QtReports ../gh_pages
rm -r ../gh_pages/${TRAVIS_BRANCH}
genhtml coverage.info --output-directory ../gh_pages/${TRAVIS_BRANCH}

# echo "\nGenerating badge"
# coverage_percent=$(lcov --summary coverage.info)
# ./../gh_pages/covbadger/covbadger-linux coverage_percent >> ../gh_pages/${TRAVIS_BRANCH}/badge.svg

echo "\nPushing to gh-pages"
cd ../gh_pages
git config --global user.name "travis"
git config --global user.email "travis@travis.org"
git add -A
git commit -a -m "Update coverage from Travis CI"
git config --global push.default simple
git push -f -q https://drclaws:$GITHUB_API_KEY@github.com/PO-31/QtReports HEAD:gh-pages > /dev/null

cd "$TRAVIS_BUILD_DIR"
