cl /EHsc /Zi /Gm decorator.cpp
cl /EHsc /Zi /Gm divider.cpp
SET PADH=6
SET PADV=12
figlet -w=160 Welcome to Twitter Land > file1.txt
type file1.txt | decorator -m 1 -l %PADH% -r %PADH% -t %PADV% -b %PADV% > file2.txt
type file1.txt | decorator -m 2 -l %PADH% -r %PADH% -t %PADV% -b %PADV% > file3.txt
type file3.txt | divider -n 8 -t file3
