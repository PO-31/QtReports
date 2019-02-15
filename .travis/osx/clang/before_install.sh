#!/bin/bash

sudo apt-add-repository --yes ppa:beineri/opt-qt551
sudo apt-get update -qq
sudo apt-get -f install clang qt-latest