#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

#define jeda Sleep(1e3); system("cls");
#define p printf
#define s scanf

char 
q1[8][100] = 
{
    "Menu: ", "Add Flight", 
    "Delete Flight", "Make Reservation", 
    "Cancel Reservation", "Display All Records", "Exit", "Select an option:"
},
q2[7][100] = 
{
    "Flight number", "Departure City", "Destination",
    "Departure Time (YYYY-MM-DD HH:MM)", "Arrival Time (YYYY-MM-DD HH:MM)", 
    "Number of Available First-Class Seats",
    "Number of Available Coach Seats"
};

struct flight {
    char 
        fn[10], // Flight number
        cdep[100], // City Departure
        cdes[100], // City Destination
        tdep[20], // Date and time departure
        tarr[20]; // Date and time arrival
    int 
        frca, // first-class seats still available
        frcs, // first-class seats sold
        coca, // coach seats still available
        cocs; // coach seats sold
};

int fc = 0, mf = 100, i, j; // flight count, max flight
struct flight f[100];

void save()
{
    FILE *file = fopen("flightdatabase.txt", "w");
    for(i = 0; i < fc; i++)
    {
        fprintf(file, "Flight %d: \n%s\n%s\n%s\n%s%s%d\n%d\n%d\n%d\n",
            i + 1, f[i].fn, f[i].cdep, f[i].cdes, f[i].tdep, f[i].tarr,
            f[i].frca, f[i].frcs, f[i].coca, f[i].cocs);
    }
    fclose(file);
}

// YYYY-MM-DD HH:MM
bool validate_time_format3(char *time)
{
    int month, day, hour, minute;
    month  = (time[5] - '0') * 10 + (time[6] - '0');
    day    = (time[8] - '0') * 10 + (time[9] - '0');
    hour   = (time[11] - '0') * 10 + (time[12] - '0');
    minute = (time[14] - '0') * 10 + (time[15] - '0');

    if(month > 12 || day > 31 || hour > 23 || minute > 59)
        return false;
    return true;
}

void add_flight()
{
    if(fc >= mf)
    {
        p("Unable to add more flight data . . .\n"); jeda;
        return;
    }

    for(i = 0; i < 7; i++)
    {
        p("%d. Enter %s: ", i + 1, q2[i]);
        switch (i)
        {
            case 0: s(" %s", f[fc].fn); break;
            case 1: getchar(); fgets(f[fc].cdep, 100, stdin); break;
            case 2: fgets(f[fc].cdes, 100, stdin); break;
            case 3: fgets(f[fc].tdep, 20, stdin); break;
            case 4: fgets(f[fc].tarr, 20, stdin); break;
            case 5: s(" %d", &f[fc].frca); break;
            case 6: s(" %d", &f[fc].coca); break;
        }
    }

    // Cek Apakah Flight Numbernya Unik
    for(i = 0; i < fc; i++)
    {
        if(strcmp(f[fc].fn, f[i].fn))
            continue;
        
        system("cls"); p("Flight Number Already Exist . . ."); jeda;
        return;
    }

    // Cek input time format 1
    if((strlen(f[fc].tdep) ^ 17) || (strlen(f[fc].tarr) ^ 17))
    {
        system("cls"); p("Invalid Time Input Format . . ."); jeda;
        return;
    }

    // Cek input time format 2
    bool cek1, cek2; int cek3 = 0; 
    char cek4[17] = "11110110110110110";
    for(i = 0; i < 17; i++)
    {
        cek1 = cek2 = false;
        if(f[fc].tarr[i] >= '0' && f[fc].tarr[i] <= '9')
            cek1 = true;
        if(f[fc].tdep[i] >= '0' && f[fc].tdep[i] <= '9')
            cek2 = true;
        
        if(cek4[i] & 1)
            cek3 += (cek1 & cek2); 
    }
    if(cek3 ^ 12 || f[fc].tarr[4] != '-' || f[fc].tarr[7] != '-' || f[fc].tarr[10] != ' ' || f[fc].tarr[13] != ':')
    {
        system("cls"); p("Invalid Time Input Format . . ."); jeda;
        return;
    }

    //Cek Input time Format 3
    if(!(validate_time_format3(f[fc].tarr) & validate_time_format3(f[fc].tdep)))
    {
        system("cls"); p("Invalid Time Input Format . . ."); jeda;
        return;
    } 

    // Cek Validitas input kursi
    if(f[fc].frca < 0 || f[fc].coca < 0)
    {
        system("cls"); p("Number of seats must be non-negative . . ."); jeda;
        return;
    }

    f[fc].frcs = f[fc].cocs = 0;
    system("cls"); fc++; save();
    p("Add Flight Successfully . . .\n"); jeda;
}

void delete_flight()
{
    if(!fc) 
    {
        p("No flight data can be deleted . . .\n"); jeda;
        return;
    }
    
    bool cek = false; char id[10]; 
    p("Enter Flight Number to Delete: "); s(" %s", id); 
    for(i = 0; i < fc; i++)
    {
        if(strcmp(f[i].fn, id))
            continue;
        
        cek = true;
        for(j = i; j < fc - 1; j++)
            f[j] = f[j + 1];
        fc--; save(); break;
    }
    system("cls"); p(cek ? "Flight Deleted Successfully . . ." : "Flight Not Found . . ."); jeda;
}

