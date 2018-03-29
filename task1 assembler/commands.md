Стандартные регистры.
IP # Instruction Pointer
SP # Stack Pointer
BP # Base Pointer. Не используется.
CFL # Conditional flag

Команды.
VAR name numerical_value # Создать целочисленную переменную
STR name "value" # Создать строковую переменную.
READ var # Считать число из stdin в переменную с меткой var
WRITE var # Вывести числовую переменную var в stdout.
WRITESTR str # Вывести строковую переменную str в stdout.
STOP # Прекратить выполнение программы и вывести на экран сообщение о прекращении выполнения.
M2M var1 var2 # memory to memory # Записать значение var1 в var2.
C2M const var # constant to memory # Записать целочисленную константу const в var
EQ var1 var2 # Сравнить var1 и var2 и записать результат в регистр сравнения.
IF label # Если результат последнего EQ истинен, продолжать выполнение, иначе прыгнуть на метку label.
ADD var1 var2 # Сложить var1 и var2 и записать результат в var1.
PUSH var # Положить var на вершину стека.
POP var # Достать из вершины стека в переменную var.
CALL fun # Вызвать функцию fun: положить адрес возврата в стек и перейти к функции. Возвращаться, записывая адрес возврата в IP руками.
