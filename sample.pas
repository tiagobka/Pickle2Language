/*RON MAK IS THE BEST PROFESSOR IN THE WORLD WE LOVE HIM WITH ALL OUR HEART*/
PROGRAM sample;
VAR
    i, j, k : integer;
    alpha, beta5x : real;
    
BEGIN
    i := 32;
    PRINTF('i = %d\n', i);
    
    
    j := i;
    i := -2 + 3*j;
    PRINTF('i = %d, j = %d\n', i, j);

    PRINTF ('Testing precedence 4+2*(3+1)-2 expect 10 value:%d\n', 4+2*(3+1)-2);
    PRINTF ('Testing precedence 4/(1+1)-2 expect 0 value:%d\n', 4/(1+1)-2);
    
    alpha := 9.3;
    beta5x := alpha;
    beta5x := alpha/3.7 - alpha*2.88;
    beta5x := 8.45*(alpha + 9.12);
    PRINTF('i = %d, j = %d, alpha = %6.2f, betax = %6.2f\n', i, j, alpha, beta5x);

    IS (1 == 2) ? {PRINTF('IS');} ISNT {PRINTF('ISNT');};
    IS (1 == 2) ? {PRINTF('IS');};
    IS (1 != 2) ? {PRINTF('IS');};

    k := 9;
    KEEP {

	PRINTF('k= %d\n', k);
	k := k - 1;
     }GOING (k > 0)
END.
