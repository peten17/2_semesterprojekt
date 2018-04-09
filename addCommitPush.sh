#!/bin/bash

git add .
git commit -a
git push

cd /home/ur/Desktop/LetsGo/2_semesterprojekt/DreamTeam.GriberStyringV2
mvn install

cp -R target /home/ur/ursim-current/programs.UR5
/home/ur/ursim-current/start-ursim.sh UR5