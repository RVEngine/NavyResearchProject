Quantico_GetData Component
=============
$Navy Research Project
========

The objective of the project is to develop an artificial agent that is capable of learning novel strategies in previously unseen environments. 
The developed agent will be able to succesfully avoid an ambush and either counter attack or run towards the town. This project will allow you to get important information on the units,
such as health, ammo, position etc. The bluforce units will detect enemy fire and respond accordingly. 
In this project we insert waypoints into a database table using a python script. It is then read on the C++ side and inserted into VBS3.



Features
--------

- Create Waypoint
- Retrieve Unit Info
- Detect enemy fire
- Log enemy fire

Installation
------------
Prerequisites:
-VBS3
-Gears Studio
-Visual Studio
-VBS3 Sim SDK
-psql
-python editor
-cmd
Steps:
-Open Gears Studio
	-Click From Disk and load your project from where you have it stored
	-Right click your component and click code editor.
-Open cmd and go to where your python script is stored 
-Start the scenerio by launching the vbs3 debugger in visual studio
	-F12 to open debug menu, start ambush mission
-Start scenerio and start python script simultaneously.
	
Contribute
----------

- Issue Tracker: https://github.com/supermo55/NavyResearchProject/issues
- Source Code: https://github.com/supermo55/NavyResearchProject
