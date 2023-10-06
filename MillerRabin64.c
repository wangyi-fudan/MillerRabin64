static	inline	unsigned long long	mul_mod(unsigned long long a, unsigned long long b, unsigned long long m) {
    unsigned long long r=0;
    while (b) {
        if (b & 1) {
            unsigned long long r2 = r + a;
            if (r2 < r) r2 -= m;
            r = r2 % m;
        }
        b >>= 1;
        if (b) {
            unsigned long long a2 = a + a;
            if (a2 < a) a2 -= m;
            a = a2 % m;
        }
    }
    return r;
}
static inline unsigned long long pow_mod(unsigned long long a, unsigned long long b, unsigned long long m) {
    unsigned long long r=1;
    while (b) {
        if (b&1) r=mul_mod(r,a,m);
        b>>=1;
        if (b) a=mul_mod(a,a,m);
    }
    return r;
}
unsigned sprp(unsigned long long n, unsigned long long a) {
    unsigned long long d=n-1;
    unsigned char s=0;
    while (!(d & 0xff)) { d>>=8; s+=8; }
    if (!(d & 0xf)) { d>>=4; s+=4; }
    if (!(d & 0x3)) { d>>=2; s+=2; }
    if (!(d & 0x1)) { d>>=1; s+=1; }
    unsigned long long b=pow_mod(a,d,n);
    if ((b==1) || (b==(n-1))) return 1;
    unsigned char r;
    for (r=1; r<s; r++) {
        b=mul_mod(b,b,n);
        if (b<=1) return 0;
        if (b==(n-1)) return 1;
    }
    return 0;
}

unsigned is_prime(unsigned long long n) {
    unsigned long long primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    const unsigned long long n_primes = sizeof(primes)/sizeof(primes[0]);
    int i;
    if (n<2||!(n&1)) return 0;
    if (n<4) return 1;
    if (!sprp(n,2)) return 0;
    if (n<2047) return 1;
    for (i=1; i<n_primes; i++)
        if(!sprp(n, primes[i]))
            return 0;
    return 1;
}

#include	<stdio.h>
int	main(void){
	for(unsigned long long i=0;	i<1024;	i++)	if(is_prime(i))	printf("%llu ",i);
	return	0;
}

