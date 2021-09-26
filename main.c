#include "main.h"

int create_account(void)
{
    char    choice;
    FILE *fp = NULL;

    printf("\t\tADD RECORD\n");
    fp = fopen("data.txt", "a+");
    if (fp == NULL)
    {
        printf("error, can't open file");
        return (0);
    }

//prompt to enter account details & read them
    printf("Enter date (day):\n");
    scanf(" %d", &acc.deposit.day);
    printf("Enter date (month):\n");
    scanf(" %d", &acc.deposit.month);
    printf("Enter date (year):\n");
    scanf(" %d", &acc.deposit.year);
    printf("Enter account number:\n");
    scanf(" %d", &acc.number);
    getchar();
    printf("Enter name:\n");
    fgets(acc.name, NAME_MAX, stdin);
    printf("Enter date of birth (day):\n");
    scanf(" %d", &acc.dob.day);
    printf("Enter date of birth (month):\n");
    scanf(" %d", &acc.dob.month);
    printf("Enter date of birth (year):\n");
    scanf(" %d", &acc.dob.year);
    printf("Enter age:\n");
    scanf(" %d", &acc.age);
    getchar();
    printf("Enter address:\n");
    fgets(acc.address, ADDRESS_MAX, stdin);
    printf("Enter citizenship number:\n");
    scanf(" %d", &acc.citizenship);
    getchar();
    printf("Enter phone number:\n");
    fgets(acc.phone, PHONE_MAX, stdin);
    printf("Enter deposit amount:\n");
    scanf(" %f", &acc.deposit_amount);
    getchar();
    printf("Enter account type:\n1.Saving\n2.Current\n3.Fixed1\n4.Fixed2\n");
    fgets(acc.type, TYPE_MAX, stdin);

//write account details to file
    fprintf(fp, "%d %d %d ", acc.deposit.day, acc.deposit.month, acc.deposit.year);
    fprintf(fp, "%d ", acc.number);
    fprintf(fp, "%d %d %d ", acc.dob.day, acc.dob.month, acc.dob.year);
    fprintf(fp, "%d ", acc.age);
    fprintf(fp, "%d ", acc.citizenship);
    fprintf(fp, "%.2f ", acc.deposit_amount);
    fprintf(fp, "%s", acc.name);
    fprintf(fp, "%s", acc.address);
    fprintf(fp, "%s", acc.phone);
    fprintf(fp, "%s", acc.type);

    fclose(fp);

// goes back to main menu or exits
    printf("\n\nEnter 1 to go back to the main menu and 0 to exit\n");
    scanf(" %c", &choice);
    if (choice == '0')
        return (0);
    if (choice == '1')
        return (1);
    while (choice != '0' && choice != '1')
    {
        printf("invalid number, enter again\n");
        scanf(" %c", &choice);
        if (choice == '0')
            return (0);
        if (choice == '1')
            return (1);
    }
    return (0);
}

