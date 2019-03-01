#!/bin/bash

cd "$HOME/packages/.git"
if [[ $? -ne 0 ]]; then
	cd "$HOME"
	rm -R -f "$HOME/packages/*"
	git clone https://github.com/PO-31/packages/ "$HOME/packages/"
else
	cd "$HOME/packages"
	git pull
fi

cd "$TRAVIS_BUILD_DIR"