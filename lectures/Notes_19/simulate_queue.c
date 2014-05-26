/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Illustrates the use of the queue ADT in modeling a real queue. *
 *              Prompts the user to input:                                     *
 *              - the average time, lambda, between two successive arrivals    *
 *                of customers joining the queue, in minutes;                  *
 *              - the average time, mu, needed to serve a customer when        *
 *                her turn comes, in minutes;                                  *
 *              - how long the simulation should be run, in hours.             *
 *              It is assumed that the interarrival time between successive    *
 *              customers and the service time for a given customer are        *
 *              modeled by exponentially distributed random variables with     *
 *              an expected value of lambda and mu, respectively.              *
 *              The first two inputs allow one to theoretically estimate:      *
 *              - the average number of customers in the queue including       *
 *                those being served;                                          *
 *              - the average number of customers in the queue waiting to be   *
 *                served;                                                      *
 *              - the average waiting time for a customer, excluding service   *
 *                time;                                                        *
 *              - the average waiting and service time for a customer.         *
 *              These estimates are computed and displayed.                    *
 *                                                                             *
 *              Then a simulation is run, with at every second, the following  *
 *              happening.                                                     *
 *              - Some customers possibly join the queue, their total number   *
 *                being randomly generated following a Poisson distribution    *
 *                with an expected value of lambda, based on the relationship  *
 *                the latter has with the exponential distribution with the    *
 *                same expected value.                                         *
 *              - The requested service time of the customers who have just    *
 *                joined the queue, if any, is randomly generated following    *
 *                an exponential distribution with an expected value of mu,    *
 *                and rounded to an integral number of seconds.                *
 *              - If somebody is being served but the remainig service time    *
 *                is 0, then that customer leaves the queue.                   *
 *              - Whether the previous case applies or nobody is being served, *
 *                if the queue is not empty then the customer at the front of  *
 *                the queue starts being served. Her requested service time    *
 *                could be 0 in which case she would immediately quit the      *
 *                queue and the process would repeat with the next customer,   *
 *                if any; otherwise what remains of the service time for this  *
 *                customer is decreased by 1.                                  *
 *              - Running sums of how long a customer had to wait before she   *
 *                could start being served, of how long it took a customer     *
 *                to wait and be fully served, and of how long the queue is    *
 *                after the customers who have just been served have left,     *
 *                including or not the customer now being served, if any, are  *
 *                kept. At the end of the simulation, these sums are divided   *
 *                by the number of seconds during which the simulation has     *
 *                been run to yield the empirical values of the entities that  *
 *                have previously been theoretically estimated.                *
 *                The total number of customers who have joined the queue      *
 *                is also displayed.                                           *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       tailored_queue.c                                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <math.h>
#include <p_io.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tailored_queue.h"

#define SIXTY 60

bool display_time(int);

