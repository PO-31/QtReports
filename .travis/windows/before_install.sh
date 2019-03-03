#!/bin/bash

git clone -b windows https://github.com/PO-31/packages/ "$HOME/packages/" --single-branch --depth 1

if [[ $? -ne 0 ]]; then
	exit 1
fi
