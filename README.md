# Simple-LL1-parser
## A Simple LL1 parser in C++  
Calculates the first and follow for the non-terminals and creates the parsing table. You can also parse strings to check if they are accepted by the LL1 parser. 
Avoid spaces while entering the grammar, use '#' for epsilon and use a single character to represent each entity.  
The order of the input for the production does not matter.  
(This code might not work properly for left-recursive or un-factored grammars, but you are free to try them out.)  

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
