The project is an ATM machine that takes the username and PIN code to login. 
The ATM will display a menu for the user to choose an operation from (balance check, deposit funds, withdraw funds, view transactions history or exit). 
The ATM will hold the data in CSV format for all users (user ID, username, password and current balance).
The passwords are loaded from users.csv (raw data) then encrypted and saved to users_Encrypted.csv on the first run. After this, the ATM will use the encrypted file to update any user data.
The transactions are saved to Transactions.csv file.
