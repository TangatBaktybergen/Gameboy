The idea is to develop retro electronic game console. As an example , we are going to implement " Tetris " game in this project. 

The basic idea of Tetris is to stack as many blocks in line as possible to get more game points. Player has 4 buttons, display and buzzer as user interface. Player can move the falling block to right and to left , rotate and drop the block faster. The player display is made of two 8x8 Matrix LED. The buzzer will create sound effect at the start and the end of the game. 

The brain of the project is ATTiny85 microcontroller where rules of game will be written. Shift register as SN74HC595N is used to expand the output/input pins of ATTiny85 because we have 4 buttons and 2 matrices to connect.The matrices will be connected through MAX7219 driver. ATTiny85 has 512 bytes of memory which is enough for the simple game as Tetris or Snake. 
