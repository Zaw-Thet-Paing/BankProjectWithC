//
// Created by deadlok on 3/27/23.
//

#ifndef BANKPROJECTWITHC_BANK_H
#define BANKPROJECTWITHC_BANK_H

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "z_library.h"
#define SIZE 50
#define NRC_DB_SIZE 2

struct history{
    char note[100];
};

struct data{
    unsigned int id;
    char name[50];
    char nrc[25]; //for business level user
    char dob[15]; //for business level user
    char gender[10]; //for business level user
    char address[100]; //for business level user
    char email[50];
    long long int phone_number;
    unsigned int security_key;
    char password[50];
    char pOrb[10];
    unsigned int amount;
    unsigned int wallet_capacity;
    unsigned int amount_limit_per_day;
    struct history trans[50];
};

struct national_id{
    char nrc[25];
};

struct my_time{
    char c_time[25];
};

struct national_id nrcDB[NRC_DB_SIZE];

struct data db[SIZE];

struct my_time Ctime[1];

//functions declaration
void loading_all_data_from_file();
void recording_all_data_to_file();
void space_counter();
void printing_all_data();
void welcome();
void registration();
void login();
int email_exist_checking(char email[50]);
int phone_exist_checking(long long int phone);
int check_strong_password(char password[50]);
void user_sector(int userIndex);
void profile(int userIndex);
void profile_update_info(int userIndex);
void profile_update_to_business_user(int userIndex);
void transfer_money(int userIndex);
void continue_to_transfer(int userIndex);
void transaction_record(int userIndex, int receiverIndex, char who, unsigned int amount);
void cash_in(int userIndex);
void trans_history(int userIndex);
void load_data_to_nrc_db();
void get_time();
void int_to_char(long long int num);
long long int char_to_int(char str[100]);
void get_current_data_to_TR(unsigned int current_amount);
unsigned int get_total_amount_of_same_day(int indexToGet, unsigned int amount_to_TR);
//validation functions
int email_validation(char email[50]);
int phone_validation(long long int phone);
int key_validation(unsigned int key);
int nrc_validation(char nrc[25]);
//encryption and decryption
/*
void encrypt_before_save();
void decrypt_before_load();
*/

//global variables
int users = 0;
int space_array[50];
char int_to_char_result[100];
unsigned int current_amount_to_TR = 0;
int current_day_to_TR = 0;

//code body

void login(){
    char lEmail[50] = "";
    char lPass[50] = "";

    int emailCheck = -1;
    int passwordCheck = 0;
    int userIndex = 0;

    while(emailCheck == -1 || passwordCheck == 0){
        printf("*******************\n");
        printf("**Bank Login Page**\n");
        printf("*******************\n");
        printf("Enter your email : ");
        scanf(" %[^\n]", lEmail);
        printf("Enter your password : ");
        scanf(" %[^\n]", lPass);
        userIndex = email_exist_checking(lEmail);
        if(userIndex == -1 || str_cmp(db[userIndex].password, lPass) == 0){
            emailCheck = -1;
            passwordCheck = 0;
            printf("Your login credential was wrong:\n");
        }else{
            emailCheck = 0;
            passwordCheck = 1;
        }

    }

    printf("Login Success\n");
    user_sector(userIndex);

}

void user_sector(int userIndex){
    int option = 0;
    printf("***************\n");
    printf("**User Sector**\n");
    printf("***************\n");
    printf("Welcome %s! Your current balance is %u.\n", db[userIndex].name, db[userIndex].amount);
    printf("1. Profile\n2. Transfer Money\n3. Cash In\n4. History\n0. Exit\n");
    printf("Enter your option ::> ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            profile(userIndex);
            break;
        case 2:
            transfer_money(userIndex);
            break;
        case 3:
            cash_in(userIndex);
            break;
        case 4:
            trans_history(userIndex);
        case 0:
            welcome();
            break;
        default:
            printf("Invalid Option\n");
            user_sector(userIndex);
            break;
    }

}

