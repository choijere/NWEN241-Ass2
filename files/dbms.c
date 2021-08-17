
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dbms.h"


// Task 4
//Displays the information stored in a row. return 1 on success. return 0 on failure
int db_show_row(struct db_table *db, unsigned int row)
{
	if(row > db->rows_used) //row number exceeds the rows used, return 0
	{
		return 0;
	}
	else
	{
		printf("ID: %lu \n", db->table[row].id);
		printf("Title: %s \n", db->table[row].title);
		printf("Year: %i \n", db->table[row].year);
		printf("Artist: %s \n", db->table[row].artist);
		
		return 1;
	}
}

// Task 5
//Adds a record into the database table. return 1 on success. return 0 on failiure
int db_add_row(struct db_table *db, struct album *a)
{
	//if db has no table yet
	if(db->table == NULL)
	{
		db->table = malloc(5*sizeof(struct album));
		if(db->table == NULL)
		{
			return 0;
		}
		db->rows_used = 0;
		db->rows_total = 5;
	}
	
	//Space present, fill in the blanks!
	if(db->rows_used < db->rows_total)
	{
		//copy album
		db->table[db->rows_used] = *a;
		
		//update space used
		db->rows_used += 1;
		return 1;
	}
	//Need more space
	else if(db->rows_used == db->rows_total)
	{
		//Add 5 additional rows
		db->table = realloc(db->table, (db->rows_total+5)*sizeof(struct album));
		db->rows_total += 5;
		
		//copy album
		db->table[db->rows_used] = *a;
		
		//update space used
		db->rows_used += 1;
		return 1;
	}
	
	return 0;
}

//Task 6
//removes an album. frees 5 spaces when they go unused
int db_remove_row(struct db_table *db, unsigned long id)
{
	//look for the album
	for(int i = 0; i < db->rows_used; i++)
	{
		//album found!
		if(db->table[i].id == id)
		{
			//erase the found album
			memmove(db->table+i, db->table+1+i, (db->rows_total-i) * sizeof(struct album));
			db->rows_used--;
			
			//5 unused slots, free those spaces!
			if((db->rows_total - db->rows_used) == 5)
			{
				db->table = realloc(db->table, (db->rows_total-5)*sizeof(struct album));
				db->rows_total -= 5;
			}
			return 1;
		}
	}
	//album not found!
	return 0;
}



