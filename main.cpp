#include <iostream>
#include<stdio.h>//文件
#include <stdlib.h>//exit(0)
#include <string.h>


using namespace std;
void filterProject(char r[],int fProject)//过滤程序中的注释字符
{
    char tempString[10000];
    int count = 0;
     for (int i = 0; i <= fProject; i++)
     {
         if (r[i] == '/'&&r[i + 1] == '/')
         {//若为单行注释“//”,则去除注释后面的东西，直至遇到回车换行
             while (r[i] != '\n')
             {
                i++;//向后扫描
             }
         }
         if (r[i] == '/'&&r[i + 1] == '*')
         {//若为多行注释“/* 。。。*/”则去除该内容
             i += 2;
             while (r[i] != '*' || r[i + 1] != '/')
             {
                i++;//继续扫描
                if (r[i] == '@')
                 {
                    printf("注释出错，没有找到 */，程序结束！！！\n");
                     exit(0);
                 }
             }
             i += 2;//跨过“*/”
         }
         if (r[i] != '\n'&&r[i] != '\t'&&r[i] != '\v'&&r[i] != '\r')//若出现无用字符，则过滤；否则加载
         {
             tempString[count++] = r[i];
         }
     }
     tempString[count] = '\0';
     strcpy(r, tempString);//产生净化之后的源程
}
int main()
{
    char resourceProject[10000];
    int fProject=0;
    int syn = -1;
    FILE *fp, *fp1;
     if ((fp = fopen("F:\\h.txt", "r")) == NULL)//打开源程序
     {
         cout << "can't open this file";
         exit(0);
     }
     resourceProject[fProject]=fgetc(fp);
     while(resourceProject[fProject]!='@')
     {
        fProject++;
        resourceProject[fProject]=fgetc(fp);
     }
     resourceProject[fProject]='\0';
     fclose(fp);
     cout <<endl<<"源程序为:" << endl;
     cout<<resourceProject<<endl;

    //清除程序中的注释
    filterProject(resourceProject,fProject);

    cout <<endl<<"过滤后的程序为:"<<endl;
     cout<<resourceProject<<endl;
     if ((fp = fopen("F:\\b.txt", "w+")) == NULL)
    {//打开源程序
         cout << "can't open this file";
         exit(0);
     }
    return 0;
}