void profile(int userIndex){
    printf("****************\n");
    printf("**User Profile**\n");
    printf("****************\n");
    printf("Welcome %s! Your balance is %u! Your Account is %s\n\n", db[userIndex].name, db[userIndex].amount, db[userIndex].pOrb);
    printf("User Informations\n");
    printf("Email : %s\n", db[userIndex].email);
    printf("Phone : %lld\n", db[userIndex].phone_number);
    if(!str_cmp(db[userIndex].nrc, "null")){
        printf("NRC : %s\n", db[userIndex].nrc);
    }
    if(!str_cmp(db[userIndex].dob, "null")){
        printf("Date of Birth : %s\n", db[userIndex].dob);
    }
    if(!str_cmp(db[userIndex].gender, "null")){
        printf("Gender : %s\n", db[userIndex].gender);
    }
    if(!str_cmp(db[userIndex].address, "null")){
        printf("Address : %s\n", db[userIndex].address);
    }
    printf("Security Key : %u\n", db[userIndex].security_key);
    printf("Password : %s\n", db[userIndex].password);
    printf("Account Type : %s\n", db[userIndex].pOrb);
    printf("Wallet Capacity : %u\n", db[userIndex].wallet_capacity);
    printf("Transaction amount limit per day : %u\n\n", db[userIndex].amount_limit_per_day);

    //update info and account type
    int option = 0;
    printf("1. Update Info\n");
    if(!str_cmp(db[userIndex].pOrb, "Business")){
        printf("2. Update to business Account\n");
    }
    printf("0. Back to user sector\n");
    printf("Enter your option ::> ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            profile_update_info(userIndex);
        case 2:
            profile_update_to_business_user(userIndex);
        case 0:
            user_sector(userIndex);
            break;
        default:
            printf("Invalid Option!\n");
            profile(userIndex);
    }
}

void profile_update_info(int userIndex){
    int option = 0;
    char uName[50];
    char uEmail[50] = "";
    long long int uPhone = 0;
    char uPassword[50] = "";
    printf("***********************\n");
    printf("**Update User Profile**\n");
    printf("***********************\n");
    printf("You can only update name, email, phone and password\n");
    printf("1. Update profile\n0. Back to Profile Page\n");
    printf("Enter your option ::> ");
    scanf("%d", &option);
    switch (option) {
        case 1:
            printf("Enter your name to update : ");
            scanf(" %[^\n]", uName);

            while(!email_validation(uEmail)){
                printf("Enter your email to update : ");
                scanf(" %[^\n]", uEmail);
                if(email_validation(uEmail) == 0){
                    printf("Invalid email format!\n");
                }
            }

            while(!phone_validation(uPhone)){
                printf("Enter your phone number to update : ");
                scanf("%lld", &uPhone);
                if(phone_validation(uPhone) == 0){
                    printf("Invalid Phone! Insert example (959XXXXXXXXX)!\n");
                }
            }

            while(!check_strong_password(uPassword)){
                printf("Enter your password to update : ");
                scanf(" %[^\n]", uPassword);
                if(check_strong_password(uPassword) == 0){
                    printf("Your password be strong\nAt least one Upper case\nAt least one Lower case\nAt least one digit\nAt least one special char\n");
                }
            }

            //solved the struct array error;
            for(int i = 0; i<50; i++){
                db[userIndex].name[i] = '\0';
                db[userIndex].email[i] = '\0';
                db[userIndex].password[i] = '\0';
            }

            str_copy(db[userIndex].name, uName);
            str_copy(db[userIndex].email, uEmail);
            db[userIndex].phone_number = uPhone;
            str_copy(db[userIndex].password, uPassword);

            printf("Your information updated success!\n");
            profile(userIndex);

            break;
        case 0:
            profile(userIndex);
            break;
        default:
            printf("Invalid Option!\n");
            profile_update_info(userIndex);
            break;
    }
}

