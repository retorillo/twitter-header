cl /EHsc decorate.cpp
SET PADH=30
SET PADV=20
figlet -w=160 Welcome to Twitter Land > file1.out
type file1.out | decorate.exe -m 1 -l %PADH% -r %PADH% -t %PADV% -b %PADV% > file2.out
type file1.out | decorate.exe -m 2 -l %PADH% -r %PADH% -t %PADV% -b %PADV% > file3.out
