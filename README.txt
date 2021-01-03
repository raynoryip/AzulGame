The save format for the files changed to->

For Mosaic.save:

/*the below format shows if there are 3 players in the game,
the save file will be shown like this.*/

3 <-- indicates how many players in this game
.
..
...
....
.....
byrul
lbyru
ulbyr
rulby
yrulb
....... 
.
..
...
....
.....
byrul
lbyru
ulbyr
rulby
yrulb
.......
.
..
...
....
.....
byrul
lbyru
ulbyr
rulby
yrulb
.......

For player.save
Human Player = 1
Bot Player = 2

0
Ray
3
1 <-- indicates human player
Day
3
1
BOT1
2
2 <-- indicates bot player

For Factory.save

Slightly modified for N players. 2 <= N  <= 4

e.g. 3 players game

2 <-- indicates num of centre Factory
7 <-- indicates num of normal factories
F
F
RYYU
BBRB
LLBL
UUUU
BRYY
YYUU
UBRY


