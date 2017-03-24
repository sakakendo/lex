##my tiny c compiler

## Link
- [ parser ]( # parser)
- [ function ]( # function )

# ToDoLIst
- [ ] ソースコードの整理
	tag付け
** すぐできそう **
- [ ] calc関数を変数に対応させる
- [ ] プリプロセッサの処理の追加
** さっぱりわからん **
- [ ] parser、モジュール単位に分ける（どんなモジュールに分ければいいのかさっぱり）
- [ ] モジュールをそれぞれの関数に渡す



## compiler works
1.lexer analysis  
2.parsing syntax analysis   
3.semantic analysis   
4.optimization    
5.code generation  

# parser
1.Variable declaration  
2.Function declaration  
3.If Statement declaration  

return the attribute of lexed component
1.reserved <character>
	1.1 int,double,float,char
	1.2 if,goto,while...
2.number
	2.1 [0-9]
	2.2 '-','.'
3.symbol
	3.1 {} 	block
	3.2 []	array
	3.3	()	function
	3.4	""	string
	3.5	''	convert char to int
	3.6	+,-,*,\,%	operator

<http://home.a00.itscom.net/hatada/lp2016/chap10/parser01.html>


##BNF defination
# number  
f_digit::=("1"|"2"|"3"|"4"|"5"|6"|"7"|"8"|9")  
digit::=("0"|"1"|"2"|"3"|"4"|"5"|6"|"7"|"8"|9")  
sign::=("+"|"-")  
operator::=("+"|"-"|"*"|"/"|"%")
digits::=`<f_digit>` | `<f_digit>` `<digit>`| `<f_digit>` `<digit>` `<digits>`    
signed::=`<digits>`|`<signd>` `<digits>`  
value::=`<signed>` | `<signed>` `<digits>`  
exp::=`<value>`|`<value>` `<ope>` `<exp>` | "(" `<exp>` ")"  
# Variable declaration
TypeSpecifier VarDeclarator ";"
TypeSpecifier VarDeclarator "," VarDeclarator ";"
TypeSpecifier VarDeclarator"="init "," VarDeclarator ";"
