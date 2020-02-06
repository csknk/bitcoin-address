Generate Legacy Bitcoin Address
===============================
An exercise in creating a legacy Bitcoin address, as described [here][1].

Python Implementation
---------------------

Usage:
1. Clone this repo
2. `cd` into the python project directory
3. Make a virtual environment: `virtualenv -p python3 venv`
4. `source` the virtual environment activation script - e.g. `source venv/bin/activate`
5. Run `pip install -r requirements.txt`

Run [python/main.py][3].

C++ Implementation (Linux)
--------------------------
For the purposes of the C++ implementation, I've used `openssl` to provide the necessary hashing functionality.

You can get reasonable information on the `openssl` functions on the Linux man pages - for example enter `man SHA256_Update`.

Note that the `int SHA256_Final(unsigned char *md, SHA256_CTX *c)` function places the message digest in `md`, which must have space for `SHA256_DIGEST_LENGTH` bytes (i.e. 32) bytes.

Bitcoin Core does not use `openssl` - the hashing algorithms are built in to the project.

### Usage
Compile the C++ programme from the `cpp` directory. Run `./bin/main`.

Enter a public key in hexstring format when requested. The output includes the various stages of Base58Check encoding - this is just for educational purposes.

Run `./bin/p2sh` for the address output only.

References
----------
* [Technical background of version 1 Bitcoin addresses][1]
* [Base58 Encoding][2]

[1]: https://en.bitcoin.it/wiki/Technical_background_of_version_1_Bitcoin_addresses
[2]: https://en.bitcoin.it/wiki/Base58Check_encoding
[3]: python/main.py
