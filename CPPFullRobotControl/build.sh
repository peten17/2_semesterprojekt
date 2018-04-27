#!/bin/bash

git pull
g++ main.cpp opcuavariable.cpp open62541.o server.cpp -I. -o FinalServerRun -lwiringPi -lpthread
sudo ./FinalServerRun