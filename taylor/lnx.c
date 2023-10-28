#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>

// OpenMP for parallelism
#include <omp.h>

// multiprecision library to to test precision
// sudo aptitude install libgmp-dev  
// sudo aptitude install libmpfr-dev
#include <gmp.h>
#include <mpfr.h>

//#define DEBUG 1
#define DEFAULTN 10


// Compilación
// gcc -Ofast -o lnx lnx.c -lm -fopenmp -lmpfr -lgmp


//ejemplo paralelo: 

//  OMP_NUM_THREADS=4 ./lnx 2 100000000
// Computing ln(2) using Taylor Series (using 100000000 terms) 
//  ln(2)=0.693147  precision=(-5.00011e-09) in 0.371306 secs 
// Con 200 bits de precision, ln(x) es: 6.9314718055994530941723212145817656807550013436025525412067997e-1
// La differencia es -5.0001124120145715352838001699005740843897447458793200223296496e-9


// Kincaid Chapter 1: ln(2) analysis 100M terms for 10-8 precision

double termino(double x,long int n);
void printprecisionlnx(double x,double res);

int main(int argc, char* argv[]){

    // This program uses taylor series to estimate ln(x)
    // The input to this program is the number x
    // optionally we can define n (by default 10) 


    double x,term,result;
    double tiempo, tiempo_inicio;
    long int n=DEFAULTN; 
    char *str, *eptr; // parameter of the strtod function

    // double strtod(const char *nptr, char **endptr) The  strtod(),  strtof(),
    // and  strtold() functions convert the initial portion of the string
    // pointed to by nptr to  double,  float,  and  long double representation,
    // respectively. The  expected  form  of the (initial portion of the) string
    // is optional leading white space as recognized by isspace(3), an optional
    // plus ('+') or  minus  sign  ('-')  and then either (i) a decimal number,
    // or (ii) a hexadecimal number, or (iii) an infinity, or (iv) a NAN
    // (not-a-number) A decimal number consists of a nonempty sequence of
    // decimal digits possibly  containing  a  radix character (decimal point,
    // locale-dependent, usually '.'), optionally followed by a decimal
    // exponent.  A decimal exponent consists of an 'E' or 'e', followed by an
    // optional plus or minus sign, followed by a nonempty sequence of decimal
    // digits, and  indicates multiplication by a power of 10.

    // Since  0  can legitimately be returned on both success and failure, the
    // calling program should set errno to 0 before the call, and then
    // determine if an error occurred by checking whether errno has a nonzero
    // value after the call.

    // Essentially, the strtod function skips all white-space characters at the
    // beginning of the string, converts the subsequent characters as part of
    // the number, and then stops when it encounters the first character that
    // isn't a number.


    /* Conversion to a double */
    str=argv[1];
    errno=0;
    x = strtod(argv[1], &eptr);

    if (errno != 0)
    {
        perror("strtod");
        /* If the value provided was out of range, display a warning message */
        if (errno == ERANGE)
            printf("The value provided was out of range\n");
        exit(EXIT_FAILURE);
    }

    if (eptr ==str ){
        fprintf(stderr, "No se encontraron dígitos al parsear x\n");
        exit(EXIT_FAILURE);
    }


    str=argv[2];
    errno=0;
    n = strtoll(argv[2], &eptr, 10);
    if (errno !=0 ){
        perror("strtol n");
        exit(EXIT_FAILURE);
    }
    if (eptr ==str ){
        fprintf(stderr, "No se encontraron dígitos al parsear n\n");
        exit(EXIT_FAILURE);
    }
    
    /* Display */
    printf("Computing ln(%g) using Taylor Series (using %li terms) \n", x,n);

    result=0.0;
    tiempo_inicio = omp_get_wtime(); // tiempo real (wallclock)
    #pragma omp parallel for reduction(+:result)
    for(long int i=1; i < n;i++){
        #ifdef DEBUG
        printf(".");
        #endif
        result += termino(x,i);
    }   
    tiempo = omp_get_wtime() -tiempo_inicio; // tiempo real (wallclock)
    
    printf(" ln(%g)=%g  precision=(%g) in %g secs \n",x,result,log(x)-result,tiempo);
    printprecisionlnx(x,result);

}

double termino(double x,long int k){
    double signo;
    double potencia;
    double divisor;
    double result;

    if((k % 2) == 0){
        //terminos 2,4,6,... el signo es negativo
        signo=-1.0;
    } else {
        //terminos 1,3,5,... el signo es positivo
        signo=1.0;
    }
    potencia=pow(x-1,k);
    divisor=1.0/(double)k;
    result=signo*potencia*divisor;

    #ifdef DEBUG
    printf("termino %li: signo %g, potencia=%g, divisor=%g, resultado %g\n",k,signo,potencia,divisor,result);
    #endif
    
    return result;
}

void printprecisionlnx(double x,double res){

    mpfr_t xp, rp, resp,diff;
    
    mpfr_init2 (xp, 200);
    mpfr_init2 (rp, 200);
    mpfr_init2 (resp, 200);
    mpfr_init2 (diff, 200);
    
    mpfr_set_d (xp, x, GMP_RNDD);
    mpfr_set_d (resp, res, GMP_RNDD);
    mpfr_log(rp,xp,GMP_RNDD);
    printf ("Con 200 bits de precision, ln(x) es: ");
    mpfr_out_str (stdout, 10, 0, rp, GMP_RNDD);
    putchar ('\n');
    
    mpfr_sub (diff, rp, resp,GMP_RNDD);

    printf ("La differencia es ");
    mpfr_out_str (stdout, 10, 0, diff, GMP_RNDD);
    putchar ('\n');
    mpfr_clear(xp);
    mpfr_clear(rp);
    mpfr_clear(resp);
    mpfr_clear(diff);
    

}
