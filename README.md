# AbstractVM

AbstractVM is a machine that uses a stack to compute simple arithmetic expressions.

These arithmetic expressions are provided to the machine as basic assembly programs.
```
1 ; -------------
2 ; exemple.avm -
3 ; -------------
4
5 push int32(42)
6 push int32(33)
7
8 add
9
10 push float(44.55)
11
12 mul
13
14 push double(42.42)
15 push int32(42)
16
17 dump
18
19 pop
20
21 assert double(42.42)
22
23 exit
```
