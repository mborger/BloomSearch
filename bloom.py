#!/usr/bin/env python3

from math import log as ln, exp as e

def optK(m,n):
    return (m//n)*ln(2)

def optM(n,p):
    return -((n*ln(p))//(ln(2)**2))

def optP(m,n):
    return e(-(m//n)*ln(2)**2)