int update_account(void)
{
    char    choice;
    int check = 0;
    FILE *old = NULL;
    FILE *new = NULL;

//prompt to enter account information to change
    printf("Enter the number of the account to edit:\n");
    scanf(" %d", &update_acc.number);
    printf("Information to change:\nEnter 1 for address, 2 for phone number\n");
    scanf(" %c", &choice);
    if (choice == '1')
    {
        printf("Enter the new address:\n");
        getchar();
        fgets(update_acc.address, ADDRESS_MAX, stdin);
    }
    else if (choice == '2')
    {
        printf("Enter the new phone number:\n");
        getchar();
        fgets(update_acc.phone, PHONE_MAX, stdin);
    }
    while (choice != '1' && choice != '2')
    {
        printf("invalid number, enter again\n");
        scanf(" %c", &choice);
        if (choice == '1')
        {
            printf("Enter the new address:\n");
            getchar();
            fgets(update_acc.address, ADDRESS_MAX, stdin);
        }
        if (choice == '2')
        {
            printf("Enter the new phone number:\n");
            getchar();
            fgets(update_acc.phone, PHONE_MAX, stdin);
        }
    }

    old = fopen("data.txt", "r");
    new = fopen("tmp.txt", "w");
        if (old == NULL)
    {
        printf("error, can't open file");
        return (0);
    }
    if (new == NULL)
    {
        printf("error, can't edit information");
        return (0);
    }

//read data from file
    while (fscanf(old, "%d",  &acc.deposit.day) != EOF)
    {
        fscanf(old, "%d %d ", &acc.deposit.month, &acc.deposit.year);
        fscanf(old, "%d ", &acc.number);
        fscanf(old, "%d %d %d ", &acc.dob.day, &acc.dob.month, &acc.dob.year);
        fscanf(old, "%d ", &acc.age);
        fscanf(old, "%d ", &acc.citizenship);
        fscanf(old, "%f ", &acc.deposit_amount);
        fgets(acc.name, NAME_MAX, old);
        fgets(acc.address, ADDRESS_MAX, old);
        fgets(acc.phone, PHONE_MAX, old);
        fgets(acc.type, TYPE_MAX, old);

//write updated data to new file
        fprintf(new, "%d %d %d ", acc.deposit.day, acc.deposit.month, acc.deposit.year);
        fprintf(new, "%d ", acc.number);
        fprintf(new, "%d %d %d ", acc.dob.day, acc.dob.month, acc.dob.year);
        fprintf(new, "%d ", acc.age);
        fprintf(new, "%d ", acc.citizenship);
        fprintf(new, "%.2f ", acc.deposit_amount);
        fprintf(new, "%s", acc.name);
        if (acc.number == update_acc.number && choice == '1')
        {
            fprintf(new, "%s", update_acc.address);
            check = 1;
        }
        else
            fprintf(new, "%s", acc.address);
        if (acc.number == update_acc.number && choice == '2')
        {
            fprintf(new, "%s", update_acc.phone);
            check = 1;
        }
        else
            fprintf(new, "%s", acc.phone);
        fprintf(new, "%s", acc.type);
    }

    if (check == 1)
        printf("Your account has been edited successfully\n");
    else
        printf("Account number does not exist, editing failed\n");

    fclose(old);
    fclose(new);
    remove("data.txt");
    rename("tmp.txt", "data.txt");

// goes back to main menu or exits
    printf("\n\nEnter 1 to go back to the main menu and 0 to exit\n");
    scanf(" %c", &choice);
    if (choice == '0')
        return (0);
    if (choice == '1')
        return (1);
    while (choice != '0' && choice != '1')
    {
        printf("invalid number, enter again\n");
        scanf(" %c", &choice);
        if (choice == '0')
            return (0);
        if (choice == '1')
            return (1);
    }
    return (0);
}

