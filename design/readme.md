This is the folder where you save your schematic and pcb design with their related files. 

LEd dot matix consists of 16 rows and 8 columns. 
74HC595 SiPo shift register is used to drive them. 2 shift registers are daisy chained in series to control the rows and 1 shift register 
controlling columns seperately. They all have same clock. 
MCU is Atmega328P
5 buttons and 1 piezo speaker are connected to the MCU. 
