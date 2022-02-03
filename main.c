#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Method Declaration

void enter_name();
void find_name();
void find_room();
void checkout_guest();
void view_bookings();

//Instance Field Declaration
FILE* view;
FILE *fp;
FILE* enter;
char admin_entry[20] = {'y'};
char user_entry[20] = {'y'};

//structure defined
struct hotel
{
    char name[20];
    char room[20];
    char bf[20];
    char wifi[20];

} h;

//main method
int main()
{

    int a,b,c;

    //Welcome screen

    printf("\n\n\t\t*************************************************\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*       -----------------------------           *\n");
    printf("\t\t*          WELCOME TO HOTEL REDISON             *\n");
    printf("\t\t*       -----------------------------           *\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*************************************************\n\n\n");

    printf("\n>>>>>>>>>>>>\tFor ADMIN access enter --> 1 \t\t\t<<<<<<<<<<<<");
    printf("\n>>>>>>>>>>>>\tFor USER access enter ---> 2 \t\t\t<<<<<<<<<<<<");
    printf("\n");
    scanf("%d",&a);

    switch(a)
    {
    case 1:
    {
        char pass[10];
        char filepass[10];
        int i;

        FILE *passw;
        passw = fopen("pass.txt","r");

        //admins password prompt
        printf("\n<<<---  Hello Admin!  --->>>\n\nPlease enter the password to continue --> ");

        for(i=0; i<5; i++)
        {
            scanf("%s",pass);
            fscanf(passw,"%s",filepass);
            if (strcmp(filepass,pass) == 0)
            {
                printf("\n\nAccess granted!\n");
                fclose(passw);
                break;
            }
            else
            {
                printf("\nIncorrect password, please try again.");
                printf("\nYou have %d trys left ",5-i-1);
                printf("\n\nEnter password >> ");
            }
            if(i==4)
            {
                fclose(passw);
                return 0;
            }


        }

        //re-entry if
        while(admin_entry[0] =='y')
        {

            printf("\n>>>>>>>>>>>>\tTo VIEW booking requests --> 1");
            printf("\n>>>>>>>>>>>>\tTo VIEW booked guests details --> 2");
            printf("\n>>>>>>>>>>>>\tTo ENTER new guest --> 3");
            printf("\n>>>>>>>>>>>>\tTo FIND room number of existing guest --> 4");
            printf("\n>>>>>>>>>>>>\tTo FIND guest of occupied room --> 5");
            printf("\n>>>>>>>>>>>>\tTo CHECKOUT room number of existing guest --> 6\n");
            scanf("%d",&b);

            switch(b)
            {
            case 1:
            {
                view_bookings();
                break;
            }
            case 2:
            {
                FILE* fpi;
                fpi = fopen("hotelnew.txt","r");

                while(fscanf(fpi,"%s %s %s",h.name,h.room,h.wifi) != -1)
                {
                    fgets(h.bf, 20, (FILE*)fpi);
                    printf("%s %s %s %s \n",h.name,h.room,h.wifi,h.bf);
                }
                fclose(fpi);
                break;
            }
            case 3:
            {
                enter_name();
                break;
            }
            case 4:
            {
                find_name();
                break;
            }
            case 5:
            {
                find_room();
                break;
            }
            case 6:
            {
                checkout_guest();
                break;
            }
            default:
            {
                printf("\nWrong entry!\n");
            }
            }
            //enter again?
            printf("Would you like to continue? (y/n)\n");
            scanf("%s",admin_entry);

        }
        if(strcmp(admin_entry,"n") == 0)
        {
            printf("\n....Exited....\n");
            //system("clear");
            return 0;
        }
        else
        {
            printf("Wrong entry!\n....Exited....\n");
            return 0;
        }
        break;
    }


    case 2:
    {
        while(user_entry[0] =='y')
        {
            printf("\n<<<---  Welcome to Hotel Redison  --->>>!\n\n");
            printf("\n>>>>>>>>>>>>\tTo view available rooms --> 1");
            printf("\n>>>>>>>>>>>>\tTo request booking of room --> 2");
            printf("\n");
            scanf("%d",&c);
            switch(c)
            {
            case 1:
            {
                view = fopen("rooms.txt","r");
                printf("Available rooms are:\n");
                while(fscanf(view,"%s",h.room) != -1)
                {
                    printf("%s \n",h.room);
                }
                fclose(view);
                break;
            }

            case 2:
            {
                printf("Enter your name: ");
                scanf("%s",h.name);
                printf("Enter room to book: ");
                scanf("%s",h.room);
                printf("Enter WiFI plan (1GB/5GB): ");
                scanf("%s",h.wifi);
                printf("Enter if bf (yes/no): ");
                scanf("%s",h.bf);

                enter = fopen("bookings.txt","a");

                fprintf(enter,"%s %s %s %s",h.name,h.room,h.wifi,h.bf);
                fprintf(enter,"\n");

                printf("\nSuccesfully requested booking\n");
                fclose(enter);
                break;

            }
            default:
            {
                printf("\nWrong entry!\n");
            }
            }

            printf("Would you like to continue? (y/n)\n");
            scanf("%s",user_entry);

        }
        if(strcmp(user_entry,"n") == 0)
        {
            printf("\n....Exited....\n");
            //system("clear");
            return 0;
        }
        else
        {
            printf("Wrong entry!\n....Exited....\n");
            return 0;
        }
        break;
    }
    }
}

