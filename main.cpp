#include <iostream>
#include<stdio.h>//文件
#include <stdlib.h>//exit(0)
#include <string.h>
#include <ctype.h>//判断是字符还是数字的头文件


using namespace std;

 static char reserveWord[32][20] = {
      "auto", "break", "case", "char", "const", "continue",
      "default", "do", "double", "else", "enum", "extern",
      "float", "for", "goto", "if", "int", "long",
      "register", "return", "short", "signed", "sizeof", "static",
      "struct", "switch", "typedef", "union", "unsigned", "void",
      "volatile", "while"
  };

  static char operatorOrDelimiter[36][10] = {
     "+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==",
      "!=", ";", "(", ")", "^", ",", "\"", "\'", "#", "&",
      "&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{",
      "}", "\\", ".", "\?", ":", "!"
 };

  static  char IDentifierTbl[1000][50] = { "" };//标识符表

 int searchReserve(char reserveWord[][20], char s[])
  {
      for (int i = 0; i < 32; i++)
      {
          if (strcmp(reserveWord[i], s) == 0)
          {//若成功查找，则返回种别码
             return i + 1;//返回种别码
         }
     }
     return -1;//否则返回-1，代表查找不成功，即为标识符
 }

bool IsLetter(char letter)
{
     if (letter >= 'a'&&letter <= 'z' || letter >= 'A'&&letter <= 'Z'|| letter=='_')
     {
          return true;
     }
     else
     {
         return false;
     }
}
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
void Scanner(int &syn, char resourceProject[], char token[], int &pProject)
{
    int i, count = 0;//count用来做token[]的指示器，收集有用字符
    char ch;//作为判断使用
    ch = resourceProject[pProject];
    while (ch == ' ')//过滤空格，防止程序因识别不了空格而结束
       {
        pProject++;
        ch = resourceProject[pProject];
       }

       for (i = 0; i<20; i++)
       {
         token[i] = '\0';
       }

       if(IsLetter(resourceProject[pProject]))
       {
         token[count++] = resourceProject[pProject];//收集
         pProject++;//下移
         while (IsLetter(resourceProject[pProject]) || isdigit(resourceProject[pProject]))
            {
            token[count++] = resourceProject[pProject];//收集
            pProject++;//下移
            }
        token[count] = '\0';
        syn = searchReserve(reserveWord, token);//查表找到种别码
        if (syn == -1)
        {
            syn = 100;
        }
        return;
        }
         else if (isdigit(resourceProject[pProject]))
        {//首字符为数字
         while (isdigit(resourceProject[pProject]))
         {//后跟数字
             token[count++] = resourceProject[pProject];//收集
             pProject++;
         }//多读了一个字符既是下次将要开始的指针位置
        token[count] = '\0';
         syn = 99;//常数种别码
     }
           else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ';' || ch == '(' || ch == ')' || ch == '^'
         || ch == ',' || ch == '\"' || ch == '\'' || ch == '~' || ch == '#' || ch == '%' || ch == '['
         || ch == ']' || ch == '{' || ch == '}' || ch == '\\' || ch == '.' || ch == '\?' || ch == ':')
     {//若为运算符或者界符，查表得到结果
         token[0] = resourceProject[pProject];
         token[1] = '\0';//形成单字符串
         for (i = 0; i<36; i++)
         {//查运算符界符表
             if (strcmp(token, operatorOrDelimiter[i]) == 0)
             {
                syn = 33 + i;//获得种别码，使用了一点技巧，使之呈线性映射
                 break;//查到即推出
             }
         }
         pProject++;//指针下移，为下一扫描做准备
         return;
     }
     else  if (resourceProject[pProject] == '<')
     {//<,<=,<<
         pProject++;//后移，超前搜索
         if (resourceProject[pProject] == '=')
         {
             syn = 38;
         }
         else if (resourceProject[pProject] == '<')
         {//左移
             pProject--;
             syn = 58;
         }
         else
         {
             pProject--;
             syn = 37;
         }
         pProject++;//指针下移
         return;
     }
     else  if (resourceProject[pProject] == '>')
     {//>,>=,>>
         pProject++;
         if (resourceProject[pProject] == '=')
         {
             syn = 40;
         }
         else if (resourceProject[pProject] == '>')
         {
             syn = 59;
         }
         else
         {
             pProject--;
             syn = 39;
         }
         pProject++;
         return;
     }
     else  if (resourceProject[pProject] == '=')
     {//=.==
         pProject++;
         if (resourceProject[pProject] == '=')
         {
             syn = 42;
         }
         else

         {
             pProject--;
             syn = 41;
         }
         pProject++;
         return;
     }
     else  if (resourceProject[pProject] == '!')
     {//!,!=
         pProject++;
        if (resourceProject[pProject] == '=')
         {
             syn = 43;
         }
         else
         {
             syn = 68;
             pProject--;
         }
         pProject++;
         return;
     }
     else  if (resourceProject[pProject] == '&')
     {//&,&&
         pProject++;
         if (resourceProject[pProject] == '&')
         {
             syn = 53;
         }
         else
         {
             pProject--;
             syn = 52;
         }
         pProject++;
         return;
     }
     else  if (resourceProject[pProject] == '|')
     {//|,||
         pProject++;
         if (resourceProject[pProject] == '|')
         {
             syn = 55;
         }
         else
         {
             pProject--;
             syn = 54;
         }
         pProject++;
         return;
     }
     else  if (resourceProject[pProject] == '@')
     {//结束符
        syn = 0;//种别码为0
     }
    else
     {//不能被以上词法分析识别，则出错。
         printf("error：there is no exist %c \n", ch);
         exit(0);
     }

}

int main()
{
    char resourceProject[10000];
    int fProject=0;
    char token[20] = { 0 };
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
        fProject = 0;//从头开始读
     if ((fp1 = fopen("F:\\b.txt", "w+")) == NULL)
    {//打开源程序
         cout << "can't open this file";
         exit(0);
     }
     while (syn != 0)
     {
         //启动扫描
         Scanner(syn, resourceProject, token, fProject);
         if (syn == 100)
         {//标识符
             for (int i = 0; i<1000; i++)
             {//插入标识符表中
                 if (strcmp(IDentifierTbl[i], token) == 0)
                 {//已在表中
                     break;
                 }
                 if (strcmp(IDentifierTbl[i], "") == 0)
                 {//查找空间
                     strcpy(IDentifierTbl[i], token);
                     break;
                 }
             }
             printf("(标识符  ,%s)\n", token);
             fprintf(fp1, "(标识符   ,%s)\n", token);
         }
         else if (syn >= 1 && syn <= 32)
         {//保留字
             printf("(%s   ,  --)\n", reserveWord[syn - 1]);
             fprintf(fp1, "(%s   ,  --)\n", reserveWord[syn - 1]);
         }
         else if (syn == 99)
         {//const 常数
             printf("(常数   ,   %s)\n", token);
             fprintf(fp1, "(常数   ,   %s)\n", token);
         }
         else if (syn >= 33 && syn <= 68)
         {
             printf("(%s   ,   --)\n", operatorOrDelimiter[syn - 33]);
             fprintf(fp1, "(%s   ,   --)\n", operatorOrDelimiter[syn - 33]);
         }
     }
     for (int i = 0; i<100; i++)
     {//插入标识符表中
         printf("第%d个标识符：  %s\n", i + 1, IDentifierTbl[i]);
         fprintf(fp1, "第%d个标识符：  %s\n", i + 1, IDentifierTbl[i]);
     }
     fclose(fp1);
     return 0;
}
