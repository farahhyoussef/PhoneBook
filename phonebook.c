#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int day,month,year;
} DOB;

typedef struct
{
    char Last_Name[50],First_Name[50],Street_Address[100],Phone_Number[20],Email[50];
    DOB date;
} Information;
Information info[1000];
int count=0;
char name[50];

int email_validaion(char email[50])
{
    int i,at,counter=0,n;
    n=isalpha(email[0]);
    if (!n)
    {
        printf("invalid,first charachter , please re enter:\n");
        return 0;
    }
    for(i=0; i<strlen(email); i++)
    {
        if(email[i]=='@')
        {
            at=i;
            counter++;
        }
    }
    if (counter!=1)
    {
        printf("invalid email address , please re enter:\n");
        return 0;
    }
    for(i=0; i<at; i++)
    {
        if(!(isalpha(email[i])||isdigit(email[i])||email[i]=='.'||email[i]=='_'||email[i]=='-'))
        {
            printf("invalid email address , please re enter:\n");
            return 0;
        }
    }
    int dot[5],c=0;
    for(i=at+1; i<strlen(email); i++)
    {
        if(email[i]=='.')
        {
            if(email[i+1]=='\0')
            {
                printf("invalid email address , please re enter:\n");
                return 0;
            }
            dot[c]=i;
            c++;
        }
    }
    if (c<1)
    {
        printf("invalid email address , please re enter:\n");
        return 0;
    }
    if(dot[0]==at+1)
    {
        printf("invalid email address , please re enter:\n");
        return 0;
    }
    c=0;
    for(i=at+1; i<strlen(email); i++)
    {
        if(!isalpha(email[i])&&i!=dot[c])
        {
            printf("invalid email address , please re enter:\n");
            return 0;
        }
        if(i==dot[c])
        {
            c++;
        }
    }
    return 1;
}

int Phone_Validation(char phone[20])
{
    int num,counter=0,i,j;
    if(phone[0]=='+'||isdigit(phone[0]))
    {
        for(i=1; i<strlen(phone); i++)
        {
            num= phone[i]-'0';
            for(j=0; j<10; j++)
            {
                if(num==j)
                {
                    counter++;

                }

            }

        }
        if(counter!=strlen(phone)-1)
        {
            printf("invalid character entered, please re etner:\n");
            return 0;
        }
    }
    else
    {
        printf("invalid character entered, please re etner:\n");
        return 0;
    }
    return 1;
}

int DOBvalidation(DOB dateOB)
{
    if((dateOB.year)>2020||((dateOB.year)<1900))
    {
        printf("invalid year of birth, please re enter:\n");
        return 0;
    }

    if (((dateOB.month)>12)||((dateOB.month)<0))

    {

        printf("invalid month, please re enter:\n");
        return 0;

    }
    if (((dateOB.day)>31)||((dateOB.day)<0))
    {

        printf("invalid day,please re enter:\n");
        return 0;
    }
    if (((dateOB.month==4)||(dateOB.month==6)||(dateOB.month==9)||(dateOB.month==11))&&(dateOB.day==31))
    {
        printf("invalid day, please re enter:\n");
        return 0;
    }
    if((dateOB.month==2)&&((dateOB.year%4!=0&&dateOB.day>28)||(dateOB.year%4==0&&dateOB.day>29)))
    {
        printf("invalid day, please re enter:\n");
        return 0;
    }

    return 1;
}

void Load()
{
    FILE *f;
    int p=0;
    f=fopen(name,"r");
    while (!f)
    {
        printf("\n\nerror in opening file,please re enter\n");
        gets(name);
        f=fopen(name,"r");

    }
    while (!feof(f))
    {
        fscanf(f,"%[^,],",info[p].Last_Name);
        fscanf(f,"%[^,],",info[p].First_Name);
        fscanf(f,"%d-%d-%d,",&info[p].date.day,&info[count].date.month,&info[count].date.year);
        fscanf(f,"%[^,],",info[p].Street_Address);
        fscanf(f,"%[^,],",info[p].Phone_Number);
        fscanf(f,"%s\n",info[p].Email);
        p++;
        count=p;

    }
    fclose(f);
}

