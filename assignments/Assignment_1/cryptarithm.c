/*
 * cryptarithm.c
 *
 *  Created on: Apr 6, 2014
 *      Author: xwux288
 */

// Try to find the value of equiation
// cross + roads = danger
int main(void) {
    for (int i = 23044; i < 98767; i++) {
        int digitCross[10] = { 0 };

        int cross = i;
        int c_c = cross / 10000;
        int c_r = cross % 10000 / 1000;
        int c_o = cross % 10000 % 1000 / 100;
        int c_s = cross % 10000 % 1000 % 100 / 10;
        int c_s1 = cross % 10000 % 1000 % 100 % 10;

        digitCross[c_c] = 1;
        if (c_r == 0)
            continue;
        if (++digitCross[c_r] == 2)
            continue;
        if (++digitCross[c_o] == 2)
            continue;
        if (++digitCross[c_s] == 2)
            continue;
        if (c_s1 != c_s)
            continue;

        for (int j = 20213; j < 98766; j++) {
            int digitCrossRoads[10] = { 0 };
            for (int k = 0; k < 10; k++) {
                digitCrossRoads[k] = digitCross[k];
            }

            int roads = j;
            int r_r = roads / 10000;
            int r_o = roads % 10000 / 1000;
            int r_a = roads % 10000 % 1000 / 100;
            int r_d = roads % 10000 % 1000 % 100 / 10;
            int r_s = roads % 10000 % 1000 % 100 % 10;

            if (c_r != r_r)
                continue;
            if (c_o != r_o)
                continue;
            if (++digitCrossRoads[r_a] == 2)
                continue;
            if (r_d == 0 || r_d != 1)
                continue;
            if (++digitCrossRoads[r_d] == 2)
                continue;
            if (c_s != r_s)
                continue;

            // Compute danger
            int danger = roads + cross;
            if (danger < 99999)
                continue;

            int d_d = danger / 100000;
            int d_a = danger % 100000 / 10000;
            int d_n = danger % 100000 % 10000 / 1000;
            int d_g = danger % 100000 % 10000 % 1000 / 100;
            int d_e = danger % 100000 % 10000 % 1000 % 100 / 10;
            int d_r = danger % 100000 % 10000 % 1000 % 100 % 10;
            int digitDanger[10] = { 0 };
            for (int t = 0; t < 10; t++)
                digitDanger[t] = digitCrossRoads[t];

            if (r_d != d_d || d_d == 0)
                continue;
            if (r_a != d_a)
                continue;
            if (++digitDanger[d_n] == 2)
                continue;
            if (++digitDanger[d_g] == 2)
                continue;
            if (++digitDanger[d_e] == 2)
                continue;
            if (c_r != r_r || c_r != d_r || r_r != d_r)
                continue;

            printf("cross = %d, roads = %d and danger = %d is a solution.\n",
                    cross, roads, danger);
        }

    }
    return EXIT_SUCCESS;
}
