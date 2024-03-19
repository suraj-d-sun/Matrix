#include<stdio.h>
int main()
{
char *command="python eg1.py 10 20";
FILE *p;
char line[256];
p=popen(command,"r");
while(fgets(line,256,p))
{
printf("%s\n",line);
}
pclose(p);
printf("THE END...");
return 0;
}