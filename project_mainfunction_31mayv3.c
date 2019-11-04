#include <stdio.h>
#include <stdlib.h>
#include <string.h>



float velocity_mps(float velocity)

{  
	float velocity_mps;
	velocity_mps = (1000.0/3600.0)*velocity;
	
	return velocity_mps;
		
}

/*
float impact_force(int mass,float velocity_mps,int stopping_distance)//arguments need to be corrected

{   
	float force;
	force = (0.5*mass*(velocity_mps)*(velocity_mps))/stopping_distance;
	return force; //this is the value when you call force
	
}*/



typedef struct
{
    int Test_ID;
	char Vehicle_ID[20];
	char Obstacle_ID[20];
	int Vehicle_age_t;
	int Impact_velocity_t;
	int Number_of_passengers_t;
	int Number_of_seatbelt_wearing_passengers_t;
	float Safety_rate_t;
	float Damage_rate_t;
	float Passenger_survival_rate_t;

}Results;


typedef struct 
{
    int Vehicle_number;
	char Vehicle_name[20];
    int Manufacture_date;
    int Top_speed;
	int Mass;
    int Number_of_seats;
    	
}Vehicle;

typedef struct
{
    int Obstacle_number;
	char Obstacle_name[20];
	int Stopping_distance;

}Obstacle;

float impact_force(Vehicle V[],float Impact_velocity_mps, Obstacle O[], int Vehicle_chosen, int Obstacle_chosen)//***might need to bring the whole array as argument

{   
	float force;
	force = (0.5*V[Vehicle_chosen-1].Mass*(Impact_velocity_mps)*(Impact_velocity_mps))/O[Obstacle_chosen-1].Stopping_distance;
	return force; //this is the value when you call force
	
}

