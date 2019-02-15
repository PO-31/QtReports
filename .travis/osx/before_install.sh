#!/bin/bash

sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
sudo add-apt-repository --yes ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq
sudo -H pip install --upgrade pip
sudo -H pip install --user cpp-coveralls
sudo pip install --upgrade pip
sudo pip install --user cpp-coveralls
