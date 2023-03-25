#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int day,month,year;
} Date;
Date *date(int d, int m, int y)
{
    Date *p= malloc(sizeof(Date));
    p->day=d ;
    p->month=m ;
    p->year= y;
    return p;
}
typedef struct
{
    char *last_name, *first_name,*address,*number,*email;
    Date *date_of_birth;
} Contact;
Contact*  contact(char* l, char* f, Date* d, char* a, char* n, char* e)
{
    Contact *p= malloc(sizeof(Contact));
    p->last_name=malloc(sizeof(char)*20);
    p->first_name=malloc(sizeof(char)*20);
    p->address=malloc(sizeof(char)*50);
    p->number=malloc(sizeof(char)*15);
    p->email=malloc(sizeof(char)*50);
    strcpy(p->last_name,l);
    strcpy(p->first_name,f);
    strcpy(p->address,a);
    strcpy(p->number,n);
    strcpy(p->email,e);
    p->date_of_birth=d;
    return p;
}
Contact *phone_book[200];
int i;
void print_contact(int j)
{
    printf("%d. %s,%s,%d-%d-%d,%s,%s,%s\n",j+1,phone_book[j]->last_name,phone_book[j]->first_name,phone_book[j]->date_of_birth->day,phone_book[j]->date_of_birth->month,phone_book[j]->date_of_birth->year,phone_book[j]->address,phone_book[j]->number,phone_book[j]->email);
}
void print_contact_nonum(int j)
{
    printf("%s,%s,%d-%d-%d,%s,%s,%s\n",phone_book[j]->last_name,phone_book[j]->first_name,phone_book[j]->date_of_birth->day,phone_book[j]->date_of_birth->month,phone_book[j]->date_of_birth->year,phone_book[j]->address,phone_book[j]->number,phone_book[j]->email);
}
void print()
{
    {
        int j;
        printf("\n");
        for(j=0; j<=i; j++)
            print_contact(j);
    }
    printf("\n");
}
char* ReadName()
{
    printf("Enter file name or file directory:");
    char *x=calloc(100,100);
    gets(x);
    return x;
}
void load_from_file()
{
    i=-1;
    FILE* file;
    do
    {
        file = fopen(ReadName(),"r");
        if(!file)
            printf("INVALID FILE NAME OR FILe PATH!!\n");
    }
    while(!file);
    char* l=calloc(15,15);
    char* f=calloc(15,15);
    char* a=calloc(50,50);
    char* n=calloc(15,15);
    char* e=calloc(50,50);
    int d,m,y;
    char*line=calloc(200,200);
    if(file)
    {
        while(fgets(line, 200, file))
        {
            l=strtok(line,",");
            f=strtok(NULL,",");
            d=atoi(strtok(NULL,"-"));
            m=atoi(strtok(NULL,"-"));
            y=atoi(strtok(NULL,","));
            a=strtok(NULL,",");
            n=strtok(NULL,",");
            e=strtok(NULL,"\n");
            phone_book[++i]= contact(l,f,date(d,m,y),a,n,e);
        }
        fclose(file);
    }
    free(l); free(f); free(a); free(n); free(e); free(line);
}
void search()
{
    char *last=calloc(15,15);
    printf("Enter the last name: ");
    scanf("%s",last);
    int j,found=0;
    int count = 0;
    for(j=0; j<=i; j++)
    {
        if(!strcmp(last,phone_book[j]->last_name))
        {
            found=1;
            printf("%d. ",count+1);
            print_contact_nonum(j);
        }
    }
    if(!found)
    {
        printf("This name is not found\n");
    }
free(last);
}
int validate_email(char *a)
{
    int count=0,h,temp=0;
    if(a[0]!=64 && a[0]!= 46)
        temp++;
    for(count; count<strlen(a); count++)
    {
        if(a[count]==64)
        {
            temp++;
            if (a[count+1]!=64 && a[count+1]!=46 )
                temp++;
            for(h=count; h<strlen(a); h++)
            {
                if(a[h]==46)
                {
                    temp++;
                    if (a[h+1]!=64 && a[h+1]!=46 && a[h+1]!=0)
                        temp++;
                    // break;
                }
            }

        }
    }
    if (temp==5)
        return 1;
    else
        return 0;
}
void add_new_contact()
{
    char* l=calloc(15,15);
    char* f=calloc(15,15);
    char* a=calloc(50,50);
    char* n=calloc(15,15);
    char* e=calloc(50,50);
    char* d=calloc(4,4);
    char* m=calloc(4,4);
    char* y=calloc(4,4);
    int d1,m1,y1;
    printf("Enter the last name:");
    scanf("%s",l);
    printf("Enter the first name:");
    scanf("%s",f);
    do
    {
        printf("Enter the day of birth(from 1 to 31):");
        scanf("%s",d);
        d1=atoi(d);
        if(d1<=0 || d1>31 || (!d1))
            printf("INVALID DAY OF BIRTH!!\n");
    }
    while (d1<=0 || d1>31 || (!d1));
    do
    {
        printf("Enter the month of birth(from 1 to 12):");
        scanf("%s",m);
        m1=atoi(m);
        if( m1<=0 || m1>12 || (!m1))
            printf("INVALID MONTH OF BIRTH!!\n");
    }
    while( m1<=0 || m1>12 || (!m1));
    do
    {

        printf("Enter the year of birth(from 1900 to 2021):");
        scanf("%s",y);
        y1=atoi(y);
        if( y1<1900 || y1>2021 || (!y1))
            printf("INVALID YEAR OF BIRTH!!\n");
    }
    while( y1<1900 || y1>2021 || (!y1));
    scanf("%c");
    printf("Enter the address:");
    gets(a);
    do
    {
        printf("Enter the phone number(no letters allowed):");
        scanf("%s",n);
        if(!atoi(n))
            printf("INVALID PHONE NUMBER!!\n");
    }
    while (!atoi(n));
    do
    {
        printf("Enter the email:");
        scanf("%s",e);
        if(!validate_email(e))
            printf("INVALID E_MAIL !!\n");
    }
    while (!validate_email(e));
    phone_book[++i]=contact(l,f,date(d1,m1,y1),a,n,e);
free(l); free(f); free(a); free(n); free(e); free(d); free(m); free(y);
}
void sort_by_name_ascending()
{
    int j,k;
    Contact* temp;
    char* str1=calloc(15,15);
    char* str2=calloc(15,15);
    for (j=0; j<=i-1; j++)
        for(k=0; k<=i-j-1; k++)
        {
            strcpy(str1,phone_book[k]->last_name);
            strcpy(str2,phone_book[k+1]->last_name);
            if (strcmp(strlwr(str1),strlwr(str2))>0)
            {
                temp=phone_book[k];
                phone_book[k]=phone_book[k+1];
                phone_book[k+1]=temp;
            }

        }
    print();
    free(str1); free(str2);
}
void sort_by_name_descending()
{
    int j,k;
    Contact* temp;
    char* str1=calloc(15,15);
    char* str2=calloc(15,15);
    for (j=0; j<=i-1; j++)
        for(k=0; k<=i-j-1; k++)
        {
            strcpy(str1,phone_book[k]->last_name);
            strcpy(str2,phone_book[k+1]->last_name);
            if (strcmp(strlwr(str1),strlwr(str2))<0)
            {
                temp=phone_book[k];
                phone_book[k]=phone_book[k+1];
                phone_book[k+1]=temp;
            }

        }
    print();
    free(str1); free(str2);
}
void sort_by_date_descending()
{
    int j,k;
    Contact* temp;
    for (j=0; j<=i-1; j++)
        for(k=0; k<=i-j-1; k++)
        {
            if (phone_book[k]->date_of_birth->year<phone_book[k+1]->date_of_birth->year)
            {
                temp=phone_book[k];
                phone_book[k]=phone_book[k+1];
                phone_book[k+1]=temp;
            }
            if(phone_book[k]->date_of_birth->year==phone_book[k+1]->date_of_birth->year && phone_book[k]->date_of_birth->month<phone_book[k+1]->date_of_birth->month)
            {
                temp=phone_book[k];
                phone_book[k]=phone_book[k+1];
                phone_book[k+1]=temp;
            }
            if(phone_book[k]->date_of_birth->year==phone_book[k+1]->date_of_birth->year && phone_book[k]->date_of_birth->month==phone_book[k+1]->date_of_birth->month && phone_book[k]->date_of_birth->day<phone_book[k+1]->date_of_birth->day)
            {
                temp=phone_book[k];
                phone_book[k]=phone_book[k+1];
                phone_book[k+1]=temp;
            }
        }
    print();
}
void sort_by_date_ascending()
{
    int j,k;
    Contact* temp;
    for (j=0; j<=i-1; j++)
        for(k=0; k<=i-j-1; k++)
        {
            if (phone_book[k]->date_of_birth->year>phone_book[k+1]->date_of_birth->year)
            {
                temp=phone_book[k];
                phone_book[k]=phone_book[k+1];
                phone_book[k+1]=temp;
            }
            if(phone_book[k]->date_of_birth->year==phone_book[k+1]->date_of_birth->year && phone_book[k]->date_of_birth->month>phone_book[k+1]->date_of_birth->month)
            {
                temp=phone_book[k];
                phone_book[k]=phone_book[k+1];
                phone_book[k+1]=temp;
            }
            if(phone_book[k]->date_of_birth->year==phone_book[k+1]->date_of_birth->year && phone_book[k]->date_of_birth->month==phone_book[k+1]->date_of_birth->month && phone_book[k]->date_of_birth->day>phone_book[k+1]->date_of_birth->day)
            {
                temp=phone_book[k];
                phone_book[k]=phone_book[k+1];
                phone_book[k+1]=temp;
            }
        }
    print();
}
void modify()
{
    char *last=calloc(15,15);
    printf("Enter the last name: ");
    scanf("%s",last);
    int j,found=0;
    int count =0;
    Contact *counter[200];
    for(j=0; j<=i; j++)
    {
        if(!strcmp(last,phone_book[j]->last_name))
        {
            found=1;
            printf("%d. ",count+1);
            counter[count++]=phone_book[j];
            print_contact_nonum(j);
        }
    }
    if(!found)
    {
        printf("This name is not found\n");
        return;
    }
    char* num=calloc(4,4);
    int num1;
    do
    {
        printf("\nEnter the contact number of the contact you want to modify:");
        scanf("%s",num);
        num1=atoi(num);
        if(num1<1 || num1>count || !num1)
            printf("INVALID NUMBER!!");
    }
    while(num1<1 || num1>count || !num1);
    printf("s");
    printf("Enter new contact details:\n");
    char* l=calloc(15,15);
    char* f=calloc(15,15);
    char* a=calloc(50,50);
    char* n=calloc(15,15);
    char* e=calloc(50,50);
    char* d=calloc(4,4);
    char* m=calloc(4,4);
    char* y=calloc(4,4);
    int d1,m1,y1;
    printf("Enter the last name:");
    scanf("%s",l);
    printf("Enter the first name:");
    scanf("%s",f);
    do
    {
        printf("Enter the day of birth(from 1 to 31):");
        scanf("%s",d);
        d1=atoi(d);
        if(d1<=0 || d1>31 || (!d1))
            printf("INVALID DAY OF BIRTH!!\n");
    }
    while (d1<=0 || d1>31 || (!d1));
    do
    {
        printf("Enter the month of birth(from 1 to 12):");
        scanf("%s",m);
        m1=atoi(m);
        if( m1<=0 || m1>12 || (!m1))
            printf("INVALID MONTH OF BIRTH!!\n");
    }
    while( m1<=0 || m1>12 || (!m1));
    do
    {

        printf("Enter the year of birth(from 1990 to 2021):");
        scanf("%s",y);
        y1=atoi(y);
        if( y1<1900 || y1>2021 || (!y1))
            printf("INVALID YEAR OF BIRTH!!\n");
    }
    while( y1<1900 || y1>2021 || (!y1));
    scanf("%c");
    printf("Enter the address:");
    gets(a);
    do
    {
        printf("Enter the phone number(no letters allowed):");
        scanf("%s",n);
        if(!atoi(n))
            printf("INVALID PHONE NUMBER!!\n");
    }
    while (!atoi(n));
    do
    {
        printf("Enter the email:");
        scanf("%s",e);
        if(!validate_email(e))
            printf("INVALID E_MAIL !!\n");
    }
    while (!validate_email(e));
    strcpy(counter[num1-1]->last_name,l);
    strcpy(counter[num1-1]->first_name,f);
    strcpy(counter[num1-1]->address,a);
    strcpy(counter[num1-1]->number,n);
    strcpy(counter[num1-1]->email,e);
    counter[num1-1]->date_of_birth=date(d1,m1,y1);
free(l); free(f); free(a); free(n); free(e); free(d); free(m); free(y); free(last); free(num);
}
int quit()
{
    printf("Are you sure you want to exit? (Make sure you save)\n1 =>> Yes\n2 =>> No\nType your choice:");
    char *x=calloc(4,4);
    scanf("%s",x);
    int y = atoi(x);
    while(y!=2 && y!=1)
    {
        printf("please enter 1 or 2:");
        scanf("%s",x);
        y = atoi(x);
    }
    free(x);
    return y;
}
void save()
{
    FILE* file;
    file = fopen(ReadName(),"w");
    int j=0;
    for(j; j<=i; j++)
    {
        fprintf(file,"%s,%s,%d-%d-%d,%s,%s,%s\n",phone_book[j]->last_name,phone_book[j]->first_name,phone_book[j]->date_of_birth->day,phone_book[j]->date_of_birth->month,phone_book[j]->date_of_birth->year,phone_book[j]->address,phone_book[j]->number,phone_book[j]->email);
    }
    fclose(file);
}
void delete_function()
{
    char *last=calloc(15,15);
    char* first=calloc(15,15);
    printf("Enter the last name:");
    scanf("%s",last);
    printf("Enter the first name:");
    scanf("%s",first);
    int j,found=0,count=0;
    Contact *edit[100];
    for(j=0; j<=i; j++)
    {
        if(!strcmp(last,phone_book[j]->last_name) && !strcmp(first,phone_book[j]->first_name))
        {
            found++;
        }
        else if(strcmp(last,phone_book[j]->last_name)!=0 || strcmp(first,phone_book[j]->first_name)!=0)
        {
            edit[count++]=phone_book[j];
        }
    }
    for (j=0; j<found; j++)
        i--;
    for(j=0; j<=i; j++)
        phone_book[j]=edit[j];
    if(!found)
    {
        printf("This name is not found\n");
        return;
    }
    free(last); free(first);
}

