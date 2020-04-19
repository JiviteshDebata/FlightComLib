from pyMultiWii import MultiWii

serialPort = "COM13"
board = MultiWii(serialPort)
while True:
    print (board.getData(MultiWii.ATTITUDE))