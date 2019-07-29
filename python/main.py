#!/usr/bin/env python3
from base58 import *
from binascii import *
import hashlib

def main():
    # Public Key
    pub_key = input("Enter public key:")

    # pub_key to bytes object and hash
    pub_key_bytes = unhexlify(pub_key)

    # First round - sha256
    round1 = sha256(pub_key_bytes).digest()

    # Second round, RIPEMD-160 hashing
    hash160 = hashlib.new('ripemd160', round1).digest()

    # Prepend the prefix to the RIPEMD-160 hash
    prefix = b'\x00'
    prefixed_hash160 = prefix + hash160

    # Calculate the checksum:
    # hash the prefixed hash160 with sha256 twice.
    # The first 4 bytes of the resulting hash is the
    # checksum.
    _ = sha256(prefixed_hash160).digest()
    checksum = sha256(_).digest()[:4]

    # The address is the base58 encoding of the concatenated
    # prefixed_hash160 and the checksum
    final = b58encode(prefixed_hash160 + checksum)
    
    print("checksum is {}".format(checksum.hex()))
    print("hex encoded address is {}".format((prefixed_hash160 + checksum).hex()))
    print(final.decode('utf-8'))

if __name__ == '__main__':
    main()
