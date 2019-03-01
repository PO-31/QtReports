#!/bin/bash
echo $PWD
ls "$HOME/packages" -a

if [ -d "$HOME/packages/.git" ]; then
	cd "$HOME/packages"
	git pull
else
	cd "$HOME"
	rm -R -f "$HOME/packages/*"
	git clone https://github.com/PO-31/packages/ "$HOME/packages/"
fi

cd "$TRAVIS_BUILD_DIR"