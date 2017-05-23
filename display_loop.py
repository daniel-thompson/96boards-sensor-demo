import serial, pyupm_i2clcd

ard = serial.Serial('/dev/tty96B0', 9600)
lcd = pyupm_i2clcd.Jhd1313m1(0, 0x3e, 0x62)

def showTemp(humid, temp, colour):
	lcd.clear()
	lcd.setCursor(0, 0)
        lcd.write("H: " +str(humid) + "%")
	lcd.setCursor(1, 0)
	lcd.write("T: " + str(temp) + "C")
	lcd.setColor(colour[0], colour[1], colour[2])

if __name__ == '__main__':
	try:
		humidity = 0
		temp = 0
		colour = [255, 180, 180]
		button = 0
		while True:
			old = (humidity, temp, colour)
			msg = ard.readline().strip()
                        tag = msg[0]
                        val = msg[1:]

                        if tag == 'H':
				humidity = int(float(val))
				print("\033c")
				if button:
					invert = [ 255-x for x in colour ]
					showTemp(humidity, temp, invert)
				else:
					showTemp(humidity, temp, colour)
                        elif tag == 'T':
				temp = float(val)
                        elif tag == 'L':
				light = int(val)
				colour[1] = light / 3
                        elif tag == 'R':
				try:
					rotary = int(val)
					colour[0] = rotary / 4
				except:
					pass
                        elif tag == 'C':
				touch = int(val)
				colour[2] = 180 * touch
                        elif tag == 'B':
				button = int(val)

			print(msg)
                        
	except KeyboardInterrupt:
		lcd.setColor(0, 0, 0)
		lcd.clear()
		
			
