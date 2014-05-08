#ifndef _PIO_H_
#define _PIO_H_

#include <stdbool.h>
#include <stdio.h>

int p_scanf(const char *, ...);
int p_fscanf(FILE *restrict, const char *, ...);
int p_prompt(const char *restrict, const char *, ...);
int p_guarded_prompt(bool (*)(void **), const char *restrict, const char *, void **);

#endif

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
 * p_prompt takes a string s, a format string s' and a variable list l of pointers as argumemts.
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
 * void * args[2] = {&m, &n};
 * The function guard might be defined as follows:
 * bool guard(void * args[2]) {
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