void Query(char Last[50])
{
    int i,compare,found=0;
    printf("\n\nPeople with this last name:\n\n");
    for (i=0; i<count; i++)
    {
        compare= strcasecmp(Last,info[i].Last_Name);

        if (!compare)
        {
            printf("First Name: %s\n",info[i].First_Name);
            printf("Date of Birth : %d-%d-%d\n",info[i].date.day,info[i].date.month,info[i].date.year);
            printf("Address:%s\n",info[i].Street_Address);
            printf("Phone:%s\n",info[i].Phone_Number);
            printf("Email:%s\n",info[i].Email);
            printf("\n------------------\n");
            found++;
        }
    }
    if(!found)
        printf("No Contact(s) Found");
}

void Add()
{
    int vald;
    printf("\nPlease, enter the last name you want to add 'No spaces included':\n");
    scanf("%s",info[count].Last_Name);

    printf("Please, enter the first name you want to add 'No spaces included':\n");
    scanf("%s",info[count].First_Name);

    printf("Please, enter the birth date in the format DD-MM-YYYY :\n");
    scanf("%d-%d-%d",&info[count].date.day,&info[count].date.month,&info[count].date.year);
    vald=DOBvalidation(info[count].date);

    while(!vald)
    {
        scanf("%d-%d-%d",&info[count].date.day,&info[count].date.month,&info[count].date.year);
        vald=DOBvalidation(info[count].date);
    }

    printf("Please, enter the address you want to add:\n");
    getchar();
    scanf("%[^\n]",info[count].Street_Address);

    printf("Please, enter the phone number you want to add, it should only consist of digits with no characters:\n");
    scanf("%s",info[count].Phone_Number);
    vald=Phone_Validation(info[count].Phone_Number);

    while(!vald)
    {
        scanf("%s",info[count].Phone_Number);
        vald=Phone_Validation(info[count].Phone_Number);

    }
    getchar();
    printf("Please, enter the email you want to add 'ex:example@domain.com **No Spaces included':\n");
    scanf("%s",info[count].Email);
    vald=email_validaion(info[count].Email);

    while(!vald)
    {
        scanf("%s",info[count].Email);
        vald=email_validaion(info[count].Email);

    }
    printf("\n\ncontact added successfully\n");
    count++;
}

void Delete_Record()
{
    int i,j,compare_last,compare_first,found=0;
    char Last[20],First[20];
    printf("Please enter the Last name you want to delete:\n");
    scanf("%s",Last);
    printf("Please enter the First name:\n");
    scanf("%s",First);
    for(i=0; i<count; i++)
    {
        compare_last= strcasecmp(Last,info[i].Last_Name);
        compare_first= strcasecmp(First,info[i].First_Name);
        if((!compare_first)&&(!compare_last))
        {   found=1;
            for(j=i; j<count-1; j++)
            {
                info[j]=info[j+1];
            }
            count--;
            i--;
        }
    }
    if(found)
    printf("\ncontact(s) with this name deleted\n");
       else printf("\ncontact(s)not found\n");

}

