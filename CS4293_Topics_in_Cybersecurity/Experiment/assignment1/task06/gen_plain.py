#!/bin/python3
def lxor(l1, l2):
	return [i1 ^ i2 for (i1, i2) in zip(l1, l2)]

p2 = list(bytes('Yes', 'ascii')) + [13] * 13
iv1 = list(bytes.fromhex("31323334353637383930313233343536"))
iv2 = list(bytes.fromhex("31323334353637383930313233343537"))
with open("plain.txt", 'wb') as f:
	f.write(bytes(lxor(lxor(p2, iv1), iv2)))