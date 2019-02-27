#!/bin/bash

# Because Xenial's repo doesn't have relatively new version
# of Qt5 (since july 2015!) we have to use this repo.

sudo add-apt-repository -y ppa:beineri/opt-qt-5.12.0-xenial

sudo apt-get update
