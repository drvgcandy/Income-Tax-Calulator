#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct taxPayer
{
    char fullName[50];
    int panCardNumber;
    int mobileNumber;
    float income;
    float taxAmount;
};
void addRecord(FILE *file)
{
    struct taxPayer record;
    
    // Getting details from user:
    printf("Enter full name: ");
    scanf("%s", record.fullName);
    printf("Enter 5-digit Pan Card number: ");
    scanf("%d", &record.panCardNumber);
    printf("Enter Mobile number: ");
    scanf("%d", &record.mobileNumber);
    printf("Enter income: ");
    scanf("%f", &record.income);

    // Calculating tax amount based on income:
    if (record.income <= 25000)
    {
        record.taxAmount = 0;
    }
    else if (record.income > 25000 && record.income <= 50000)
    {
        record.taxAmount = (record.income - 25000) * 0.05;
    }
    else if (record.income > 50000 && record.income <= 75000)
    {
        record.taxAmount = 1250 + ((record.income - 50000) * 0.2);
    }
    else if (record.income > 75000 && record.income <= 100000)
    {
        record.taxAmount = 5520 + ((record.income - 75000) * 0.3);
    }
    else
    {
        record.taxAmount = 11250 + ((record.income - 100000) * 0.4);
    }

    // Write record to the file:
    fwrite(&record, sizeof(struct taxPayer), 1, file);
    printf("Record added successfully.\n");
}

// For display of all the records:
void showAllRecords(FILE *file)
{
    struct taxPayer record;
    fseek(file, 0, SEEK_SET);
    printf("%-20s %-20s %-20s %-20s  \n", "Name", "Pan Card No.", "Income", "Tax Paid");
    while (fread(&record, sizeof(struct taxPayer), 1, file))
    {
        printf("%-20s %-19d Rs.%-19.2f Rs.%-17.2f  \n", record.fullName, record.panCardNumber, record.income, record.taxAmount);
    }
}

// For searching a record:
void searchRecord(FILE *file)
{
    int search;
    struct taxPayer record;
    
    // Input Pan Card number to search
    printf("Enter Pan Card number to search: ");
    scanf("%d", &search);
    fseek(file, 0, SEEK_SET);
    
    while (fread(&record, sizeof(struct taxPayer), 1, file))
    {
        if (record.panCardNumber == search)
        {
            printf("%-20s %-20s %-20s %-20s  \n", "Name", "Pan Card No.", "Income", "Tax Paid");
            printf("%-20s %-19d Rs.%-19.2f Rs.%-17.2f  \n", record.fullName, record.panCardNumber, record.income, record.taxAmount);
            return;
        }
    }
    printf("Record not found.\n");
}
void *editRecord(FILE *file)
{
    int toSearch;
    
    // Input Pan Card number to search for editing:
    printf("Enter the Pan Card number of the taxpayer to update: ");
    scanf("%d", &toSearch);
    fseek(file, 0, SEEK_SET);

    struct taxPayer record;
    int found = 0;

    FILE *temp = fopen("temp.txt", "wb");

    while (fread(&record, sizeof(record), 1, file) == 1)
    {
        if (record.panCardNumber == toSearch)
        {
            found = 1;
            printf("Enter new income: ");
            scanf("%f", &record.income);

            // Recalculate tax amount
            if (record.income <= 25000)
            {
                record.taxAmount = 0;
            }
            else if (record.income > 25000 && record.income <= 50000)
            {
                record.taxAmount = (record.income - 25000) * 0.05;
            }
            else if (record.income > 50000 && record.income <= 75000)
            {
                record.taxAmount = 1250 + ((record.income - 50000) * 0.2);
            }
            else if (record.income > 75000 && record.income <= 100000)
            {
                record.taxAmount = 5520 + ((record.income - 75000) * 0.3);
            }
            else
            {
                record.taxAmount = 11250 + ((record.income - 100000) * 0.4);
            }
            
            fwrite(&record, sizeof(record), 1, temp);
        }
        else
        {
            fwrite(&record, sizeof(record), 1, temp);
        }
    }
    
    fclose(file);
    fclose(temp);

    if (found)
    {
        // Replacing the original file with the temporary file here:
        remove("taxPayers.txt");
        rename("temp.txt", "taxPayers.txt");
        printf("Taxpayer with Pan Card number %d has been updated.\n", toSearch);
    }
    else
    {
        printf("Taxpayer with Pan Card number %d not found.\n", toSearch);
        remove("temp.txt");
    }

    // Reopen the original file for further operations:
    file = fopen("taxPayers.txt", "ab+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    return file;
}

// For deleting a record:
FILE *deleteRecord(FILE *file)
{
    int toSearch;
    
    // Input Pan Card number to search for deletion
    printf("Enter the Pan Card number of the taxpayer to delete: ");
    scanf("%d", &toSearch);
    fseek(file, 0, SEEK_SET);

    struct taxPayer record;
    int found = 0;
    FILE *temp = fopen("temp.txt", "wb");
    while (fread(&record, sizeof(record), 1, file) == 1)
    {
        if (record.panCardNumber == toSearch)
        {
            found = 1;
        }
        else
        {
            fwrite(&record, sizeof(record), 1, temp);
        }
    }
  
    fclose(file);
    fclose(temp);

    if (found)
    {

        remove("taxPayers.txt");
        rename("temp.txt", "taxPayers.txt");
        printf("Taxpayer with Pan Card number %d has been deleted.\n", toSearch);
    }
    else
    {
        printf("Taxpayer with Pan Card number %d not found.\n", toSearch);
        remove("temp.txt");
    }

    file = fopen("taxPayers.txt", "ab+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    return file;
}

int main()
{
    FILE *file = fopen("taxPayers.txt", "ab+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    int choice;
    do
    {
        // Display menu options
        printf("\n1. Add New Record\n");
        printf("2. List All Tax Payers along with Income Tax to be paid\n");
        printf("3. Search\n");
        printf("4. Edit\n");
        printf("5. Delete Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        
        // Take user choice
        fflush(stdin);
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addRecord(file);
            break;
        case 2:
            showAllRecords(file);
            break;
        case 3:
            searchRecord(file);
            break;
        case 4:
            editRecord(file);
            break;
        case 5:
            deleteRecord(file);
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }

    } while (choice != 6);

    // Close the file
    fclose(file);
    return 0;
}
