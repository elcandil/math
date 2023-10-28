#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>


#define DEFAULTN 10

int main(int argc, char* argv[]){

    // This program uses taylor series to estimate ln(x)
    // The input to this program is the number x
    // optionally we can define n (by default 10) 

    double x;
    int n=DEFAULTN; 

    char *eptr; // parameter of the strtod function

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
    errno=0;
    x = strtod(argv[1], &eptr);

    if (err != 0)
    {
        /* If the value provided was out of range, display a warning message */
        if (errno == ERANGE)
            printf("The value provided was out of range\n");
        exit(-1);
    }

    n=atoi(2);

    /* Display */
    printf("Computing ln(%g) using Taylor Series (using %i terms) \n", x,n);
    


    
}