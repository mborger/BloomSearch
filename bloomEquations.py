#!/usr/bin/env python3

"""
k represents the number of hash functions
m is the length of the bit string
n is the expected number of elements to be inserted
p is the false positive probability
"""

from math import log as ln, exp as e

def optK(m,n):
    return (m//n)*ln(2)

def optM(n,p):
    return -((n*ln(p))//(ln(2)**2))

def optP(m,n):
    return e(-(m//n)*ln(2)**2)
