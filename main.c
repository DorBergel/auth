#include <stdio.h>
#include <string.h>


#define BUFFER_SIZE 50


int logIn()
{
	FILE* fp = fopen("cardentials.txt", "r");
	char password[BUFFER_SIZE];
	char email[BUFFER_SIZE];
	char currPassword[BUFFER_SIZE];
	char currEmail[BUFFER_SIZE];
	char line[BUFFER_SIZE * 2];
	int flag = 0;

	printf("Please enter your email: ");
	scanf("%s", email);
	printf("Please enter your password: ");
	scanf("%s", password);


	while (fgets(line, BUFFER_SIZE*2, fp)) {
		
		sscanf(line, "%[^,],%[^\n]", currEmail, currPassword);
		
		// DEBUG section
		/*
		printf("input_mail = %s     curr_mail = %s       strcmp: %d \n", email, currEmail, strcmp(email, currEmail));
		printf("input_password = %s    curr_password = %s       strcmp: %d\n", password, currPassword, strcmp(password, currPassword));
		printf("---------------------------------\n");
		*/

		if (strcmp(email, currEmail) == 0 && strcmp(password, currPassword) == 0) {
			flag = 1;
			break;
		}
	}

	fclose(fp);
	printf("Flag: %d", flag);
	return flag;
}

void signUp()
{
	FILE* fp = fopen("cardentials.txt", "a");
	char password[BUFFER_SIZE];
	char email[BUFFER_SIZE];


	system("CLS");
	printf("Please enter your email: ");
	scanf("%s", email); 
	//email[strlen(email) - 1] = '\0';

	printf("Please enter your password: ");
	scanf("%s", password);
	//password[strlen(password) - 1] = '\0';

	fprintf(fp, "\n%s,%s", email, password);


	system("CLS");
	printf("Thank You for sign up\n");

	fclose(fp);
}

void main()
{
	logIn();
}