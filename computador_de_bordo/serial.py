import serial

ser = serial.Serial('COM3',9600)
print(ser)
recebi = ser.read()
print(recebi)


while (1):
    leitura = ser.readline()
    pot = leitura.rstrip()
    print(pot.decode("utf-8"))
