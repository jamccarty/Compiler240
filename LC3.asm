
;  int x = 7 ;

AND R0, R0, #0
ADD R0, R0, #7
STR R0, FP, #0

;  int y = a + b ;

LDR R0, FP, #4
LDR R1, FP, #5
ADD R0, R0, R1
STR R0, FP, #-1

;  x = a + 4 ;

LDR R0, FP, #4
AND R1, R1, #0
ADD R1, R1, #4
ADD R0, R0, R1
STR R0, FP, #0

;  int t = x + b ;

LDR R0, FP, #0
LDR R1, FP, #5
ADD R0, R0, R1
STR R0, FP, #-2

;  return x + t ;

LDR R0, FP, #0
LDR R1, FP, #-2
ADD R0, R0, R1
R0, R5, #3
RET
