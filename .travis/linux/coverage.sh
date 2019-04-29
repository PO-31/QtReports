#!/bin/bash

echo
echo "Collect coverage data"

# Collects coverage data after testing program run
lcov --version
lcov --capture --directory "$TRAVIS_BUILD_DIR/qtreports" --output-file coverage.info
# Discards temporary and unrelated to the project files
lcov --remove coverage.info --output-file coverage.info "*moc_*.cpp"
lcov --remove coverage.info --output-file coverage.info "*/usr/*"
lcov --remove coverage.info --output-file coverage.info "/opt/qt*"

echo
echo "Generating html view of coverage data"
cd "$TRAVIS_BUILD_DIR"
git clone -b gh-pages https://github.com/PO-31/QtReports ../gh_pages
rm -r ../gh_pages/${TRAVIS_BRANCH}
genhtml coverage.info --output-directory ../gh_pages/${TRAVIS_BRANCH}

echo
echo "Generating badge"
# Gets only per cent value from coverage summary info
coverage_percent=$(lcov --summary coverage.info | egrep -m 1 -o '[0-9]+\.[0-9]')
# Creates badge of coverage status for main page of repo
./../gh_pages/covbadger/covbadger-linux $coverage_percent >> ../gh_pages/${TRAVIS_BRANCH}/badge.svg

echo
echo "Pushing to gh-pages"
cd ../gh_pages
git config --global user.name "travis"
git config --global user.email "travis@travis.org"
git add -A
git commit -a -m "Update coverage from Travis CI"
git config --global push.default simple
git push -f -q https://faaswdepkhab:$GITHUB_API_KEY@github.com/PO-31/QtReports HEAD:gh-pages > /dev/null

cd "$TRAVIS_BUILD_DIR"