void profile_update_to_business_user(int userIndex){
    int option = 0;
    char bNrc[25] = "";
    char bDob[15];
    char bGender[10];
    char bAddress[100];
    printf("***********************************\n");
    printf("**Account update as Business User**\n");
    printf("***********************************\n");
    printf("You need your nrc to update\n");
    printf("1. Continue to update\n0. Back to profile\n");
    printf("Enter your option : ");
    scanf("%d", &option);

    switch(option){
        case 1:
            printf("Insert your info carefully to update! If something wrong, you can't change it later!\n");

            while(!nrc_validation(bNrc)){
                printf("Enter your nrc : ");
                scanf(" %[^\n]", bNrc);
                if(nrc_validation(bNrc) == 0){
                    printf("Invalid NRC format! Only allow 1/yng(N) and 2/mdy(N) | eg., 1/ygn(N)111111\n");
                }
            }

            printf("Enter your date of birth (dd-mm-yyyy) : ");
            scanf(" %[^\n]", bDob);

            printf("Enter your gender (Male | Female | Other) : ");
            scanf(" %[^\n]", bGender);

            printf("Enter your address : ");
            scanf(" %[^\n]", bAddress);

            str_copy(db[userIndex].nrc, bNrc);
            str_copy(db[userIndex].dob, bDob);
            str_copy(db[userIndex].gender, bGender);
            str_copy(db[userIndex].address, bAddress);
            str_copy(db[userIndex].pOrb, "Business");
            db[userIndex].wallet_capacity = 10000000;
            db[userIndex].amount_limit_per_day = 1000000;
            profile(userIndex);

            break;
        case 0:
            profile(userIndex);
            break;
        default:
            printf("Invalid Option!\n");
            profile_update_to_business_user(userIndex);
            break;
    }
}

void transfer_money(int userIndex){
    int option = 0;
    printf("******************\n");
    printf("**Transfer Money**\n");
    printf("******************\n");
    printf("1. Continue to Transfer\n0. Back to User Sector\n");
    printf("Enter your option : ");
    scanf("%d", &option);

    switch(option){
        case 1:
            continue_to_transfer(userIndex);
            break;
        case 0:
            transfer_money(userIndex);
            break;
        default:
            printf("Invalid Option!\n");
            break;
    }

}

void continue_to_transfer(int userIndex){
    int option = 0;
    int receiverIndex = 0;
    unsigned int amountToTransfer = 0;
    char yOrn;
    char passwordToProceed[50] = "";
    printf("Your balance is %u. Amount limit per day is %u\n", db[userIndex].amount, db[userIndex].amount_limit_per_day);
    printf("1. Transfer with phone number\n2. Transfer with email (Recommend)\n");
    printf("Enter your option ::> ");
    scanf("%d", &option);
    if(option == 1){

        //transfer with phone number
        long long int receiver_phone = 0;
        while(phone_exist_checking(receiver_phone) == -1){
            printf("Enter receiver phone : ");
            scanf("%lld", &receiver_phone);
            receiverIndex = phone_exist_checking(receiver_phone);
            if(receiverIndex == -1){
                printf("Bank user does not exists with this phone number!\n");
            }
        }
        printf("Your receiver info : %s - %s - %lld\n", db[receiverIndex].name, db[receiverIndex].email, db[receiverIndex].phone_number);

    } else if(option == 2){

        //transfer with email
        char receiver_email[50] = "";
        while(email_exist_checking(receiver_email) == -1){
            printf("Enter receiver email : ");
            scanf(" %[^\n]", receiver_email);
            receiverIndex = email_exist_checking(receiver_email);
            if(receiverIndex == -1){
                printf("Bank user does not exist with this email!\n");
            }
        }

    }else{
        printf("Invalid Option!\n");
        continue_to_transfer(userIndex);
    }

    printf("Your receiver info : %s - %s - %lld\n", db[receiverIndex].name, db[receiverIndex].email, db[receiverIndex].phone_number);

    printf("Are you sure to transfer to this user (y/n)? ");
    scanf(" %c", &yOrn);
    if(yOrn == 'n' || yOrn == 'N'){
        transfer_money(userIndex);
    }

    int total_receive_amount = 0;
    while(amountToTransfer < db[userIndex].amount){
        printf("Enter your amount to transfer : ");
        scanf("%u", &amountToTransfer);

        if(db[userIndex].amount > amountToTransfer){
            total_receive_amount = amountToTransfer + db[receiverIndex].amount;
            if(total_receive_amount > db[receiverIndex].wallet_capacity){
                printf("Receiver wallet capacity was exceeded! You can transfer at most %d\n", db[receiverIndex].wallet_capacity - db[receiverIndex].amount);
                amountToTransfer = 0;
            }else{
                /*
                 *break statement if everything ok
                 * Check Amount Limit Per Day Here
                 * ERROR
                 */
                unsigned int total_amount_of_same_day_for_cUser = get_total_amount_of_same_day(userIndex, amountToTransfer);
                unsigned int total_amount_of_same_day_for_receiver = get_total_amount_of_same_day(receiverIndex, amountToTransfer);

                if((total_amount_of_same_day_for_cUser + amountToTransfer) > db[userIndex].amount_limit_per_day){

                    int transfer_at_most = db[userIndex].amount_limit_per_day - total_amount_of_same_day_for_cUser;
                    printf("Your amount limit per day was exceeded! You can transfer at most %u\n", transfer_at_most);
                    amountToTransfer = 0;

                }else{

                    if((total_amount_of_same_day_for_receiver + amountToTransfer) > db[receiverIndex].amount_limit_per_day){
                        int receive_at_most = db[receiverIndex].amount_limit_per_day - total_amount_of_same_day_for_receiver;
                        printf("Receiver amount limit per day was exceeded! Receiver can receive at most %u\n", receive_at_most);
                        amountToTransfer = 0;
                    }else{
                        break;
                    }

                }

            }
        }else{
            printf("Your balance is not enough to transfer!\n");
            amountToTransfer = 0;
        }
    }

    while(!str_cmp(db[userIndex].password, passwordToProceed)){
        printf("Enter your password to proceed the transaction : ");
        scanf(" %[^\n]", passwordToProceed);
        if(!str_cmp(db[userIndex].password, passwordToProceed)){
            printf("Incorrect password!\n");
        }
    }

    printf("Transaction complete!\n");
    transaction_record(userIndex, receiverIndex, 't', amountToTransfer);
    transaction_record(userIndex, receiverIndex, 'r', amountToTransfer);
    user_sector(userIndex);


}