void Modify()
{
    char Last[20];
    int i,n,c,num=1,o=0,options[20],vald,again=0,y;
    printf("Please enter the Last name you want to Modify:\n");
    scanf("%s",Last);

    for(i=0; i<count; i++)
    {
        n= strcasecmp(Last,info[i].Last_Name);
        if (!n)
        {
            printf("\ncontact number #%d :\n",num);
            printf("Last Name  : %s\n",info[i].Last_Name);
            printf("First Name : %s\n",info[i].First_Name);
            printf("Date of Birth : %d-%d-%d\n",info[i].date.day,info[i].date.month,info[i].date.year);
            printf("Street Address : %s\n",info[i].Street_Address);
            printf("Phone Number : %s\n",info[i].Phone_Number);
            printf("Email : %s\n",info[i].Email);
            printf("\n---------------------\n");
            options[num-1]=i;
            num++;
        }
    }
    if(!(num-1))
    {
        printf("\nlast name not found\n");
    }

    else
    {
        if(num!=2)
        {

            printf("Please choose the number of the record you want to modify:\n");
            scanf("%d",&o);
            while(o<=0||o>num-1)
            {
                printf("wrong entry, please re enter\n");
                scanf("%d",&o);
            }
            o--;
        }
        do
        {
            again=0;
            printf("Please choose a field to modify:\n1-Last Name\n2-First Name\n3-Date of Birth\n4-Street Address\n5-Phone Number\n6-Email\n7-all fields\n");
            scanf("%d",&c);

            switch(c)
            {
            case 1 :
                printf("Please enter the modified 'No spaces included':\n");
                scanf("%s", info[options[o]].Last_Name);
                printf("last name modified successfully\n");
                break;
            case 2 :
                printf("Please enter the modified first name 'No spaces included':\n");
                scanf("%s",info[options[o]].First_Name);
                printf("first name modified successfully\n");
                break;
            case 3:
                printf("Please enter the modified date of birth in the format DD-MM-YYYY:\n");
                scanf("%d-%d-%d",&info[options[o]].date.day,&info[options[o]].date.month,&info[options[o]].date.year);
                vald=DOBvalidation(info[options[o]].date);

                while(!vald)
                {
                    scanf("%d-%d-%d",&info[options[o]].date.day,&info[options[o]].date.month,&info[options[o]].date.year);
                    vald=DOBvalidation(info[options[o]].date);
                }
                printf("date of birth modified successfully\n");
                break;
            case 4 :
                printf("Please enter the modified street address:\n");

                getchar();
                scanf("%[^\n]%*c",info[options[o]].Street_Address);
                printf("Address modified successfully\n");
                break;
            case 5 :
                printf("Please enter the modified phone number,it should only consist of digits with no characters:\n");
                scanf("%s",info[options[o]].Phone_Number);
                vald=Phone_Validation(info[options[o]].Phone_Number);

                while(!vald)
                {
                    scanf("%s",info[options[o]].Phone_Number);
                    vald=Phone_Validation(info[options[o]].Phone_Number);
                }
                getchar();
                printf("phone number modified successfully\n");
                break;
            case 6 :
                printf("Please enter the modified email 'ex:example@domain.com **No spaces included':\n");
                scanf("%s",info[options[o]].Email);
                vald=email_validaion(info[options[o]].Email);
                while(!vald)
                {
                    scanf("%s",info[options[o]].Email);
                    vald=email_validaion(info[options[o]].Email);
                }
                printf("email modified successfully\n");
                break;
            case 7:
                printf("please enter modified data\n");
                printf("last name:\n");
                scanf("%s", info[options[o]].Last_Name);
                printf("first name:\n");
                scanf("%s",info[options[o]].First_Name);
                printf("date of birth should be in the format DD-MM-YYYY\ndate of birth:\n");
                scanf("%d-%d-%d",&info[options[o]].date.day,&info[options[o]].date.month,&info[options[o]].date.year);
                vald=DOBvalidation(info[options[o]].date);
                while(!vald)
                {
                    scanf("%d-%d-%d",&info[options[o]].date.day,&info[options[o]].date.month,&info[options[o]].date.year);
                    vald=DOBvalidation(info[options[o]].date);
                }
                printf("street address:\n");
                getchar();
                scanf("%[^\n]%*c",info[options[o]].Street_Address);
                printf("phone number should only consist of digits with no characters\nphone number:\n");
                scanf("%s",info[options[o]].Phone_Number);
                vald=Phone_Validation(info[options[o]].Phone_Number);
                while(!vald)
                {
                    scanf("%s",info[options[o]].Phone_Number);
                    vald=Phone_Validation(info[options[o]].Phone_Number);
                }
                getchar();
                printf("email should be in format'ex:example@domain.com **No spaces included'\nemail:\n");
                scanf("%s",info[options[o]].Email);
                vald=email_validaion(info[options[o]].Email);
                while(!vald)
                {
                    scanf("%s",info[options[o]].Email);
                    vald=email_validaion(info[options[o]].Email);
                }
                printf("contact modified successfully\n");
                break;
            default:
                printf("Wrong input\n");
            }
            if(c!=7)
            {
                printf("do you want to modify another field, please choose 1 or 2\n1-Yes\n2-No\n");
                scanf("%d",&y);
                if(y==1)
                {
                    again=1;
                }
                else if(y==2)
                {
                    again=0;
                }
            }

        }
        while(again);
    }
}

void sortByLname()
{
    Information temp;
    int i,j,compare;
    for (i=0; i<count; i++)
    {
        for(j=0; j<count-1-i; j++)
        {
            compare= strcasecmp(info[j].Last_Name,info[j+1].Last_Name);
            if(compare>0)
            {
                temp=info[j];
                info[j]=info[j+1];
                info[j+1]=temp;
            }
            else if(compare==0)
            {

                compare= strcasecmp(info[j].First_Name,info[j+1].First_Name);
                if(compare>0)
                {
                    temp=info[j];
                    info[j]=info[j+1];
                    info[j+1]=temp;
                }
            }

        }
    }
}

