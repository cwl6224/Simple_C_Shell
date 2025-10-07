Just a simple shell. compile with Linux/Unix using c for example. gcc mysh.c -o mysh.exe -ansi

Commands available: 
    echo: Repeats the message entered. if no message is given print carriage return. called with echo()
        -n: echo without carraige return
    PS1: Change shell prompt to any character or string of characters .called with ps1()
    cat: Print out contents of file to shell. can do multiple files. called with cat()
    cp: Copes file from source to dest. Will create dest file if needed. called with copy()
    rm: Deletes file. Can do multiple. called with delete()
    mkdir: Makes directory file. Can do multiple. called with makeDir()
    rmdir: Removes directory file.  Can do multiple. called with removeDir()
    exit: Exits the shell. Called with closeShell()

Was a class assignment for CS390 Intro to Unix/Linux
