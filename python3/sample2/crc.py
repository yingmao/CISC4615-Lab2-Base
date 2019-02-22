import binascii
import sys

def crc32(v):
    return '%X' % (binascii.crc32(v.encode()) & 0xffffffff)


while True:
    print("Input text:")
    text = sys.stdin.readline().strip()
    print("CRC:" + crc32(text))
    if text == "bye":
        break
