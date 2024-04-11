# Ice-Station-Z-Save-Fix
- An Application for ISZ (Ice Station Z) that Attempts to Fixes your ISZ Data0, Data1, Data2 Corrupted.

## Custom Plugin Formats!
```
Name:         Format:                Extension:
Zombie        Text Plugin Format     *.Zplg  
Ice Station   Text Plugin Format     *.ISplg
Grey Base     Binary Plugin Format   *.GBplg
```

## *.Zplg Plugin Example:
- *.Zplg Support! .Zplg has been revamped completely! Allowing for extremely easy writing of BugFix Plugins.
```
CREATOR = TheRealYunix
GOTO = 32
CRASH_RANGE_MIN = 0
CRASH_RANGE_MAX = 100
CHANGE_VALUE = 9999
NOTE = Changes Health to 9999
```
## *.ISplg Plugin Example:
- *.ISplg Support! A plugin with some security Features to Protect your Work, along with some improvements to the .Zplg Format.
```
BUFFER = 4
CREATOR = Cracko298
GOTO = s32, s36, s40, s44
CRASH_RANGE_MIN = e0
CRASH_RANGE_MAX = s100, s102, a104
CHANGE_VALUE = e9999
NOTE = Changes All Stats to 9999.
```
## *.GBplg Plugin Example:
- *.GBplg Support! A binary plugin format that makes it very space efficient, it has the same issue as .Zplg However, only allowing Modification of a Singlular Byte.

```

```


# How to use?
Place the exported save slots (Data0, Data1, Data2) in the same directory as the tool.

New version(v0.3):
![image](https://user-images.githubusercontent.com/97799691/185791100-b0a2da49-0592-4f33-b999-5d1dfa03e0a1.png)

Old version(v0.3):
![image](https://user-images.githubusercontent.com/97799691/185761793-6e2571c3-094d-40b0-9c16-77292ab3e66a.png)
