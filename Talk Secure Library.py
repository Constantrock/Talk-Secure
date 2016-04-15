#I am writing a program for the purpose of encrypting communication
#between two computers

#I wrote this code over the summer
#being young and dumb none of this was commented
#I have forgotten how much of this math works
#the variable names don't describe what they are
#I do, however, have access to explanations of the process
#I will be rewriting this shortly

#http://sergematovic.tripod.com/rsa1.html

#the next step is tow rewrite this with comments
#it will serve as the foundation of the encryption
#then I will write the server side code for finding other computers
#then I will write the client side code for the actual communication
#I have no estimates of how long this will take

#the general method is to
#Generate private key
#generate public key
#encrypt message
#decrypt message

import random

#Returns True or False if number is prime or not prime
def isprime(x):
    #there are no even primes except two
    if x % 2 == 0:
        return False
    #the median factor is always the square root
    #there shouldn't be any need to check for even numbers
    #so start with an odd then increment by two
    for i in xrange(3, int((x**(1.0/2.0)))+1 , 2):
        if x % i == 0:
            return False
    return True

#this magic return the Greatest common denominator
#I don't remember how
#I hope it isn't important
def gcd(a, b):
    s = 0
    old_s = 1
    r = b
    old_r = a
    t = 1
    old_t = 0
    while r != 0:
        quotient = old_r / r
        old_r, r = r, old_r - quotient * r
        old_s, s = s, old_s - quotient * s
        old_t, t = t, old_t - quotient * t
    return old_r


# modular inverse returns s instead of r
#the modular inverse is the number k so that J * k  = 1 mod(n)
def modinverse(a, b):
    s = 0
    old_s = 1
    r = b
    old_r = a
    t = 1
    old_t = 0
    while r != 0:
        quotient = old_r / r
        old_r, r = r, old_r - quotient * r
        old_s, s = s, old_s - quotient * s
        old_t, t = t, old_t - quotient * t
    return old_s


#the modular exponent returns modular exponent
def modexp(Base, Exponent, Modulus):
    if Modulus == 1:
        return 0
    c = 1
    #this method is faster although it takes more operations
    #exponentiate then modulate repeatedly
    for i in xrange(0, Exponent+1, 1):
        c = (c * base) % Modulus
    return c



"""Generate two large primes"""
""" Prime1 and Prime2"""

"""n = Prime1 * Prime2"""
"""z = ((Prime1 - 1) * (Prime2 - 1))"""
"""Generate Prime3"""
"""generate a number k that is larger than Prime3 and coprime with Prime3"""
"""The server's public key is n, k"""

"""This is the server side library"""
"""it has a list of large primes already"""

def KeyGen(Prime1, Prime2, KeyChainNum):
    PossibleKeys = []
    #I hope that dynamic typing will keep this from overflowing
    ModN = Prime1 * Prime2 #pq
    PrivKey = ((Prime1 - 1) * (Prime2 - 1)) #m
    for i in xrange(3,PrivMod,1):
        if isprime(i) == True and gcd(i, PrivKeyA) == 1:
            PossibleKeys.append(i)
    PubKeyExp=PossibleKeys[random.SystemRandom().randrange(len(PossibleKeys))]#e
    PrivKeyExp = ModInverse(e, ModN) #d
    #Time to make sure no errors ocured
    if gcd(PubKeyExp, PrivKey) != 1:
        return -1
    if PubKeyExp <= 1 or PubKeyExp >= PrivKey:
        return -1
    if (PrivKeyExp * PubKeyExp) % PrivKey != 1:
        return -1
    
    KeyChainNum = [ModN, PubKeyExp, PrivKeyExp]
    
    return KeyChainNum



#Encryption is just modular exponentiation Message to the power of PubKeyExp
#Mod ModN

def encryptor(KeyChainNum, Message):
    EncryptedMessage = modexp(Message, KeyChainNum[1], KeyChainNum[0])
    return EncryptedMessage

#decryption is just as simple

def Decryptor(EncryptedMessage, KeyChainNum[2], KeyChainNum[0]):
    DecryptedMessage = modexp(EncryptedMessage, PrivKeyExp, ModN)
    return DecryptedMessage
