#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<iostream>
using namespace std;

void parse(char* cmd, char** args) {
	int i=0;
	int count=0;
	while(cmd[i]!='\n' && cmd[i]!='\0') {
		int j=0;
		args[count]=(char*)malloc(100*sizeof(char));
		while(cmd[i]!=' ' && cmd[i]!='\n' && cmd[i]!='\0') {
			args[count][j]=cmd[i];
			j++;
			i++;
		}
		if(j!=0){
		args[count][j]='\0';
		count++;
		}
		if(cmd[i]=='\n' || cmd[i]=='\0') break;
		i++;
	}
	args[count]=NULL;
}
int main(){
	int glb=0;
	char line[10240],cmd[128]="g++ /cpi/ic.cpp -o /cpi/a",**args,path[1024],c;
	args=(char**)malloc(10);
	FILE* fg,*fm,*fh,*fo;
	fg=fopen("/cpi/global.cpp","w+");
	fm=fopen("/cpi/main.cpp","w+");
	fh=fopen("/cpi/head.h","r");
	fo=fopen("outcode.cpp","w");
loop:

	scanf("%[^\n]%*c",line);
	if(line[0]=='`' || line[0]=='^'){
		fprintf(fg,"%s\n",line+1);
		if(line[0]=='`') glb=!glb;
	}
	else if(line[0]=='$') {
		rewind(fm);
		rewind(fg);

		c = fgetc(fh); 
    	while (c != EOF) 
	    { 
	        fputc(c, fo); 
	        c = fgetc(fh); 
	    } 
	    fputc('\n', fo);

	    c = fgetc(fg); 
    	while (c != EOF) 
	    { 
	        fputc(c, fo); 
	        c = fgetc(fg); 
	    } 

	    fputs("\n\nint main (int argc, char* argv[]) {\n\n",fo);

	    c = fgetc(fm); 
    	while (c != EOF) 
	    { 
	        fputc(c, fo); 
	        c = fgetc(fm); 
	    } 
	    fputs("\nreturn 0;\n}\n",fo);
	    fclose(fh);
		fclose(fm);
		fclose(fg);
		fclose(fo);

		if (line[1]=='$'){
			parse(line+2,args);
			execvp(args[0],args);
		}else{
			pid_t t=fork();
			if(t==0){
			strcat(cmd,line+1);
			parse(cmd,args);
			execvp("g++",args);
			}else{
				cout<<"Compiling...\n";
				wait(NULL);
				cout<<"Compiled...\n\t\tExecuting...\n";
				execlp("/cpi/a","/cpi/a",NULL);
			}
		}
	}else{
		if(glb) fprintf(fg,"%s\n",line);
		else fprintf(fm,"%s\n",line);
	}

goto loop;
	return 0;
}