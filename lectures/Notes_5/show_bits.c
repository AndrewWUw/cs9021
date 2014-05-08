/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Prompts the user for a type and a value of that type           *
 *              and displays its internal representation.                      *
 *                                                                             *
 * Purpose: Provide a simple utility to see the bits...                        *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bail_out(void);
void show_bits(int);
void show_byte(char *);

enum {UNSIGNED_LONG_LONG, UNSIGNED_LONG, UNSIGNED, UNSIGNED_SHORT, LONG_LONG, LONG, INT, SHORT, FLOAT, DOUBLE, LONG_DOUBLE};

int main(void) {
    char input[5];
    printf("Enter input, using sequence of letters from\n\
  s for signed\n\
  u for unsigned\n\
  h for short\n\
  i for int\n\
  l for long\n\
  f for float\n\
  d for double:\n");
    scanf("%4s", input);
    bool _signed = false;
    bool _unsigned = false;
    bool _short = false;
    bool _int = false;
    bool _long = false;
    bool _long_long = false;
    bool _float = false;
    bool _double = false;
    int processed = 0;
    for (int i = 0; i < strlen(input); ++i)
        if (input[i] == 's' && !_signed) {
            _signed = true;
            ++processed;
        }
        else if (input[i] == 'u' && !_unsigned) {
            _unsigned = true;
            ++processed;
        }
        else if (input[i] == 'h' && !_short) {
            _short = true;
            ++processed;
        }
        else if (input[i] == 'i' && !_int) {
            _int = true;
            ++processed;
        }
        else if (input[i] == 'l' && !_long_long) {
            if (_long) {
                _long = false;
                _long_long = true;
            }
            else
                _long = true;
            ++processed;
        }
        else if (input[i] == 'f' && !_float) {
            _float = true;
            ++processed;
        }
        else if (input[i] == 'd' && !_double) {
            _double = true;
            ++processed;
        }
    if (processed != strlen(input))
        bail_out();
    char type[24];
    for (int i = 0; i < 24; ++i)
        type[i] = '\0';
    processed = 0;
    if (_signed) {
        if (_unsigned || _float || _double)
            bail_out();
        strcat(type, "signed ");
        ++processed;
    }
    else if (_unsigned) {
        if (_float || _double)
            bail_out();
        strcat(type, "unsigned ");
        ++processed;
    }
    if (_short) {
        if (_long || _long_long || _float || _double)
            bail_out();
        strcat(type, "short ");
        ++processed;
    }    
    else if (_long) {
        if (_float)
            bail_out();
        strcat(type, "long ");
        ++processed;
    }    
    else if (_long_long) {
        if (_float || _double)
            bail_out();
        strcat(type, "long long ");
        processed += 2;
    }
    if (_int) {
        if (_float || _double)
            bail_out();
        strcat(type, "int ");
        ++processed;
    }
    else if (_float) {
        if (_double)
            bail_out();
        strcat(type, "float ");
        ++processed;
    }
    else if (_double) {
        strcat(type, "double ");
        ++processed;
    }
    if (processed != strlen(input))
        bail_out();
    printf("\nI understand that you want to enter a value of type %s\n", type);
    if (_unsigned)
        if (_long_long)
            show_bits(UNSIGNED_LONG_LONG);
        else if (_long)
            show_bits(UNSIGNED_LONG);
        else if (_short)
            show_bits(UNSIGNED_SHORT);
        else
            show_bits(UNSIGNED);
    else if (!_float && !_double)
        if (_long_long)
            show_bits(LONG_LONG);
        else if (_long)
            show_bits(LONG);
        else if (_short)
            show_bits(SHORT);
        else
            show_bits(INT);
    else if (_float)
        show_bits(FLOAT);
    else if (_long)
        show_bits(LONG_DOUBLE);
    else
        show_bits(DOUBLE);
    return EXIT_SUCCESS;
}

