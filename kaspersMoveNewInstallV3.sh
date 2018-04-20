#!/bin/bash

cd /home/ur/Desktop/Projekt/2_semesterprojekt/DreamTeam.GriberStyringV3/target

rm -f GriberStyringV3-2.0-SNAPSHOT.urcap
rm -f GriberStyringV3-2.0-SNAPSHOT.jar

cd /home/ur/Desktop/Projekt/2_semesterprojekt/DreamTeam.GriberStyringV3
mvn install

cd /home/ur/Desktop/Projekt/2_semesterprojekt/DreamTeam.GriberStyringV3/target

cp -rf GriberStyringV3-2.0-SNAPSHOT.urcap /home/ur/ursim-current/programs.UR5
