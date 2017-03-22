
##my tiny c compiler

master-branch

# Link
- [ git command ] ( # git command)
- [ parser ] ( # parser)
- [ function ] ( # function )


## git command

git checkout -b <new-branch-name>
git checkout <move-branch>
git merge <commit-pos>

dev-branch
master-branch

# parser
1.Variable declaration
2.Function declaration
3.If Statement declaration

<http://home.a00.itscom.net/hatada/lp2016/chap10/parser01.html>

## compiler works
1.lexer analysis  
2.parsing syntax analysis   
3.semantic analysis   
4.optimization    
5.code generation  

## BNF defination
f_digit::=("1"|"2"|"3"|"4"|"5"|6"|"7"|"8"|9")  
digit::=("0"|"1"|"2"|"3"|"4"|"5"|6"|"7"|"8"|9")  
sign::=("+"|"-")  
operator::=("+"|"-"|"*"|"/"|"%")
digits::=`<f_digit>` | `<f_digit>` `<digit>`| `<f_digit>` `<digit>` `<digits>`    
signed::=`<digits>`|`<signd>` `<digits>`  
value::=`<signed>` | `<signed>` `<digits>`  
exp::=`<value>`|`<value>` `<ope>` `<exp>` | "(" `<exp>` ")"  

| Operatimon <br> Priority |
|--------|
|  *  /  |
|  +  -  |


