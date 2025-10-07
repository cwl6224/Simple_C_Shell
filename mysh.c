
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*gcc mysh.c -o mysh.exe -ansi*/

#define MAX 2000


/* 
Program: My Shell

Commands:
    echo: Repeats the message entered. if no message is given print carriage return. called with echo()
        -n: echo without carraige return
    PS1: Change shell prompt to any character or string of characters .called with ps1()
    cat: Print out contents of file to shell. can do multiple files. called with cat()
    cp: Copes file from source to dest. Will create dest file if needed. called with copy()
    rm: Deletes file. Can do multiple. called with delete()
    mkdir: Makes directory file. Can do multiple. called with makeDir()
    rmdir: Removes directory file.  Can do multiple. called with removeDir()
    exit: Exits the shell. Called with closeShell()
*/


void echo(char **args)
{
    int i;
    char *found;
    char *tag = "-n";
    if(args[1]==0)
    {
        printf("\n");
        return;
    }
    if (strcmp(args[1],tag)==0)
    {
        if(args[2]!=0)
        {
            for(i = 2; args[i];i++)
            {
                found = strchr(args[i],'\n');
                if(found)
                {
                    args[i][strcspn(args[i],"\n")] = 0;
                }
                printf("%s ",args[i]);
             }
        }
    }
    else
    {
        for(i = 1; args[i];i++)
        {
            found = strchr(args[i],'\n');
            if(found)
            {
                args[i][strcspn(args[i],"\n")] = 0;
            }
            printf("%s ",args[i]);
        }
        printf("\n");
    }
}

void ps1(char *prompt, char **args)
{ 
    int i;
    if(args[1]==0)
    {
        printf("Usage: PS1 <new prompt>\n");
        return;
    }
    strcpy(prompt,"");
    for(i = 1; args[i];i++)
        {
         strcat(prompt,args[i]);
         if(args[i+1]!=0)
         {
            strcat(prompt," ");
         }
        }
    prompt[strcspn(prompt,"\n")] = 0;  
}

void cat(char **args)
{
    char *found;
    char buff[200];
    int i;
    FILE *file;
    if (args[1]==0)
    {
         printf("Usage: cat <filename>\n");
         return;
    }
    
    for(i=1; args[i];i++)
    {
        file = fopen(args[i], "r");
        if (file == NULL)
        {
            printf("%s: No such file in directory.\n",args[i]);
            continue;
        }
        else
        {
           while (fgets(buff,200,file))
            {
                printf("%s",buff);
            }
        }
        fclose(file);
    }
}

void closeShell(int *stat)
{
    *stat = 0;
}

void copy(char **args)
{
    char buff[200];
    int i;
    FILE *source, *dest;

    if(args[1]==0 || args[2]==0)
    {
        printf("Usage: cp <source> <destination>\n");
        return;
    }

    source = fopen(args[1],"r");
    dest = fopen(args[2],"w");
    if (source==NULL)
    {
        printf("%s: No such source file in directory.\n",args[1]);
        return;
    }
    while (fgets(buff,200,source))
    {
        fprintf(dest,"%s",buff);
    }
    fclose(source);
    fclose(dest);   
}

void delete(char **args)
{   
    int i;
    if(args[1]==0)
    {
        printf("Usage: rm <filename>\n");
    }
    for(i=1; args[i];i++)
    {
        if(remove(args[i])==0)
        {
            continue;
        }
        else
        {
            printf("%s: No such file in directory\n",args[i]);
        }
    }

}

void makeDir(char **args)
{
    int i;
    if (args[1] == 0)
    {
        printf("Usage: mkdir <directoryname>\n");
        return;
    }
    for(i=1; args[i];i++)
    {
        if (mkdir(args[i],0777)==-1)
        {
            printf("%s: Failed to create directory.\n", args[i]);
        }
        else
        {
            continue;
        }
    }
}

void removeDir(char **args)
{
    int i;
    if (args[1] == 0)
    {
        printf("Usage: rmdir <directoryname>\n");
        return;
    }
    for(i=1; args[i];i++)
    {
        if (rmdir(args[i])==0)
        {
            continue;
        }
        else
        {
           printf("%s: Error removing directory.\n",args[i]);
        }
    }
}


void tokenize(char *line,char **cmd)
{
    char *token,input[4096];
    int i;
    char *found;

    strcpy(input,line);
    token = strtok(input, " \t");
    for (i = 0; token != 0 && i < MAX; ++i)
    {
        cmd[i] = token;
        found = strchr(cmd[i],'\n');
            if(found)
            {
                cmd[i][strcspn(cmd[i],"\n")] = 0;
            }
        token = strtok(0, " \t");
    }
    cmd[i] = 0;
}

int main(int argc, char *argv[])
{
    int status = 1;
    char line[MAX];
    char *cmd[MAX];
    char prompt[100] = "$";
    
    while(status)
    {
        printf("%s ",prompt);
        fgets(line,MAX,stdin);
        tokenize(line,cmd);
        if(strcmp(cmd[0],"exit")==0)
        {
            closeShell(&status);
        }
        else if (strcmp(cmd[0],"echo") == 0)
        {
            echo(cmd);
        }
        else if (strcmp(cmd[0],"PS1") == 0)
        {
            ps1(prompt,cmd);
        }
        else if (strcmp(cmd[0],"cat")==0)
        {
            cat(cmd);
        }
        else if(strcmp(cmd[0],"cp")==0)
        {
            copy(cmd);
        }
        else if(strcmp(cmd[0],"rm")==0)
        {
            delete(cmd);
        }
        else if(strcmp(cmd[0],"mkdir")==0)
        {
            makeDir(cmd);
        }
        else if(strcmp(cmd[0],"rmdir")==0)
        {
            removeDir(cmd);
        }
        else
        {
            printf("%s: command not found\n",cmd[0]);
        }
    }
    return 0;
}