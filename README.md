Simple Pachislo hopper coin counter

Robert DiNapoli  - 2025 -  rjgee@hotmail.com



Preface:

I needed to count several thousand quarters in stacks of 40 for rolling in coin sleeves. I know coin counters are cheap these days. You can pick up a Vevor or comparible cheap unit for around $60. And they will even sort the coins for you. However, I couldn't really justify buying a coin counter when I'm probably only going to need it 1 time in my life.

Enter a hopper from a Japanese Pachislo machine,  an Arduino, and about 2 hours time, and I have a one time use coin counter. It's quick and dirty. But works.


Build list:

Pachislo Hopper – I'm using one from a Sammy unit (Juki JSH777). Most hoppers will be similar, but you'll need to figure out the wiring on your own.
External power supply to power the hopper. Anything between 7vdc and 12vdc seems to work well. 
Arduino Relay unit
Switch to trigger count start
Arduino – I'm using a mega, but almost any Arduino should suffice as we don't need a lot of inputs / outputs.

Before uploading to your Arduino, on line 27, adjust coinsToCount to whatever number you want the unit to spit out before stopping.


Press the switch, and the hopper motor will activate. It will stop when it has reached the proper number of coins, or after 3 seconds of not detecting a coin ejected (hopper empty?)

