# Screen Lock
Our propresenter opperators kept loosing their mouse on the secondary display, so we made this to keep that from happening. It watches your mouse movements and when it sees a negative y coordinate (mouse is on the second screen) it bumps the mouse back onto the primary screen.

### Requirements
*To Run*  
- OSX (We're on 10.12, but It shouldn't matter as long as you build it on the same version you plan to run it on)  
- Your second monitor must be in this location:  
![Monitor Setup](https://raw.githubusercontent.com/BarefootChurch/ScreenLock/master/monitor-setup.jpg)  

*To Build*  
- XCode command line tools must be installed (`xcode-select --install`)  
- Link with the ApplicationServices framework (`gcc -Wall -o ScreenLock ScreenLock.c -framework ApplicationServices`)  
