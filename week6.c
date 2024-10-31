/*
 ============================================================================
 Name        : week6.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Personal Project. A way to create data entries and put them into text files. Purpose: to make a little
 diary on my computer. Also being able to edit entires, delete entries, etc.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void CreateDiaryEntry() {
	char title[50];
	char content[1000];
	char filename[100] = "diary/";

	//Let user put a title for the entry
	printf("Title of entry: ");
	scanf("%49s", title);
	getchar();

	//Add title to filename.
	strcat(filename, title);
	strcat(filename, ".txt");

	//opens a file and allows user to write in it.
	FILE *file = fopen(filename, "w");
	if (file == NULL) {
	    printf("Error creating file!\n");
	    return;
	    }
	//get the content of diary from the user.
	printf("Enter your diary entry content (end with a single period '.'): \n");
	while (1) {
	    fgets(content, sizeof(content), stdin);
	    if (strcmp(content, ".\n") == 0) break;
	    fprintf(file, "%s", content);
	    }
	fclose(file);
	printf("Diary entry created successfully!\n");
}

void DisplayDiaryEntry() {
	char title[50];
	char filename[100] = "diary/";

	printf("Enter the title of the diary to display: ");
	scanf("%49s", title);
	getchar();

	strcat(filename, title);
	strcat(filename, ".txt");

	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("Diary entry not found!\n");
		return;
	}
	printf("Contents of %s:\n", title);
	char line[1000];
	while (fgets(line, sizeof(line), file) != NULL) {
		printf("%s", line);
	}
	fclose(file);
}

void EditDiaryEntry() {
	char title[50];
	char content[1000];
	char filename[100];

	printf("Enter the title of the diary entry to edit: ");
	scanf("%49s", title);
	getchar();

	strcat(filename, title);
	strcat(filename, ".txt");

	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		printf("Diary entry not found!\n");
		return;
	}

	printf("Enter the new content (end with a single period '.'): \n");
	while (1) {
		fgets(content, sizeof(content), stdin);
		if (strcmp(content, ".\n") == 0) break;
		fprintf(file, "%s", content);

	}

	fclose(file);
	printf("Diary entry edited successfully!\n");
}

void DeleteDiaryEntry() {
	char title[50];
	char filename[100] = "diary/";

	printf("Enter the title of the diary entry to delete: ");
	scanf("%49s", title);
	getchar();

	strcat(filename, title);
	strcat(filename, ".txt");

	if (remove(filename) == 0) {
		printf("Diary entry deleted successfully!\n");
	}else {
		printf("Error deleting the diary entry. It may not exist.\n");
	}
}


int main() {
	struct stat st = {0};
	if (stat("diary", &st) == -1) {
	    mkdir("diary");
	}

	int choice;
	do {
	    printf("\nDiary Menu:\n");
	    printf("1. Add a new entry\n");
	    printf("2. Display an entry\n");
	    printf("3. Edit an entry\n");
	    printf("4. Delete an entry\n");
	    printf("5. Exit\n");
	    printf("Enter your choice: ");
	    scanf("%d", &choice);
	    getchar();  // Clear newline after scanf

	    switch (choice) {
	        case 1:
	            CreateDiaryEntry();
	            break;
	        case 2:
	            DisplayDiaryEntry();
	            break;
	        case 3:
	            EditDiaryEntry();
	            break;
	        case 4:
	            DeleteDiaryEntry();
	            break;
	        case 5:
	            printf("Exiting the program.\n");
	            break;
	        default:
	            printf("Invalid choice. Please try again.\n");
	        }
	    } while (choice != 5);
	return 0;
}