void transaction_record(int userIndex, int receiverIndex, char who, unsigned int amount){
    //t for transfer // r fro receive
    int user_name_counter = str_len(db[userIndex].name);
    int receiver_name_counter = str_len(db[receiverIndex].name);
    for(int i = 0; i<100; i++){
        int_to_char_result[i] = '\0';
    }
    int_to_char(amount);
    int amount_counter = str_len(int_to_char_result);

    if(who == 't'){
        int index_counter = 0;
        char first_text[15] = "Send_Money_to_";
        int first_text_counter = str_len(first_text);
        for(int i=0; i<first_text_counter; i++){
            db[userIndex].trans[space_array[userIndex]-13].note[index_counter] = first_text[i];
            index_counter++;
        }

        for(int i = 0; i<receiver_name_counter; i++){
            db[userIndex].trans[space_array[userIndex]-13].note[index_counter] = db[receiverIndex].name[i];
            index_counter++;
        }

        char second_text[5] = "_$";
        int second_text_counter = str_len(second_text);
        for(int i = 0; i<second_text_counter; i++){
            db[userIndex].trans[space_array[userIndex]-13].note[index_counter] = second_text[i];
            index_counter++;
        }

        for(int i = 0; i<amount_counter; i++){
            db[userIndex].trans[space_array[userIndex]-13].note[index_counter] = int_to_char_result[i];
            index_counter++;
        }

        char third_text[5] = "_at";
        int third_text_counter = str_len(third_text);
        for(int i = 0; i<third_text_counter; i++){
            db[userIndex].trans[space_array[userIndex]-13].note[index_counter] = third_text[i];
            index_counter++;
        }

        //need to add time
        get_time();
        for(int i = 0; i< str_len(Ctime[0].c_time); i++){
            db[userIndex].trans[space_array[userIndex]-13].note[index_counter] = Ctime[0].c_time[i];
            index_counter++;
        }

        space_array[userIndex]++;
        db[userIndex].amount -= amount;

    }else{

        int index_counter = 0;
        char first_text[20] = "Receive_Money_from_";
        int first_text_counter = str_len(first_text);
        for(int i=0; i<first_text_counter; i++){
            db[receiverIndex].trans[space_array[receiverIndex]-13].note[index_counter] = first_text[i];
            index_counter++;
        }

        for(int i = 0; i<user_name_counter; i++){
            db[receiverIndex].trans[space_array[receiverIndex]-13].note[index_counter] = db[userIndex].name[i];
            index_counter++;
        }

        char second_text[5] = "_$";
        int second_text_counter = str_len(second_text);
        for(int i = 0; i<second_text_counter; i++){
            db[receiverIndex].trans[space_array[receiverIndex]-13].note[index_counter] = second_text[i];
            index_counter++;
        }


        for(int i = 0; i<amount_counter; i++){
            db[receiverIndex].trans[space_array[receiverIndex]-13].note[index_counter] = int_to_char_result[i];
            index_counter++;
        }

        //Fix here
        char third_text[5] = "_at";
        int third_text_counter = str_len(third_text);
        for(int i = 0; i<third_text_counter; i++){
            db[receiverIndex].trans[space_array[receiverIndex]-13].note[index_counter] = third_text[i];
            index_counter++;
        }

        //time
        get_time();
        for(int i = 0; i< str_len(Ctime[0].c_time); i++){
            db[receiverIndex].trans[space_array[receiverIndex]-13].note[index_counter] = Ctime[0].c_time[i];
            index_counter++;
        }

        space_array[receiverIndex]++;
        db[receiverIndex].amount += amount;

    }
}

