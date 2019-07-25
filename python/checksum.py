#!/usr/bin/env python3
import sys
from base58 import *
from utilities import *

def checksum(address):
    hex_bytes = b58decode(address)
    print("hex:\t{}".format(hex_bytes.hex()))
    checksum = hex_bytes[-4:]
    check_digest = hex_bytes[:-4]
    if (checksum == double_sha256(check_digest)[:4]):
        return True
    else:
        return False
    # print("checksum:\t{}".format(checksum.hex()))
    # print("check_digest:\t{}".format(check_digest.hex()))
    # print(double_sha256(check_digest)[:4].hex())

if __name__ == '__main__':
    if len(sys.argv) < 2:
        address = input("Enter address to check:")
    else:
        address = sys.argv[1]
    print(checksum(address))
