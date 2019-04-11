#include <iostream>
#include<stdio.h>//�ļ�
#include <stdlib.h>//exit(0)
#include <string.h>
#include <ctype.h>//�ж����ַ��������ֵ�ͷ�ļ�


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

  static  char IDentifierTbl[1000][50] = { "" };//��ʶ����

 int searchReserve(char reserveWord[][20], char s[])
  {
      for (int i = 0; i < 32; i++)
      {
          if (strcmp(reserveWord[i], s) == 0)
          {//���ɹ����ң��򷵻��ֱ���
             return i + 1;//�����ֱ���
         }
     }
     return -1;//���򷵻�-1��������Ҳ��ɹ�����Ϊ��ʶ��
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
void filterProject(char r[],int fProject)//���˳����е�ע���ַ�
{
    char tempString[10000];
    int count = 0;
     for (int i = 0; i <= fProject; i++)
     {
         if (r[i] == '/'&&r[i + 1] == '/')
         {//��Ϊ����ע�͡�//��,��ȥ��ע�ͺ���Ķ�����ֱ�������س�����
             while (r[i] != '\n')
             {
                i++;//���ɨ��
             }
         }
         if (r[i] == '/'&&r[i + 1] == '*')
         {//��Ϊ����ע�͡�/* ������*/����ȥ��������
             i += 2;
             while (r[i] != '*' || r[i + 1] != '/')
             {
                i++;//����ɨ��
                if (r[i] == '@')
                 {
                    printf("ע�ͳ���û���ҵ� */���������������\n");
                     exit(0);
                 }
             }
             i += 2;//�����*/��
         }
         if (r[i] != '\n'&&r[i] != '\t'&&r[i] != '\v'&&r[i] != '\r')//�����������ַ�������ˣ��������
         {
             tempString[count++] = r[i];
         }
     }
     tempString[count] = '\0';
     strcpy(r, tempString);//��������֮���Դ��
}
void Scanner(int &syn, char resourceProject[], char token[], int &pProject)
{
    int i, count = 0;//count������token[]��ָʾ�����ռ������ַ�
    char ch;//��Ϊ�ж�ʹ��
    ch = resourceProject[pProject];
    while (ch == ' ')//���˿ո񣬷�ֹ������ʶ���˿ո������
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
         token[count++] = resourceProject[pProject];//�ռ�
         pProject++;//����
         while (IsLetter(resourceProject[pProject]) || isdigit(resourceProject[pProject]))
            {
            token[count++] = resourceProject[pProject];//�ռ�
            pProject++;//����
            }
        token[count] = '\0';
        syn = searchReserve(reserveWord, token);//����ҵ��ֱ���
        if (syn == -1)
        {
            syn = 100;
        }
        return;
        }
         else if (isdigit(resourceProject[pProject]))
        {//���ַ�Ϊ����
         while (isdigit(resourceProject[pProject]))
         {//�������
             token[count++] = resourceProject[pProject];//�ռ�
             pProject++;
         }//�����һ���ַ������´ν�Ҫ��ʼ��ָ��λ��
        token[count] = '\0';
         syn = 99;//�����ֱ���
     }
           else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ';' || ch == '(' || ch == ')' || ch == '^'
         || ch == ',' || ch == '\"' || ch == '\'' || ch == '~' || ch == '#' || ch == '%' || ch == '['
         || ch == ']' || ch == '{' || ch == '}' || ch == '\\' || ch == '.' || ch == '\?' || ch == ':')
     {//��Ϊ��������߽�������õ����
         token[0] = resourceProject[pProject];
         token[1] = '\0';//�γɵ��ַ���
         for (i = 0; i<36; i++)
         {//������������
             if (strcmp(token, operatorOrDelimiter[i]) == 0)
             {
                syn = 33 + i;//����ֱ��룬ʹ����һ�㼼�ɣ�ʹ֮������ӳ��
                 break;//�鵽���Ƴ�
             }
         }
         pProject++;//ָ�����ƣ�Ϊ��һɨ����׼��
         return;
     }
     else  if (resourceProject[pProject] == '<')
     {//<,<=,<<
         pProject++;//���ƣ���ǰ����
         if (resourceProject[pProject] == '=')
         {
             syn = 38;
         }
         else if (resourceProject[pProject] == '<')
         {//����
             pProject--;
             syn = 58;
         }
         else
         {
             pProject--;
             syn = 37;
         }
         pProject++;//ָ������
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
     {//������
        syn = 0;//�ֱ���Ϊ0
     }
    else
     {//���ܱ����ϴʷ�����ʶ�������
         printf("error��there is no exist %c \n", ch);
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
     if ((fp = fopen("F:\\h.txt", "r")) == NULL)//��Դ����
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
     cout <<endl<<"Դ����Ϊ:" << endl;
     cout<<resourceProject<<endl;

    //��������е�ע��
    filterProject(resourceProject,fProject);

   cout <<endl<<"���˺�ĳ���Ϊ:"<<endl;
     cout<<resourceProject<<endl;
        fProject = 0;//��ͷ��ʼ��
     if ((fp1 = fopen("F:\\b.txt", "w+")) == NULL)
    {//��Դ����
         cout << "can't open this file";
         exit(0);
     }
     while (syn != 0)
     {
         //����ɨ��
         Scanner(syn, resourceProject, token, fProject);
         if (syn == 100)
         {//��ʶ��
             for (int i = 0; i<1000; i++)
             {//�����ʶ������
                 if (strcmp(IDentifierTbl[i], token) == 0)
                 {//���ڱ���
                     break;
                 }
                 if (strcmp(IDentifierTbl[i], "") == 0)
                 {//���ҿռ�
                     strcpy(IDentifierTbl[i], token);
                     break;
                 }
             }
             printf("(��ʶ��  ,%s)\n", token);
             fprintf(fp1, "(��ʶ��   ,%s)\n", token);
         }
         else if (syn >= 1 && syn <= 32)
         {//������
             printf("(%s   ,  --)\n", reserveWord[syn - 1]);
             fprintf(fp1, "(%s   ,  --)\n", reserveWord[syn - 1]);
         }
         else if (syn == 99)
         {//const ����
             printf("(����   ,   %s)\n", token);
             fprintf(fp1, "(����   ,   %s)\n", token);
         }
         else if (syn >= 33 && syn <= 68)
         {
             printf("(%s   ,   --)\n", operatorOrDelimiter[syn - 33]);
             fprintf(fp1, "(%s   ,   --)\n", operatorOrDelimiter[syn - 33]);
         }
     }
     for (int i = 0; i<100; i++)
     {//�����ʶ������
         printf("��%d����ʶ����  %s\n", i + 1, IDentifierTbl[i]);
         fprintf(fp1, "��%d����ʶ����  %s\n", i + 1, IDentifierTbl[i]);
     }
     fclose(fp1);
     return 0;
}
