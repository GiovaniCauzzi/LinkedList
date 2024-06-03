cls
del out.exe
echo COMPILING...
@REM gcc ./src/main.c -o ./out -lm -g
gcc ./src/* -o ./out -lm -g
@REM timeout -t 2
out