void cash_in(int userIndex){
    printf("***********\n");
    printf("**Cash In**\n");
    printf("***********\n");
    int option = 0;
    printf("1. Continue to Cash In\n0. Back to user sector\n");
    printf("Enter your option ::> ");
    scanf("%d", &option);
    if(option == 1){

        int check = 1;
        unsigned int cash_in_amount = 0;
        unsigned int total_amount = 0;
        while(check){
            printf("Enter your amount to cash in : ");
            scanf("%u", &cash_in_amount);
            total_amount = cash_in_amount + db[userIndex].amount;
            if(total_amount > db[userIndex].wallet_capacity){
                printf("Your wallet capacity was exceeded! You can cash in at most %d", db[userIndex].wallet_capacity - db[userIndex].amount);
                check = 1;
            }else{
                check = 0;
            }
        }
        db[userIndex].amount = total_amount;
        printf("Cash In %u Success!\n", cash_in_amount);
        cash_in(userIndex);

    }else if(option == 0){
        user_sector(userIndex);
    }else{
        printf("Invalid Option!\n");
        cash_in(userIndex);
    }
}

void trans_history(int userIndex){
    printf("***********************\n");
    printf("**Transaction History**\n");
    printf("***********************\n");
    for(int i = (space_array[userIndex]-13)-1; i >= 0; i--){
        printf("%s\n", db[userIndex].trans[i].note);
    }
    if(!db[userIndex].trans[0].note[0]){
        printf("No transaction record exists!\n");
    }
    int option = 0;
    printf("0. Back to user sector\n");
    printf("Enter your option : ");
    scanf("%d", &option);
    if(option == 0){
        user_sector(userIndex);
    }else{
        printf("Invalid Option\n");
        trans_history(userIndex);
    }
}

