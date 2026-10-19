ch13:
$ free -m
              total        used        free      shared  buff/cache   available
Mem:           7950        1240        4810          24        1900        6420
Swap:             0           0           0

ch14:
Q1: compiled and ran ./null -> Segmentation fault (core dumped)
Q2: gdb ./null -> Program received signal SIGSEGV, Segmentation fault at *p = 10;
Q3: valgrind --leak-check=yes ./null -> Invalid write of size 4, Address 0x0 is not stack'd, malloc'd or (recently) free'd
Q4: forgot to free() -> gdb shows no error, valgrind shows "definitely lost". OS reclaims memory after process exits.
Q5: data[100] = 0 -> runs ok, but valgrind shows "Invalid write of size 4". Not correct.
Q6: print after free -> prints garbage value, valgrind shows "Invalid read of size 4".
Q7: free(data + 50) -> error: free(): invalid pointer, Aborted.
