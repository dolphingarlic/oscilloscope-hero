import serial

controller = serial.Serial('COM9')
console = serial.Serial('COM7')

while True:
    console.write(controller.read())
