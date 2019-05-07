#!/bin/bash

echo "Version: $QTREPORTS_VERSION"

echo
echo "Clone repository and update doc"
cd ..
git clone https://github.com/PO-31/PO-31.github.io 
cd PO-31.github.io
export OUT_LANG='ENGLISH' && rm -d -f -r en && cd ru && doxygen ../Doxyfile
cd ..
export OUT_LANG='RUSSIAN' && rm -d -f -r ru && cd ru && doxygen ../Doxyfile
	
echo
echo "Push changes to remote repository"
git config --global user.name "travis"
git config --global user.email "travis@travis.org"
git add -A

git commit -am "Update doc from Travis CI"
git config --global push.default simple

# The secret key set in Travis CI environment settings
git push -f -q https://faaswdepkhab:$GITHUB_API_KEY@github.com/PO-31/PO-31.github.io > /dev/null
exit