//method declare to enter name
void enter_name()
{

    FILE *tem1;
    FILE *tem2;

    printf("\nEnter guest name --> ");
    scanf("%s",h.name);
    printf("\nEnter their room number --> ");
    scanf("%s",h.room);
    printf("\nEnter wifi plan (1GB/5GB) --> ");
    scanf("%s",h.wifi);
    printf("\nEnter if breakfast is included --> ");
    scanf("%s",h.bf);

    //entering guests
    fp = fopen("hotelnew.txt","a");

    if( fp == NULL)
    {
        printf("\nFile not found");
        exit(1);
    }
    else
    {
        fprintf(fp,"%s %s %s %s",h.name,h.room,h.wifi,h.bf);
        fprintf(fp,"\n");
        printf("\nDone\n");
    }
    fclose(fp);

    //
    char remove_guest[20];
    strcpy(remove_guest,h.name);
    char remove_room[20];
    strcpy(remove_room,h.room);

    //removing booking
    tem1 = fopen("tem1.txt","a");
    enter = fopen("bookings.txt","r");

    while(fscanf(enter,"%s %s %s",h.name,h.room,h.wifi) != -1)
    {
        fgetc(enter);
        fgets(h.bf, 20, (FILE*)enter);
        if(strcmp(h.name,remove_guest) != 0)
        {
            fprintf(tem1,"%s %s %s %s",h.name,h.room,h.wifi,h.bf);
            fprintf(tem1,"\n");
        }
    }
    fclose(enter);
    fclose(tem1);
    remove("bookings.txt");
    rename("tem1.txt","bookings.txt");

    //removing room
    tem2 = fopen("tem2.txt","a");
    view = fopen("rooms.txt","r");


    while(fscanf(view,"%s",h.room) != -1)
    {
        if(strcmp(h.room,remove_room) != 0)
        {
            fprintf(tem2,"%s",h.room);
            fprintf(tem2,"\n");
        }
    }
    fclose(view);
    fclose(tem2);
    remove("rooms.txt");
    rename("tem2.txt","rooms.txt");
}

//method defined to find quest name
void find_name()
{
    char entered_name[20];
    int guestFound =0;

    printf("\nEnter guest name to find -->");
    scanf("%s",entered_name);

    fp = fopen("hotelnew.txt","r");
    while(fscanf(fp,"%s %s %s",h.name,h.room,h.wifi) != -1)
    {
        fgets(h.bf, 20, (FILE*)fp);
        if(strcmp(h.name,entered_name) == 0)
        {
            guestFound = 1;
            printf("\nGuest found!");
            printf("\nName  is %s",h.name);
            printf("\nRoom number is %s",h.room);
            printf("\nWiFi plan is %s",h.wifi);
            printf("\nBreakfast included %s",h.bf);

        }
    }
    if(guestFound == 0)
    {
        printf("\nGuest %s not found!\n", entered_name);
    }
    fclose(fp);
}

//method definition for guest checkout
void checkout_guest()
{
    char checkout_room[20];
    FILE *tem5;

    printf("Enter Room number to checkout->>\n");
    scanf("%s",checkout_room);

    tem5=fopen("tem5.txt","a");
    fp=fopen("hotelnew.txt","r");

    if(fp==NULL)
    {
        printf("File not found");
        exit(1);
    }
    else
    {
        while(fscanf(fp,"%s %s %s",h.name,h.room,h.wifi)!=-1)
        {
            fgetc(fp);
            fgets(h.bf,20,(FILE*)fp);
            if(strcmp(h.room,checkout_room)!=0)
            {
                fprintf(tem5,"%s %s %s %s",h.name,h.room,h.wifi,h.bf);
                fprintf(tem5,"\n");
            }
        }
    }
    fclose(fp);
    fclose(tem5);

    remove("hotelnew.txt");
    rename("tem5.txt","hotelnew.txt");
    printf("\nRoom check out successfully!");

    //room added to room-list
    view = fopen("rooms.txt","a");
    fprintf(view,"%s",checkout_room);
    fprintf(view,"\n");
    printf("\n%s added to room-list\n",checkout_room);
    fclose(view);
}

//method definition for finding rooms available
void find_room()
{
    char entered_room[20];
    int roomFound =0;
    printf("\nEnter room number to find -->");
    scanf("%s",entered_room);

    fp = fopen("hotelnew.txt","r");
    while(fscanf(fp,"%s %s %s",h.name,h.room,h.wifi) != -1)
    {
        fgets(h.bf, 20, (FILE*)fp);
        if(strcmp(h.room,entered_room) == 0)
        {
            roomFound = 1;
            printf("\nRoom found!");
            printf("\nName  is %s",h.name);
            printf("\nRoom number is %s",h.room);
            printf("\nWiFi plan is %s",h.wifi);
            printf("\nBreakfast included %s",h.bf);
        }
    }
    if(roomFound == 0)
    {
        printf("\nRoom %s not found!\n", entered_room);
    }
    fclose(fp);
}

//method defined to view bookings
void view_bookings()
{

    enter = fopen("bookings.txt","r");

    while(fscanf(enter,"%s %s %s",h.name,h.room,h.wifi) != -1)
    {
        fgets(h.bf, 20, (FILE*)enter);
        printf("%s %s %s %s \n",h.name,h.room,h.wifi,h.bf);
    }
    fclose(enter);
}
