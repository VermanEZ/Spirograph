# Spirograph
A program that can draw interesting lines like [Spirograph](https://en.wikipedia.org/wiki/Spirograph), using only C++ language and [SFML library](https://www.sfml-dev.org/)
## Compile
To use this program you need to install [SFML library](https://www.sfml-dev.org/download.php),
then if you're using Visual Studio follow [this tutorial](https://www.youtube.com/watch?v=YfMQyOw1zik) to use this lib and compile the program.
If you're using mingw compiler follow this [link](https://www.sfml-dev.org/tutorials/2.5/start-linux.php), this is the linux installation but you can use it on windows too.
To compile this with mingw:
```console
$ g++ main.cpp Game.cpp -o main.exe -I<sfml-install-path>/include -L<sfml-install-path>/lib -lsfml-graphics -lsfml-window -lsfml-system
```
On windows you'll need to have sfml-graphics-2.dll sfml-window-2.dll sfml-system-2.dll in the program directory, these dlls are located in sfml-install-path/bin
## Controls
|Keys|Description|
|---|---|
|<kdb>Space</kdb>|Show circles|
|<kdb>e</kdb>|Save config|
|<kdb>Esc</kdb>|Exit program|

### Config file template
```
<length_of_arm>,<speed_of_arm>
...
...
```
#### Example
```
30,30
40,40
50,50
60,60
```
