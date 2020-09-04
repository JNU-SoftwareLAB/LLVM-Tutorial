## Structure

- Token

Memory Address (Memory Cell)

- Variable

Set of Memory Address (Variable can access memory)

## Instruction List

Instruction | Syntax | Constration
--- | --- | ---
alloca |  <result\> = alloca <type> | alloca-i ∈ [[result]]
load | <result\> = load [atomic\] <ty\>, <ty>* <pointer> | [[pointer]] ⊆ [[result]]
store | <ty\> <value\>, <ty\>* <pointer\> | [[value]] ⊆ [[pointer]]
bitcast | bitcast <ty1\> <value\> to <ty2\>| [[value]] ⊆ [[result]]
call | call <ty0\> <fnptrval\>(<ty1\> arg1, ... , <tyn> argN) | ?
getelementptr | getelementptr <ty\>, <ty\>* <ptrval\> {, [inrange] <ty\> <idx\>}*| ? 
br | | None
blockaddress | | None
indirectbr | | None
icmp | | None
ret |  | None
ptrtoint | | None
sext | | None
urem | | None
sub | | None