Kleiner Sketch um mit einem Arduino und einem 433MHz Empfansmodul (z.B. MX-RM-5V) eine Wetterstation mit infactory Protokoll zu empfangen.
Das Modul muss an einem interruptfähigen Port am Arduino angeschlossen werden, z.B. bei Uno oder Nano an D2 oder D3.
Getestet wurde der Script an einem Aussensensor einer nor-tec Wetterstationvon Schou Company A/S. Der Sensor überträgt Temperatur,
Luftfeuchte, die ID, den Kanal und den Akkuzustand. Benötigt wird das das Library RF433recv das über die Bbliothekenverwaltung in der
Arduino IDE hinzugefügt werden kann.
