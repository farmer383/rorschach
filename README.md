# rorschach
dynamically modifies an ELFs hash upon each execution to evade detection

# usage
```
./rorschach

./rorschach -e elf.elf
```

poc
```
__________________________________________________________________________________________
|________________________________________|_______________________________________________|
| $ ./rorschach -e a.out                 | $ for i in $(seq 1 10); do md5sum a.out; done |
|                                        | a4e16873c09f62b1022e4f30086f30dd  a.out       |
|                                        | 8d2cfbbb2a638586639ab437d2447a62  a.out       |
|                                        | 41e6ca329f0663e8c168b4500c904692  a.out       |
|                                        | c6de92916b4b74473579cb0d83315e28  a.out       |
|                                        | f754a150525ce8d335fee27329d00dc6  a.out       |
|                                        | 4be7528e6ed82b35b51cd4a8c04506af  a.out       |
|                                        | 1b29a22e1b9004c2f23dc0886fd093ac  a.out       |
|                                        | b4ab48e12e42e489384e868094678899  a.out       |
|                                        | 9f26e2565da389539438b334e1095d4b  a.out       |
|                                        | 982c9dc477bdd10c18b925127a7f1390  a.out       |
------------------------------------------------------------------------------------------
```