int transaction(void)
{
    char    choice;
    int check = 0;
    FILE *old = NULL;
    FILE *new = NULL;

//prompt to enter transaction details
    printf("Enter account number:\n");
    scanf(" %d", &transaction_acc.number);
    printf("Do you want to:\n1.Deposit\n2.Withdraw\nEnter your choice:\n");
    scanf(" %c", &choice);
    if (choice == '1')
    {
        printf("Enter the amount you want to deposit:\n");
        scanf(" %f", &transaction_acc.deposit_amount);
    }
    if (choice == '2')
    {
        printf("Enter the amount you want to withdraw:\n");
        scanf(" %f", &transaction_acc.deposit_amount);
    }

    while (choice != '1' && choice != '2')
    {
        printf("invalid number, enter again\n");
        scanf(" %c", &choice);
        if (choice == '1')
        {
            printf("Enter the amount you want to deposit:\n");
            scanf(" %f", &transaction_acc.deposit_amount);
        }
        if (choice == '2')
        {
            printf("Enter the amount you want to withdraw:\n");
            scanf(" %f", &transaction_acc.deposit_amount);
        }
    }

    old = fopen("data.txt", "r");
    new = fopen("tmp.txt", "w");
        if (old == NULL)
    {
        printf("error, can't open file");
        return (0);
    }
    if (new == NULL)
    {
        printf("error, can't edit information");
        return (0);
    }

//read data from file
    while (fscanf(old, "%d",  &acc.deposit.day) != EOF)
    {
        fscanf(old, "%d %d ", &acc.deposit.month, &acc.deposit.year);
        fscanf(old, "%d ", &acc.number);
        fscanf(old, "%d %d %d ", &acc.dob.day, &acc.dob.month, &acc.dob.year);
        fscanf(old, "%d ", &acc.age);
        fscanf(old, "%d ", &acc.citizenship);
        fscanf(old, "%f ", &acc.deposit_amount);
        fgets(acc.name, NAME_MAX, old);
        fgets(acc.address, ADDRESS_MAX, old);
        fgets(acc.phone, PHONE_MAX, old);
        fgets(acc.type, TYPE_MAX, old);

//write data to new file
        fprintf(new, "%d %d %d ", acc.deposit.day, acc.deposit.month, acc.deposit.year);
        fprintf(new, "%d ", acc.number);
        fprintf(new, "%d %d %d ", acc.dob.day, acc.dob.month, acc.dob.year);
        fprintf(new, "%d ", acc.age);
        fprintf(new, "%d ", acc.citizenship);
        if (acc.number == transaction_acc.number)
        {
            if (choice == '1')
                acc.deposit_amount += transaction_acc.deposit_amount;

            if (choice == '2')
                acc.deposit_amount -= transaction_acc.deposit_amount;
            check = 1;
        }
        fprintf(new, "%.2f ", acc.deposit_amount);
        fprintf(new, "%s", acc.name);
        fprintf(new, "%s", acc.address);
        fprintf(new, "%s", acc.phone);
        fprintf(new, "%s", acc.type);
    }

    if (check == 1)
        printf("The transaction was successful\n");
    else
        printf("Account number does not exist, transaction failed\n");

    fclose(old);
    fclose(new);
    remove("data.txt");
    rename("tmp.txt", "data.txt");

// goes back to main menu or exits
    printf("\n\nEnter 1 to go back to the main menu and 0 to exit\n");
    scanf(" %c", &choice);
    if (choice == '0')
        return (0);
    if (choice == '1')
        return (1);
    while (choice != '0' && choice != '1')
    {
        printf("invalid number, enter again\n");
        scanf(" %c", &choice);
        if (choice == '0')
            return (0);
        if (choice == '1')
            return (1);
    }
    return (0);
}

