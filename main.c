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
int userExist(char* m, char* p);
int keyExist(int n);

int signUp();
int logIn();


void testAuthentication()
{
	// Test 1: Login to a non-existing account
	printf("Test 1: Login to a non-existing account\n");
	int loginResult = logIn();
	if (loginResult == 0)
		printf("Login failed (as expected)\n");
	else
		printf("Unexpected successful login\n");

	// Test 2: Login to an existing account
	printf("\nTest 2: Login to an existing account\n");
	printf("Email: email@example.com\n");
	printf("Password: password123\n");
	loginResult = userExist("email@example.com", "password123");
	if (loginResult != 0)
		printf("Login successful, User ID: %d\n", loginResult);
	else
		printf("Login failed\n");

	// Test 3: Signup with an existing email
	printf("\nTest 3: Signup with an existing email\n");
	int signupResult = signUp();
	if (signupResult == 0)
		printf("Signup failed (as expected, email already exists)\n");
	else
		printf("Unexpected successful signup, User ID: %d\n", signupResult);

	// Test 4: Signup correctly
	printf("\nTest 4: Signup correctly\n");
	printf("Email: newuser@example.com\n");
	printf("Password: newpassword123\n");
	signupResult = signUp();
	if (signupResult == 0)
		printf("Unexpected signup failure\n");
	else
		printf("Signup successful, User ID: %d\n", signupResult);
}


void main()
{
	int choice = -1;
	int key = -1;

	do {
		printf("1. SignUp\n");
		printf("2. LogIn\n");
		printf("3. Exit\n");
		printf("What would you like to do: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			key = signUp(); // 1 if failed
			break;
		case 2:
			key = logIn(); // 1 if failed
			break;
		case 3:
			key = -1;
		}
	} while (key == 0);

}


int logIn()
{
	/*
	This function get the new user cardentials, check if the mail already mailExist,
	generate ID and store the data in the users text file.
	Input: none
	Output: 0 if there was an error, key else
	*/

	User* newUser = malloc(sizeof(User));
	FILE* fp;
	int key;

	//system("CLS");

	printf("Email: ");
	scanf("%s", newUser->mail);
	printf("Password: ");
	scanf("%s", newUser->password);
	system("CLS");
	key = userExist(newUser->mail, newUser->password);
	if (key != 0) {
		return key;
	}
	
	return 0;
}

int signUp()
{
	/*
	This function get the new user cardentials, check if the mail already mailExist,
	generate ID and store the data in the users text file.
	Input: none
	Output: 0 if there was an error, key else
	*/

	User* newUser = malloc(sizeof(User));
	FILE* fp;
	int newKey;

	//system("CLS");

	printf("Email: ");
	scanf("%s", newUser->mail);
	printf("Password: ");
	scanf("%s", newUser->password);

	if (mailExist(newUser->mail)) {
		system("CLS");
		printf("Email already exist\n");
		return 0;
	}
	else {
		do {
			newKey = (rand() % 10000) + 1;
		} while (keyExist(newKey));
		newUser->id = newKey;
		fp = fopen("users.txt", "a");
		fprintf(fp, "%s,%s,%d \n", newUser->mail, newUser->password, newUser->id);
		fclose(fp);
		system("CLS");
		printf("Congrates, You Signed Up!\n");
	}

	return newKey;
}

int mailExist(char* m)
{
	/*
	This function check if specific mail exist
	Input: mail
	Output: 1 if exist, else 0
	*/

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
	/*
	This function check if combination of mail and password exist
	Input: mail, password
	Output: Key if user exist, else 0
	*/

	FILE* fp = fopen("users.txt", "r");
	User* curr = malloc(sizeof(User));
	int key;
	while (fscanf(fp, "%[^,],%[^,],%d\n", curr->mail, curr->password, &curr->id) == 3) {
		/* DEBUG
		printf("Now chacking: \n");
		printf("%s\n", curr->mail);
		printf("%s\n", curr->password);
		printf("%d\n", curr->id);
		printf("---------------------------------\n");
		*/
		if (strcmp(m, curr->mail) == 0 && strcmp(p, curr->password) == 0) {
			key = curr->id;
			fclose(fp);
			free(curr);
			return key;
		}
	}

	fclose(fp);
	free(curr);

	return 0;
}

int keyExist(int n)
{
	/*
	This function check if the generated key is exist.
	Input: number
	Output: 1 if the key exist, else 0
	*/

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
		if (n == curr->id) {
			fclose(fp);
			free(curr);
			return 1;
		}
	}

	fclose(fp);
	free(curr);

	return 0;
}