void registration(){
    char rName[50];
    char rEmail[50];
    long long int rPhone = 0;
    unsigned int rKey = 0;
    char rPassword[50] = "";

    printf("**************************\n");
    printf("**Bank Registration Page**\n");
    printf("**************************\n");

    printf("Enter your email : ");
    scanf(" %[^\n]", rEmail);
    if(email_validation(rEmail)){
        if(email_exist_checking(rEmail) == -1){
            printf("Now you can register!\n");

            printf("Enter your name  :");
            scanf(" %[^\n]", rName);

            while(!phone_validation(rPhone)){
                printf("Enter your phone number : ");
                scanf("%lld", &rPhone);
                if(phone_validation(rPhone) == 0){
                    printf("Invalid Phone Number! Example Type 959XXXXXXXXX!\n");
                }
            }

            while (!key_validation(rKey)){
                printf("Enter your security key : ");
                scanf("%u", &rKey);
                if(key_validation(rKey) == 0){
                    printf("Your security key must be 4 digits!\n");
                }
            }

            while (!check_strong_password(rPassword)){
                printf("Enter your password : ");
                scanf(" %[^\n]", rPassword);
                if(check_strong_password(rPassword) == 0){
                    printf("Your password must be 8 digits\nAt least one Upper Case\nAt least one lower case\nAt least one digit\nAt least one special characters\nTry Again!\n");
                }
            }

            db[users].id = users+1;
            str_copy(db[users].name, rName);
            str_copy(db[users].nrc, "null");
            str_copy(db[users].dob, "null");
            str_copy(db[users].gender, "null");
            str_copy(db[users].address, "null");
            str_copy(db[users].email, rEmail);
            db[users].phone_number = rPhone;
            db[users].security_key = rKey;
            str_copy(db[users].password, rPassword);
            str_copy(db[users].pOrb, "Personal");
            db[users].amount = 10000;
            db[users].wallet_capacity = 1000000;
            db[users].amount_limit_per_day = 100000;

            users++;
            printing_all_data();
            welcome();

        }else{
            printf("Your email already taken!\n");
            registration();
        }
    }else{
        printf("Your email format not valid!\n");
        registration();
    }

}

void welcome(){
    int option = 0;
    printf("#####################\n");
    printf("##Welcome From Bank##\n");
    printf("#####################\n\n");
    printf("1. Login\n2. Register\n0. Exit\n");
    printf("Enter your option ::> ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            login();
            break;
        case 2:
            registration();
            break;
        case 0:
            recording_all_data_to_file();
            printf("Thanks for Using Our Bank :-)\n");
            exit(0);
            break;
        default:
            printf("Invalid Option! Again!\n");
            welcome();
            break;
    }
}

void printing_all_data(){
    for(int i = 0; i<users; i++){
        printf("%u %s %s %s %s %s %s %lld %u %s %s %u %u %u", db[i].id, db[i].name,
               db[i].nrc, db[i].dob, db[i].gender, db[i].address, db[i].email, db[i].phone_number, db[i].security_key,
               db[i].password, db[i].pOrb, db[i].amount, db[i].wallet_capacity, db[i].amount_limit_per_day);

        for(int j = 0; j<space_array[i]-13; j++){
            printf(" %s", db[i].trans[j].note);
        }
        printf("%c", '\n');
    }
}

void space_counter(){
    FILE *fptr;
    fptr = fopen("db.txt", "r");
    if(fptr == NULL){
        printf("Error: Call Space Counter Function\n");
        exit(1);
    }else{
        char c = fgetc(fptr);
        int index = 0;
        while(!feof(fptr)){
            if(c != '\n'){
                if(c == ' '){
                    space_array[index]++;
                }
                c= fgetc(fptr);
            }else{
                index++;
                c = fgetc(fptr);
            }
        }

        for(int i = 0; i<50; i++){
            printf("%d ", space_array[i]);
        }
        printf("\n");

    }
    fclose(fptr);
}

void loading_all_data_from_file(){
    FILE *fptr;
    fptr = fopen("db.txt", "r");
    if(fptr == NULL){
        printf("Error: Loading All Data From File\n");
        exit(1);
    }else{
        for(int i = 0; i<SIZE; i++){
            fscanf(fptr, "%u %s %s %s %s %s %s %lld %u %s %s %u %u %u", &db[i].id, db[i].name,
                   db[i].nrc, db[i].dob, db[i].gender, db[i].address, db[i].email, &db[i].phone_number, &db[i].security_key,
                   db[i].password, db[i].pOrb, &db[i].amount, &db[i].wallet_capacity, &db[i].amount_limit_per_day);

            for(int j = 0; j<space_array[i] - 13; j++){
                fscanf(fptr, " %s", db[i].trans[j].note);
            }

            if(db[i].name[0] == '\0'){
                break;
            }

            users++;

        }
    }
    fclose(fptr);
}