int check_account(void)
{
    char    choice;
    int check = 0;
    FILE *fp;

//prompt to enter account to view
    printf("Do you want to check by:\n1.Account number\n2.Name\nEnter your choice.\n");
    scanf(" %c", &choice);
    if (choice == '1')
    {
        printf("\nEnter account number:\n");
        scanf(" %d", &check_acc.number);
    }
    if (choice == '2')
    {
        printf("\nEnter name:\n");
        getchar();
        fgets(check_acc.name, NAME_MAX, stdin);
    }
    while (choice != '1' && choice != '2')
    {
        printf("invalid number, enter again\n");
        scanf(" %c", &choice);
        if (choice == '1')
        {
            printf("\nEnter account number:\n");
            scanf(" %d", &check_acc.number);
        }
        if (choice == '2')
        {
            printf("\nEnter name:\n");
            getchar();
            fgets(check_acc.name, NAME_MAX, stdin);
        }
    }

//read data from file
    fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("error, can't open file");
        return (0);
    }
    while (fscanf(fp, "%d",  &acc.deposit.day) != EOF)
    {
        fscanf(fp, "%d %d ", &acc.deposit.month, &acc.deposit.year);
        fscanf(fp, "%d ", &acc.number);
        fscanf(fp, "%d %d %d ", &acc.dob.day, &acc.dob.month, &acc.dob.year);
        fscanf(fp, "%d ", &acc.age);
        fscanf(fp, "%d ", &acc.citizenship);
        fscanf(fp, "%f ", &acc.deposit_amount);
        fgets(acc.name, NAME_MAX, fp);
        fgets(acc.address, ADDRESS_MAX, fp);
        fgets(acc.phone, PHONE_MAX, fp);
        fgets(acc.type, TYPE_MAX, fp);

//find account and print data
        if (choice == '1' && acc.number == check_acc.number)
        {
            printf("\nAccount number: %d\n", acc.number);
            printf("Name: %s", acc.name);
            printf("Address: %s", acc.address);
            printf("Phone: %s", acc.phone);
            printf("DOB: %d/%d/%d\n", acc.dob.day, acc.dob.month, acc.dob.year);
            printf("Age: %d\n", acc.age);
            printf("Citizenship number: %d\n", acc.citizenship);
            printf("Amount deposited: %.2f\n", acc.deposit_amount);
            printf("Deposit date: %d/%d/%d\n", acc.deposit.day, acc.deposit.month, acc.deposit.year);
            printf("Account type: %s", acc.type);
            check = 1;
        }
        else if (choice == '2' && strcmp(acc.name, check_acc.name) == 0)
        {
            printf("\nAccount number: %d\n", acc.number);
            printf("Name: %s", acc.name);
            printf("Address: %s", acc.address);
            printf("Phone: %s", acc.phone);
            printf("DOB: %d/%d/%d\n", acc.dob.day, acc.dob.month, acc.dob.year);
            printf("Age: %d\n", acc.age);
            printf("Citizenship number: %d\n", acc.citizenship);
            printf("Amount deposited: %.2f\n", acc.deposit_amount);
            printf("Deposit date: %d/%d/%d\n", acc.deposit.day, acc.deposit.month, acc.deposit.year);
            printf("Account type: %s", acc.type);
            check = 1;
        }
    }
    if (check != 1)
        printf("Account number does not exist.\n");
    fclose(fp);

// goes back to main menu or exits
    printf("\n\nEnter 1 to go back to the main menu and 0 to exit\n");
    scanf(" %c", &choice);
    if (choice == '0')
        return (0);
    if (choice == '1')
        return (1);
    while (choice != '0' && choice != '1')
    {
        printf("invalid number, enter again\n");
        scanf(" %c", &choice);
        if (choice == '0')
            return (0);
        if (choice == '1')
            return (1);
    }
    return (0);
}

int remove_account(void)
{
    char    choice;
    int check = 0;
    FILE *old = NULL;
    FILE *new = NULL;

    printf("Enter number of account to delete:\n");
    scanf(" %d", &remove_acc.number);

    old = fopen("data.txt", "r");
    new = fopen("tmp.txt", "w");
    if (old == NULL)
    {
        printf("error, can't open file");
        return (0);
    }
    if (new == NULL)
    {
        printf("error, can't remove account currently");
        return (0);
    }

//read data from file
    while (fscanf(old, "%d",  &acc.deposit.day) != EOF)
    {
        fscanf(old, "%d %d ", &acc.deposit.month, &acc.deposit.year);
        fscanf(old, "%d ", &acc.number);
        fscanf(old, "%d %d %d ", &acc.dob.day, &acc.dob.month, &acc.dob.year);
        fscanf(old, "%d ", &acc.age);
        fscanf(old, "%d ", &acc.citizenship);
        fscanf(old, "%f ", &acc.deposit_amount);
        fgets(acc.name, NAME_MAX, old);
        fgets(acc.address, ADDRESS_MAX, old);
        fgets(acc.phone, PHONE_MAX, old);
        fgets(acc.type, TYPE_MAX, old);

//find account to remove & write updated data to new file
        if (acc.number != remove_acc.number)
        {
            fprintf(new, "%d %d %d ", acc.deposit.day, acc.deposit.month, acc.deposit.year);
            fprintf(new, "%d ", acc.number);
            fprintf(new, "%d %d %d ", acc.dob.day, acc.dob.month, acc.dob.year);
            fprintf(new, "%d ", acc.age);
            fprintf(new, "%d ", acc.citizenship);
            fprintf(new, "%.2f ", acc.deposit_amount);
            fprintf(new, "%s", acc.name);
            fprintf(new, "%s", acc.address);
            fprintf(new, "%s", acc.phone);
            fprintf(new, "%s", acc.type);
        }
        else
            check = 1;
    }

    if (check == 1)
        printf("The account has been removed successfully\n");
    else
        printf("Account number does not exist, removal failed\n");

    fclose(old);
    fclose(new);
    remove("data.txt");
    rename("tmp.txt", "data.txt");

// goes back to main menu or exits
    printf("\n\nEnter 1 to go back to the main menu and 0 to exit\n");
    scanf(" %c", &choice);
    if (choice == '0')
        return (0);
    if (choice == '1')
        return (1);
    while (choice != '0' && choice != '1')
    {
        printf("invalid number, enter again\n");
        scanf(" %c", &choice);
        if (choice == '0')
            return (0);
        if (choice == '1')
            return (1);
    }
    return (0);
}

