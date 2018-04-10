#!/bin/bash

cd /home/ur/Desktop/Projekt/2_semesterprojekt/DreamTeam.GriberStyringV2
mvn install

cd /home/ur/Desktop/Projekt/2_semesterprojekt/DreamTeam.GriberStyringV2/target

cp -Ru GriberStyringV2-1.0-SNAPSHOT.urcap /home/ur/ursim-current/programs.UR5