data;

param N := 21;
param S := 21; /* upper_bound */
param c := 14;
param t :=
	 1	4
	 2	3
	 3	9
	 4	5
	 5	9
	 6	4
	 7	8
	 8	7
	 9	5
	 10	1
	 11	3
	 12	1
	 13	5
	 14	3
	 15	5
	 16	3
	 17	13
	 18	5
	 19	2
	 20	3
	 21	7;

param p :  1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17  18  19  20  21  :=
		1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		2  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		3  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		4  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		5  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		6  0  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		7  0  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		8  0  0  0  0  0  1  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		9  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0
		10  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0
		11  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0
		12  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0
		13  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0
		14  0  0  0  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		15  0  0  0  0  0  0  0  0  0  1  1  1  0  0  0  0  0  0  0  0  0
		16  0  0  0  0  0  0  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0
		17  0  0  0  0  0  0  0  0  0  0  0  0  1  0  0  1  0  0  0  0  0
		18  0  0  0  0  0  0  0  0  0  0  0  0  1  0  1  0  0  0  0  0  0
		19  0  0  0  0  0  0  0  0  0  0  0  0  0  1  0  0  0  1  0  0  0
		20  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  1  0  0  0  0
		21  0  1  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0;