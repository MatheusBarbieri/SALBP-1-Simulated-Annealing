param N;
/* number of Taks */

param S;
/* contain Stations */

param c;
/* station cycle time */

param p{1..N, 1..N} binary;
/* precedence of taks */

param t{1..N};
/* time of each task */

var x{1..S, 1..N} binary;
/* station s performed task i */

var y{1..S} binary;
/* stations in use */

minimize m: sum{s in 1..S} y[s];

s.t. task_allocation{i in 1..N}: sum{s in 1..S} x[s,i] = 1;
s.t. station_use{s in 1..S}: sum{i in 1..N} x[s,i] <= y[s] * 10000;
s.t. cycle_time{s in 1..S}: sum{i in 1..N} x[s,i] * t[i] <= c;
s.t. precedence{i in 1..N, j in 1..N, b in 1..S}: x[b,j] * p[i,j] <= sum{s in b..S} x[s,i];


solve;

# Report / Result Section (Optional)
printf '\n#################################\n';
printf 'SALBP-1 / LP Model Result\n';
printf '\n';
printf 'm = %d\n', m;
printf '\nN\\S ';
for {s in 1..S} {
    printf '%3d', s;
}
printf '\n';
for {i in 1..N} {
    printf ' %2d ', i;
    for {s in 1..S} {
        printf '%3d', x[s,i];
    }
    printf '\n';
}
