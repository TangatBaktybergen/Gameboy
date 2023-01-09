>>>
**Project-Template**

Please use this template for your practical electronics project. (feel free to delete this section) 

You can find a quick guide in the following [cheat sheet](https://www.markdownguide.org/cheat-sheet/) or specific [gitlab style](https://docs.gitlab.com/ee/user/markdown.html) here

>>>


----

# Electronic game console

by: *Tangat Baktybergen and Towfiqur Rahman Khan*


**Faculty of Technology and Bionics**

***Rhine-Waal University of Applied Sciences***

Date: 9 January 2023

----

## Abstract

The goal of our project is to create a simple handheld gaming device (Gameboy) using dot matrix as a display which can be operated with some control buttons.

The components are used to create this device:

- 2 8x8 dot matrix displays
- 3 shift registers (SN74HC595N)
- 1 ATMega328p microcontroller unit
- 5 push buttons
- 1 active buzzer

Among these 5 action buttons, 4 buttons used for movements (Up, Down, Right, Left) and an event button (Start, Reset). The buzzer produces sound during the game.


## Table of Contents

[[_TOC_]]

## 1 Introduction

Game Boy is an 8-bit handheld gaming console. The console features  dot-matrix screen with adjustable contrast, five game control buttons (four directional buttons and "START" / "SELECT"), a single speaker and uses microcontroller as physical media for games. The color scheme is made from two tones. Due to the complexity of controling the matrix display , a simple "Simon Says" game is implemented for a demonstration purpose.[1]

### 1.1	Background

The Game Boy game console developed and manufactured by Nintendo. It was first released in Japan on April 21, 1989, in North America later the same year, and in Europe in late 1990. It was designed by the same team that developed the Game & Watch series of handheld electronic games and several Nintendo Entertainment System (NES) games: Satoru Okada, Gunpei Yokoi, and Nintendo Research & Development 1.[1]

The Game Boy was designed by Nintendo's chief engineer Gunpei Yokoi and its Nintendo R&D1 team. Following the popularity of the Nintendo Entertainment System, he held a meeting with Nintendo president Hiroshi Yamauchi, saying that he could do a handheld system with interchangeable games. The original internal code name for the Game Boy is Dot Matrix Game, referring to its dot-matrix display in contrast to the preceding Game & Watch series (which Yokoi had created in 1980) that has segmented LCDs pre-printed with an overlay, limiting each model to only play one game. The initials DMG came to be featured on the final product's model number: "DMG-01". Satoru Okada and Yokoi led the development of the console, which led to disagreements. Yokoi felt that the console could be small, light, durable and successful and have a recognizable library of games. Shigesato Itoi visited Nintendo and conceived the name "Game Boy" for the console Yokoi was designing. The internal reaction to the Game Boy at Nintendo was initially very poor, earning it the derogatory nickname "DameGame" from Nintendo employees, in which dame (だめ) means "hopeless" or "useless" (dame originating as a term used in the game Go, meaning "meaningless territory").Henk Rogers brought the game Tetris to Nintendo of America and convinced its president Minoru Arakawa to port it for the new system so it can reach a wider audience. Arakawa agreed and as a result, the game was ultimately bundled with the Game Boy and the system was released in Japan in April 1989, North America in July, and in Europe in September the following year. Nintendo had spent $10 million on marketing the Game Boy.[1]


## 2	Literature review

On March 20, 1995, Nintendo released several special edition Game Boy models with colored cases, advertising them in the "Play It Loud!" campaign known in Japan as Game Boy Bros. Play It Loud! units were manufactured in red, green, black, yellow, white, blue, and clear (transparent), or sometimes called X-Ray in the UK. Most common are the yellow, red, clear and black. Green is fairly scarce but blue and white are the rarest. Blue was a Europe and Japan-only release, white was a Japanese majority release with UK Toys R Us stores also getting it as an exclusive edition to them. The white remains the rarest of all the Play it Loud colors. A rare, limited edition Manchester United Game Boy is red, with the logos of the team emblazoned on it. It was released simultaneously with the Play it Loud! handhelds in the United Kingdom. The Play It Loud's screens also have a darker border than the normal Game Boy.[1]

On July 21, 1996, Nintendo released the Game Boy Pocket for US$69.99: a smaller, lighter unit that required fewer batteries. It has space for two AAA batteries, which provide approximately 10 hours of gameplay. The unit is also fitted with a 3 volt, 2.35 mm x 0.75 mm DC jack which can be used to power the system. The Pocket has a smaller link port, which requires an adapter to link with the older Game Boy. The port design is used on all subsequent Game Boy models, excluding the Game Boy Micro. The screen was changed to a true black-and-white display, rather than the "pea soup" monochromatic display of the original Game Boy. Also, the Game Boy Pocket (GBP) has a larger screen than the Game Boy Color (GBC) that later superseded it. The GBP's screen has a 65 mm (2.56 in) diagonal, 48.5 mm (1.91 in) width, and 43.5 mm (1.71 in) height, compared to a 59 mm (2.32 in) diagonal for the GBC. Although like its predecessor, the Game Boy Pocket has no backlight to allow play in a darkened area, it did notably improve visibility and pixel response-time (mostly eliminating ghosting). The first version did not have a power LED. This was soon added due to public demand, along with new Game Boy Pocket units of different colors (released on April 28, 1997), some of them new to the Game Boy line. There were several limited-edition Game Boy Pockets, including a gold-metal model exclusive to Japan. The Game Boy Pocket was not a new software platform and played the same software as the original Game Boy model.[1]

A clear 'skeleton' Famitsu Model-F edition appeared in 1997, which had only 5,000 units released, and a clear yellow edition.[1]

The Game Boy Light was released on April 14, 1998, and only available in Japan. Like the Game Boy Pocket, the system was priced at ¥6,800. The Game Boy Light is slightly bigger than the Game Boy Pocket and features an electroluminescent backlight for low-light conditions. It uses two AA batteries, which give it approximately 12 gameplay hours with the light on and 20 with it off. It was available in two standard colors: gold and silver. It also received numerous special editions, including a clear 'skeleton' Famitsu 500 edition (Model-F02) with white buttons. This edition was also limited to 5000 units, like the first Model-F. Astro Boy edition with a clear case and a picture of Astro Boy on it, an Osamu Tezuka World edition with a clear red case and a picture of his characters and a solid yellow Pokémon Center Tokyo version.[1]

## 3	Methodology

The display consists of 2 cathode-row 8x8 matrix which make 16 columns and 8 rows.It is controlled with shift registers(Serial in Parallel out).One of the shift registers is used to send row data and the other two are in series for columns.Each shift register has 8 output pins. So, each shift register take only 8 row or 8 column control.

Rows are combined into one shift register while columns have two separate shift registers in series. However,when all LEDs are lit , 8 LEDs simultaneously draw current from each output pin of the shift register.The shift register's output current is 35mA and 5mA for each output pin which is not enough.Consequently, 8 row NPN transistor were added to amplify the current at the output and reduce shift register's work load. 

As mentioned before there are 5 buttons for control purpose. Buttons are connected to ground. Resistors were not used to save some space and they are pulled internally using programming.

The buzzer is simple tone generator as output device.

The microcontroller ATMega328p is implemented as in commonly used Arduino device. It has 16 MHz external clock, powered by 3 x AAA batteries which runs at 4.5 V within standards. Additional empty pins are added for furher programming of the MCU(microcontroller unit) without taking it from the pcb. The external connection pins are at RX/TX and MOSI/MISO/SCK/RESET as SPI connection. 

Arduino IDE was chosen as a software development environment because we are using the base microcontroller of Arduino UNO.Arduino IDE supports C/C++ and can flash code to bare microcontrollers which makes it user friendly.

"Simon Says" is a memory game. The matrix display shows random sequence of arrows (up,down,right and left) which the player must remember and repeat using 4 push buttons.

Game code overview:
1. Check if a new game is starting. If it is, generate random number sequence of 0 to 3 that points which arrow and button has to be pressed. Reset the round counter as it is a new game.
2. The number of rounds to play can be set manually. Each round the game will display arrows in a pattern, and then player has limited time to recreate the pattern by pressing corresponding control buttons.
3. The loop is used to display arrow patterns until the player reaches the winning round number or missclick of the button leads to restart of the game.

Creating random pattern of arrows:
```startSequence():
randomSeed(analogRead(A0));
for(int i=0;i<=3;i++){ // there are only 4 buttons in the pattern to choose
buttonSequence[i]=round(random(0,3));} 
```
Checking which button is pressed:
```buttonCheck():
if (digitalRead(button[0])== HIGH) { // if the button pressed return the index of arrow pattern to check
return 0;} else if(digitalRead(button[1])==HIGH) {
return1; 
...
else { return 4;} // 4 doesnot belong to array of pattern and means nothing 
}
```
An example of turning all LEDs on with shift registers:
```turnOnAll():
digitalWrite(latchPin, LOW); // enable latch pin to transfer data to column shift register
shiftOut(dataPin, clockPin, MSBFIRST, 255); // send 255 saying to turn on all LEDs on
digitalWrite(latchPin, HIGH); // disable latch pin stop sending data
digitalWrite(latchPin2, LOW); // enable latch pin to transfer data to row shift register
shiftOut(dataPin2, clockPin2, MSBFIRST, 0); // row is cathode so set to low
digitalWrite(latchPin2, HIGH); // disable latch pin stop sending data

```

Example how to draw a table:

| Left Aligned | Centered | Right Aligned |
| :---         | :---:    | ---:          |
| Cell 1       | Cell 2   | Cell 3        |
| Cell 4       | Cell 5   | Cell 6        |
| OpAmp 741    | 2        | 1.00          |


## 4	Results
Presenting final result of our project:

The front picture of gameboy:
![alt text](resources/bot.jpeg "Front view")


The bottom picture of gameboy:
![alt text](resources/front.jpeg "Bottom view")

## 5	Discussion

The project is successful.Matrix display works perfectly and games are also functionning as desired. All components are connected correctly and perform as it is supposed to.During the project , we also gained a lot of practical experience in the manufacturing of the PCB.It showed us that the design of the PCB should be precisely checked  and there is always a big room for improvement of both hardware and software to reach user friendly PCB design.


## 6	Concluding Comments

There are a lot of improvements can be done in the future. The main objective is to optimize software to control display. One of the ideas is to create a shift register library that can easily shift data to display. Another good objective is to implement a game card system using external microcontroller. This will allow player to change between games without programming the main controller every time. Finally, we would like to redesign the PCB to be more user friendly. For example, to put bigger push buttons and move them more to the center.

## 7	References

* [1] https://en.wikipedia.org/wiki/Game_Boy
* [2] 

## 8	Appendices

