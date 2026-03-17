import serial, time, os

arduino = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
time.sleep(2) 

btnOn = False

try:
  while True:
      line = arduino.readline().decode('ascii').strip()

      if line:
          try:
              x, y, btn = line.split(':')
              x = int(x) / 2
              y = -int(y) / 2
              btn = int(btn)

              if x != 0 or y != 0:
                os.system(f"ydotool mousemove -x {x} -y {y}")

              if btn == 0:
                if not btnOn:
                  os.system("ydotool click 0xC0")
                btnOn = True
              else:
                btnOn = False
              time.sleep(.02) 
          except ValueError:
              pass
except KeyboardInterrupt:
  pass