#!/bin/bash

cd /home/ur/Desktop/Projekt/2_semesterprojekt/DreamTeam.GriberStyringV2/target

rm -f GriberStyringV2-2.1-SNAPSHOT.urcap
rm -f GriberStyringV2-2.1-SNAPSHOT.jar

cd /home/ur/Desktop/Projekt/2_semesterprojekt/DreamTeam.GriberStyringV2
mvn install

cd /home/ur/Desktop/Projekt/2_semesterprojekt/DreamTeam.GriberStyringV2/target

cp -rf GriberStyringV2-2.3-SNAPSHOT.urcap /home/ur/ursim-current/programs.UR5
