import serial

console = serial.Serial('COM7')
controller = serial.Serial('COM9')
print('Ready to Rock!')

while True:
    console.write(controller.read())
