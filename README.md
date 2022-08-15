# Interpreter
Description of Interpreter

I will introduce my own language , which is written according to C++
language. 
Interpreter can do some operations such as declaration of
variables, output ,math and logic operations and condition .

My new keywords of variables are:

int is “round”,

double/float is “comma”,

char/string is “sym”,

bool is “logic”.

Declaration:

We can declare variables , first we are writing the type of variable , the
name of variable , symbol “=”, value of variable and finally symbol “;” to show the line ends.

For example:

round num = 5 ;

comma num1 = 4.7;

sym line = “hello”;

logic a = false;

Output:

The keyword of output is “show”.  We wirte “show” then symbol “<<” (as in C++) the variable and symbol “;”
the line ends.

For example:

show << num;  ( The value of the variable will appear on the screen, in this case the value
of “num” -> 5)

show << sym; (ouput will be “hello”)

Operations:

For “round” we can do math operations such as “ + , - , * , / , % ”

For “comma” we can do math operations such as “+, - , * , / “

For “sym” we can do “ + ”

For “logic” we can do “ && , ||, > , < , ==, != , ! ”

Condition:

The keyword of condition is “cond”. After the keyword we put braces ()
and between braces we write the condition , after that we don’t put
scopes as in C++.

For example:

cond( num != num1)

//something;