int view_account_list(void)
{
    char    choice;
    FILE *fp = NULL;

    printf("\n\tAccount list:\n\n");

//read data from file
    fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("error, can't open file");
        return (0);
    }
    while (fscanf(fp, "%d",  &acc.deposit.day) != EOF)
    {
        fscanf(fp, "%*d %*d %d %*d %*d %*d %*d %*d %*d %*f ", &acc.number);
        fgets(acc.name, NAME_MAX, fp);
        fgets(acc.address, ADDRESS_MAX, fp);
        fgets(acc.phone, PHONE_MAX, fp);
        fgets(acc.type, TYPE_MAX, fp);

//find account and print data
        printf("Account number: %d\n", acc.number);
        printf("Name: %s", acc.name);
        printf("Address: %s", acc.address);
        printf("Phone: %s\n", acc.phone);
    }

    fclose(fp);

// goes back to main menu or exits
    printf("\n\nEnter 1 to go back to the main menu and 0 to exit\n");
    scanf(" %c", &choice);
    if (choice == '0')
        return (0);
    if (choice == '1')
        return (1);
    while (choice != '0' && choice != '1')
    {
        printf("invalid number, enter again\n");
        scanf(" %c", &choice);
        if (choice == '0')
            return (0);
        if (choice == '1')
            return (1);
    }
    return (0);
}

void    display_main_menu(void)
{
        char choice;
        int return_value;

// displays main menu choices
    printf("CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM\n\n");
    printf("\tWELCOME TO THE MAIN MENU\n\n");
    printf("1.Create a new account\n");
    printf("2.Update information on existing account\n");
    printf("3.For transactions\n");
    printf("4.Check the details of existing account\n");
    printf("5.Remove existing account\n");
    printf("6.View customer's list\n");
    printf("7.Exit\n");
    printf("\n\tEnter Your Choice:\n");
    scanf(" %c", &choice);

// prompts for input until valid choice is entered
    if (choice < '1' || choice > '7')
    {
        printf("invalid number, enter again\n");
        while (choice < '1' || choice  > '7')
        {
            scanf(" %c", &choice);
            printf("invalid number, enter again\n");
            if (choice > '0' && choice < '8')
                break ;
        }
    }
// goes to entered choice
    if (choice == '1')
        return_value = create_account();
    if (choice == '2')
        return_value = update_account();   
    if (choice == '3')
        return_value = transaction();
    if (choice == '4')
        return_value = check_account();
    if (choice == '5')
        return_value = remove_account();
    if (choice == '6')
        return_value = view_account_list();
    if (choice == '7')
        return ;
    if (return_value == 1)
        display_main_menu();
    if (return_value == 0)
        return ;
}

int main(void)
{
    display_main_menu();
    return (0);
}