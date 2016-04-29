#include <stdio.h>
#include <math.h>

int isprime(long x){
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

int main(){
  FILE *fp;

  fp = fopen("primes.txt", "w+");
  for(long i = 1000000000; i > 900000000; i--){
    if(isprime(i) == 1){
      printf("%ld\n", i);
      fprintf(fp, "%ld\n", i);
    }
  }
  
  fclose(fp);
}