void crash_simulation(Vehicle V[], Obstacle O[], int user_has_acceptedvalues, Results S_s[] )
{
    int Vehicle_chosen, Obstacle_chosen, Results_save, current_date=2019;
    int Vehicle_age, Number_of_passengers, Number_of_seatbelt_wearing_passengers;
	float Impact_velocity, Impact_velocity_mps, Impact_force_calculated;
	float Safety_rate,AllPassenger_survival_rate_seatbelton, Passenger_survival_rate_seatbeltwithout;//*******might need to adjust arguments
	
    
	do
	{   
	    
        printf("Please select a vehicle and obstacle number:\n");
        scanf("%d %d", &Vehicle_chosen, &Obstacle_chosen);
    
        if(Vehicle_chosen < 1 || Vehicle_chosen > 10 ||	Obstacle_chosen < 1 || Obstacle_chosen > 10)
	    {
	        printf("Error Invalid Vehicle or Obstacle number\n");
	    }
	    else
	    {
	        printf("Please enter the Vehicle age rounded off to the nearest year and Impact velocity in kmph\n");
		    scanf("%d %f", &Vehicle_age, &Impact_velocity);
		
		    if(Vehicle_age > current_date - V[Vehicle_chosen-1].Manufacture_date || Vehicle_age < 0 || Impact_velocity > V[Vehicle_chosen-1].Top_speed || Impact_velocity < 0)
		    {
		        printf("Invalid Vehicle age or Impact velocity\n");
		    }
		    else
		    {
		        printf("Please enter the number of passenger and the number of passengers wearing a seatbelt\n");
			    scanf("%d %d", &Number_of_passengers, &Number_of_seatbelt_wearing_passengers);
			    if( Number_of_passengers > V[Vehicle_chosen-1].Number_of_seats || Number_of_passengers < 0 ||Number_of_seatbelt_wearing_passengers > Number_of_passengers || Number_of_seatbelt_wearing_passengers<0)
			    {
			        printf("Invalid number of passengers or number of seatbelt wearing passengers\n");
			    }
			    else
			    {
			
			            
				        float Safety_rate = 1;
			            printf("Valies entered have been processed\n");
				
				        Safety_rate -=  0.25*(Vehicle_age - 2)*(Vehicle_age - 2);
					
                        Impact_velocity_mps = velocity_mps(Impact_velocity); //decrease safety rate by force 
					    Impact_force_calculated = impact_force(V, Impact_velocity_mps, O, Vehicle_chosen, Obstacle_chosen);
                        Safety_rate -= Impact_force_calculated/10000.0;
					
			            printf("DETAILS: Safety rate:%f..........\n", Safety_rate);//Safety_rate_final = x ****finish if statement
					    printf("If you accept this information enter '1',if you would like to regenerate all conditions enter '0'\n");
					    scanf("%d", &user_has_acceptedvalues);
				
			    }
		    }
        }
    }
    while(user_has_acceptedvalues < 1);
    printf("Starting crash test\n");
	
	//damage rate calculate
	
	
	// survival rate
	
	
	if( Number_of_passengers > Number_of_seatbelt_wearing_passengers)
	{
	    AllPassenger_survival_rate_seatbelton = Safety_rate/4;
        Passenger_survival_rate_seatbeltwithout = Safety_rate/9;		
	}
	
	AllPassenger_survival_rate_seatbelton = Safety_rate;
	Passenger_survival_rate_seatbeltwithout = Safety_rate;
	
	printf("Safety rate: %f\n", Safety_rate);
	//***Print the table here
	
	
	//save simulations to the array. Save function will take all info from this array
	//****fix saving warnings
	printf("If you would like to save these results press 1, if not press 0\n");
	scanf("%d", &Results_save);
	if(Results_save = 1)
	{    //***Make counter for test ID
	    S_s[0].Test_ID = 1;
	    strcpy(S_s[0].Vehicle_ID, V[Vehicle_chosen-1].Vehicle_name);
	    strcpy(S_s[0].Obstacle_ID, O[Obstacle_chosen-1].Obstacle_name);
	    S_s[0].Vehicle_age_t = Vehicle_age;
	    S_s[0].Impact_velocity_t = Impact_velocity_mps;
	    S_s[0].Number_of_passengers_t = Number_of_passengers;
	    S_s[0].Number_of_seatbelt_wearing_passengers_t = Number_of_seatbelt_wearing_passengers;
	    S_s[0].Safety_rate_t = Safety_rate;
	    S_s[0].Damage_rate_t = 0.0; //not yet calculated
	    S_s[0].Passenger_survival_rate_t = Passenger_survival_rate_seatbeltwithout;
	    
        //refer to files lab 10 for example
		FILE* irfile = fopen("individual_results.txt", "w");
		if(irfile == NULL)
		{
		    printf("Unable to open the file!\n");
            //exit(-1)			
	    }
	
	    fprintf(irfile, "%d %s %s %d %d %d %d %f %f %f\n",
		S_s[0].Test_ID, S_s[0].Vehicle_ID, S_s[0].Obstacle_ID, S_s[0].Vehicle_age_t, 
		S_s[0].Impact_velocity_t, S_s[0].Number_of_passengers_t, S_s[0].Number_of_seatbelt_wearing_passengers_t,
		S_s[0].Safety_rate_t, S_s[0].Damage_rate_t, S_s[0].Passenger_survival_rate_t);
		

		fclose(irfile);
	}
}


void input_or_update_oinfo(int update_onum, Obstacle O_i[])
{
    if(update_onum > 0 && update_onum < 11)
	{
	    O_i[update_onum - 1].Obstacle_number = update_onum;
        printf("Please also enter the Obstacle name and Stopping distance\n");
        scanf("%s %d", O_i[update_onum - 1].Obstacle_name, &O_i[update_onum - 1].Stopping_distance); 		
	    printf("Obstacle %d updatred\n", O_i[ update_onum - 1].Obstacle_number);	
	}
    else
	{
	    printf("Invalid number\n");
	}


}

void Obstacle_search(int n_o_o, char o_s[], Obstacle O[])
{
    int i,is_found;
	
	for(i = 0; i < n_o_o; i++) 
	{
	    if (strcmp(O[i].Obstacle_name, o_s) ==0)// ==0 means same,remember == equates and =  defines
		{
		    printf("Obstacle number:%d  Obstacle name:%s  Stopping distance:%d\n",
			O[i].Obstacle_number, O[i].Obstacle_name, O[i].Stopping_distance);
			//******create a variable is found
			is_found = 1;
		
		} 
	}
	if( is_found == 1)
	{
	    printf("Obstacle details\n");
	}
	else
	{
	    printf("Obstacle not found\n");
	}




}

