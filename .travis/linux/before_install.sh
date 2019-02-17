#!/bin/bash

if [ "${CC}" = "clang" ]; then
	sudo add-apt-repository ppa:beineri/opt-qt-5.12.0-xenial
fi

sudo apt-get update
