data;

param N := 7;
param S := 7; /* nosso upper_bound... pode ser igual a N */
param c := 6;
param t :=
    1   1
    2   5
    3   4
    4   3
    5   5
    6   6
    7   5;

param p :  1  2  3  4  5  6  7 :=
         1  0  0  0  0  0  0  0
         2  1  0  0  0  0  0  0
         3  0  1  0  0  0  0  0
         4  1  0  0  0  0  0  0
         5  0  1  0  0  0  0  0
         6  0  0  0  0  1  0  0
         7  0  0  0  1  0  0  0;
