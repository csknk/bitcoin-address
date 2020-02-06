#!/usr/bin/env python3
import sys
from base58 import *
from utilities import *

def checksum(address):
    hex_bytes = b58decode(address)
    checksum = hex_bytes[-4:]

    if __name__ == '__main__':
        scriptPubKeyHash = hex_bytes[:-4]
        scriptPubKeyHash = scriptPubKeyHash[1:]
        print("address:\t{}".format(address))
        print("hex:\t\t{}".format(scriptPubKeyHash.hex()))
        print("checksum:\t{}".format(checksum.hex()))

    check_digest = hex_bytes[:-4]
    if (checksum == double_sha256(check_digest)[:4]):
        return True
    else:
        return False

if __name__ == '__main__':
    if len(sys.argv) < 2:
        address = input("Enter address to check:")
    else:
        address = sys.argv[1]
    print(checksum(address))
