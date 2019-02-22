import socket
import struct
import sys
import binascii
def crc32(v):
    return binascii.crc32(v)
if len(sys.argv) != 3:
    print("Useage: python " + sys.argv[0] + " <ip> <liseten port>")
    sys.exit(-1)
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
while True:
    print("Input text:")
    text = sys.stdin.readline().strip()
    ss = struct.pack("!50si",text,crc32(text))
    s.sendto(ss,(sys.argv[1],int(sys.argv[2])))
    if text == "bye":
        break
