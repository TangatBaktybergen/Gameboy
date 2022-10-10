Please use this place holder to describe your project. Roughly should be DIN-A4 long. 

The idea is to develop retro electronic game console. As an example , we are going to implement " Tetris " game in this project. 

Electronic components: 

1) ATTiny85
2) 8x8 LED Dot Matrix
3) MAX7219 Matrix Driver
4) SN74HC55N Shift Register
5) Button
6) Buzzer
7) Switch
8) Capacitor
9) Resistor

As a brain of our project "ATTiny85" was chosen because the project does not require a lot of memory space , GPIOs and power.

As an output display , console has 2 combined 8x8 LED Matrices and it is enough to play other games too.

To simplify control and pin connections between matrix and ATTiny85 , the matrix driver MAX7219 is used.

ATTiny85 does not have enough GPIO for the project , so the shift register SN74HC55N is used to expand GPIO of ATTiny85.

4 buttons are used for control of gaming object on the display. Functions of buttons may vary depending on the game. For example, for "Tetris" controls are "Rotate block" , "Drop the block", "Go right" and "Go left".

Buzzer as an audio output.Buzzer makes different sounds showing the start or the end of game.

Switch to turn on/off the console. To save the battery life when its not used.

Capacitors to decrease power supply noise and stabilize. Resistors to control current flow.
