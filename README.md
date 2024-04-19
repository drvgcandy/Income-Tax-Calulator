# Income Tax Calculator

This is a simple income tax calculator program written in C. The program manages a list of taxpayers with their details including name, PAN card number, mobile number, income, and calculated tax. The program provides functionalities to add, list, search, edit, and delete taxpayer records.

## Features

- **Add Record**: Allows the user to input taxpayer details and calculates the tax based on the income.
- **List All Tax Payers**: Displays a list of all taxpayers along with their income and tax to be paid.
- **Search**: Enables the user to search for a taxpayer by their PAN card number.
- **Edit**: Allows the user to update the income and recalculate the tax for a specific taxpayer.
- **Delete Record**: Enables the user to delete a taxpayer record by PAN card number.
- **Exit**: Exits the program.

## Tax Calculation

The tax calculation is based on the following brackets:
- Income <= 25,000: 0% tax
- 25,001 <= Income <= 50,000: 5% of the income above 25,000
- 50,001 <= Income <= 75,000: 1,250 + 20% of the income above 50,000
- 75,001 <= Income <= 100,000: 5,520 + 30% of the income above 75,000
- Income > 100,000: 11,250 + 40% of the income above 100,000

## Usage

1. **Add New Record**: 
   - Input taxpayer details including name, PAN card number, mobile number, and income.
   - The program will calculate the tax based on the income.

2. **List All Tax Payers**: 
   - Displays a list of all taxpayers along with their income and tax to be paid.

3. **Search**: 
   - Enter the PAN card number to search for a specific taxpayer.

4. **Edit**: 
   - Enter the PAN card number of the taxpayer to update their income and recalculate the tax.

5. **Delete Record**: 
   - Enter the PAN card number of the taxpayer to delete their record.

6. **Exit**: 
   - Exits the program.

## How to Run

Compile the program using a C compiler and run the executable.

