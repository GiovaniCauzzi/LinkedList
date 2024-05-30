cls
del out.exe
echo COMPILANDO CODIGO
@REM gcc ./src/main.c -o ./out -lm -g
gcc ./src/* -o ./out -lm -g
@REM timeout -t 2
out