void recording_all_data_to_file(){
    FILE *fptr;
    fptr = fopen("db.txt", "w");
    if(fptr == NULL){
        printf("Error: Recording all data to file\n");
        exit(1);
    }else{
        for(int i = 0; i<users; i++){
            fprintf(fptr, "%u %s %s %s %s %s %s %lld %u %s %s %u %u %u", db[i].id, db[i].name,
                   db[i].nrc, db[i].dob, db[i].gender, db[i].address, db[i].email, db[i].phone_number, db[i].security_key,
                   db[i].password, db[i].pOrb, db[i].amount, db[i].wallet_capacity, db[i].amount_limit_per_day);

            for(int j = 0; j<space_array[i] - 13; j++){
                fprintf(fptr, " %s", db[i].trans[j].note);
            }
            fprintf(fptr,"%c", '\n');
        }
    }
    fclose(fptr);
}

int email_exist_checking(char email[50]){
    for(int i = 0; i<users; i++){
        if(str_cmp(db[i].email, email)){
            return i;
        }
    }
    return -1;
}

int phone_exist_checking(long long int phone){
    for(int i = 0; i<users; i++){
        if(db[i].phone_number == phone){
            return i;
        }
    }
    return -1;
}

int check_strong_password(char password[50]){
    int length = str_len(password);
    int Upper = 0;
    int lower = 0;
    int digit = 0;
    int special = 0;
    char c;
    if(length >= 8){
        for(int i = 0; i<length; i++){
            c = password[i];
            if(c >= 'A' && c <= 'Z'){
                Upper++;
            }else if(c >= 'a' && c <= 'z'){
                lower++;
            }else if(c >= '0' && c <= '9'){
                digit++;
            }else if(c >= '!' && c <= '/'){
                special++;
            }else if(c >= ':' && c <= '@'){
                special++;
            }else if(c >= '[' && c <= '`'){
                special++;
            }else if(c >= '{' && c <= '}'){
                special++;
            }
        }
        if((Upper >= 1) && (lower >= 1) && (digit >= 1) && (special >= 1)){
            return 1;
        }else{
            return 0;
        }
    }
    return 0;
}

void get_current_data_to_TR(unsigned int current_amount){
    char current_day[5];
    get_time();
    current_day[0] = Ctime[0].c_time[9];
    current_day[1] = Ctime[0].c_time[10];
    int current_day_result = char_to_int(current_day);

    current_day_to_TR = current_day_result;
    current_amount_to_TR = current_amount;

    printf("Current data to TR : %d | %u\n", current_day_to_TR, current_amount_to_TR);
}

unsigned int get_total_amount_of_same_day(int indexToGet, unsigned int amount_to_TR){

    get_current_data_to_TR(amount_to_TR);
    unsigned int total_amount_of_same_day = 0;
    int record_counter = space_array[indexToGet] - 13;

    char trans_day[3];
    char trans_amount[10];

    int amount_finder = 0;
    int amount_counter = 0;
    int day_finder = 0;
    int index_counter = 0;

    for(int i = (record_counter-1); i >= 0; i--){
        int current_record_counter = str_len(db[indexToGet].trans[i].note);

        //to find $
        for(int j = 0; j<current_record_counter; j++){
            if(db[indexToGet].trans[i].note[j] == '$'){
                break;
            }
            index_counter++;
        }
        amount_counter = 0;
        for(int j = index_counter; j<current_record_counter; j++){
            if(db[indexToGet].trans[i].note[j] == '_'){
                break;
            }
            amount_counter++;
        }
        index_counter++;
        for(int a = 0; a<10; a++){
            trans_amount[a] = '\0';
        }

        //put amount to trans_amount
        for(int j = 0; j<amount_counter-1; j++){
            trans_amount[j] = db[indexToGet].trans[i].note[index_counter];
            index_counter++;
        }

        unsigned int trans_amount_result = char_to_int(trans_amount);
//        printf("Current Amount Record : %u\n", trans_amount_result);

        //to find #
        for(int j = index_counter; j<current_record_counter; j++){
            if(db[indexToGet].trans[i].note[j] == '#'){
                break;
            }
            index_counter++;
        }

        //put day to trans_day
        trans_day[0] = db[indexToGet].trans[i].note[index_counter+1];
        trans_day[1] = db[indexToGet].trans[i].note[index_counter+2];

        long long int trans_day_result = char_to_int(trans_day);
//        printf("Current Day Record : %d\n\n", trans_day_result);

        if(trans_day_result == current_day_to_TR){
            total_amount_of_same_day += trans_amount_result;
        }
        index_counter = 0;
    }


    return total_amount_of_same_day;
}