void make_reservation ()
{
    if(!fc)
    {
        system("cls"); p("No Flight Data Added Yet . . .\n"); jeda;
        return;
    }

    char id[10], ch; int n;
    p("Enter %s: ", q2[0]);
    bool cek1 = false, cek2;
    s(" %s", id);

    // Cari pesawatnya berdasarkan id
    for(i = 0; i < fc; i++)
    {
        if(strcmp(f[i].fn, id))
            continue;

        cek1 = cek2 = true; do
        {
            p("Select seat type (1. First-Class, 2. Coach): ");
            s(" %c", &ch);
            switch (ch)
            {
                case '1':
                    p("Enter number of tickets to book: ") ;s(" %d", &n);
                    if(f[i].frca >= n)
                    {
                        f[i].frca -= n,
                        f[i].frcs += n;
                    }
                    else 
                    {
                        p("Not Enough Seat Available . . .\n");
                        cek2 = false; jeda;
                    }
                    break;
                case '2':
                    p("Enter number of tickets to book: ") ;s(" %d", &n);
                    if(f[i].coca >= n)
                    {   
                        f[i].coca -= n,
                        f[i].cocs += n;
                    }   
                    else 
                    {
                        p("Not Enough Seat Available . . .\n");
                        cek2 = false; jeda;
                    }
                    break;
                default:
                {
                    p("Booking Failed. Invalid Seat Type Input\n"); jeda;
                    break;
                }
            }
        } while(ch != '1' && ch != '2');
    }
    system("cls");
    if(cek1) 
    {
        if(cek2)
            p("Reservation Successfuly . . .\n");
        else 
            p("Reservation Unsuccessfuly . . .\n");
    }
    else p("Flight not Found . . .\n");
    jeda;
}

void cancel_reservation()
{
    if(!fc)
    {
        system("cls"); p("No Flight Data Added Yet . . .\n"); jeda;
        return;
    }

    char id[10], ch; int n;
    p("Enter %s: ", q2[0]);
    bool cek1 = false, cek2;
    s(" %s", id);

    //Cari pesawat berdasarkan id
    for(i = 0; i < fc; i++)
    {
        if(strcmp(f[i].fn, id))
            continue;
        
        cek1 = true; do
        {
            p("Select seat type to cancel (1. First-Class, 2. Coach): ");
            s(" %c", &ch); cek2 = true;
            switch(ch)
            {
                case '1':
                    p("Enter number of tickets to cancel: "); s(" %d", &n);
                    if(f[i].frcs >= n)
                    {
                        f[i].frcs -= n,
                        f[i].frca += n;
                    }
                    else
                    {
                        p("Invalid Tickets to Cancel: \n");
                        jeda; cek2 = false;
                    }
                    break;
                case '2':
                    p("Enter number of tickets to cancel: "); s(" %d", &n);
                    if(f[i].cocs >= n)
                    {
                        f[i].cocs -= n, 
                        f[i].coca += n;
                    }
                    else
                    {
                        p("Invalid Tickets to Cancel: \n");
                        jeda; cek2 = false;
                    }
                    break;
                default:
                {
                    p("Cancellation Failed. Invalid Seat Type Input\n"); 
                    jeda;
                }
                break;
            }
        } while(ch != '1' && ch != '2');
    }
    system("cls"); 
    if(cek1)
        p(cek2 ? "Reservation Successfuly . . ." : "Reservation Unsuccessfuly . . .");
    else p("Flight not Found . . .\n");
    jeda;
}

void display_flights()
{
    if(!fc)
    {
        system("cls"); p("No flight data to display . . .\n"); jeda;
        return;
    }

    for(i = 0; i < fc; i++)
    {
        p("\nFlight %d:\n", i + 1);
        for(j = 0; j < 7; j++)
        {
            p("%d.%d) %s: ", i + 1, j + 1, q2[j]);
            switch (j)
            {
                case 0: p(" %s\n", f[i].fn); break;
                case 1: p(" %s", f[i].cdep); break;
                case 2: p(" %s", f[i].cdes); break;
                case 3: p(" %s", f[i].tdep); break;
                case 4: p(" %s", f[i].tarr); break;
                case 5: p(" %d\n", f[i].frca); break;
                case 6: p(" %d\n", f[i].coca); break;
            }
        }
    }   

    p("Press Enter to Continue . . .\n");
    while(getchar() != '\n');
    getchar(); 
    return;
}

int main()
{
    char ch; 
    do 
    {
        for(i = 0; i < 8; i++)
        {
            if(i && i <= 6)
                printf("%d. ", i);
            printf("%s\n", q1[i]);
        }
        scanf(" %c", &ch);
        system("cls");
        switch (ch)
        {
            case '1': // Add Flight
                add_flight();
                break;
            case '2': // Delete Flight
                delete_flight();
                break;
            case '3': // Make Reservation
                make_reservation();
                break;
            case '4': // Cancel Reservation
                cancel_reservation();
                break;
            case '5': // Display
                display_flights();
                system("cls");
                break;
            default:
                if(ch ^ '6') {
                    p("Invalid Option\n"); jeda;
                } break;
        }
    } while(ch != '6');
    p("Exit . . ."); jeda;
    return 0;
}
