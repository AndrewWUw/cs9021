#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* p_scanf and p_fscanf are similar to scanf and fscanf, respectively,
 * as described in Section 15.8 of "C A Reference Manual", fifth edition,
 * by Samuel P. Harbison III and Guy L. Steele J.,
 * except for the processing of multibyte characters:
 * the l size specifier to the c, s and [ conversion letters is not supported.
 * p_scanf and p_fscanf differ from scanf and fscanf in that:
 * - they expect the input to be terminated by \n EOF;
 * - they expect the whole contents of the control string to be used up;
 * - they expect no input to remain after all conversions have been performed;
 * - they expect the format string to be syntactically correct;
 * - they perform a conversion only if the input matches the range of possible values
 *   of the type determined by the conversion letter and size specifier;
 * - they allow the format string to contain any number of substrings of the form
 *   <=n, >=n or !=n, where n is an integer or floating point number, to be placed right
 *   after the * and maximum size width modifiers if present, to force the input to be
 *   accepted only if it is less than or equal to, greater than or nonequal to,
 *   or nonequal to n, respectively;
 *   these new modifiers will be ignored if the associated conversion letter is one of
 *   c, s, p, n %, or [.
 * If one of the previous conditions fails to be satisfied, then the functions return
 * EXIT_FAILURE and print out to standard error a cause for failure, reporting that
 * 1. Control D does not follow carriage return, or
 * 2. there is not enough input to match the whole format string, or
 * 3. some input is left after the whole format string has been processed, or
 * 4. a part of the format string is not syntactically correct, or
 * 5. a part of the format string is not matched by the input,
 *   with a mention of whether
 *   - no input is left, or
 *   - the input does not match the type determined by the part of the format string
 *     being processed (in particular, the z size specifier expects the input to be positive,
 *     even if associated with the d or i conversion letters, and
 *     the u, o and x conversion letters, associated with any size specifier,
 *     expect the input to be positive), or
 *   - the norm of the input is too large, or too close to 0, or
 *   - for the new modifers of the form <=n, >=n and !=n, that the input fails a constraint
 *     of the form <=, >= or !=, respectively.
 * When 1., 2. or 3. are causes for failure, the first cause, in that order, is reported.
 * When there is a cause for failure which is neither 1., 2. or 3.,
 * then the cause associated with the leftmost conversion specifier or character
 * in the format string is reported, and the final segment of the segment string starting with
 * that leftmost conversion specifier or character is output to standard error.
 * The functions also return EXIT_FAILURE if there is a syntactic error in the format string,
 * printing out to standard error a message to this effect together with what remains of the
 * format string that cannot be processed, unless a shorter initial segment of the format string
 * fails to match the input for one of the reasons 1.to 5. above.
 *
 * p_prompt takes a string s, a format string s' and a variable list l of pointers as arguments.
 * The string s is printed out to standard output (not followed by a new line character), and
 * the program waits for the user to input some values that will be processed by p_scanf with
 * s' and l as aguments. The function p_prompt returns EXIT_SUCCESS if p_scanf succeeds;
 * otherwise the error messages of p_scanf are sent to standard error and the procedure repeats.
 *
 * p_guarded_prompt takes a pointer to a function, say guard, a string s, a format string s',
 * and a pointer p to a pointer to void as arguments; p is meant to be an array args of
 * pointers of size equal to the number of values to store, and
 * guard is meant to take p as argument and return true or false.
 * Let l be the variable list of pointers determined by args in the obvious way.
 * The string s is printed out to standard output (not followed by a new line character), and
 * the program waits for the user to input some values that will be processed similarly as
 * if they were processed by p_scanf with s' and l as aguments.
 * The function p_guarded_prompt returns EXIT_SUCCESS if p_scanf would succeed and guard returns
 * true. If p_scanf would fail then the error messages of p_scanf are sent to standard error
 * and the procedure repeats. If p_scanf would succed and guard returns false then guard might be
 * implemented in such as way that it sends error messages to a stream (preferably standard error)
 * and the procedure repeats.
 * As an example of use, suppose that a negative int and an int greater than 15 have to be
 * provided by the user, and stored in int variables m and n, respectively.
 * Then the code might define args as follows:
 * void *args[2] = {&m, &n};
 * The function guard might be defined as follows:
 * bool guard(void *args[2]) {
 *     if (*(int *)args[0] >= 0) {
 *         fprintf(stderr, "First input is not negative.\n");
 *         return false;
 *     }    
 *     if (*(int *)args[1] <= 15) {
 *         fprintf(stderr, "Second input is not greater than 15.\n");
 *         return false;
 *     }    
 * return true;
 * }
 * The function p_guarded_prompt would be called as follows:
 * p_guarded_prompt(guard, "Input a negative int and an int greater than 15: ", "%d %d", args).
 * But note that the function p_guarded_prompt is meant to be used to impose more complex
 * conditions on the input: with this example, a statement of the form
 * p_prompt("Input a negative int and an int greater than 15: ", "%<=-1d %>=16d", args)
 * would do the job. */


/* A linked list to store all constraints of the form !=n. */
typedef struct Neq_constraint {
    long double neq_value;
    struct Neq_constraint *neq_values;
} Neq_constraint;


/* A structure to store the values of the * and max field width modifiers, as well as
 * all constraints of the form <=n, >=n and !=n.
 * If more than one constraint of the form <=n or >=n is present in a given format string,
 * then a reduction to a unique constraint of the same form will be performed. */
typedef struct {
    bool store;
    int max_field_width;
    bool le_request;
    long double le_value;
    bool ge_request;
    long double ge_value;
    Neq_constraint *neq_values;
} Modifiers;

    
int p_scanf(const char *, ...);
int p_fscanf(FILE *restrict, const char *, ...);
int p_prompt(const char *restrict, const char *, ...);
int p_guarded_prompt(bool (*)(void **), const char *restrict, const char *, void **);
static int _1p_fscanf(FILE *restrict, const char *, va_list *);
static int _2p_fscanf(FILE *restrict, const char *, void **);
static int _1p_convert(char **, const char *, va_list *, Modifiers *, char *);
static int _2p_convert(char **, const char *, void **, Modifiers *, char *);
static int _1p_char_count(ptrdiff_t, const char *, va_list *, bool);
static int _2p_char_count(ptrdiff_t, const char *, void **, bool);
static bool _p_char_count(const char *, int *, int *);
static int _1p_signed_int(char **, const char *, va_list *, Modifiers *);
static int _2p_signed_int(char **, const char *, void **, Modifiers *);
static int _p_signed_int(char **, const char *, int *, int *, long long *);
static int _1p_intmax(char **, const char *, va_list *, Modifiers *);
static int _2p_intmax(char **, const char *, void **, Modifiers *);
static int _p_intmax(char **, const char *, intmax_t *);
static int _1p_unsigned_int(char **, const char *, va_list *, Modifiers *);
static int _2p_unsigned_int(char **, const char *, void **, Modifiers *);
static int _p_unsigned_int(char **, const char *, int *, int *, unsigned long long *);
static int _1p_uintmax(char **, const char *, va_list *, Modifiers *);
static int _2p_uintmax(char **, const char *, void **, Modifiers *);
static int _p_uintmax(char **, const char *, uintmax_t *);
static int _1p_float(char **, const char *, va_list *, Modifiers *);
static int _2p_float(char **, const char *, void **, Modifiers *);
static int _p_float(char **, const char *, float *);
static int _1p_double(char **, const char *, va_list *, Modifiers *);
static int _2p_double(char **, const char *, void **, Modifiers *);
static int _p_double(char **, const char *, double *);
static int _1p_long_double(char **, const char *, va_list *, Modifiers *);
static int _2p_long_double(char **, const char *, void **, Modifiers *);
static int _p_long_double(char **, const char *, long double *);
static int collect_input(FILE *restrict, char **);
static bool nonspace_left(char *, char *);
static void remove_leading_spaces(const char **, char **);
static int process_modifiers(const char *, Modifiers *);
static int constraint_not_satisfied(long double, Modifiers *);
static bool closing_bracket(const char *, int *, bool *);
static void limit_input(char **, char *, int);
static int input_too_large(void);
static int input_too_small(void);
static int bad_format(void);
static int bad_input(char *);


int p_scanf(const char *format, ...) {    
    va_list args;    
    va_start(args, format);
    rewind(stdin);
    int return_value = _1p_fscanf(stdin, format, &args);
    va_end(args);
    return return_value;
}


int p_fscanf(FILE *restrict file, const char *format, ...) {
    va_list args;   
    va_start(args, format);
    rewind(file);
    int return_value = _1p_fscanf(file, format, &args);
    va_end(args);
    return return_value;
}


int p_prompt(const char *restrict prompt, const char *format, ...) {    
    va_list args;    
    bool failure;
    do {
        va_start(args, format);
        printf("\n%s", prompt);
        rewind(stdin);
        failure = _1p_fscanf(stdin, format, &args);
    } while (failure);
    va_end(args);
    return EXIT_SUCCESS;
}


int p_guarded_prompt(bool (*guard)(void **), const char *restrict prompt, const char *format, void **args_p) {
    bool failure;
    do {
        printf("\n%s", prompt);
        rewind(stdin);
        failure = _2p_fscanf(stdin, format, args_p);
    } while (failure || !guard(args_p));
    return EXIT_SUCCESS;
}


static int _1p_fscanf(FILE *restrict file, const char *format, va_list *args_p) {    
    char *input_left;
    if (collect_input(file, &input_left))
        return EXIT_FAILURE;
    char *whole_input = input_left;
    while (true) {
        /* Nothing is left of format, hence only space should be left in input. */
        if (!*format) {
            if (!nonspace_left(input_left, whole_input))
                return EXIT_SUCCESS;
            return EXIT_FAILURE;
        }
        /* If what is left of format starts with a space character,
         * remove all leading space characters in what is left of format
         * and in what is left of input. */
        if (isspace(*format)) {
            remove_leading_spaces(&format, &input_left);
            continue;
        }
        if (*format == '%') {
            Modifiers modifiers;
            /* Store input iff % is not followed by the * character. */
            modifiers . store = true;
            /* If a positive integer n (without leading +, and with any leading 0 being ignored)
             * follows % or %*, then n represents the maximum field width, namely,
             * the maximum number of characters in input to be consumed if the associated
             * conversion letter is one of d, i, u, o, x, c, s, a, f, e, g or [;
             * it will be ignored if the associated conversion letter is one of p, n or %.
             * As a consequence, if n is represented as a sequence of 0s then the specification
             * is no different to n being absent from the specification;
             * this corresponds to the case where the value of max_field_with is 0. */
            modifiers . max_field_width = 0;
            /* For the new <=n, >=n and !=n modifiers. */
            modifiers . le_request = false;
            modifiers . ge_request = false;
            modifiers . neq_values = NULL;
            /* The function process_modifiers sets the values of the fields of modifiers
             * and returns the index of the associated conversion letter or of the unique
             * or first letter of the associated size specifier in what is left of format. */
            int offset = process_modifiers(format, &modifiers);
            /* The function _1p_convert tries to convert an initial segment of what is left
             * of input. If the conversion is successful and the value of modifiers . store
             * is true, then the result of the conversion is stored in the next member of *args_p,
             * the variable list of pointer arguments.
             * A return value of 0 indicates that there is a mistake in the format string.
             * A return value of -1 indicates that the conversion could not be performed
             * due to bad input.
             * A strictly positive return value indicates that the conversion was successful
             * and gives the number of characters in what was left of the format string that
             * have been consumed as a result. */
            int extra_offset =
                _1p_convert(&input_left, format + offset, args_p, &modifiers, whole_input);
            if (extra_offset > 0) {
                format += offset + extra_offset;
                continue;
            }
            free(whole_input);
            fprintf(stderr, "End \"%s\" of format string could not be processed.\n", format);
            return EXIT_FAILURE;
        }
        /* What is left of format starts neither with a space nor with the % character;
         * that character has to be the first character of what is left of input,
         * in which case it can be consumed in both format and input.*/
        if (*input_left++ != *format) {
            bad_input(input_left);
            free(whole_input);
            fprintf(stderr, "End \"%s\" of format string could not be processed.\n", format);
            return EXIT_FAILURE;
        }
        ++format;
    }
}


static int _2p_fscanf(FILE *restrict file, const char *format, void **args_p) {    
    char *input_left;
    if (collect_input(file, &input_left))
        return EXIT_FAILURE;
    char *whole_input = input_left;
    while (true) {
        /* Nothing is left of format, hence only space should be left in input. */
        if (!*format) {
            if (!nonspace_left(input_left, whole_input))
                return EXIT_SUCCESS;
            return EXIT_FAILURE;
        }
        /* If what is left of format starts with a space character,
         * remove all leading space characters in what is left of format
         * and in what is left of input. */
        if (isspace(*format)) {
            remove_leading_spaces(&format, &input_left);
            continue;
        }
        if (*format == '%') {
            Modifiers modifiers;
            /* Store input iff % is not followed by the * character. */
            modifiers . store = true;            
            /* If a positive integer n (without leading +, and with any leading 0 being ignored)
             * follows % or %*, then n represents the maximum field width, namely,
             * the maximum number of characters in input to be consumed if the associated
             * conversion letter is one of d, i, u, o, x, c, s, a, f, e, g or [;
             * it will be ignored if the associated conversion letter is one of p, n or %.
             * As a consequence, if n is represented as a sequence of 0s then the specification
             * is no different to n being absent from the specification;
             * this corresponds to the case where the value of max_field_with is 0. */
            modifiers . max_field_width = 0;
            /* For the new <=n, >=n and !=n modifiers. */
            modifiers . le_request = false;
            modifiers . ge_request = false;
            modifiers . neq_values = NULL;
            /* The function process_modifiers sets the values of store and max_field_width
             * and returns the index of the associated conversion letter or of the unique
             * or first letter of the associated size specifier in what is left of format. */
            int offset = process_modifiers(format, &modifiers);
            /* The function _2p_convert tries to convert an initial segment of what is left
             * of input. If the conversion is successful and the value of modifiers . store
             * is true, then the result of the conversion is stored in the next member of *args_p,
             * the variable list of pointer arguments.
             * A return value of 0 indicates that there is a mistake in the format string.
             * A return value of -1 indicates that the conversion could not be performed
             * due to bad input.
             * A strictly positive return value indicates that the conversion was successful
             * and gives the number of characters in what was left of the format string that
             * have been consumed as a result. */
            int extra_offset =
                _2p_convert(&input_left, format + offset, args_p, &modifiers, whole_input);
            if (extra_offset > 0) {
                format += offset + extra_offset;
                ++args_p;
                continue;
            }
            free(whole_input);
            fprintf(stderr, "End \"%s\" of format string could not be processed.\n", format);
            return EXIT_FAILURE;
        }
        /* What is left of format starts neither with a space nor with the % character;
         * that character has to be the first character of what is left of input,
         * in which case it can be consumed in both format and input.*/
        if (*input_left++ != *format) {
            bad_input(input_left);
            free(whole_input);
            fprintf(stderr, "End \"%s\" of format string could not be processed.\n", format);
            return EXIT_FAILURE;
        }
        ++format;
    }
}


static int _1p_convert(char **input_left_p, const char *format, va_list *args_p, Modifiers *modifiers_p, char *whole_input) {
    if (*format == '%') {
        if (*(*input_left_p)++ != '%')
            return bad_input(*input_left_p);
        /* One character has been consumed from format. */
        return 1;
    }
    int max_field_width = modifiers_p -> max_field_width;
    bool store = modifiers_p -> store;
    if (*format == 'c') {
        if (!**input_left_p)
            return bad_input(*input_left_p);
        if (store) {
            char *arg = va_arg(*args_p, char *);
            *arg = **input_left_p;
        }
        /* Executed at most max_field_width - 1 times if there is a constraint
         * on the field width, and never otherwise since max_field_width is then zero. */
        while (*++*input_left_p && max_field_width-- > 1)
            ;
        /* One character has been consumed from format. */
        return 1;
    }
    if (*format == '[') {
        /* If format is of the form [... with ... beginning with neither ] nor ^] then
         * a closing bracket should be found in ..., and the index of its first occurrence
         * will be recorded in c_bracket.
         * If format is of the form []... or [^]... then a closing bracket should be found
         * in ..., and the index of its first occurrence will be recorded in c_bracket. */
        int c_bracket = 0;
        /* If format is of the form [^ then complement will be set to true. */
        bool complement = false;
        /* There is an error in the format string if a closing bracket that satisfies the
         * preceeding constraints cannot be found. */
        if (!closing_bracket(format, &c_bracket, &complement))
            return 0;
        char *arg;
        if (store)
            arg = va_arg(*args_p, char *);
        int i_offset = 0;
        /* Look for longest initial segment of *input_left_p,
         * of length at most equal to max_field_width if the latter is nonzero, such that
         * if not all of *input_left_p is being consumed then ... */
        while (*(*input_left_p + i_offset) && (!max_field_width || i_offset < max_field_width)) {
            int f_offset = 0;
            /* ... the first character c in *input_left_p that is not consumed is such that:
             * - c is not in the bracket expression and complement is equal to false, or
             * - c is in the bracket expression and complement is equal to true. */
            while (++f_offset < c_bracket)
                if (*(*input_left_p + i_offset) == *(format + f_offset))
                    break;
            if (!complement && f_offset == c_bracket ||
                complement && f_offset != c_bracket) {
                /* The empty string does not match a bracket expression. */
                if (!i_offset)
                    return bad_input(*input_left_p);
                break;
            }
            if (store)
                *arg++ = *(*input_left_p + i_offset);
            ++i_offset;
        }
        if (store)
            *arg = '\0';
        *input_left_p += i_offset;
        /* Including the initial [, c_bracket + 1 characters have been consumed from format. */
        return ++c_bracket;
    }
    /* If the conversion letter is n and possibly associated with a valid size specifier,
     * conversion_length will be set to 1 in case there is no size specifier, 2 in case
     * there is a 1-character size specifier, and 3 in case there is a 2-character size
     * specifier; otherwise conversion_length will be set to 0. */
    int conversion_length;
    /* If the conversion letter is n, *input_left_p - whole_input is the number of characters
     * that have been consumed from input. */
    if (conversion_length = _1p_char_count(*input_left_p - whole_input, format, args_p, store))
        return conversion_length;
    /* The conversion letter has to be one of s, d, i, u, o, x, a, f, e or g, and
     * leading space in what is left of *input_left_p can be deleted. */
    while (isspace(**input_left_p))
        ++*input_left_p;
    /* There has to be some input left. */
    if (!**input_left_p)
        return bad_input(*input_left_p);
    /* Look for longest initial segment of *input_left_p consisting of nonspace characters,
     * and of length at most equal to max_field_width if the latter is nonzero, ... */
    if (*format == 's') {
        if (store) {
            /* ... saving all those characters in turn in the next member of *args_p, the
             * array of pointer arguments, if required ... */
            char *arg = va_arg(*args_p, char *);
            int i_offset = 0;
            while (*(*input_left_p + i_offset) &&
                   !isspace(*(*input_left_p + i_offset)) &&
                   (!max_field_width || i_offset < max_field_width))
                *arg++ = *(*input_left_p + i_offset++);
            *arg = '\0';
        }
        /* ... and in any case, deleting all those characters from *input_left_p. */
        while (*++*input_left_p && !isspace(**input_left_p) && --max_field_width)
            ;
        /* One character has been consumed from format. */
        return 1;
    }
    /* If max_field_width is nonzero and there are more than max_field_width characters in
     **input_left_p before the final NULL character, then replace the member of *input_left_p
     * of index max_field_width with NULL, and keep track of it as char_to_restore. */
    char char_to_restore;
    limit_input(input_left_p, &char_to_restore, max_field_width);
    errno = 0;
    char *input_left = *input_left_p;
    /* If the conversion letter is valid and possibly associated with a valid size specifier,
     * and if the conversion can be performed then conversion_length will be set to 1
     * in case there is no size specifier, 2 in case there is a 1-character size specifier,
     * and 3 in case there is a 2-character size specifier.
     * If the conversion letter is valid and possibly associated with a valid size specifier,
     * and if the conversion cannot be performed then conversion_length will be set to -1.
     * If the conversion letter is invalid, or if it is valid but associated with an invalid
     * size specifier then conversion_length will be set to 0. */
    if ((conversion_length = _1p_signed_int(input_left_p, format, args_p, modifiers_p)) ||
        (conversion_length = _1p_intmax(input_left_p, format, args_p, modifiers_p)) ||
        (conversion_length = _1p_unsigned_int(input_left_p, format, args_p, modifiers_p)) ||
        (conversion_length = _1p_uintmax(input_left_p, format, args_p, modifiers_p)) ||
        (conversion_length = _1p_float(input_left_p, format, args_p, modifiers_p)) ||
        (conversion_length = _1p_double(input_left_p, format, args_p, modifiers_p)) ||
        (conversion_length = _1p_long_double(input_left_p, format, args_p, modifiers_p))) {
        /* A conversion has been attempted.
         * It might have been unsuccessful, in which case the value of conversion_length is -1.
         * In any case, *input_left_p - input_left characters have been consumed from the input;
         * in case max_field_width is nonzero and the conversion has been successful,
         * that value has to be subtracted from modifiers_p -> max_field_width to give the index
         * in (the updated) *input_left_p of the occurrence of char_to_restore that had been
         * replaced by NULL in *input_left_p before the conversion took place. */
        if (conversion_length > 0 && max_field_width)
            *(*input_left_p + (input_left - *input_left_p) + max_field_width) = char_to_restore;
        /* conversion_length characters have been consumed from format, unless conversion_length
         * is equal to 1 in which case an error message remains to be displayed before the
         * whole procedure exists. */
        return conversion_length;
    }
    return bad_format();
}


static int _2p_convert(char **input_left_p, const char *format, void **args_p, Modifiers *modifiers_p, char *whole_input) {
    if (*format == '%') {
        if (*(*input_left_p)++ != '%')
            return bad_input(*input_left_p);
        /* One character has been consumed from format. */
        return 1;
    }
    int max_field_width = modifiers_p -> max_field_width;
    bool store = modifiers_p -> store;
    if (*format == 'c') {
        if (!**input_left_p)
            return bad_input(*input_left_p);
        if (store)       
            *(char *)*args_p = **input_left_p;
        /* Executed at most max_field_width - 1 times if there is a constraint
         * on the field width, and never otherwise since max_field_width is then zero. */
        while (*++*input_left_p && max_field_width-- > 1)
            ;
        /* One character has been consumed from format. */
        return 1;
    }
    if (*format == '[') {      
        /* If format is of the form [... with ... beginning with neither ] nor ^] then
         * a closing bracket should be found in ..., and the index of its first occurrence
         * will be recorded in c_bracket.
         * If format is of the form []... or [^]... then a closing bracket should be found
         * in ..., and the index of its first occurrence will be recorded in c_bracket. */
        int c_bracket = 0;
        /* If format is of the form [^ then complement will be set to true. */
        bool complement = false;
        /* There is an error in the format string if a closing bracket that satisfies the
         * preceeding constraints cannot be found. */
        if (!closing_bracket(format, &c_bracket, &complement))
            return 0;
        int i_offset = 0;        
        /* Look for longest initial segment of *input_left_p,
         * of length at most equal to max_field_width if the latter is nonzero, such that
         * if not all of *input_left_p is being consumed then ... */
        while (*(*input_left_p + i_offset) && (!max_field_width || i_offset < max_field_width)) {
            int f_offset = 0;            
            /* ... the first character c in *input_left_p that is not consumed is such that:
             * - c is not in the bracket expression and complement is equal to false, or
             * - c is in the bracket expression and complement is equal to true. */
            while (++f_offset < c_bracket)
                if (*(*input_left_p + i_offset) == *(format + f_offset))
                    break;
            if (!complement && f_offset == c_bracket ||
                complement && f_offset != c_bracket) {
                /* The empty string does not match a bracket expression. */
                if (!i_offset)
                    return bad_input(*input_left_p);
                break;
            }
            /* ... saving all those characters in turn in the next member of args_p, the
             * array of pointer arguments, if required ... */
            if (store)
                *(char *)(*args_p)++ = *(*input_left_p + i_offset);
            ++i_offset;
        }
        if (store)
            *(char *)*args_p = '\0';
        *input_left_p += i_offset;
        /* Including the initial [, c_bracket + 1 characters have been consumed from format. */
        return ++c_bracket;
    }
    /* If the conversion letter is n and possibly associated with a valid size specifier,
     * conversion_length will be set to 1 in case there is no size specifier, 2 in case
     * there is a 1-character size specifier, and 3 in case there is a 2-character size
     * specifier; otherwise conversion_length will be set to 0. */
    int conversion_length;
    /* If the conversion letter is n, *input_left_p - whole_input is the number of characters
     * that have been consumed from input. */
    if (conversion_length = _2p_char_count(*input_left_p - whole_input, format, args_p, store))
        return conversion_length;
    /* The conversion letter has to be one of s, d, i, u, o, x, a, f, e or g, and
     * leading space in what is left of *input_left_p can be deleted. */
    while (isspace(**input_left_p))
        ++*input_left_p;
    /* There has to be some input left. */
    if (!**input_left_p)
        return bad_input(*input_left_p);
    /* Look for longest initial segment of *input_left_p consisting of nonspace characters,
     * and of length at most equal to max_field_width if the latter is nonzero, ... */
    if (*format == 's') {
        if (store) {            
            int i_offset = 0;
            while (*(*input_left_p + i_offset) &&
                   !isspace(*(*input_left_p + i_offset)) &&
                   (!max_field_width || i_offset < max_field_width))
                *(char *)(*args_p)++ = *(*input_left_p + i_offset++);
            *(char *)*args_p = '\0';
        }
        /* ... and in any case, deleting all those characters from *input_left_p. */
        while (*++*input_left_p && !isspace(**input_left_p) && --max_field_width)
            ;
        /* One character has been consumed from format. */
        return 1;
    }    
    /* If max_field_width is nonzero and there are more than max_field_width characters in
     **input_left_p before the final NULL character, then replace the member of *input_left_p
     * of index max_field_width with NULL, and keep track of it as char_to_restore. */
    char char_to_restore;
    limit_input(input_left_p, &char_to_restore, max_field_width);
    errno = 0;
    char *input = *input_left_p;
    /* If the conversion letter is valid and possibly associated with a valid size specifier,
     * and if the conversion can be performed then conversion_length will be set to 1
     * in case there is no size specifier, 2 in case there is a 1-character size specifier,
     * and 3 in case there is a 2-character size specifier.
     * If the conversion letter is valid and possibly associated with a valid size specifier,
     * and if the conversion cannot be performed then conversion_length will be set to -1.
     * If the conversion letter is invalid, or if it is valid but associated with an invalid
     * size specifier then conversion_length will be set to 0. */
    if ((conversion_length = _2p_signed_int(input_left_p, format, args_p, modifiers_p)) ||
        (conversion_length = _2p_intmax(input_left_p, format, args_p, modifiers_p)) ||
        (conversion_length = _2p_unsigned_int(input_left_p, format, args_p, modifiers_p)) ||
        (conversion_length = _2p_uintmax(input_left_p, format, args_p, modifiers_p)) ||
        (conversion_length = _2p_float(input_left_p, format, args_p, modifiers_p)) ||
        (conversion_length = _2p_double(input_left_p, format, args_p, modifiers_p)) ||
        (conversion_length = _2p_long_double(input_left_p, format, args_p, modifiers_p))) {
        /* A conversion has been attempted.
         * It might have been unsuccessful, in which case the value of conversion_length is -1.
         * In any case, *input_left_p - input_left characters have been consumed from the input;
         * in case max_field_width is nonzero and the conversion has been successful,
         * that value has to be subtracted from modifiers_p -> max_field_width to give the index
         * in (the updated) *input_left_p of the occurrence of char_to_restore that had been
         * replaced by NULL in *input_left_p before the conversion took place. */
        if (conversion_length > 0 && max_field_width)
            *(*input_left_p + (input - *input_left_p) + max_field_width) = char_to_restore;
        /* conversion_length characters have been consumed from format, unless conversion_length
         * is equal to 1 in which case an error message remains to be displayed before the
         * whole procedure exists. */
        return conversion_length;
    }
    return bad_format();
}


static int _1p_char_count(ptrdiff_t count, const char *format, va_list *args_p, bool store) {
    int conversion = 0;
    int conversion_length = 3;            
    if (!_p_char_count(format, &conversion, &conversion_length))
        return 0;
    if (store)
        switch (conversion) {
            case 0: {           /* lln */
                long long *arg = va_arg(*args_p, long long *);
                *arg = count;
                break;
            }
            case 1: {           /* hhn */
                char *arg = va_arg(*args_p, char *);
                *arg = count;
                break;
            }
            case 2: {           /* ln */
                long *arg = va_arg(*args_p, long *);
                *arg = count;
                break;
            }
            case 3: {           /* hn */
                short *arg = va_arg(*args_p, short *);
                *arg = count;
                break;
            }
            case 4: {           /* jn */
                intmax_t *arg = va_arg(*args_p, intmax_t *);
                *arg = count;
                break;
            }
            case 5: {           /* zn */
                ptrdiff_t *arg = va_arg(*args_p, ptrdiff_t *);
                *arg = count;
                break;
            }
            case 6: {           /* tn */
                size_t *arg = va_arg(*args_p, size_t *);
                *arg = count;
                break;
            }
            case 7: {           /* n */
                int *arg = va_arg(*args_p, int *);
                *arg = count;
            }
        }
    /* conversion_length characters have been consumed from format. */
    return conversion_length;
}

                    
static int _2p_char_count(ptrdiff_t count, const char *format, void **args_p, bool store) {
    int conversion = 0;
    int conversion_length = 3;            
    if (!_p_char_count(format, &conversion, &conversion_length))
        return 0;
    if (store)
        switch (conversion) {
            case 0:             /* lln */
                *(long long *)*args_p = count;
                break;
            case 1:             /* hhn */
                *(char *)*args_p = count;
                break;
            case 2:             /* ln */
                *(long *)*args_p = count;
                break;
            case 3:             /* hn */
                *(short *)*args_p = count;
                break;
            case 4:             /* jn */
                *(intmax_t *)*args_p = count;
                break;
            case 5:             /* zn */
                *(ptrdiff_t *)*args_p = count;
                break;
            case 6:             /* tn */
                *(size_t *)*args_p = count;
                break;
            case 7:             /* n */
                *(int *)*args_p = count;
        }
    /* conversion_length characters have been consumed from format. */
    return conversion_length;
}

                    
static bool _p_char_count(const char *format, int *conversion, int *conversion_length) {
    return
        !strncmp(format, "lln", *conversion_length) ||
        ++*conversion && !strncmp(format, "hhn", *conversion_length) ||
        ++*conversion && !strncmp(format, "ln", --*conversion_length) ||
        ++*conversion && !strncmp(format, "hn", *conversion_length) ||
        ++*conversion && !strncmp(format, "jn", *conversion_length) ||
        ++*conversion && !strncmp(format, "zn", *conversion_length) ||
        ++*conversion && !strncmp(format, "tn", *conversion_length) ||
        ++*conversion && !strncmp(format, "n", --*conversion_length);
}


static int _1p_signed_int(char **input_p, const char *format, va_list *args_p, Modifiers *modifiers_p) {
    int conversion = 0;
    int conversion_length = 3;
    long long signed_int;
    int outcome = _p_signed_int(input_p, format, &conversion, &conversion_length, &signed_int);
    /* If outcome is 0 then the conversion letter is neither d nor i, or it is associated
     * with an incorrect size specifier, or is associated with j or z.
     * If outcome is -1 then the input is not appropriate. */
    if (outcome != 1)
        return outcome;
    if (constraint_not_satisfied(signed_int, modifiers_p))
        return -1;
    if (modifiers_p -> store)
        switch (conversion) {
            case 0:             /* lld */
            case 6: {           /* lli */
                long long *arg = va_arg(*args_p, long long *);
                *arg = signed_int;
                break;
            }
            case 1:             /* hhd */
            case 7: {           /* hhi */                
                char *arg = va_arg(*args_p, char *);
                *arg = signed_int;
                break;
            }
            case 2:             /* ld */
            case 8: {           /* li */
                long *arg = va_arg(*args_p, long *);
                *arg = signed_int;
                break;
            }
            case 3:             /* hd */
            case 9: {           /* hi */
                short *arg = va_arg(*args_p, short *);
                *arg = signed_int;
                break;
            }
            case 4:             /* td */
            case 10: {          /* ti */
                ptrdiff_t *arg = va_arg(*args_p, ptrdiff_t *);
                *arg = signed_int;
                break;
            }
            case 5:             /* d */
            case 11: {          /* i */
                int *arg = va_arg(*args_p, int *);
                *arg = signed_int;
                break;
            }
            case 12: {          /* p */
                void **arg = va_arg(*args_p, void **);
                *arg = signed_int;
            }
        }
    /* conversion_length characters have been consumed from format. */
    return conversion_length;
}


static int _2p_signed_int(char **input_p, const char *format, void **args_p, Modifiers *modifiers_p) {
    int conversion = 0;
    int conversion_length = 3;
    long long signed_int;
    int outcome = _p_signed_int(input_p, format, &conversion, &conversion_length, &signed_int);
    /* If outcome is 0 then the conversion letter is neither d nor i, or it is associated
     * with an incorrect size specifier, or is associated with j or z.
     * If outcome is -1 then the input is not appropriate. */
    if (outcome != 1)
        return outcome;
    if (constraint_not_satisfied(signed_int, modifiers_p))
        return -1;
    if (modifiers_p -> store)
        switch (conversion) {
            case 0:             /* lld */
            case 6:             /* lli */
                *(long long *)*args_p = signed_int;
                break;
            case 1:             /* hhd */
            case 7:             /* hhi */
                *(char *)*args_p = signed_int;
                break;
            case 2:             /* ld */
            case 8:             /* li */
                *(long *)*args_p = signed_int;
                break;
            case 3:             /* hd */
            case 9:             /* hi */
                *(short *)*args_p = signed_int;
                break;
            case 4:             /* td */
            case 10:            /* ti */
                *(ptrdiff_t *)*args_p = signed_int;
                break;
            case 5:             /* d */
            case 11:            /* i */
                *(int *)*args_p = signed_int;
                break;
            case 12:            /* p */
                *(void **)*args_p = signed_int;
        }
    /* conversion_length characters have been consumed from format. */
    return conversion_length;
}


static int _p_signed_int(char **input_p, const char *format, int *conversion_p, int *conversion_length_p, long long *signed_int_p) {
    if (!strncmp(format, "lld", *conversion_length_p) ||
        ++*conversion_p && !strncmp(format, "hhd", *conversion_length_p) ||
        ++*conversion_p && !strncmp(format, "ld", --*conversion_length_p) ||
        ++*conversion_p && !strncmp(format, "hd", *conversion_length_p) ||
        ++*conversion_p && !strncmp(format, "td", *conversion_length_p) ||
        ++*conversion_p && !strncmp(format, "d", --*conversion_length_p))
        *signed_int_p = strtoll(*input_p, input_p, 10);
    /* First reinitialize *conversion_length_p to 3. */
    else if ((*conversion_length_p = 3) &&
             (++*conversion_p && !strncmp(format, "lli", *conversion_length_p) ||
              ++*conversion_p && !strncmp(format, "hhi", *conversion_length_p) ||
              ++*conversion_p && !strncmp(format, "li", --*conversion_length_p) ||
              ++*conversion_p && !strncmp(format, "hi", *conversion_length_p) ||
              ++*conversion_p && !strncmp(format, "ti", *conversion_length_p) ||
              ++*conversion_p && !strncmp(format, "i", --*conversion_length_p)))
        *signed_int_p = strtoll(*input_p, input_p, 0);
    /* At this point *conversion_length_p is equal to 1. */
    else if (++*conversion_p && !strncmp(format, "p", 1))
        *signed_int_p = strtoll(*input_p, input_p, 16);
    else
        return 0;
    if (errno == EINVAL)
        return bad_input(*input_p);
    if (errno == ERANGE)
        return input_too_large();
    switch (*conversion_p) {
        case 1:                 /* hhd */
        case 7:                 /* hhi */
            if (*signed_int_p > CHAR_MAX || *signed_int_p < CHAR_MIN)
                return input_too_large();
            break;
        case 2:                 /* ld */
        case 8:                 /* li */
            if (*signed_int_p > LONG_MAX || *signed_int_p < LONG_MIN)
                return input_too_large();
            break;
        case 3:                 /* hd */
        case 9:                 /* hi */
            if (*signed_int_p > SHRT_MAX || *signed_int_p < SHRT_MIN)
                return input_too_large();
            break;
        case 4:                 /* td */
        case 10:                /* ti */
            if (*signed_int_p > PTRDIFF_MAX || *signed_int_p < PTRDIFF_MIN)
                return input_too_large();
            break;
        case 5:                 /* d */
        case 11:                /* i */
            if (*signed_int_p > INT_MAX || *signed_int_p < INT_MIN)
                return input_too_large();
        case 12:                /* p */
            if (*signed_int_p > INTPTR_MAX || *signed_int_p < INTPTR_MIN)
                return input_too_large();
    }
    return 1;
}


static int _1p_intmax(char **input_p, const char *format, va_list *args_p, Modifiers *modifiers_p) {
    intmax_t intmax_t_int;
    int outcome = _p_intmax(input_p, format, &intmax_t_int);
    /* If outcome is 0 then the conversion is neither jd nor ji.
     * If outcome is -1 then the input is not appropriate. */
    if (outcome != 1)
        return outcome;
    if (constraint_not_satisfied(intmax_t_int, modifiers_p))
        return -1;
    if (modifiers_p -> store) {
        intmax_t *arg = va_arg(*args_p, intmax_t *);
        *arg = intmax_t_int;
    }
    /* Two characters have been consumed from format. */
    return 2;
}


static int _2p_intmax(char **input_p, const char *format, void **args_p, Modifiers *modifiers_p) {    intmax_t intmax_t_int;
    int outcome = _p_intmax(input_p, format, &intmax_t_int);
    /* If outcome is 0 then the conversion is neither jd nor ji.
     * If outcome is -1 then the input is not appropriate. */
    if (outcome != 1)
        return outcome;
    if (constraint_not_satisfied(intmax_t_int, modifiers_p))
        return -1;
    if (modifiers_p -> store)
        *(intmax_t *)*args_p = intmax_t_int;
    /* Two characters have been consumed from format. */
    return 2;
}


static int _p_intmax(char **input_p, const char *format, intmax_t *intmax_t_int_p) {
    if (!strncmp(format, "jd", 2))
        *intmax_t_int_p = strtoimax(*input_p, input_p, 10);
    else if (!strncmp(format, "ji", 2))
        *intmax_t_int_p = strtoimax(*input_p, input_p, 0);
    else
        return 0;
    if (errno == EINVAL)
        return bad_input(*input_p);
    if (errno == ERANGE)
        return input_too_large();
    return 1;
}


static int _1p_unsigned_int(char **input_p, const char *format, va_list *args_p, Modifiers *modifiers_p) {
    int conversion = 0;
    int conversion_length = 3;
    unsigned long long unsigned_int;
    int outcome = _p_unsigned_int(input_p, format, &conversion, &conversion_length, &unsigned_int);
    /* If outcome is 0 then the conversion letter is not d associated with z and it is
     * neither u, o, nor x, or it is u, o or x associated with an incorrect size specifier,
     * or it is u, o or x associated with j.
     * If outcome is -1 then the input is not appropriate. */
    if (outcome != 1)
        return outcome;
    if (constraint_not_satisfied(unsigned_int, modifiers_p))
        return -1;
    if (modifiers_p -> store)
        switch (conversion) {
            case 0:             /* llu */
            case 8:             /* llo */
            case 15: {          /* llx */                
                unsigned long long *arg = va_arg(*args_p, unsigned long long *);
                *arg = unsigned_int;
                break;
            }
            case 1:             /* hhu */
            case 9:             /* hho */
            case 16: {          /* hhx */
                unsigned char *arg = va_arg(*args_p, unsigned char *);
                *arg = unsigned_int;
                break;
            }
            case 2:             /* lu */
            case 10:            /* lo */
            case 17: {          /* lx */
                unsigned long *arg = va_arg(*args_p, unsigned long *);
                *arg = unsigned_int;
                break;
            }
            case 3:             /* hu */
            case 11:            /* ho */
            case 18: {          /* hx */
                unsigned short *arg = va_arg(*args_p, unsigned short *);
                *arg = unsigned_int;
                break;
            }
            /* We are more stringent than fscanf, as we do not accept input of type
             * size_t to be negative. */
            case 4:             /* zd */
            case 5:             /* zu */
            case 12:            /* zo */
            case 19: {          /* zx */
                size_t *arg = va_arg(*args_p, size_t *);
                *arg = unsigned_int;
                break;
            }
            case 6:             /* tu */
            case 13:            /* to */
            case 20: {          /* tx */
                ptrdiff_t *arg = va_arg(*args_p, ptrdiff_t *);
                *arg = unsigned_int;
                break;
            }
            case 7:             /* u */
            case 14:            /* o */
            case 21: {          /* x */
                unsigned *arg = va_arg(*args_p, unsigned *);
                *arg = unsigned_int;
            }
        }
    /* conversion_length characters have been consumed from format. */
    return conversion_length;
}


static int _2p_unsigned_int(char **input_p, const char *format, void **args_p, Modifiers *modifiers_p) {
    int conversion = 0;
    int conversion_length = 3;
    unsigned long long unsigned_int;
    int outcome = _p_unsigned_int(input_p, format, &conversion, &conversion_length, &unsigned_int);
    /* If outcome is 0 then the conversion letter is not d associated with z and it is
     * neither u, o, nor x, or it is u, o or x associated with an incorrect size specifier,
     * or it is u, o or x associated with j.
     * If outcome is -1 then the input is not appropriate. */
    if (outcome != 1)
        return outcome;
    if (constraint_not_satisfied(unsigned_int, modifiers_p))
        return -1;
    if (modifiers_p -> store)
        switch (conversion) {
            case 0:             /* llu */
            case 8:             /* llo */
            case 15:            /* llx */                
                *(unsigned long long *)*args_p = unsigned_int;
                break;
            case 1:             /* hhu */
            case 9:             /* hho */
            case 16:            /* hhx */
                *(unsigned char *)*args_p = unsigned_int;
                break;
            case 2:             /* lu */
            case 10:            /* lo */
            case 17:            /* lx */
                *(unsigned long *)*args_p = unsigned_int;
                break;
            case 3:             /* hu */
            case 11:            /* ho */
            case 18:            /* hx */
                *(unsigned short *)*args_p = unsigned_int;
                break;
            /* We are more stringent than fscanf, as we do not accept input of type
             * size_t to be negative. */
            case 4:             /* zd */
            case 5:             /* zu */
            case 12:            /* zo */
            case 19:            /* zx */
                *(size_t *)*args_p = unsigned_int;
                break;
            case 6:             /* tu */
            case 13:            /* to */
            case 20:            /* tx */
                *(ptrdiff_t *)*args_p = unsigned_int;
                break;
            case 7:             /* u */
            case 14:            /* o */
            case 21:            /* x */
                *(unsigned *)*args_p = unsigned_int;
        }
    /* conversion_length characters have been consumed from format. */
    return conversion_length;
}


static int _p_unsigned_int(char **input_p, const char *format, int *conversion_p, int *conversion_length_p, unsigned long long *unsigned_int_p) {
    if (!strncmp(format, "llu", *conversion_length_p) ||
        ++*conversion_p && !strncmp(format, "hhu", *conversion_length_p) ||
        ++*conversion_p && !strncmp(format, "lu", --*conversion_length_p) ||
        ++*conversion_p && !strncmp(format, "hu", *conversion_length_p) ||
        ++*conversion_p && !strncmp(format, "zd", *conversion_length_p) ||
        ++*conversion_p && !strncmp(format, "zu", *conversion_length_p) ||
        ++*conversion_p && !strncmp(format, "tu", *conversion_length_p) ||
        ++*conversion_p && !strncmp(format, "u", --*conversion_length_p)) {
        /* We are more stringent than fscanf, as we do not accept negative input. */
        if (**input_p == '-')
            return bad_input(*input_p);
        *unsigned_int_p = strtoull(*input_p, input_p, 10);
    }
    /* First reinitialize *conversion_length_p to 3. */
    else if ((*conversion_length_p = 3) &&
             (++*conversion_p && !strncmp(format, "llo", *conversion_length_p) ||
              ++*conversion_p && !strncmp(format, "hho", *conversion_length_p) ||
              ++*conversion_p && !strncmp(format, "lo", --*conversion_length_p) ||
              ++*conversion_p && !strncmp(format, "ho", *conversion_length_p) ||
              ++*conversion_p && !strncmp(format, "zo", *conversion_length_p) ||
              ++*conversion_p && !strncmp(format, "to", *conversion_length_p) ||
              ++*conversion_p && !strncmp(format, "o", --*conversion_length_p))) {
        /* We are more stringent than fscanf, as we do not accept negative input. */
        if (**input_p == '-')
            return bad_input(*input_p);
        *unsigned_int_p = strtoull(*input_p, input_p, 8);
    }
    /* First reinitialize *conversion_length_p to 3. */
    else if ((*conversion_length_p = 3) &&
             (++*conversion_p && !strncmp(format, "llx", *conversion_length_p) ||
              ++*conversion_p && !strncmp(format, "hhx", *conversion_length_p) ||
              ++*conversion_p && !strncmp(format, "lx", --*conversion_length_p) ||
              ++*conversion_p && !strncmp(format, "hx", *conversion_length_p) ||
              ++*conversion_p && !strncmp(format, "zx", *conversion_length_p) ||
              ++*conversion_p && !strncmp(format, "tx", *conversion_length_p) ||
              ++*conversion_p && !strncmp(format, "x", --*conversion_length_p))) {
        /* We are more stringent than fscanf, as we do not accept negative input. */
        if (**input_p == '-')
            return bad_input(*input_p);
        *unsigned_int_p = strtoull(*input_p, input_p, 16);
    }
    /* First reinitialize *conversion_length_p to 2. */
    else if ((*conversion_length_p = 2) &&
             ++*conversion_p && !strncmp(format, "zi", 2)) {
        /* We are more stringent than fscanf, as we do not accept negative input. */
        if (**input_p == '-')
            return bad_input(*input_p);
        *unsigned_int_p = strtoull(*input_p, input_p, 0);
    }
    else
        return 0;
    if (errno == EINVAL)
        return bad_input(*input_p);
    if (errno == ERANGE)
        return input_too_large();
    switch (*conversion_p) {
        case 1:                 /* hhu */
        case 9:                 /* hho */
        case 16:                /* hhx */
            if (*unsigned_int_p > UCHAR_MAX)
                return input_too_large();
            break;
        case 2:                 /* lu */
        case 10:                /* lo */
        case 17:                /* lx */
            if (*unsigned_int_p > ULONG_MAX)
                return input_too_large();
            break;
        case 3:                 /* hu */
        case 11:                /* ho */
        case 18:                /* hx */
            if (*unsigned_int_p > USHRT_MAX)
                return input_too_large();
            break;
        case 4:                 /* zd */
        case 5:                 /* zu */
        case 12:                /* zo */
        case 19:                /* zx */
            if (*unsigned_int_p > SIZE_MAX)
                return input_too_large();
            break;
        case 6:                 /* tu */
        case 13:                /* to */
        case 20:                /* tx */
            if (*unsigned_int_p > PTRDIFF_MAX)
                return input_too_large();
            break;
        case 7:                 /* u */
        case 14:                /* o */
        case 21:                /* x */
            if (*unsigned_int_p > UINT_MAX)
                return input_too_large();
    }
    return 1;
}


static int _1p_uintmax(char **input_p, const char *format, va_list *args_p, Modifiers *modifiers_p) {
    uintmax_t uintmax_t_int;
    int outcome = _p_uintmax(input_p, format, &uintmax_t_int);
    /* If outcome is 0 then the conversion is neither ju, jo nor jx.
     * If outcome is -1 then the input is not appropriate. */
    if (outcome != 1)
        return outcome;
    if (constraint_not_satisfied(uintmax_t_int, modifiers_p))
        return -1;
    if (modifiers_p -> store) {
        uintmax_t *arg = va_arg(*args_p, uintmax_t *);
        *arg = uintmax_t_int;
    }
    /* Two characters have been consumed from format. */
    return 2;
}


static int _2p_uintmax(char **input_p, const char *format, void **args_p, Modifiers *modifiers_p) {
    uintmax_t uintmax_t_int;
    int outcome = _p_uintmax(input_p, format, &uintmax_t_int);
    /* If outcome is 0 then the conversion is neither ju, jo nor jx.
     * If outcome is -1 then the input is not appropriate. */
    if (outcome != 1)
        return outcome;
    if (constraint_not_satisfied(uintmax_t_int, modifiers_p))
        return -1;
    if (modifiers_p -> store)
        *(uintmax_t *)*args_p = uintmax_t_int;
    /* Two characters have been consumed from format. */
    return 2;
}


static int _p_uintmax(char **input_p, const char *format, uintmax_t *uintmax_t_int_p) {
    if (!strncmp(format, "ju", 2)) {
        /* We are more stringent than fscanf, as we do not accept negative input. */
        if (**input_p == '-')
            return bad_input(*input_p);
        *uintmax_t_int_p = strtoumax(*input_p, input_p, 10);
    }
    else if (!strncmp(format, "jo", 2)) {
        /* We are more stringent than fscanf, as we do not accept negative input. */
        if (**input_p == '-')
            return bad_input(*input_p);
        *uintmax_t_int_p = strtoumax(*input_p, input_p, 8);
    }
    else if (!strncmp(format, "jx", 2)) {
        /* We are more stringent than fscanf, as we do not accept negative input. */
        if (**input_p == '-')
            return bad_input(*input_p);
        *uintmax_t_int_p = strtoumax(*input_p, input_p, 16);
    }
    else
        return 0;
    if (errno == EINVAL)
        return bad_input(*input_p);
    if (errno == ERANGE)
        return input_too_large();
    return 1;
}


static int _1p_float(char **input_p, const char *format, va_list *args_p, Modifiers *modifiers_p) {
    float floating_point;
    int outcome = _p_float(input_p, format, &floating_point);
    /* If outcome is 0 then the conversion is neither a, f, e nor g.
     * If outcome is -1 then the input is not appropriate. */
    if (outcome != 1)
        return outcome;
    if (constraint_not_satisfied(floating_point, modifiers_p))
        return -1;
    if (modifiers_p -> store) {
        float *arg = va_arg(*args_p, float *);
        *arg = floating_point;
    }
    /* One character has been consumed from format. */
    return 1;
}


static int _2p_float(char **input_p, const char *format, void **args_p, Modifiers *modifiers_p) {
    float floating_point;
    int outcome = _p_float(input_p, format, &floating_point);
    /* If outcome is 0 then the conversion is neither a, f, e nor g.
     * If outcome is -1 then the input is not appropriate. */
    if (outcome != 1)
        return outcome;
    if (constraint_not_satisfied(floating_point, modifiers_p))
        return -1;
    if (modifiers_p -> store)
        *(float *)*args_p = floating_point;
    return 1;
}


static int _p_float(char **input_p, const char *format, float *floating_point_p) {
    if (*format == 'a' || *format == 'f' || *format == 'e' || *format == 'g') {       
        char *input = *input_p;
        *floating_point_p = strtof(*input_p, input_p);
        if (*input_p == input)
            return bad_input(*input_p);
    }
    else
        return 0;
    if (errno == ERANGE) {
        if (!*floating_point_p)
            return input_too_small();
        return input_too_large();
    }
    /* One character has been consumed from format. */
    return 1;
}


static int _1p_double(char **input_p, const char *format, va_list *args_p, Modifiers *modifiers_p) {
    double floating_point;
    int outcome = _p_double(input_p, format, &floating_point);
    /* If outcome is 0 then the conversion is neither la, lf, le nor lg.
     * If outcome is -1 then the input is not appropriate. */
    if (outcome != 1)
        return outcome;
    if (constraint_not_satisfied(floating_point, modifiers_p))
        return -1;
    if (modifiers_p -> store) {
        double *arg = va_arg(*args_p, double *);
        *arg = floating_point;
    }
    /* Two characters have been consumed from format. */
    return 2;
}


static int _2p_double(char **input_p, const char *format, void **args_p, Modifiers *modifiers_p) {
    double floating_point;
    int outcome = _p_double(input_p, format, &floating_point);
    /* If outcome is 0 then the conversion is neither la, lf, le nor lg.
     * If outcome is -1 then the input is not appropriate. */
    if (outcome != 1)
        return outcome;
    if (constraint_not_satisfied(floating_point, modifiers_p))
        return -1;
    if (modifiers_p -> store)
        *(double *)*args_p = floating_point;
    /* Two characters have been consumed from format. */
    return 2;
}


static int _p_double(char **input_p, const char *format, double *floating_point_p) {
    if (!strncmp(format, "la", 2) ||
        !strncmp(format, "lf", 2) ||
        !strncmp(format, "le", 2) ||
        !strncmp(format, "lg", 2)) {
        char *input = *input_p;
        *floating_point_p = strtod(*input_p, input_p);
        if (*input_p == input)
            return bad_input(*input_p);
    }
    else
        return 0;
    if (errno == ERANGE) {
        if (!*floating_point_p)
            return input_too_small();
        return input_too_large();
    }
    return 1;
}


static int _1p_long_double(char **input_p, const char *format, va_list *args_p, Modifiers *modifiers_p) {
    long double floating_point;
    int outcome = _p_long_double(input_p, format, &floating_point);
    /* If outcome is 0 then the conversion is neither La, Lf, Le nor Lg.
     * If outcome is -1 then the input is not appropriate. */
    if (outcome != 1)
        return outcome;
    if (constraint_not_satisfied(floating_point, modifiers_p))
        return -1;
    if (modifiers_p -> store) {
        long double *arg = va_arg(*args_p, long double *);
        *arg = floating_point;
    }
    /* Two characters have been consumed from format. */
    return 2;
}


static int _2p_long_double(char **input_p, const char *format, void **args_p, Modifiers *modifiers_p) {
    long double floating_point;
    int outcome = _p_long_double(input_p, format, &floating_point);
    /* If outcome is 0 then the conversion is neither La, Lf, Le nor Lg.
     * If outcome is -1 then the input is not appropriate. */
    if (outcome != 1)
        return outcome;
    if (constraint_not_satisfied(floating_point, modifiers_p))
        return -1;
    if (modifiers_p -> store)
    *(long double *)*args_p = floating_point;
    /* Two characters have been consumed from format. */
    return 2;
}


static int _p_long_double(char **input_p, const char *format, long double *floating_point_p) {
    if(!strncmp(format, "La", 2) ||
       !strncmp(format, "Lf", 2) ||
       !strncmp(format, "Le", 2) ||
       !strncmp(format, "Lg", 2)) {
        char *input = *input_p;
        *floating_point_p = strtold(*input_p, input_p);
        if (*input_p == input)
            return bad_input(*input_p);
    }
    else
        return 0;
    if (errno == ERANGE) {
        if (!*floating_point_p)
            return input_too_small();
        return input_too_large();
    }
    return 1;
}


static int collect_input(FILE *restrict file, char **input_p) {
    *input_p = malloc(sizeof(char));    
    if (!*input_p) {
        fprintf(stderr, "The input could not be buffered.\n");
        return EXIT_FAILURE;
    }    
    int size = 0;    
    int input_buffer_size = 1;
    int c;
    do {
        /* Multiply buffer size by 2 everytime it gets full. */
        if (size == input_buffer_size) {
            input_buffer_size *= 2;
            *input_p = realloc(*input_p, input_buffer_size * sizeof(char));
            if (!*input_p) {
                fprintf(stderr, "The input could not be buffered.\n");
                return EXIT_FAILURE;
            }
        }
    } while ((c = fgetc(file)) != EOF && (*(*input_p + size++) = c));
    *(*input_p + size) = '\0';
    if (size && *(*input_p + --size) != '\n') {
        free(*input_p);
        fprintf(stderr, "Control D should follow carriage return.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


static bool nonspace_left(char *input_left, char *all_input) {
    while (isspace(*input_left))
        ++input_left;
    if (*input_left) {
        free(all_input);
        fprintf(stderr, "Too much input.\n");
        return true;
    }
    return false;
}


static void remove_leading_spaces(const char **format_p, char **input_p) {
    while (isspace(**format_p))
        ++*format_p;
    while (isspace(**input_p))
        ++*input_p;
}


static int process_modifiers(const char *format, Modifiers *modifiers_p) {
    int offset = 1;
    if (*(format + offset) == '*') {
        modifiers_p -> store = false;
        ++offset;
    }            
    if (isdigit(*(format + offset))) {
        modifiers_p -> max_field_width = *(format + offset++) - '0';
        while (isdigit(*(format + offset)))
            modifiers_p -> max_field_width =
                modifiers_p -> max_field_width * 10 + *(format + offset++) - '0';
        if (*(format + offset) == 'p')
            modifiers_p -> max_field_width = 0;
    }
    const char *format_c1 = format + offset;
    while (true) {
        char *format_c2;
        if (!strncmp(format_c1, "<=", 2)) {
            format_c1 += 2;
            long double floating_point = strtold(format_c1, &format_c2);
            if (format_c1 == format_c2)
                return bad_format();
            format_c1 = format_c2;
            if (modifiers_p -> le_request)
                modifiers_p -> le_value = fminl(modifiers_p -> le_value, floating_point);
            else {
                modifiers_p -> le_request = true;
                modifiers_p -> le_value = floating_point;
            }
            continue;
        }
        if (!strncmp(format_c1, ">=", 2)) {
            format_c1 += 2;
            long double floating_point = strtold(format_c1, &format_c2);
            if (format_c1 == format_c2)
                return bad_format();
            format_c1 = format_c2;
            if (modifiers_p -> ge_request)
                modifiers_p -> ge_value = fmaxl(modifiers_p -> ge_value, floating_point);
            else {
                modifiers_p -> ge_request = true;
                modifiers_p -> ge_value = floating_point;
            }
            continue;
        }
        if (!strncmp(format_c1, "!=", 2)) {
            format_c1 += 2;
            long double floating_point = strtold(format_c1, &format_c2);
            if (format_c1 == format_c2)
                return bad_format();
            format_c1 = format_c2;
            Neq_constraint *neq_constraint = malloc(sizeof(Neq_constraint));
            neq_constraint -> neq_value = floating_point;
            neq_constraint -> neq_values = modifiers_p -> neq_values;
            modifiers_p -> neq_values = neq_constraint;
            continue;
        }
        break;
    }
    return format_c1 - format;
}


static int constraint_not_satisfied(long double floating_point, Modifiers *modifiers_p) {
    if (modifiers_p -> le_request && floating_point > modifiers_p -> le_value) {
        fprintf(stderr, "Last value processed larger than <= constraint.\n");
        return -1;
    }
    if (modifiers_p -> ge_request && floating_point < modifiers_p -> ge_value) {
        fprintf(stderr, "Last value processed smaller than >= constraint.\n");
        return -1;
    }
    while (modifiers_p -> neq_values) {
        if (floating_point == modifiers_p -> neq_values -> neq_value) {
            fprintf(stderr, "Last value processed equal to != constraint.\n");
            return -1;
        }
        modifiers_p -> neq_values = modifiers_p -> neq_values -> neq_values;
    }
    return 0;
}


static bool closing_bracket(const char *format, int *c_bracket_p, bool *complement_p) {
    char c;
    while ((c = *(format + ++*c_bracket_p)) &&
           (c != ']' || *c_bracket_p == 1) || (*(format + 1) == '^' && *c_bracket_p == 2))
        ;
    if (!c || *c_bracket_p == 1 || (*(format + 1) == '^' && *c_bracket_p == 2))
        return bad_format();
    if (*(format + 1) == '^')
        *complement_p = true;
    return true;
}


static void limit_input(char **input_p, char *char_to_restore, int max_field_width) {
    int offset = 0;
    while (offset < max_field_width && *(*input_p + offset))
        ++offset;
    if (offset && offset == max_field_width) {
        *char_to_restore = *(*input_p + offset);
        *(*input_p + offset) = '\0';
    }
}


static int input_too_large(void) {
    fprintf(stderr, "Norm of last value processed in input is too large.\n");
    return -1;
}


static int input_too_small(void) {
    fprintf(stderr, "Last value processed in input is too close to 0.\n");
    return -1;
}


static int bad_format(void) {
    fprintf(stderr, "Error in format string.\n");
    return -1;
}


static int bad_input(char *input) {
    while (isspace(*input))
        ++input;
    if (!*input)
        fprintf(stderr, "Not enough input.\n");
    else
        fprintf(stderr, "Input does not match format string.\n");
    return -1;
}