void save_Vehicle_Obstacle_info(Vehicle V[], Obstacle O[])
{
    //Vehicle names
	FILE* Vfile = fopen("Vehicle.txt", "w");
	if(Vfile == NULL)
	{
	    printf("unable to open the file!\n");
	    //exit(-1);
	}
    int i;
	for(i = 0; i < 3; i++)
	{
	    fprintf(Vfile, "%s\n", V[i].Vehicle_name);
	
	}
	
	fclose(Vfile);
	
	
	//Obstacle names
	FILE* Ofile = fopen("Obstacle.txt", "w");
	if(Ofile == NULL)
	{
	    printf("unable to open the file!\n");
	    //exit(-1);
	}
    int a;
	for(a = 0; i < 3; i++)
	{
	    fprintf(Ofile, "%s\n", O[a].Obstacle_name);
	
	}
	
	fclose(Ofile);
	




}


void input_or_update_vinfo(int update_vnum, Vehicle V_i[])
{
    if( update_vnum  > 0 && update_vnum < 11)
	{   
	    V_i[update_vnum - 1].Vehicle_number = update_vnum;
	    printf("Please also enter the Vehicle name, Manufacture date, Top speed, Mass and Number of seats(leave only a space between each value)\n"); 
        scanf("%s %d %d %d %d", V_i[update_vnum - 1].Vehicle_name, &V_i[update_vnum - 1].Manufacture_date, &V_i[update_vnum - 1].Top_speed,
		&V_i[update_vnum - 1].Mass, &V_i[update_vnum - 1].Number_of_seats);
        printf("Vehicle %d updated\n", V_i[update_vnum - 1].Vehicle_number);	
	
	}
	else
	{   
	    printf("Invalid number\n");
	
	
	}




}

void Vehicle_search(int n_o_v, char c_s[], Vehicle V[])
{
    int i,is_found;
	
    for(i = 0; i < n_o_v; i++) 
	{
	    if (strcmp(V[i].Vehicle_name, c_s) ==0)// ==0 means same,remember == equates and =  defines
		{
		    printf("Car number:%d  Car name:%s  Manufacture date:%d  Top speed:%d  Mass:%d  Number of seats:%d\n",
		    V[i].Vehicle_number, V[i].Vehicle_name, V[i].Manufacture_date,
			V[i].Top_speed, V[i].Mass, V[i].Number_of_seats);
			//******create a variable is found
			is_found = 1;
		
		} /*******remove else statement and put new if statement OUTSIDE the loop to show it is found
		else
		{
		    printf("Not found!\n");   
		} */
	}
	if( is_found == 1)
	{
	    printf("Vehicle details\n");
	}
	else
	{
	    printf("Vehicle not found\n");
	}
    //While loop can be used at bottom of switch statement
}


/*format - print a menu,asign each item to a number,select a number,
when user selects it performs that function with user inputs */

