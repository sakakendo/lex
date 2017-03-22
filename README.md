
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
# function



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

==function description==

```
calc()
input format
only one pare brackets are forgiven
calc(['(','3','*','3','-','2',')'])
```
```
def simplecalc(form):
input format
simplecalc(['3','*','3'])
simplecalc(['num','ope','num'])
```
master-branch


##compiler works
1.lexer analysis
2.parsing syntax analysis
3.semantic analysis
4.optimization
5.code generation

##BNF defination
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

==function description==

```
calc()
input format
only one pare brackets are forgiven
calc(['(','3','*','3','-','2',')'])
```
```
def simplecalc(form):
input format
simplecalc(['3','*','3'])
simplecalc(['num','ope','num'])
```
