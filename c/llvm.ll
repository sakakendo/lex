;hello
		@.str = private unnamed_addr constant [12 x i8] c"hello world\00", align 1
 		define i32 @main() #0 {
 		%1 = alloca i32, align 4
 		store i32 0, i32* %1, align 4
 		%2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str, i32 0, i32 0))
 			ret i32 0
 		}	
 		declare i32 @printf(i8*, ...) #1	
 	