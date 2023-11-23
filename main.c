#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 25

typedef struct User {
	char mail[BUFFER_SIZE];
	char password[BUFFER_SIZE];
	int id;
} User;

int mailExist(char* m);
int countLines();
int signUp();

void main()
{
	signUp();
}


int login()
{

}

int signUp()
{
	/*
	This function get the new user cardentials, check if the mail already mailExist,
	generate ID and store the data in the users text file.
	Input: none
	Output: 1 if there was an error, 0 else
	*/

	User* newUser = malloc(sizeof(User));
	FILE* fp;

	system("CLS");

	printf("Email: ");
	scanf("%s", newUser->mail);
	printf("Password: ");
	scanf("%s", newUser->password);

	if (mailExist(newUser->mail)) {
		system("CLS");
		printf("Email already exist\n");
		return 1;
	}
	else {
		newUser->id = countLines() + 1;
		fp = fopen("users.txt", "a");
		fprintf(fp, "%s,%s,%d\n", newUser->mail, newUser->password, newUser->id);
		fclose(fp);
		system("CLS");
		printf("Congrates, You Signed Up!\n");
	}

	return 0;
}

int mailExist(char* m)
{
	FILE* fp = fopen("users.txt", "r");
	User* curr = malloc(sizeof(User));

	while (fscanf(fp, "%[^,],%[^,],%d\n", curr->mail, curr->password, &curr->id) == 3){
		/* DEBUG
		printf("Now chacking: \n");
		printf("%s\n", curr->mail);
		printf("%s\n", curr->password);
		printf("%d\n", curr->id);
		printf("---------------------------------\n");
		*/
		if (strcmp(m, curr->mail) == 0) {
			fclose(fp);
			free(curr);
			return 1;
		}
	}

	fclose(fp);
	free(curr);	

	return 0;
}


int userExist(char* m, char* p)
{
	FILE* fp = fopen("users.txt", "r");
	User* curr = malloc(sizeof(User));

	while (fscanf(fp, "%[^,],%[^,],%d\n", curr->mail, curr->password, &curr->id) == 3) {
		/* DEBUG
		printf("Now chacking: \n");
		printf("%s\n", curr->mail);
		printf("%s\n", curr->password);
		printf("%d\n", curr->id);
		printf("---------------------------------\n");
		*/
		if (strcmp(m, curr->mail) == 0 && strcmp(p, curr->password) == 0) {
			fclose(fp);
			free(curr);
			return 1;
		}
	}

	fclose(fp);
	free(curr);

	return 0;
}


int countLines() {
	int count = 0;
	char ch;
	FILE* file = fopen("users.txt", "r");

	// Read each character in the file
	while ((ch = fgetc(file)) != EOF) {
		// Increment count for each newline character
		if (ch == '\n') {
			count++;
		}
	}

	// Increment count for the last line if not ending with newline
	if (ch != '\n' && count > 0) {
		count++;
	}

	fclose(file);

	return count;
}