int main()
{
    printf("\t\t\t\t\tWELCOME TO OUR PROGRAM!\n\n");
    load_from_file();
    char*choice=calloc(4,4);
    int choice1;
    char*choice2=calloc(4,4);
    int choice12;
    while(1)
    {
        printf("Please Select Your Choice:\n1.Load File\n2.Search\n3.Add\n4.Delete\n5.Modify\n6.Print(sorted)\n7.Save\n8.Quit\nEnter choice:");
        scanf("%s%c", choice);
        choice1=atoi(choice);
        switch(choice1)
        {
        case 1:
            load_from_file();
            break;

        case 2:
            search();
            break;

        case 3:
            add_new_contact();
            break;

        case 4:
            delete_function();
            break;

        case 5:
            modify();
            break;

        case 6:{
            printf("\nChoose the sorting technique before printing:\n1. sort by name ascendingly\n2. sort by name descendingly\n3. sort by date ascendingly\n4. sort by date descendingly\nEnter your choice:");
            do
            {
                scanf("%s%c",choice2);
                choice12= atoi(choice2);
                if(!choice12 || choice12>4 || choice12<1)
                    printf("INVALID CHOICE!!\nEnter a new choice:");
            }
            while(!choice12 || choice12>4 || choice12<1);
            switch(choice12)
            {
            case 1:
                sort_by_name_ascending();
                break;
            case 2:
                sort_by_name_descending();
                break;
            case 3:
                sort_by_date_ascending();
                break;
            case 4:
                sort_by_date_descending();
                break;
            }
            break;
            }

        case 7:
            save();
            break;

        case 8:
            if(quit()==1)
            {
                printf("THANKS FOR USING OUR PROGRAM!");
                exit(0);
            }
            break;

        default:
            printf("INVALID NUMBER!!");
            break;
        }
    }
    free(choice); free(choice2);
    return 0;
}
