# v62 Client HD

This DLL modifies the memory of v62 MapleStory clients to change the experience of the game.

### Libraries
- [Detours](https://github.com/microsoft/Detours) - Intercepts windows api and in-game function calls
- [discord-rpc](https://github.com/discord/discord-rpc) - For discord rich presence interaction

### How To Use
  
1. Compile .dll
2. Inject .dll in localhost.exe (http://https://www.cgsoftlabs.ro/studpe.html)
3. Run your client!  

### Configure
The default `config.ini` file isn't included because it's optional.  
The default resolution is 1024x768 if no config is present.  

Make a file called `config.ini` in your game folder and the program will try to use it.  
All settings are optional and can be ommitted (in case you don't want players knowing/using it).  
```
[general]
width=1280
height=720
debug=false
```

- `debug`=`true/false` Enables or disables the output console

## Developing

**This code can only be compiled on \[Release\] \[x86\] configuration**

## Thanks
MapleEzorsia
Lily
