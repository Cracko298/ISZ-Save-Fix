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
- Fully Text-Base with no encoding/decoding. And singular byte manipulation.
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
- If you want it too be Encrypted/Decrypted you need to use a Custom Script and .dll to Encrypt/Decrypt. Otherwise, set the `ENCODED` Attribute to an Int `0`.
- This plugin is 100% readable and able to be modified when not Encrypted.
- Allows modification of multiple bytes of your choice `1-4 bytes/bytearray`, bigger Numbers such as `9999` will be a `2-Bytearray` instead of Singular Byte.
- `e = "everything"` Everything on that line is the same as the Value that Follows it. **Example: You want all the values on that line to be a Int Value of `9999`, you would Use: `a9999`.**
- `s = "singular"` A Singular Value that only works for one byte, **Example: You want to GOTO both the bytes: `0x283, 0x222`, you'd Use: `s283, s222`, to change BOTH of there values.**
- `a = "after byte"` An operator for everything (including the byte) afterward to be the same Value. **Example: `s223, s9999, a100`, which inbcludes all bytes (including the 3rd) to be an Int Value of `100`.**
```
ENCODED = 0
BUFFER = 4
BYTEARRAY_SIZE = 4
CREATOR = Cracko298
GOTO = s32, s36, s40, s44
CRASH_RANGE_MIN = e0
CRASH_RANGE_MAX = s100, s102, a104
CHANGE_VALUE = e9999
NOTE = Changes All Stats to 9999.
```
## *.GBplg Plugin Example:
- *.GBplg Support! A binary plugin format that makes it very space efficient, it has the same issue as .Zplg However, only allowing Modification of a Singlular Byte.
- Doesn't support notes, only Creator/Developer Name.
```
43 72 61 63 6B 6F 32 39 38 00 00 00 00 20 00 00 00 64 00 0F 27
^Name                                  ^Byte ^     ^     ^CHANGE_VALUE
                                             ^     ^
                                             ^CRASH_RANGE_MIN
                                                   ^CRASH_RANGE_MAX
```


# How to use?
Place the exported save slots (Data0, Data1, Data2) in the same directory as the tool.

New version(v0.3):
![image](https://user-images.githubusercontent.com/97799691/185791100-b0a2da49-0592-4f33-b999-5d1dfa03e0a1.png)

Old version(v0.3):
![image](https://user-images.githubusercontent.com/97799691/185761793-6e2571c3-094d-40b0-9c16-77292ab3e66a.png)