int main(void)
{  
    int number_of_vehicles = 3;//****where to declare it
	int main_menu_selection;
	
	Vehicle Vehicle_info[10];
    Vehicle_info[0] = (Vehicle){ 1, "Toyota", 1991, 200, 1100, 5 }; 
	Vehicle_info[1] = (Vehicle){ 2, "Bugatti", 2005, 415, 1888, 2 };
	Vehicle_info[2] = (Vehicle){ 3, "Alexander Dennis", 2005, 129, 18000, 90 };
	
	//open file for reading
    FILE* Vehiclefile = fopen("Vehicle.txt", "r");
    if (Vehiclefile == NULL)
    {
        printf("unable to open the file!There might be no vehicle information\n");
	    //exit(-1);
    }
	int number, date, t_speed, kg, 	seats, i;
	char name[20];
	
	
	for(i = 0; i < number_of_vehicles ; i++)
	{
	    fscanf(Vehiclefile, "%d" "%s" "%d" "%d" "%d" "%d", &number, name, &date, &t_speed, &kg, &seats);
	    Vehicle_info[i].Vehicle_number = number;
	    strcpy(Vehicle_info[i].Vehicle_name, name);
	    Vehicle_info[i].Manufacture_date = date;
	    Vehicle_info[i].Top_speed = t_speed;
	    Vehicle_info[i].Mass = kg;
	    Vehicle_info[i].Number_of_seats = seats;
	}
    fclose(Vehiclefile);
	
	
    
	
	Obstacle Obstacle_info[10];
	//Obstacle_info[n] = (Obstacle){ number, "string", number};
	
	Obstacle_info[0] = (Obstacle){ 1, "bus", 50};
	Obstacle_info[1] = (Obstacle){ 2, "tree", 100};
	Obstacle_info[2] = (Obstacle){ 3, "house", 150};
	
	
	FILE* Obstaclefile = fopen("Obstacle.txt", "r");
    if (Obstaclefile == NULL)
    {
        printf("unable to open the file!\n");
	    //exit(-1);
    }
	int O_number, S_distance;
	char O_name[20];
	for(i = 0; i < number_of_vehicles ; i++)
	{
	    fscanf(Obstaclefile, "%d %s %d", &O_number, O_name, &S_distance);//****error with char value
	    Obstacle_info[i].Obstacle_number = O_number;
	    strcpy(Obstacle_info[i].Obstacle_name, O_name);
	    Obstacle_info[i].Stopping_distance = S_distance;
	}
	fclose(Obstaclefile);
	
	
	//Display menu
	printf("CRASH TEST SIMULATOR\n");
	printf("1. Search a vehicle\n");
	printf("2. Search an obstacle\n");
	printf("3. Input?update vehicle information \n");
	printf("4. Input/update obstacle information \n");
	printf("5. Simulate a vehicle crash test against an obstacle\n");
	printf("6. Display simulation results\n");
	printf("7. Display all results\n");
	printf("8. Save all results\n");
	printf("9. Save vehicle/obstacle information\n");
	printf("10. Exit\n");
	
	printf("Please select a menu item\n");
	scanf("%d", &main_menu_selection);
	
	//if statement for valid selection
	if( main_menu_selection < 1 || main_menu_selection > 10)//*****make do while loop later
	{
	    printf("Invalid selection\n");
	}
	else
	{
	//use switch statement for inputs(example photo 30.5)
	    int update_Vehicle_number;
        int number_of_vehicles = 3;
        int i, number_of_Obstacles = 3;		 //index is vehicle number
	    char car_selection[20];

        int number_of_obstacles = 3; 
	    char obstacle_selection[20];

        int update_Obstacle_number;

        int user_has_acceptedvalues;

        int Simulations_saved;		
	    switch(main_menu_selection)
		{
		    case 1:
            for(i = 0; i < number_of_vehicles; i++)
	        {
	            printf("Vehicle name:%s\n", Vehicle_info[i].Vehicle_name);//****why is it printing i for all,declarations?? 
	        }
	
	        printf("Please select one of the available vehicles by name\n"); 
	        scanf("%19s", car_selection);
	
	        Vehicle_search(number_of_vehicles, car_selection, Vehicle_info);
	            
        
            break;	

            case 2:
	        for(i = 0; i < number_of_obstacles; i++)
	        {
	        printf("Vehicle name:%s\n", Obstacle_info[i].Obstacle_name); 
	        }
	
	        printf("Please select one of the available obstacles by name\n");//****X to exit 
	        scanf("%19s", obstacle_selection);
	
	        Obstacle_search(number_of_obstacles, obstacle_selection, Obstacle_info);
            break;					
			
			case 3:
                //type code from search vehicle item
			    printf("Please enter the number of the vehicle you want to add or edit: \n");
	            scanf("%d", &update_Vehicle_number);
	
	            input_or_update_vinfo(update_Vehicle_number, Vehicle_info);
	            
        
            break;
			
			case 4:
            //Input/upodate obstacle info
			printf("Please enter the number of the obstacle you want to add or edit: \n");
	        scanf("%d", &update_Obstacle_number);
	
	        input_or_update_oinfo(update_Obstacle_number, Obstacle_info);
        
            break;
			
			case 5:
            //crash simulation against obstacle
            crash_simulation(Vehicle_info, Obstacle_info, user_has_acceptedvalues, Simulations_saved);
            break;
			
			case 6:
            //Display simulation results
        
            break;
			
			case 7:
            //Display all results
        
            break;
			
			case 8:
            //save all results
        
            break;
			
			case 9:
            //save vehicle/obstacle info
			save_Vehicle_Obstacle_info(Vehicle_info, Obstacle_info);
        
            break;
			
			case 10:
            //Exit
        
            break;
			
			
			
	    }
	
	}
	
	return 0;
}