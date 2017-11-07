数据结构表达式求值，利用堆栈，实现将中缀表达式转换成后缀表达式
#include <stdio.h>
#include <stdlib.h>
#include "exp.h"
#include "stack.h"
#include<string.h>
#define MAXSIZE 100

int isInt(char c)
{
    if(c>='0'&&c<='9')
        return 1;
    else return 0;
}
int num(char str[])
{
    int res=0,n,i,fla=0;
    n=strlen(str);
    if(str[n-1]=='-')
    {
        fla=1;
        i=n-2;
    }
    else
        i=n-1;
    for(;i>=0;i--)
       res=res*10+str[i]-'0';
    if(fla)
        res=0-res;;
    return res;
}
//12-5+33*6-(50*2-10)*5@
void str(int n,char s[])
{

        sprintf(s,"%d",n);
}
void trans(char exp[],char suffexp[])
{
    int i=1,j=0;
    char ch1,ch2,op;
    Stack stack;
    Stack*s=&stack;
    Creat(s);
    Push(s,'@');
    ch1=exp[0];
    while(!IsEmpty(stack)&&ch1!='\0')
    {
        if(isInt(ch1))
        {
            suffexp[j++]=ch1;
            if(!isInt(exp[i]))
                suffexp[j++]='#';
            ch1=exp[i++];
        }
        else if(ch1==')')
                {
                    Pop(s,&op);
                    while(op!='(')
                    {
                        suffexp[j++]=op;
                        Pop(s,&op);
                    }
                    ch1=exp[i++];
                }
        else{
            GetTop(s,&ch2);
            if(isp(ch1)>isp(ch2))//优先级高
                {
                    Push(s,ch1);
                    ch1=exp[i++];
                }
            else{
                op=ch2;
                if(op=='('||op==')')
                    {
                        Push(s,ch1);
                        ch1=exp[i++];
                    }
                else
                    {
                        Pop(s,&op);
                        suffexp[j++]=op;
                    }
            }
        }
    }
    suffexp[j]='\0';
}
int add(char suffexp[])
{
    char ch1,ch2,op;
    char n[100];
    Stack stack;
    Stack*s=&stack;
    Creat(s);
    Push(s,'#');
    int i=1,res;
    ch1=suffexp[0];
    while(ch1!='@')
    {
        if((ch1>='0'&&ch1<='9')||ch1=='#')
            Push(s,ch1);
        else
        {
            int j=0,n1,n2;
            char t;
            op=ch1;
            Pop(s,&t);
            GetTop(s,&ch2);
            while(ch2!='#')
            {
                Pop(s,&n[j++]);
                GetTop(s,&ch2);
            }
            n[j]='\0';
            n1=num(n);
            j=0;
            Pop(s,&t);
            GetTop(s,&ch2);
            while(ch2!='#')
            {
                Pop(s,&n[j++]);
                GetTop(s,&ch2);
            }
            n[j]='\0';
            n2=num(n);
            switch(op)
            {
                case '+':res=n1+n2;break;
                case '-':res=n2-n1;break;
                case '*':res=n2*n1;break;
                case '/':res=n2/n1;break;
            }
            str(res,n);
            for(j=0;j<strlen(n);++j)
                Push(s,n[j]);
            Push(s,'#');
        }
        ch1=suffexp[i++];
    }
    i=0;
    Pop(s,&ch1);
            GetTop(s,&ch2);
            while(ch2!='#')
            {
                Pop(s,&n[i++]);
                GetTop(s,&ch2);
            }
            n[i]='\0';
    return num(n);
}
int main()
{
    char exp[MAXSIZE];//输入的表达式
    char suffexp[MAXSIZE];//后缀表达式
    printf("输入一个中缀表达式：\n");
    scanf("%s",exp);
    //转换成后缀表达式
    trans(exp,suffexp);
    printf("%s\n",suffexp);
    printf("\n%d\n",add(suffexp));
    printf("Hello world!\n");
    return 0;
}
