# Simple-LL1-parser
A Simple LL1 parser in C++
(might not work properly for left recursive/un-factored grammars)

Sample Inputs:

3
S->aAbB|bAaB|#
A->S
B->S

4
S->ACB|CbB|Ba
A->da|BC
B->g|#
C->h|#

1
A->abc|def|ghi

6
S->aBDh
B->cC
C->bC|#
D->EF
E->g|#
F->f|#

5
S->A
A->aBD
D->dD|#
B->b
C->g

3
S->AaAb|BbBa
A->#
B->#

5
E->TA
A->+TA|#
T->FB
B->xFB|#
F->(E)|i

3
S->(L)|a
L->SB
B->,SB|#
