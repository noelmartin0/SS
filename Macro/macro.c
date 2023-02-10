#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *f1,*f2,*f3,*f4,*f5;
void main()
{
    char lbl[20],opc[20],opr[20],mname[20],arg[20],check[20];char ch,dlbl[20],dopc[20],dopr[20];
    int c;
    f1=fopen("MACIN.DAT","r");
    rewind(f1);
    f2=fopen("NAMETAB.DAT","r");
    rewind(f2);
    f3=fopen("DEFTAB.DAT","r");
    f4=fopen("EXPAND.DAT","w");
    f5=fopen("ARGTAB.DAT","w");
    while(!feof(f1))
    {
        l1:
        fscanf(f1,"%s %s %s",lbl,opc,opr);
        if(strcmp(opc,mname)==0)
            c=1;
        if(strcmp(opc,"MACRO")==0)
        {
            while(strcmp(opc,"MEND")!=0)
            {
                fscanf(f1,"%s%s%s",lbl,opc,opr);
                continue;
            }
            goto l1;
        }
        rewind(f2);
        rewind(f3);
        fscanf(f2,"%s",mname);
        if(strcmp(opc,mname)==0)
        {
            fprintf(f5," %s",opr);
            rewind(f5);
            while(!feof(f3))
            {
                fscanf(f3,"%s%s%s",dlbl,dopc,dopr);
                if(strcmp(dopc,"MEND")!=0)
                {
                    if(strcmp(dopc,"MACRO")==0)
                    {
                         continue;
                    }
                    if(strcmp(dopr,"=X'?1'")==0)
                        strcpy(dopr,"=X'F1'");
                    if(strcmp(dopr,"?2,X")==0)
                        strcpy(dopr,"BUFFER,X");
                    if(strcmp(dopr,"?3")==0)
                        strcpy(dopr,"LENGTH");
                    if(c==1)
                    {
                        fprintf(f4," %s\t%s\t%s\n",lbl,opc,opr);
                        c=0;
                    }
                    fprintf(f4," %s\t%s\t%s\n",dlbl,dopc,dopr);
                }
            }
            goto l1;
        }
        fprintf(f4," %s\t%s\t%s\n",lbl,opc,opr);
    }
    _fcloseall();
    printf("\n INPUT\n\n Macro Program before expanded \n");
    printf(" ---------------------------------\n");
    f1=fopen("MACIN.DAT","r");
    ch=fgetc(f1);
    while(ch!=EOF)
    {
        printf("%c",ch);
        ch=fgetc(f1);
    }
    printf("\n Definition Table \n");
    printf(" ---------------------------------\n");
    f2=fopen("DEFTAB.DAT","r");
    ch=fgetc(f2);
    while(ch!=EOF)
    {
        printf("%c",ch);
        ch=fgetc(f2);
    }
    printf("\n Name Table \n");
    printf(" ---------------------------------\n");
    f3=fopen("NAMETAB.DAT","r");
    ch=fgetc(f3);
    while(ch!=EOF)
    {
        printf("%c",ch);
        ch=fgetc(f3);
    }
    printf("\n\n OUTPUT\n\n Macro Program after expanded \n");
    printf(" ---------------------------------\n\n");
    f4=fopen("EXPAND.DAT","r");
    ch=fgetc(f4);
    while(ch!=EOF)
    {
        printf("%c",ch);
        ch=fgetc(f4);
    }
    printf("\n Argument Table \n");
    printf(" ---------------------------------\n\n");
    f5=fopen("ARGTAB.DAT","r");
    ch=fgetc(f5);
    while(ch!=EOF)
    {
        printf("%c",ch);
        ch=fgetc(f5);
    }
    _fcloseall();
}