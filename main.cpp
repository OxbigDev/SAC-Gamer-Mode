#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <io.h>
#include <fstream>

#define TASKLIST_FILE_NAME "tasklist_current.txt"
#define EXCEPTIONLIST_FILE_NAME "exceptionlist.txt"
using namespace std;


char* GetPid(char* line){
    int i=0;
    char* pid=new char;

    while(&line[i]!=" "){i++;}
    i++;
    while(&line[i]!=" "){
        pid = line;
        i++;
    }

    return pid;
};

int main() {
    int flag_kill, loop_indy=0;
    char * task_name,*exception_name,* pid,*line,*line2;
    FILE* fp,*fp2;

    system(("TASKLIST > %s", TASKLIST_FILE_NAME));

    fp = fopen(TASKLIST_FILE_NAME,"r");
    while (fscanf(fp,"%s ",line)!=EOF){
        if(loop_indy<2){loop_indy++;
            continue;}
        int i=0;
        while(&line[i]!=" "){
            task_name[i] = line[i];
            i++;
        }
        fp2 = fopen(EXCEPTIONLIST_FILE_NAME,"r");
                while(fscanf(fp2,"%s ",line2)){
                    int k=0;
                    while(&line2[k]!=" "){
                        exception_name[i]=line2[i];
                        k++;
                    }
                    if(strcmp(task_name,exception_name)){
                        flag_kill =0;
                        break;
                    }
                    flag_kill=1;
                }
                fclose(fp2);
                if (flag_kill==1){
                    pid=GetPid(line);
                    system( ("TASKKILL /f /PID %s",pid));    // This line is os specific
                }
    }
    fclose(fp);
    return 0;
}