void show_bits(int type) {
    int k = 0;
    switch(type) {
        case UNSIGNED_LONG_LONG: {
            unsigned long long value;
            do {
                printf("Enter a value of that type: ");
                rewind(stdin);
            } while (!scanf("%llu", &value) && !fflush(stdin));
            printf("\nThe internal representation is:\n  ");
            char *pt_to_char = &value;
            while (k++ < sizeof(unsigned long long))
                show_byte(pt_to_char++);
            break;
        }
        case UNSIGNED_LONG: {
            unsigned long value;
            do {
                printf("Enter a value of that type: ");
                rewind(stdin);
            } while (!scanf("%lu", &value) && !fflush(stdin));
            printf("\nThe internal representation is:\n  ");
            char *pt_to_char = &value;
            while (k++ < sizeof(unsigned long))
                show_byte(pt_to_char++);
            break;
        }
        case UNSIGNED: {
            unsigned value;
            do {
                printf("Enter a value of that type: ");
                rewind(stdin);
            } while (!scanf("%u", &value) && !fflush(stdin));
            printf("\nThe internal representation is:\n  ");
            char *pt_to_char = &value;
            while (k++ < sizeof(unsigned))
                show_byte(pt_to_char++);
            break;
        }
        case UNSIGNED_SHORT: {
            unsigned short value;
            do {
                printf("Enter a value of that type: ");
                rewind(stdin);
            } while (!scanf("%hu", &value) && !fflush(stdin));
            printf("\nThe internal representation is:\n  ");
            char *pt_to_char = &value;
            while (k++ < sizeof(unsigned short))
                show_byte(pt_to_char++);
            break;
        }
        case LONG_LONG: {
            long long value;
            do {
                printf("Enter a value of that type: ");
                rewind(stdin);
            } while (!scanf("%lld", &value) && !fflush(stdin));
            printf("\nThe internal representation is:\n  ");
            char *pt_to_char = &value;
            while (k++ < sizeof(long long))
                show_byte(pt_to_char++);
            break;
        }
        case LONG: {
            long value;
            do {
                printf("Enter a value of that type: ");
                rewind(stdin);
            } while (!scanf("%ld", &value) && !fflush(stdin));
            printf("\nThe internal representation is:\n  ");
            char *pt_to_char = &value;
            while (k++ < sizeof(long))
                show_byte(pt_to_char++);
            break;
        }
        case INT: {
            int value;
            do {
                printf("Enter a value of that type: ");
                rewind(stdin);
            } while (!scanf("%d", &value) && !fflush(stdin));
            printf("\nThe internal representation is:\n  ");
            char *pt_to_char = &value;
            while (k++ < sizeof(int))
                show_byte(pt_to_char++);
            break;
        }
        case SHORT: {
            short value;
            do {
                printf("Enter a value of that type: ");
                rewind(stdin);
            } while (!scanf("%hd", &value) && !fflush(stdin));
            printf("\nThe internal representation is:\n  ");
            char *pt_to_char = &value;
            while (k++ < sizeof(short))
                show_byte(pt_to_char++);
            break;
        }
        case FLOAT: {
            float value;
            do {
                printf("Enter a value of that type: ");
                rewind(stdin);
            } while (!scanf("%f", &value) && !fflush(stdin));
            printf("\nThe internal representation is:\n  ");
            char *pt_to_char = &value;
            while (k++ < sizeof(float))
                show_byte(pt_to_char++);
            break;
        }
        case DOUBLE: {
            double value;
            do {
                printf("Enter a value of that type: ");
                rewind(stdin);
            } while (!scanf("%lf", &value) && !fflush(stdin));
            printf("\nThe internal representation is:\n  ");
            char *pt_to_char = &value;
            while (k++ < sizeof(double))
                show_byte(pt_to_char++);
            break;
        }
        case LONG_DOUBLE: {
            long double value;
            do {
                printf("Enter a value of that type: ");
                rewind(stdin);
            } while (!scanf("%Lf", &value) && !fflush(stdin));
            printf("\nThe internal representation is:\n  ");
            char *pt_to_char = &value;
            while (k++ < sizeof(long double))
                show_byte(pt_to_char++);
        }
    }
    putchar('\n');
}
            
void bail_out(void) {
    printf("Incorrect type description. Sorry...\n");
    exit(EXIT_FAILURE);
}

void show_byte(char *pt_to_char) {
    for (int i = 0; i < 8; ++i) {
        printf("%d", (*pt_to_char & 0x80) != 0);
        *pt_to_char <<= 1;
    }
    putchar(' ');
}

