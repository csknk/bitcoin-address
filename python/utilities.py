#!/usr/bin/env python3
from hashlib import *

def double_sha256(bytes):
    return sha256(sha256(bytes).digest()).digest()