int main(void) {
    srand(time(NULL));
    double average_time_between_two_arrivals;
    p_prompt("Enter the average time, in minutes, between two arrivals: ",
             "%>=0!=0lf", &average_time_between_two_arrivals);
    double average_service_time;
    p_prompt("Enter the average time, in minutes, needed to serve a customer: ",
             "%>=0!=0lf", &average_service_time);
    double traffic_intensity = average_service_time / average_time_between_two_arrivals;
    printf("Estimated average number of customers in queue including those being served: %.1f\n",
           traffic_intensity / (1 - traffic_intensity));
    printf("Estimated average number of customers in queue waiting to be served: %.1f\n",
           traffic_intensity * traffic_intensity / (1 - traffic_intensity));
    printf("Estimated average waiting time, excluding serving time:");
    display_time(average_service_time / (1 / traffic_intensity - 1) * SIXTY) ?
        putchar('\n') : printf(" instantaneous\n");
    printf("Estimated average waiting and serving time:");
    display_time(1 / (1 / average_service_time - 1 / average_time_between_two_arrivals) * SIXTY) ?
        putchar('\n') : printf(" instantaneous\n");
    
    double simulation_time;
    p_prompt("For how long, in hours, do you want to run to simulation? ",
             "%>=0!=0lf", &simulation_time);
    int simulation_limit = simulation_time * SIXTY * SIXTY;
    average_time_between_two_arrivals *= SIXTY;
    average_service_time *= SIXTY;
    Queue queue;
    initialise_queue(&queue);
    int nb_of_customers = 0;
    double cumulative_queue_length = 0;
    double cumulative_waiting_length = 0;
    /* A service time of -1 indicates that nobody is being served, which can only happen
     * if the queue is empty, possibly following the departure of the last served customer. */
    int service_time = -1;
    double cumulative_waiting_time = 0;
    double cumulative_waiting_and_serving_time = 0;
    for (int simulation_tick = 0; simulation_tick < simulation_limit; ++simulation_tick) {
        /* If rnd() randomly generates a real in [0, 1] then -exp . log(rnd()) simulates the
         * cumulative distribution of an exponentially distributed random variable with an
         * expected value of exp.
         * To simulate a Poisson distribution with an expected value of exp, it suffices to
         * keep a running sum of the values generated by the previous expression until that
         * sum becomes greater than 1; the number of terms in that sum can then be interpreted
         * as a value randomly generated from that distribution. */
        double r = 0;
        while ((r += -average_time_between_two_arrivals * log((double)rand() / RAND_MAX)) <= 1) {
            ++nb_of_customers;
            Value customer;
            customer.arrival_time = simulation_tick;
            customer.service_time = -average_service_time * log((double)rand() / RAND_MAX);
            enqueue(customer, &queue);
        }
        /* A new customer can now start being served. */
        if (service_time == -1 && !is_empty_queue(&queue)) {
            service_time = queue.pt_to_front_node->value.service_time;
            cumulative_waiting_time += simulation_tick - queue.pt_to_front_node->value.arrival_time;
        }
        /* If the customer at the front has been served, then she should now quit the queue
         * and all customers that follow her and that need no time to be served should follow
         * her (these guys have been queuing for a while just to find out that they
         * do not have an indispensible piece of information when they are about to be
         * served; surely, they are pretty pissed off when they quit the queue). */
        while (service_time == 0) {
            cumulative_waiting_and_serving_time +=
                simulation_tick - queue.pt_to_front_node->value.arrival_time;
            Value dummy;
            dequeue(&queue, &dummy);
            if (!is_empty_queue(&queue)) {
                service_time = queue.pt_to_front_node->value.service_time;
                cumulative_waiting_time += simulation_tick - queue.pt_to_front_node->value.arrival_time;
            }
            else
                service_time = -1;
        }
        cumulative_queue_length += queue_length(&queue);
        if (!is_empty_queue(&queue)) {
            --service_time;      
            cumulative_waiting_length += queue_length(&queue) - 1;
        }
    }
    if (nb_of_customers) {
        printf("Number of customers who have joinded the queue: %d\n", nb_of_customers);
        printf("Average number of customers in queue including those being served: %.1f\n",
               cumulative_queue_length / simulation_limit);
        printf("Average number of customers in queue waiting to be served: %.1f\n",
               cumulative_waiting_length / simulation_limit);
        printf("Average waiting time, excluding serving time:");
        display_time(cumulative_waiting_time / nb_of_customers) ?
            putchar('\n') : printf(" instantaneous\n");
        printf("Average waiting and serving time:");
        display_time(cumulative_waiting_and_serving_time / nb_of_customers) ?
            putchar('\n') : printf(" instantaneous\n");
    }
    else
        puts("No one has joined the queue; a very quiet day...");
    empty_queue(&queue);
    return EXIT_SUCCESS;
}

bool display_time(int time) {
    bool nonzero_time = false;
    if (time >= SIXTY * SIXTY) {
        int hours = time / (SIXTY * SIXTY);
        printf(" %d ", hours);
        hours > 1 ? printf("hours") : printf("hour");
        time %= SIXTY * SIXTY;
        nonzero_time = true;
    }
    if (time >= SIXTY) {
        int minutes = time / SIXTY;
        printf(" %d ", minutes);
        minutes > 1 ? printf("minutes") : printf("minute");
        time %= SIXTY;
        nonzero_time = true;
    }
    if (time) {
        printf(" %d ", time);
        time > 1 ? printf("seconds") : printf("second");
        nonzero_time = true;
    }
    return nonzero_time;
}
