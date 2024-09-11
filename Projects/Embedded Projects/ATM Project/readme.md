# 💳 ATM Project
This project is a C++ simulation of an ATM system, enabling users to create accounts, deposit and withdraw funds, transfer money between accounts, and exit. The system ensures robust input validation for account names, card numbers, and transaction processes, providing a secure and user-friendly banking experience.

## 📋 Table of Contents
- [📝 Introduction](#introduction)
- [🚀 Features](#features)
- [🔍 Functions Overview](#functions-overview)
- [🛠 Installation and Usage](#installation-and-usage)
- [📚 Example](#example)
- [🎉 Conclusion](#conclusion)

## 📝 Introduction
This project simulates a simple ATM system written in C++. The program ensures validation for account names and card numbers, and provides options for creating accounts, depositing, transferring, withdrawing, and exiting. 

The primary focus is on validating user input to prevent errors such as incorrect account names or invalid card numbers. The user is guided through each step with clear error messages.

## 🚀 Features
- Validates account names with the following checks:
  - Length (should not exceed 100 characters).
  - Contains only letters and spaces.
  - No consecutive spaces or leading/trailing spaces.
  - A minimum of three characters in the name.
  - No more than four consecutive identical letters.
  
- Validates card numbers with these checks:
  - Exactly 10 digits.
  - Contains only numbers.
  - Not all digits are the same.
  
- Provides the following operations:
  1. Create a new account.
  2. Deposit into an account.
  3. Transfer to another account.
  4. Withdraw from an account.
  5. Exit the program.

## 🔍 Functions Overview

| Function Name           | Description |
|-------------------------|-------------|
| `valid_account_name`     | Validates that the account name meets the specified conditions. |
| `valid_card_number`      | Ensures that the card number is exactly 10 digits and follows the validation rules. |
| `check_operation_number` | Allows the user to select the desired operation from the ATM system. |

### `void valid_account_name(char accountname[])`
- Ensures that the entered account name is valid by checking for:
  - Character count.
  - Presence of only letters and spaces.
  - No consecutive spaces or leading/trailing spaces.
  - No more than four consecutive identical characters.

### `void valid_card_number(char cardnumber[])`
- Validates the card number by ensuring it contains exactly 10 digits, contains only numbers, and is not made up of identical digits.

### `int check_operation_number()`
- Provides the user with a list of operations to choose from (1-5). Ensures the selected option is valid and between the given range.

## 🛠️ Installation and Usage

1. Clone the repository or download the project files.
2. Compile the C++ code using any C++ compiler:
   ```bash
   g++ atm.cpp -o atm
    ```
3. Run the executable:
    ```bash
   ./atm
    ```

4. Follow the prompts to enter account names and card numbers. The program will validate the input and guide you through the available ATM operations.

## 📚 Example
When prompted to enter an account name:

- If you input "John Doe", the program will display an error asking you to re-enter the name due to consecutive spaces.
- Similarly, if you enter "JJJJJohn", it will prompt you to re-enter since there are more than four consecutive identical characters.

When prompted to enter a card number:

- If you input "1111111111", the program will detect that all digits are identical and ask for a new number.
## 🎉 Conclusion
This ATM project provides a robust foundation for simulating a simple banking interface. It emphasizes input validation to ensure accuracy and prevents common mistakes when entering account details. Feel free to expand this project by adding new features or enhancing existing ones!