void sortByDOB()
{
    Information temp;
    int i,j;
    for (i=0; i<count; i++)
    {
        for(j=0; j<count-1-i; j++)
        {
            if(info[j+1].date.year<info[j].date.year)

            {
                temp=info[j];
                info[j]=info[j+1];
                info[j+1]=temp;

            }
            else if (info[j+1].date.year==info[j].date.year)
            {
                if (info[j+1].date.month<info[j].date.month)
                {
                    temp=info[j];
                    info[j]=info[j+1];
                    info[j+1]=temp;

                }
                else if(info[j+1].date.month==info[j].date.month)
                    if (info[j+1].date.day<info[j].date.day)
                    {
                        temp=info[j];
                        info[j]=info[j+1];
                        info[j+1]=temp;

                    }
            }
        }
    }
}

void Print_info()
{
    int i,ans;

    printf("Please choose the way of sorting:\n1-By Last Name\n2-By Date of Birth\n\n");
    printf("your choice:");

    scanf("%d",&ans);

    while((ans!=1)&&(ans!=2))
    {
        printf("\n wrong input,please re enter:\n");
        scanf("%d",&ans);
    }
    if(ans==1)
    {
        sortByLname();
        printf("Sorting by Last name:\n\n");
    }
    else if(ans==2)
    {
        sortByDOB();
        printf("Sorting by date of birth:\n\n");
    }
    for(i=0; i<count; i++)
    {
        printf("contact number #%d : \n",i+1);
        printf("Last Name  : %s\n",info[i].Last_Name);
        printf("First Name : %s\n",info[i].First_Name);
        printf("Date of Birth : %d-%d-%d\n",info[i].date.day,info[i].date.month,info[i].date.year);
        printf("Street Address : %s\n",info[i].Street_Address);
        printf("Phone Number : %s\n",info[i].Phone_Number);
        printf("Email : %s\n",info[i].Email);
        printf("\n---------------------\n");
    }
}

void Quit()
{
    int ans;

    printf ("Are you sure you want to quit? 'All changes will be discarded and not saved' please choose:\n1-Yes\n2-No\n");
    printf("your choice:");
    getchar();
    scanf("%d",&ans);
    while((ans!=1)&& (ans!=2))
    {
        printf("\n wrong input,please re enter:\n");
        scanf("%d",&ans);
    }
    if(ans==1)

        exit(0);
}

void Save()
{
    int i;

    FILE *f;
    f=fopen(name,"w");
    if (!f)
    {
        printf("error in opening file\n");
        exit(0);
    }
    else
    {
        for(i=0; i<count; i++)
        {
            fprintf(f,"%s,",info[i].Last_Name);
            fprintf(f,"%s,",info[i].First_Name);
            fprintf(f,"%d-%d-%d,",info[i].date.day,info[i].date.month,info[i].date.year);
            fprintf(f,"%s,",info[i].Street_Address);
            fprintf(f,"%s,",info[i].Phone_Number);
            fprintf(f,"%s\n",info[i].Email);
        }
        fclose(f);
        printf("Saved Successfully\n");
    }
}

void choice()
{
    int c,found=0;
    char search[50];

    printf("\n\n\nPlease choose the number of your option:\n\n1-Load\n2-Search\n3-Add\n4-Delete\n5-Modify\n6-Print\n7-Save\n8-Quit\n\n");
    printf("your choice:");
    scanf("%d",&c);
    while(c>0&&c<9)
    {   found=1;
        switch(c)
        {
        case 1:
        {
            printf("\nPlease,Enter file name in format \"example.txt\"\nOR File Destination: ");
            getchar();
            gets(name);
            Load();
            printf("\n\nfile loaded successfully");
            break;
        }
        case 2 :
        {
            printf("\nPlease enter the last name you're searching for:\n");
            scanf("%s",search);
            Query(search);
            break;
        }
        case 3:
        {
            Add();
            break;
        }
        case 4:
        {
            Delete_Record();
            break;
        }
        case 5:
        {
            Modify();

            break;
        }
        case 6:
        {
            Print_info();

            break;
        }
        case 7:
        {
            Save();
            break;
        }
        case 8 :
        {
            Quit();
            break;
        }

        default :
        {
            printf("\nwrong entry, please re enter:\n");
            choice();
        }
        }
        choice();
    }
    if(!found)
    {
        printf("\n invalid, please re enter\n");
    }
    choice();
}

int main()
{
    printf("\t\tPhone Book\n");
    printf("\t\t---------\n");
    printf("Please,Enter file name in format \"example.txt\"\nOR File Destination: ");
    gets(name);
    Load();
    printf("\n\nFile is loaded");
    choice();
    return 0;
}

