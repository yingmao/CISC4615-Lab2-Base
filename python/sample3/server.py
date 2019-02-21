import socket
import sys
import binascii
import struct
def crc32(v):
    return binascii.crc32(v)
if len(sys.argv) != 2:
    print("Useage: python " + sys.argv[0] + " <liseten port>")
    sys.exit(-1)
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("0.0.0.0", int(sys.argv[1])))
print("Waiting...")
while True:
    data, addr = s.recvfrom(1024)
    str,crc = struct.unpack("!50si",data)
    print "str:%s\ncrc:%X" % (str,crc & 0xffffffff)
    if data == "bye":
        break
