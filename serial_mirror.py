import serial

controller = serial.Serial('COM7')
console = serial.Serial('COM9')
print('Ready to Rock!')

while True:
    console.write(controller.read())
