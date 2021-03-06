  /* here is the overview of how this works
     two prime numbers are chosen p and q
     these numbers must remain private
     the modulus is p * q which is very large and public and called n
     the function phi of n is easy to calculate one way, but not another
     some numbers, pub, have special properties when evaluated mod(n)
     to find pubs they need to be prime and coprime with phi of n
     once we have one we need to find the number, priv,
     that pub * priv mod(n) = 1 the modular inverse
     these two numbers are special because any number x is such that
     ((x^pub)^priv) mod(n) = x
     since priv is impossible to calculate without phi of n
     and phi of n is almost impossible to calculate 
     this makes the encryption scheme very secure
     the implemintation of RSA used in this program
     is very slow, simple, and most importantly basic
     without further adieu, here are the definitions of Talk-Secure
  */

//load libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>
// begin definitions

//rounding is useful for getting the integr of the square root
long rounder(float x){
  // add .5 so that if the number is something like 4.6
  //it will round to five
  x += .5;
  return (long) x;
}
// simple use of checking if all the numbers below sqrt(x) are not factors
// slow but simple for a slow and simple programmer
long isprime(long x){
  if(x == 1){
    // 1 isn't prime
    return 0;
  }
  int i;
  long square_root_x = round(sqrt(x));
  for(i = 2; i < (square_root_x + 1); i++){
      if (x % i == 0){
	return 0;}
    }
    return 1;
}

// greatet common denominator of a and b
// if the GCD is 1 then they are coprime
// they have no factors
int gcd(long a, long b ){
  long c;
  while ( a != 0 ) {
     c = a; a = b%a;  b = c;
  }
  return b;
}

//function for extended Euclidean Algorithm
int gcdExtended(int a, int b, int *x, int *y){
    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }
 
    int x1, y1; // To store results of recursive call
    int gcd = gcdExtended(b%a, a, &x1, &y1);
 
    // Update x and y using results of recursive
    // call
    *x = y1 - (b/a) * x1;
    *y = x1;
 
    return gcd;
}
 
//modular inverse works like GCD, but returns different value
long ModInverse(long a, long m){
    int x, y;
    long g = gcdExtended(a, m, &x, &y);
    if (g != 1)
      printf( "Inverse doesn't exist\n");
    else{
        // m is added to handle negative x
        long res = (x%m + m) % m;
	return res;
    }
    return -1;
}


  // iterating method is still faster than using large values
long modexp( int base, long exponent, long modulus){
  if (modulus == 1){
    return 0;
      }
  int c = 1;
  int i;
  // keep taking the mod of the base  while you exponentiate
  for(i = 0; i < (exponent + 1); i++){
    c = (c * base) % modulus;
  }
  return c;
}

//here comes the magic
long privkeyexp(phiofn){
  srand(time(NULL));
  int r= rand();
  // a function x -> pos where 0 < x < 1 and where 1 < pos < phi of n
  float num = (float)r/(float)(RAND_MAX/1); //random 0 < x < 1
  long possible_priv_key = (rounder(num * phiofn));
  // until priv_key_exp = something repeat this process
  long priv_key_exp = 1;
  while (priv_key_exp == 1){
    // if pos is prime and coprime with phiofn then it is a suitable key
    if(isprime(possible_priv_key)==1){
      if((gcd(possible_priv_key, phiofn)==1)){
	priv_key_exp = possible_priv_key;
      }
    }
    // add one and then make sure it will be smaller than
    if((possible_priv_key % (phiofn - 1)) == 0){
      possible_priv_key =  (possible_priv_key + 2) % phiofn;
    }
    possible_priv_key = (possible_priv_key + 1) % phiofn;
  }
  return priv_key_exp;
}


long primereturn(seed){
  if(seed == 1){
    return 6353;
  }
  if(seed == 2){
    return 6827;
  }
  return -1;
}

// main will return 0 and store the public and private keys into a file
int main(){
  //calculate the keys
  //get the two prime numbers we need
  long prime1 = primereturn(1);
  long prime2 = primereturn(2);
  //calculate the modulus
  long modn = prime1 * prime2;
  //claculate the phi of n
  long phiofn = ((prime1 -1) * (prime2 -1));
  //calculate the random key we will use
  long privatekey = privkeyexp(phiofn);
  //now take the inverse of the public key
  long publickey = ModInverse(privatekey, phiofn);
  //this concludes the calculations
  //time to store
  printf("%ld\n%ld\n%ld\n", privatekey, publickey, modn);
  return 0;
}
