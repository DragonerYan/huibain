#include <iostream>
#include<stdio.h>//�ļ�
#include <stdlib.h>//exit(0)
#include <string.h>


using namespace std;
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
int main()
{
    char resourceProject[10000];
    int fProject=0;
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
     if ((fp = fopen("F:\\b.txt", "w+")) == NULL)
    {//��Դ����
         cout << "can't open this file";
         exit(0);
     }
    return 0;
}
