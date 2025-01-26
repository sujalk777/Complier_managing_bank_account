# Bank Account Management System

## Project Overview
This project provides an efficient system for managing bank accounts using optimized data structures like AVL trees and hashing. It is implemented in C++ and designed for operations such as creating, updating, and deleting accounts, along with handling transactions.

## Features
- Create new bank accounts
- Process deposits and withdrawals
- Perform balance inquiries
- Update account information
- Delete accounts

## Data Structures and Algorithms
- **AVL Trees**: Used for balanced storage and quick retrieval of account information.
- **Hashing**: Implemented for efficient indexing and searching of accounts.

## Class Structure
### Main Classes and Their Responsibilities:
- **`Entry`**: Represents a bank account with attributes such as account number, account holder's name, and balance.
- **`Evaluator`**: Handles the processing of banking operations.
- **`ExprTreeNode`**: Defines nodes for expression trees used in transaction evaluations.
- **`SymTable`**: Implements the symbol table for storing and retrieving account data.
- **`UnlimitedInt` and `UnlimitedRational`**: Manage large integers and rational numbers for precise financial calculations.

## Getting Started
### Prerequisites
- A C++ compiler (e.g., `g++`).
- A terminal or command prompt.

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/sujalk777/Complier_managing_bank_account.git
   cd Complier_managing_bank_account
   ```

2. Compile the source files:
   ```bash
   g++ -o bank_manager *.cpp
   ```

3. Run the executable:
   ```bash
   ./bank_manager
   ```

## Usage
### Example Commands
- **Create a New Account:**
  Enter the required account details when prompted.

- **Deposit Money:**
  Specify the account number and deposit amount.

- **Withdraw Money:**
  Provide the account number and withdrawal amount.

- **Check Balance:**
  Input the account number to retrieve the current balance.

- **Update Account Information:**
  Enter the account number and the details to be updated.

### Sample Output
```
Welcome to the Bank Account Management System
1. Create Account
2. Deposit Money
3. Withdraw Money
4. Check Balance
5. Update Account
6. Exit
Choose an option: 1
Enter account details: 
[...details logged...]
```

