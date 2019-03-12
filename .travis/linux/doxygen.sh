#!/bin/bash

echo "Version: $QTREPORTS_VERSION"

echo
echo "Clone repository and update doc"
cd ..
git clone https://github.com/PO-31/PO-31.github.io 
cd PO-31.github.io
rm -d -f -r html
doxygen Doxyfile
	
echo
echo "Push changes to remote repository"
git config --global user.name "travis"
git config --global user.email "travis@travis.org"
git add -A

git commit -am "Update doc from Travis CI"
git config --global push.default simple
	
git push -f -q https://faaswdepkhab:$GITHUB_API_KEY@github.com/PO-31/PO-31.github.io > /dev/null
exit
