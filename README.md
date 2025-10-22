**first-to-15 (C) — “it compiles on my machine™” edition**:

A very old learning project where Tic-Tac-Toe meets the Lo Shu magic square.

You pick a board cell (A–I), then pick a unique number 1–9. Make any straight line that sums to 15 and you win. That’s it. Old-school console vibes, globals everywhere, and it’s honestly kind of fun.

**Why this exists:**
I wanted to learn C. So I did the very C thing: print a banner, system("cls") the screen, sprinkle globals like parmesan, and make a game. If you came here looking for modern architecture… you’ll find character.
TL;DR — How to play 

**On your turn:**
Choose a position (A–I) that isn’t taken.
Choose a number (1–9) that hasn’t been used by anyone.
First player to make a horizontal / vertical / diagonal line whose numbers sum to 15 wins.
If all nine numbers are used and no 15, it’s a draw.

**Modes:**
1 = Player vs Player\n
2 = Player vs Computer (bot picks random valid moves)\n
3 = Exit\n

Bot is… random

No strategy. Fun to beat, though.
