# rs485tottlbasedcontrolwithprotocol
serial controller send the data through docklight or hercules or realterm software.

isme mai docklight software me hex file ko select karunga or command send karunga AA 00 AC to turn off the led and AA 01 AC to turn on the led.

jo mera jitna bhi code hai rs485receiver, rs485sender, rs485tottltesting in sabme maine arduino cable ka use kiya hai. isme rs485tottl module ka koi role nahi hai.mai same arduino ke serial monitor se data nahi send karke mai same com port docklight ya hercules me select kar leta tha aur waha se send karta tha. jo ki sahi chiz nahi hai. isme actually arduino cable ka use ho rha hai usb ke taur par. lekin isme rs485tottl module ka koi role nahi hai.

lekin jo mera rs485tottlcontrolled wala file hai. isme maine simply arduino ke cable ko hata diya hai puri tarah se aur rs485tottl module ka use karke docklight aur realterm aur hercules se serially data send kar rha hu. aur led ko control kar rha hu.now mai python me code likhkar rs485tousb com port select karke data send karunga aur check krunga ki mera led control ho pata hai ya nahi


esp32withrs485tottlcontrolled.ino file jo hai ye code humne esp32 me banaya hai rs485tottl module ke sath. isme hum simply esp32 ko rs485tottl module ke sath connect karte hai.  rs485tottl  VCC- esp32 VCC, rs485tottl gnd to esp32 gnd, rs485tottl RX pin with esp32 TX pin and rs485tottl TX pin with esp32 RX pin. Serial1.begin(9600, SERIAL_8N1, 1, 3);