//validation functions
int email_validation(char email[50]){
    int at_index_counter = index_counter(email, '@');
    int email_counter = str_len(email);
    //check for space
    for(int i = 0; i<email_counter; i++){
        if(email[i] == ' '){
            return 0;
        }
    }
    if(at_index_counter == 1){
        int at_index = indexOf_char(email, '@');
        int dot_index_counter = 0;
        int dot_index = 0;
        for(int i = at_index; i<email_counter; i++){
            if(email[i] == '.'){
                dot_index = i;
                dot_index_counter++;
            }
        }
        if(dot_index_counter == 1){
            if(email[dot_index+1] != '\0'){
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else{
        return 0;
    }

}

int phone_validation(long long int phone){
    int code = phone / 1000000000;
    if(code == 959){
        if(int_len(phone) == 12){
            return 1;
        }
    }
    return 0;
}

int key_validation(unsigned int key){
    int key_length = int_len(key);
    if(key_length == 4){
        return 1;
    }
    return 0;
}

int nrc_validation(char nrc[25]){
    load_data_to_nrc_db();
    char nrc_type[15];
    for(int i = 0; i<15; i++){
        nrc_type[i] = '\0';
    }
    int nrc_counter = str_len(nrc);
    int get_nrc_type_index = indexOf_char(nrc, ')');
    for(int i = 0; i<=get_nrc_type_index; i++){
        nrc_type[i] = nrc[i];
    }

    for(int i = 0; i<NRC_DB_SIZE; i++){
        if(str_cmp(nrcDB[i].nrc, nrc_type)){
            if(nrc_counter == 14){
                return 1;
            }
        }
    }

    return 0;
}

void load_data_to_nrc_db(){
    str_copy(nrcDB[0].nrc, "1/ygn(N)");
    str_copy(nrcDB[1].nrc, "2/mdy(N)");
}

void get_time(){
    time_t tm;
    time(&tm);

//    printf("Current time =%s\n", ctime(&tm));

    FILE *fptr = fopen("myTime.txt","w");
    fprintf(fptr,"%s", ctime(&tm));

    fclose(fptr);

    int index=0;
    int time_space_counter=0;

    Ctime[0].c_time[index]='_';
    index++;

    FILE *fptr2 = fopen("myTime.txt","r");
    char c = fgetc(fptr2);

    while (c != '\n'){

        if( c==' '){

            time_space_counter++;

            if(time_space_counter == 1){
                Ctime[0].c_time[index]='!';
                c = fgetc(fptr2);
                index++;
            } else if(time_space_counter == 2){
                Ctime[0].c_time[index]='#';
                c = fgetc(fptr2);
                index++;
            } else if(time_space_counter==4){
                Ctime[0].c_time[index]='@';
                c = fgetc(fptr2);
                index++;
            } else{
                Ctime[0].c_time[index]='_';
                c = fgetc(fptr2);
                index++;
            }
        } else{

            Ctime[0].c_time[index]=c;
            c = fgetc(fptr2);
            index++;

        }
    }
}

void int_to_char(long long int num){
    FILE *fptr1;
    fptr1 = fopen("convertITC.txt", "w");
    fprintf(fptr1, "%lld", num);
    fclose(fptr1);

    FILE *fptr2;
    fptr2 = fopen("convertITC.txt", "r");
    fscanf(fptr2, "%s", &int_to_char_result[0]);
    fclose(fptr2);
}

long long int char_to_int(char str[100]){
    long long int data = 0;

    FILE *fptr1;
    fptr1 = fopen("convertCTI.txt", "w");
    fprintf(fptr1, "%s", str);
    fclose(fptr1);

    FILE *fptr2;
    fptr2 = fopen("convertCTI.txt", "r");
    fscanf(fptr2, "%lld", &data);
    fclose(fptr2);

    return data;
}

#endif //BANKPROJECTWITHC_BANK_H
