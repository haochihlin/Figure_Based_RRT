# Figure_Based_RRT

[Abstract]   
The purpose of this program is to create a simple code for implementing the RRT (Rapidly exploring random tree) algorithm.
You can watch the demo video on the following link: https://www.youtube.com/watch?v=AFrtssAUE4E    
One of the most important feature of this program is that the user could load any format of figure as the map,    
saving the trouble on setting obstacles in other RRT programs.    
For the concept of RRT algorithm, please see the [wiki](https://en.wikipedia.org/wiki/Rapidly_exploring_random_tree) or [ LaValle, Steven M's paper] (http://msl.cs.uiuc.edu/~lavalle/papers/Lav98c.pdf)      
Author: LIN, Hao-Chih (Jim)     
Date: 2016/05/22       
Notices: Since I took this task as a one-day challenge, there are still existing some bugs.       
License: LGPL 3.0    
    
[How to compile]   
== Support Platform ==    
Windows and Linux   

== Required Environment ==   
Qt-Creator, OpenCV
    
== Steps ==      
1. Modify the path of OpenCV libs in "RRT_figurebase.pro" file     
2. In Qt-Creator, execute "Compile & Run"    
     
[How to use]    
1. Create/Draw a custom map by any figure-editor. (e.g. windowa built-in "Paint")     
2. Execute the program and load your map.      
3. Left mouse click to set the start point(red), Right mouse click to set the goal area(green).    
4. Press the "Start" button then check the result.    

[Contact info]   
If you have any question or suggestion, please send a mail to following address:  
f44006076@gmail.com  
