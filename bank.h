//
// Created by whs on 5/30/23.
//

#ifndef DIPLEVEL1_FINAL_PROJECT_BANK_H

#include "time.h"
//#################### structure for main  START############################
struct trans{
    char note[200];
};

struct cash{
    char note[200];
};

struct info {
    unsigned int id;
    char name[30];
    char nrc[50];
    char email[50];
    char password[50];
    char phNumber[15];
    char address[100];
    unsigned int cur_amount; //current amount
    char pOrb[20]; //personal or business
    unsigned int loan_amount;
    int acc_level;
    unsigned int transAmoLimitPerDay; //transfer amount limited per day => minimize for our project 5min
    struct trans trc[100]; // transfer record
    struct cash crc[100];
};

//#################### structure for main  END ############################


//###################### structure and function prototyping for avl tree START ############################
struct node {
    struct info data;
    struct node* left;
    struct node* right;
    int ht;
};

struct node* root = NULL;

//function prototyping for AVL_TREE
struct node* create(struct info);
struct node* insert(struct node*,struct info);
struct node* search(struct node*,unsigned int);
struct node* Delete(struct node*, unsigned int);
void print_data(struct node* root);
struct node* rotate_left(struct node*);
struct node* rotate_right(struct node*);
int balance_factor(struct node*);
int height(struct node*);

//###################### structure and function prototyping for avl tree END ############################




//############################## function prototyping for main #################################
void welcome();
void login();
void registration();
void userSector(struct info);
int charCounting(char toCount[50]);
void copyChar(char fromFirst[50], char toSecond[50]);
void gmailValidation(char toValid[50]);
void check_password_correct(char login_pass[50], char db_password[50]);
void check_gmail_exist(struct node* root,char inputGmail[50]);
void nrc_validation(char nrc[50]);
void insert_data_to_file(FILE *fptr,struct node* root);
void recording_all_data_to_file();
void loading_all_data_from_file();
void easyToGuess(char uPass[50]);
void phNumberValidation(char inputPhNumber[15]);
void addCountryCode(char phNumber[15]);
void compare_two_charArray(char first[50], char second[50]);
void phone_num_exist_checking(struct node*, char phNumber[15]);
void space_counter();
void transfer_money(unsigned int transfer,unsigned int receiver, unsigned int amount);
void current_data_to_transfer(unsigned int current_amount_to_transfer_param);
unsigned int get_limit_amount(struct info user_info);
unsigned int calculate_amounts_same_days(unsigned int to_calcu_index,char who);
void get_time();
unsigned int char_to_unsigned_int(char charArray[]);
void transaction_record(unsigned int transfer,unsigned int receiver, char who,unsigned int amount);
void integer_to_char(unsigned int value);
void cash_in_out_record(unsigned int user_index, unsigned int amount, char in_Or_out);
void nrc_exist_checking(struct node* root, char nrc[50]);
int check_input(char input[2]);
//#################  Global variable  ######################
unsigned int user = 0;
int checkValid = -1;
int eFound = -1;
int is_password_correct = -1;
int nrc_valid = -1;
int nrc_Found = 1;
int guessPass = -1;
int phNumberFound = 1;
int phNumberValid= -1;
int is_TwoCharArray_same=-1;
int isContinue = 0;
unsigned int is_receiver_phNum_exist = -1;
unsigned int current_amount_to_transfer = 0;

unsigned int current_day_to_transfer = 0;

int space_array[50];
int cash_in_out_space_array[50];
char current_time_array[24];
char integer_to_char_array[10];



//##################################################################  AVL_TREE_START  ############################################################################

struct node* create(struct info data) {
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    // if a memory error has occurred
    if (new_node == NULL)
    {
        printf("\nMemory can't be allocated\n");
        return NULL;
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

// rotates to the left
struct node* rotate_left(struct node* root)
{
    struct node* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;

    // update the heights of the nodes
    root->ht = height(root);
    right_child->ht = height(right_child);

    // return the new node after rotation
    return right_child;
}

//rotates to the right
struct node* rotate_right(struct node* root)
{
    struct node* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;

    // update the heights of the nodes
    root->ht = height(root);
    left_child->ht = height(left_child);

    // return the new node after rotation
    return left_child;
}

// calculates the balance factor of a node
int balance_factor(struct node* root)
{
    int lh, rh;
    if (root == NULL)
        return 0;
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
    return lh - rh;
}

// calculate the height of the node
int height(struct node* root)
{
    int lh, rh;
    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;

    if (lh > rh)
        return (lh);
    return (rh);
}

struct node* insert(struct node* root, struct info data) {
    if(root == NULL) {
        struct node* new_node = create(data);
        if(new_node == NULL) {
            return NULL;
        }
        root=new_node;
    }else if(data.id >root->data.id){
        root->right = insert(root->right,data);

        if(balance_factor(root) == -2) {
            if(data.id > root->right->data.id) {
                root= rotate_left(root);
            }else{
                root->right = rotate_right(root->right);
                root = rotate_left(root);
            }
        }

    }else {
        root->left = insert(root->left,data);

        if(balance_factor(root) == 2) {
            if(data.id < root->left->data.id) {
                root = rotate_right(root);
            }else{
                root->left = rotate_left(root->left);
                root = rotate_right(root);
            }
        }
    }

    root->ht = height(root);
    return root;
}

struct node * Delete(struct node *root, unsigned int x) {
    struct node *temp = NULL;

    if (root == NULL)
    {
        return NULL;
    }

    if (x > root->data.id)
    {
        root->right = Delete (root->right, x);

        if (balance_factor(root)== 2)
        {
            if (balance_factor(root->left) >= 0)
            {
                root = rotate_right(root);
            }
            else
            {
                root->left = rotate_left(root->left);
                root = rotate_right(root);
            }
        }
    }
    else if (x<root->data.id) {
        root->left = Delete (root->left, x);

        if ( balance_factor(root) == -2 ) {
            if (balance_factor(root->right) <= 0)
            {
                root = rotate_left(root);
            }
            else
            {
                root->right = rotate_right(root->right);
                root = rotate_left(root);
            }
        }
    }
    else {
        if (root->right != NULL) {
            temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;

            root->data = temp->data;
            root->right = Delete (root->right, temp->data.id);

            if (balance_factor(root)== 2)
            {
                if (balance_factor(root->left) >= 0)
                {
                    root = rotate_right(root);
                }
                else
                {
                    root->left = rotate_left(root->left);
                    root = rotate_right(root);
                }
            }
        }
        else
        {
            return (root->left);
        }
    }
    root->ht = height(root);
    return (root);
}
// search a node in the AVL tree
struct node* search(struct node* root,unsigned int key)
{
    if (root == NULL)
    {
        return NULL;
    }

    if(root->data.id == key)
    {
        return root;
    }

    if(key > root->data.id)
    {
        search(root->right, key);
    }
    else
    {
        search(root->left, key);
    }
}

// inorder traversal of the tree
void print_data(struct node* root) //############################################ inorder is used for printing data ##################################3
{
    if (root == NULL)
    {
        return;
    }

    print_data(root->left);
    struct info userInfo = root->data;
    printf("%u %s %s %s %s %s %s %u %s %u %d %u",userInfo.id, userInfo.name, userInfo.nrc, userInfo.email, userInfo.password,userInfo.phNumber, userInfo.address, userInfo.cur_amount, userInfo.pOrb, userInfo.loan_amount, userInfo.acc_level, userInfo.transAmoLimitPerDay);
    int index=userInfo.id - 1;
    for (int i = 0; i < space_array[index]-11; ++i) {
        printf(" %s",userInfo.trc[i].note);
    }
    for (int i = 0; i < cash_in_out_space_array[index]; ++i) {
        printf(" %s",userInfo.crc[i].note);
    }
    printf("%c",'\n');

    print_data(root->right);
}

//##################################################################  AVL_TREE_END  ############################################################################



//****************************************************************** main-start  *******************************************************************************

void welcome() {
    space_counter();
    print_data(root); //print all data
    char input[2];
    printf("######### This is welcome screen ###########\n");
    printf("Press 1 to Login:\n");
    printf("Press 2 to Register:\n");
    printf("Press 3 to exit:");

    scanf(" %[^\n]", &input[0]);
    int option = check_input(input);

    if(option == 49) {

        login();
    }else if(option == 50) {

        registration();

    }else if(option == 51) {
        recording_all_data_to_file();
        exit(1);
    }else{
        printf("Wrong option!\n");
        welcome();
    }

}



void insert_data_to_file(FILE *fptr,struct node* root)
{
    if (root == NULL)
    {
        return;
    }

    insert_data_to_file(fptr,root->left);
    struct info data = root->data;
    fprintf(fptr,"%u %s %s %s %s %s %s %u %s %u %d %u",data.id, data.name, data.nrc, data.email, data.password,data.phNumber, data.address, data.cur_amount, data.pOrb, data.loan_amount, data.acc_level, data.transAmoLimitPerDay);
    int index = root->data.id -1; //id start 1 , so its index is 0.

        for (int i = 0; i < space_array[index]-11; ++i) {
            if(data.trc[i].note[0] != '\0') {
                fprintf(fptr, " %s", data.trc[i].note);
            }
        }

        if(data.trc[space_array[index]-12].note[0] != '?') {
            fprintf(fptr, " %c",'?');
        }

        for (int i = 0; i < cash_in_out_space_array[index]; ++i) {
            fprintf(fptr," %s", data.crc[i].note);
        }



    fprintf(fptr,"%c",'\n');
    insert_data_to_file(fptr,root->right);
}

void recording_all_data_to_file() {
    FILE *fptr = fopen("bankDb.txt","w");
    if(fptr == NULL) {
        printf("Error at recording data!!\n");
    }else{
        insert_data_to_file(fptr,root);
    }
    fclose(fptr);
}

void loading_all_data_from_file() {
    FILE *fptr = fopen("bankDb.txt","r");
    if(fptr == NULL) {
        printf("Error at loading data\n");
    }else{
        int isBreak=1;
        while (isBreak) {
            //autofill "\0" at the end of each inserted data.If data are overwrite,"\0" can solve this problem.
            // eg. oldData => w,a,i,h,i,n,s,o,e,@,g,m,a,i,l,.,c,o,m => newData => h,m,w,e,@,g,m,a,i,l,.,c,o,m,\0,l,.,c,o,m
            struct info userInfo;                     //                                                       ^
            fscanf(fptr,"%u%s%s%s%s%s%s%u%s%u%d%u",&userInfo.id, &userInfo.name[0], &userInfo.nrc[0], &userInfo.email[0], &userInfo.password[0],&userInfo.phNumber[0], &userInfo.address[0], &userInfo.cur_amount, &userInfo.pOrb[0], &userInfo.loan_amount, &userInfo.acc_level, &userInfo.transAmoLimitPerDay);
            int index = userInfo.id - 1;
            for (int i = 0; i < space_array[index]-11; ++i) {
                fscanf(fptr,"%s", &userInfo.trc[i].note[0]);
            }
            for (int i = 0; i < cash_in_out_space_array[index]; ++i) {
                fscanf(fptr, "%s", &userInfo.crc[i].note[0]);
            }
            if(userInfo.id == 0){
//                printf("looping is break\n");
                isBreak = 0;
                break;
            }
            root=insert(root,userInfo);
            userInfo.id = 0;


            user++;
        }



    }
    fclose(fptr);
}

void login() {
    printf("################# This is login section ######################\n");
    unsigned int login_id;
    char login_password[50];

    printf("Enter your account id : ");
    scanf("%u", &login_id);

    printf("Enter your password : ");
    scanf(" %[^\n]", &login_password[0]);

    struct node* result = search(root,login_id);

    is_password_correct = -1;
    check_password_correct(login_password, result->data.password);

    if(result != NULL && is_password_correct == 1) {

        printf("Welcome sir : %s \n",result->data.name);
        printf("Your current amount : %u \n", result->data.cur_amount);
        userSector(result->data);
    }else{
        printf("Id or Password wrong!. Please Try Again! \n");
        welcome();
    }



}

void registration() {
    printf("********************* This is registration section ***********************\n");
    struct info newUser;
    char re_Email[50];
    char re_name[30];
    char re_nrc[50];
    char re_phNumber[15];
    char re_pass[50];
    char re_address[100];
    char default_personal[9] = {'p','e','r','s','o','n','a','l','\0'};

    checkValid = -1;
    while (checkValid == -1) {
        printf("Enter your email : ");
        scanf(" %[^\n]",&re_Email[0]);
        gmailValidation(re_Email);
    }

    eFound= -1;
    check_gmail_exist(root, re_Email);

    if(eFound != -1){
            printf("############## email has already existed, Try Again!! ##################\n");
            welcome();

    }else{
        printf("Enter your name :");
        scanf(" %[^\n]", &re_name[0]);

        nrc_Found = 1;
        while (nrc_Found == 1){

            nrc_valid=-1;
            while(nrc_valid == -1){
                printf("Enter your nrc number with this format > 1/example(N)111111 <:");
                scanf(" %[^\n]", &re_nrc[0]);
                nrc_validation(re_nrc);
            }

            isContinue = 0;
            if(root == NULL) {
                nrc_Found = -1;
            }

            nrc_exist_checking(root,re_nrc);

            if(isContinue == 1) {
                nrc_Found = 1;
                printf("NRC has already existed!!\n");
            }
        }

        phNumberFound = 1;
        while (phNumberFound == 1) {

            phNumberValid = -1;
            while (phNumberValid == -1) {
                printf("Enter your Phone Number : +959 ");
                scanf(" %[^\n]", &re_phNumber[0]);
                phNumberValidation(re_phNumber);

            }

            addCountryCode(re_phNumber);
            isContinue = 0;
            if(root == NULL) {
                phNumberFound = -1;
            }

            phone_num_exist_checking(root,re_phNumber);

            if(isContinue == 1) {
                phNumberFound = 1;
                printf("Phone number has already existed!!\n");
            }
        }

        guessPass = -1;
        while (guessPass == -1) {
            printf("Enter  password : ");
            scanf(" %[^\n]", &re_pass[0]);
            easyToGuess(re_pass);
        }

        printf("Enter your current amount : ");
        scanf("%u", &newUser.cur_amount);

        printf("Enter your  address : ");
        scanf(" %[^\n]", &re_address[0]);

        newUser.id = user+1;
        copyChar(re_name,newUser.name);
        copyChar(re_nrc,newUser.nrc);
        copyChar(re_Email,newUser.email);
        copyChar(re_pass,newUser.password);
        copyChar(re_phNumber,newUser.phNumber);
        copyChar(re_address,newUser.address);

        //default data
        copyChar(default_personal,newUser.pOrb);
        newUser.loan_amount = 0;
        newUser.acc_level = 3;
        newUser.transAmoLimitPerDay = 5000;

        root = insert(root,newUser);
        printf("This is your account Id : >>>>>> %u <<<<<<< . Please Login with this Id and password!\n",newUser.id);
        user++;

        recording_all_data_to_file();

    }



    welcome();
}

void userSector(struct info current_user_data) {
    space_counter();
    char input[2];
    printf("############# This is userSector section ############### \n");
    printf("Press 1 to Transfer Money:\nPress 2 to Cash in :\nPress 3 to Cash out:\nPress 4 to Loan:\nPress 5 Exit");
    scanf(" %[^\n]", &input[0]);
    int option = check_input(input);
    if(option == 49) {
        printf("This is for transfer option.\n");
        char phNumber_for_transfer[15];
        unsigned int transfer_amount = 0;
        char confirm_password[50];
        is_receiver_phNum_exist = -1;
        while (is_receiver_phNum_exist == -1) {
            printf("Enter receiver's phone Number : +959 ");
            scanf(" %[^\n]", &phNumber_for_transfer[0]);
            addCountryCode(phNumber_for_transfer);
            is_TwoCharArray_same = -1;
            compare_two_charArray(phNumber_for_transfer, current_user_data.phNumber);
            if(is_TwoCharArray_same == 1){
                printf("Yon can't transfer money to yourself\n");
                continue;
            }
            if(root == NULL) {
                is_receiver_phNum_exist = -1;
            }
            phone_num_exist_checking(root,phNumber_for_transfer);
            if(is_receiver_phNum_exist == -1) {
                printf("Account doesn't exist with %s. Try Again!\n",phNumber_for_transfer);
            }
        }

        printf("This is receiver id >>>>>>> %d <<<<<<<<\n",is_receiver_phNum_exist);

        while (transfer_amount < current_user_data.cur_amount){
            printf("Enter amount to transfer :");
            scanf("%u", &transfer_amount);
           if(current_user_data.cur_amount-1000 >= transfer_amount) {
                break;
            }else{
                printf("No sufficient balance:\n");
                transfer_amount = 0;
               userSector(current_user_data);
               break;
            }
        }

        int wrong_times_counter = 0;
        is_password_correct = -1;
        while (is_password_correct == -1){
            printf("Enter password to confirm :");
            scanf(" %[^\n]", &confirm_password[0]);
            check_password_correct(confirm_password, current_user_data.password);
            if(is_password_correct == -1) {
                printf("Wrong password . Try again!\n");
            }
            wrong_times_counter++;
            if(wrong_times_counter == 3){
                userSector(current_user_data);
                break;

            }
        }

        transfer_money(current_user_data.id,is_receiver_phNum_exist,transfer_amount);
        recording_all_data_to_file();
        userSector(current_user_data);
    }
    else if(option == 50) {
        struct node* current_user_info = search(root, current_user_data.id);
        struct info user_data = current_user_info->data;
        unsigned int cash_in_amount=0;
        printf("############################### This is CashIn option ############################\n");

        printf("Enter cash in amount : ");
        scanf("%u", &cash_in_amount);
        user_data.cur_amount += cash_in_amount;

        root = Delete(root, user_data.id);
        root = insert(root, user_data);
        cash_in_out_record(user_data.id, cash_in_amount,'i'); // 'i' means cash in
        printf("########################## Cash in successful!! ##########################################\n");
        recording_all_data_to_file();
        userSector(current_user_data);
    }
    else if(option == 51) {
        printf("################################ This is Cash Out option ###########################\n");
        char confirm_password[50];
        struct node* current_user_info = search(root, current_user_data.id);
        struct info user_data = current_user_info->data;
        unsigned int cash_out_amount = 0;
        while (cash_out_amount < user_data.cur_amount){
            printf("Enter amount to cash Out :");
            scanf("%u", &cash_out_amount);
            if(user_data.cur_amount-1000 > cash_out_amount) {
                break;
            }else{
                printf("No sufficient balance:\n");
                cash_out_amount = 0;
            }
        }

        int wrong_times_counter = 0;
        is_password_correct = -1;
        while (is_password_correct == -1){
            printf("Enter password to confirm :");
            scanf(" %[^\n]", &confirm_password[0]);
            check_password_correct(confirm_password, user_data.password);
            if(is_password_correct == -1) {
                printf("[-]Wrong password . Try again!\n");
            }
            wrong_times_counter++;
            if(wrong_times_counter == 3){
                userSector(current_user_data);
                break;
            }
        }

        user_data.cur_amount -= cash_out_amount;

        root = Delete(root, user_data.id);
        root = insert(root, user_data);

        cash_in_out_record(user_data.id, cash_out_amount,'o'); // 'o' means cash out
        recording_all_data_to_file();
        printf("################################# Cash Out successful! ########################################\n");
        userSector(current_user_data);
    }
    else if(option == 52) {
        printf("################################ This is Loan option ###############################\n");
        struct node* current_user_info = search(root, current_user_data.id);
        struct info user_data = current_user_info->data;
        unsigned int temp_loan_amount = 0;
        printf("Enter loan amount :");
        scanf("%u", &temp_loan_amount);

        if(user_data.loan_amount+temp_loan_amount > 10000){
            printf("############################# loan amount limit full  ############################\n");
            userSector(current_user_data);
        }else{
            user_data.loan_amount += temp_loan_amount;
            user_data.cur_amount += temp_loan_amount;

            root = Delete(root,user_data.id);
            root = insert(root,user_data);

            recording_all_data_to_file();
            printf("################################################### loan  success ! #######################################################3\n");
            userSector(current_user_data);
        }


    }
    else if(option == 53) {
        exit(1);
    }
    else{
        printf("wrong option!\n");
        userSector(current_user_data);
    }
}

int check_input(char input[2]){
    if( input[0]>=49 &&input[0]<= 57 && input[1]=='\0'){
        return input[0];
    } else{
        return -1;
    }
}

void space_counter() {
    for (int i = 0; i < 50; ++i) {
        space_array[i] = 0;
    }

    for (int i = 0; i < 50; ++i) {
        cash_in_out_space_array[i] = 0;
    }

    FILE *fptr = fopen("bankDb.txt", "r");

    if(fptr == NULL) {
        printf("Error at space_counter_function\n");
    }else{
        char c = fgetc(fptr);
        int index = 0;
        int is_QMark_found = -1;
        while (!feof(fptr)) {
            if(c != '\n') {
                if(c == ' ') {
                    if(is_QMark_found == 1) {
                        cash_in_out_space_array[index] += 1;
                    }else{
                        space_array[index] +=1;
                    }

                }
                if(c == '?') {
                    is_QMark_found = 1;

                }
                c = fgetc(fptr);
            }else{
                index++;
                is_QMark_found = -1;
                c = fgetc(fptr);
            }
        }

        for (int j = 0; j < 50; ++j) {
            printf(" %d ",space_array[j]);
        }
        printf("\n");

        for (int i = 0; i < 50; ++i) {
            printf(" %d ", cash_in_out_space_array[i]);
        }
        printf("\n");
    }
}

void cash_in_out_record(unsigned int user_index,unsigned int amount,char in_Or_out) {
    struct node* current_user_info = search(root, user_index);
    struct info current_user_data =current_user_info->data;
    unsigned int current_user_index = user_index-1;
    integer_to_char(amount);
    int amount_counter = charCounting(integer_to_char_array);
// from-WinHtut-to-lonelone-100
    char cash_In[8] = {'C','a','s','h','-','I','n','-'};
    char cash_Out[9] ={'C','a','s','h','-','O','u','t','-'};
    char at[4] = {'-','a','t', '-'};

    get_time();

    int current_time_array_counter = charCounting(current_time_array);

    if(in_Or_out == 'i'){
        int counter = 0;

        for (int i = 0; i < 8; ++i) {
            current_user_data.crc[cash_in_out_space_array[current_user_index]].note[counter] = cash_In[i];
            counter++;
        }

        for (int i = 1; i < amount_counter; ++i) {
            current_user_data.crc[cash_in_out_space_array[current_user_index]].note[counter]  = integer_to_char_array[i];
            counter++;
        }

        for (int k = 0; k < 4; ++k) {
            current_user_data.crc[cash_in_out_space_array[current_user_index]].note[counter]  = at[k];
            counter++;
        }

        for (int i = 0; i < 24; ++i) {
            current_user_data.crc[cash_in_out_space_array[current_user_index]].note[counter]  = current_time_array[i];
            counter++;
        }
        cash_in_out_space_array[current_user_index] += 1;
        root= Delete(root,user_index);
        root= insert(root,current_user_data);
    }else{
        int counter = 0;

        for (int i = 0; i < 9; ++i) {
            current_user_data.crc[cash_in_out_space_array[current_user_index]].note[counter] = cash_Out[i];
            counter++;
        }

        for (int i = 1; i < amount_counter; ++i) {
            current_user_data.crc[cash_in_out_space_array[current_user_index]].note[counter]  = integer_to_char_array[i];
            counter++;
        }

        for (int k = 0; k < 4; ++k) {
            current_user_data.crc[cash_in_out_space_array[current_user_index]].note[counter]  = at[k];
            counter++;
        }

        for (int i = 0; i < 24; ++i) {
            current_user_data.crc[cash_in_out_space_array[current_user_index]].note[counter]  = current_time_array[i];
            counter++;
        }
        cash_in_out_space_array[current_user_index] += 1;
        root= Delete(root,user_index);
        root= insert(root,current_user_data);
    }
}

void check_password_correct(char login_pass[50], char db_password[50]) {
    int login_password_count = charCounting(login_pass);
    int db_password_count = charCounting(db_password);
    int same= 0;
    if(login_password_count == db_password_count) {
        for (int i = 0; i < db_password_count; ++i) {
            if(login_pass[i] == db_password[i]) {
                same++;
            }else{
                break;
            }
        }

        if(same == db_password_count) {
            is_password_correct=1;
        }
    }else{
        is_password_correct=-1;
    }

}

void gmailValidation(char toValid[50]) {
    char form[10] = {'@','g','m','a', 'i', 'l', '.', 'c', 'o', 'm'};
    int endPoint = charCounting(toValid);
    int formCount = charCounting(form);
    int isValid = 0;
    for (int i = 0; i < endPoint; ++i) {
        if(toValid[i] == ' ') {
            break;
        }else if(toValid[i] == form[0]){
            int index = i;
            if(endPoint-index == 10) {
                for (int j = 0; j < formCount; ++j) {
                    if(toValid[index] == form[j]){
                        isValid++;
                        index++;
                    } else{
                        break;
                    }
                }
            }
        }
    }
    if(isValid == formCount) {
        checkValid = 1;
    }else{
        printf("[-]Invalid gmail!\n");
    }
}

void check_gmail_exist(struct node* root,char inputGmail[50])
{
    int sameCount = 0;
    int inputGmailCount = charCounting(inputGmail);
    if (root == NULL)
    {
        return;
    }

    check_gmail_exist(root->left,inputGmail);

        int dbGmailCount = charCounting(root->data.email);
        if(inputGmailCount == dbGmailCount) {
            for (int i = 0; i < inputGmailCount; ++i) {
                if(inputGmail[i] == root->data.email[i]) {
                    sameCount++;
                }else {
                    break;
                }
            }
        }
        if(sameCount == inputGmailCount) {
            eFound = 1;
        }

    check_gmail_exist(root->right,inputGmail);
}

void nrc_validation(char nrc[50]) {
    int valid_point = 6;            // for all format example 1/palana(N)111111
    int id_valid_point = 6;         // for code example 111111
    int valid_counter =0;           // If valid_counter is equal valid_point, nrc is valid.
    int nrc_count = charCounting(nrc);
    int id_valid_counter = 0;
    int is_contain_slat = -1;
    char region[2] = {'\0','\0'};
    for (int i = 0; i < nrc_count; ++i) {
        if(nrc[i] == '/'){
            is_contain_slat=1;
        }
    }
    if(is_contain_slat == -1) {
        printf("[-] wrong format, try again!\n");
        return;
    }
    for (int i = 0; i < nrc_count; ++i) {
       if(nrc[i] == '/') {
           break;
       }else{
           region[i] = nrc[i];
       }
    }
    int region_count = charCounting(region);
    if(region_count == 1 && region[0] > 48 && region[0] < 58) {
        valid_counter++;
    }else if(region_count == 2 && region[0] == 49 && region[1] > 47 && region[1] < 54) {
        valid_counter++;
    }

    for (int i = 0; i < nrc_count; ++i) {
        if(nrc[i] == '/' || nrc[i] == '(' || nrc[i] == 'N' || nrc[i] == ')' ) {
            valid_counter++;
        }
        if(nrc[i] == ')' ) {
            int index=i+1;
            for (int j = index; j < nrc_count; ++j) {
                if(nrc[j] > 47 && nrc[j] < 58) {
                    id_valid_counter++;
                }
            }
            if(id_valid_counter == id_valid_point) {
                valid_counter++;
                break;
            }

        }

    }

    if(valid_counter == valid_point) {
        nrc_valid=1;
    }else{
        printf("validPoint : %d \n", valid_counter);
        printf("[-] wrong format, try again!\n");
    }
}

int charCounting(char toCount[50]) {
    int count = 0;
    for (int i = 0; i < 50; ++i) {
        if(toCount[i] == '\0'){
            break;
        } else{
            count++;
        }
    }
    return count;
}

void copyChar(char fromFirst[50], char toSecond[50]) {
    for (int i = 0; i < 50; ++i) {
        toSecond[i] = '\0';
    }
    int fromFirstCount = charCounting(fromFirst);
    for (int j = 0; j < fromFirstCount; ++j) {
        toSecond[j] = fromFirst[j];
    }
}

void easyToGuess(char uPass[50]) {
    int specialCount = 0;
    int numberCount = 0;
    int upperCount = 0;
    int lowerCount = 0;
    int uPassCount = charCounting(uPass);

    if(uPassCount >= 8){
        for (int i = 0; i < uPassCount; ++i) {
            if( (uPass[i] == 64 || uPass[i] >= 33 && uPass[i] <= 47)) {
                specialCount++;
            }else if(uPass[i] >= 48 && uPass[i] <=57){
                numberCount++;
            }else if(uPass[i] >=65 && uPass[i] <= 90) {
                upperCount++;
            }else if(uPass[i] >= 97 && uPass[i] <= 122) {
                lowerCount++;
            }
        }
    }else{
        printf("[-]Must be 8 characters or more\n");
        return;
    }

    if(specialCount > 0 && numberCount > 0 && upperCount > 0 && lowerCount > 0) {
        printf("[+]strong password!\n");
        guessPass = 1;
    }else{
        printf("[-]weak password!\n");
        guessPass = -1;
    }

}

void phNumberValidation(char inputPhNumber[15]) {
    int phNumberCount = charCounting(inputPhNumber);
    if(inputPhNumber[0] == '2' && inputPhNumber[1] == '0'){
        if(phNumberCount == 8) {
            printf("Valid phone number!\n");
            phNumberValid = 1;
        } else{
            printf("Invalid phone number!\n");
        }
    }else {
        if(phNumberCount == 9) {
            phNumberValid = 1;
        } else{
            printf("Invalid phone number!\n");
        }
    }
}

void addCountryCode(char phNumber[15]) {
    char countryCode[4] = {'+', '9', '5', '9'};
    char temp_array[50];
    copyChar(phNumber, temp_array);
    for (int i = 0; i < 15; ++i) {
        phNumber[i] = '\0';
    }
    int last_index_of_countryCode = 0;
    for (int i = 0; i < 4; ++i) {
        phNumber[i] = countryCode[i];
        last_index_of_countryCode++;
    }

    int phNumber_count = charCounting(temp_array);
    for (int j = 0; j < phNumber_count; ++j) {
        phNumber[last_index_of_countryCode] = temp_array[j];
        last_index_of_countryCode++;
    }
}

void phone_num_exist_checking(struct node* root, char phNumber[15])
{
    if (root == NULL )
    {
        return;
    }
        phone_num_exist_checking(root->left, phNumber);
    int firstCount = charCounting(root->data.phNumber);
    int secCount = charCounting(phNumber);
    int same = 0;
    if (firstCount == secCount) {
        for (int i = 0; i < firstCount; ++i) {
            if (root->data.phNumber[i] == phNumber[i]) {
                same++;
            } else {
                break;
            }
        }
        if (same == firstCount) {
            phNumberFound = 1;
            isContinue = 1;
            is_receiver_phNum_exist= root->data.id;
        }else{
            phNumberFound = -1;
        }
    }else{
        phNumberFound = -1;

    }

        phone_num_exist_checking(root->right, phNumber);


}


void nrc_exist_checking(struct node* root, char nrc[50])
{
    if (root == NULL )
    {
        return;
    }
    nrc_exist_checking(root->left, nrc);
    int firstCount = charCounting(root->data.nrc);
    int secCount = charCounting(nrc);
    int same = 0;
    if (firstCount == secCount) {
        for (int i = 0; i < firstCount; ++i) {
            if (root->data.nrc[i] == nrc[i]) {
                same++;
            } else {
                break;
            }
        }
        if (same == firstCount) {
            nrc_Found = 1;
            isContinue = 1;
        }else{
            nrc_Found = -1;
        }
    }else{
        nrc_Found = -1;

    }

    nrc_exist_checking(root->right, nrc);


}

void compare_two_charArray(char first[50], char second[50]) {
    int firstCount = charCounting(first);
    int secCount = charCounting(second);
    int same = 0;
    if (firstCount == secCount) {
        for (int i = 0; i < firstCount; ++i) {
            if(first[i] == second[i]) {
                same++;
            } else{
                break;
            }
        }
        if(same == firstCount) {
            is_TwoCharArray_same=1;
        }
    }
}

void transfer_money(unsigned int transfer, unsigned int receiver, unsigned int amount) {

    struct node* transferer_info = search(root,transfer);
    struct node* receiver_info = search(root,receiver);

    if(transferer_info == NULL || receiver_info== NULL) {
        printf("error ata transfer_money :\n");
        return;
    }
    struct info transferer_data = transferer_info->data;
    struct info receiver_data = receiver_info->data;

    printf("Loading for transfer.....\n");
    current_data_to_transfer(amount);
    printf("crrent_data_to_transfer :%u\n\n",current_amount_to_transfer);
    // for transfer
    unsigned int trans_limit_for_transfer = get_limit_amount(transferer_data);
    unsigned int total_amount_of_transfer = calculate_amounts_same_days(transferer_data.id,'t');
    total_amount_of_transfer += amount;
//    printf("total amount transfer : %u\n", total_amount_of_transfer);

    //for receiver
    unsigned int trans_limit_for_receiver = get_limit_amount(receiver_data);
    unsigned int total_amount_of_receiver = calculate_amounts_same_days(receiver_data.id,'r');
    total_amount_of_receiver += amount;
//    printf("total amount receiver: %u\n", total_amount_of_receiver);


    if(total_amount_of_transfer >= trans_limit_for_transfer){
        printf("You can't transfer. Your transfer limit is full!!\n");
        userSector(transferer_data);
    }else if(total_amount_of_receiver >= trans_limit_for_receiver){
        printf("You can't transfer. Receive_limit of receiver is full!\n");
        userSector(transferer_data);
    }else{
        transferer_data.cur_amount -= amount;
        receiver_data.cur_amount += amount;

        root= Delete(root,transferer_data.id);
        root= Delete(root,receiver_data.id);
        root= insert(root,transferer_data);
        root= insert(root, receiver_data);


        transaction_record(transfer,receiver,'t',amount);
        transaction_record(transfer,receiver,'r',amount);
        printf("Transaction complete!\n");
    }

}


void current_data_to_transfer(unsigned int current_amount_to_transfer_param) {
    char current_day[2];
    get_time();
//    printf("Current info: %s : current_amount_to_trasfer : %u\n",current_time_array, current_amount_to_transfer_param);

    if(current_time_array[8] == '/'){
        current_day[0] = '0';

    }else{
        current_day[0] = current_time_array[8];
    }
    current_day[1] = current_time_array[9];
    unsigned int current_day_with_unsigned = char_to_unsigned_int(current_day);

    current_amount_to_transfer = current_amount_to_transfer_param;
    current_day_to_transfer = current_day_with_unsigned;
//    printf("current day : %u\n",current_day_to_transfer);


}

void transaction_record(unsigned int transfer,unsigned int receiver, char who,unsigned int amount) {
    struct node* transferer_info = search(root,transfer);
    struct node* receiver_info = search(root,receiver);
    if(transferer_info == NULL || receiver_info== NULL) {
        printf("Errror at transaction_Record\n");
        return;
    }
    struct info transferer_data = transferer_info->data;
    struct info receiver_data = receiver_info->data;
    int transfer_name_counter = charCounting(transferer_data.name);
    int receiver_name_counter = charCounting(receiver_data.name);
    integer_to_char(amount);
    int amount_counter = charCounting(integer_to_char_array);
// from-WinHtut-to-lonelone-100
    char from[5] = {'f','r','o','m','-'};
    char to[4] = {'-','t','o', '-'};

    get_time();

    int current_time_array_counter = charCounting(current_time_array);

    if(who == 't'){
        int counter = 0;

        for (int i = 0; i < 5; ++i) {
            transferer_data.trc[space_array[transfer-1]-12].note[counter] = from[i];
            counter++;
        }

        for (int j = 0; j < transfer_name_counter; ++j) {
            transferer_data.trc[space_array[transfer-1]-12].note[counter] = transferer_data.name[j];
            counter++;
        }

        for (int k = 0; k < 4; ++k) {
            transferer_data.trc[space_array[transfer-1]-12].note[counter] = to[k];
            counter++;
        }

        for (int a = 0; a < receiver_name_counter; ++a) {
            transferer_data.trc[space_array[transfer-1]-12].note[counter] = receiver_data.name[a];
            counter++;
        }

        transferer_data.trc[space_array[transfer-1]-12].note[counter] = '$';
        counter++;

        for (int i = 1; i < amount_counter; ++i) {
            transferer_data.trc[space_array[transfer-1]-12].note[counter] = integer_to_char_array[i];
            counter++;
        }

        transferer_data.trc[space_array[transfer-1]-12].note[counter] = '-';
        counter++;

        for (int i = 0; i < 24; ++i) {
            transferer_data.trc[space_array[transfer-1]-12].note[counter] = current_time_array[i];
            counter++;
        }
//        space_array[transfer-1] += 1;
        root= Delete(root,transfer);
        root= insert(root,transferer_data);
    }else{
        char rec[14]={'-','R','e','c','e','i','v','e','-','F','r','o','m','-'};
        int counter = 0;

        for (int i = 0; i < receiver_name_counter; ++i) {
            receiver_data.trc[space_array[receiver-1]-12].note[counter] = receiver_data.name[i];
            counter++;
        }

        for (int i = 0; i < 14; ++i) {
            receiver_data.trc[space_array[receiver-1]-12].note[counter] = rec[i];
            counter++;
        }

        for (int i = 0; i < transfer_name_counter; ++i) {
            receiver_data.trc[space_array[receiver-1]-12].note[counter] = transferer_data.name[i];
            counter++;
        }

        receiver_data.trc[space_array[receiver-1]-12].note[counter] = '$';
        counter++;

        for (int i = 1; i < amount_counter; ++i) {
            receiver_data.trc[space_array[receiver-1]-12].note[counter] = integer_to_char_array[i];
            counter++;
        }

        receiver_data.trc[space_array[receiver-1]-12].note[counter] = '-';
        counter++;

        for (int i = 0; i < 24; ++i) {
            receiver_data.trc[space_array[receiver-1]-12].note[counter] = current_time_array[i];
            counter++;
        }

//        space_array[receiver-1] += 1;
        root= Delete(root, receiver);
        root= insert(root,receiver_data);
    }
}

unsigned int char_to_unsigned_int(char charArray[]) {
    unsigned int date = 0;
    FILE *fptr = fopen("char_to_unsigned.txt", "w");
    if(fptr == NULL) {
        printf("Error at opening char_to_unsigned function\n");
    }else{
        fprintf(fptr, "%s", charArray);
    }
    fclose(fptr);

    FILE *fptr2 = fopen("char_to_unsigned.txt", "r");
    fscanf(fptr2, "%u", &date);
    fclose(fptr2);

    return date;
}

unsigned int get_limit_amount(struct info user_info) {
    unsigned int trans_limit = 0;
    int acc_level = user_info.acc_level;
    char pOrb = user_info.pOrb[0];
    int p_or_b = 0;

    if(pOrb == 'p'){
        p_or_b = 1;
    }else{
        p_or_b = 2;
    }

    switch (acc_level) {
        case 1:
            if(p_or_b == 1) {
                trans_limit = 100000;
            }else{
                trans_limit = 1000000;
            }
            break;

        case 2:
            if(p_or_b == 1) {
                trans_limit = 50000;
            }else{
                trans_limit = 500000;
            }
            break;

        case 3:
            if(p_or_b == 1) {
                trans_limit = 10000;
            }else{
                trans_limit  = 100000;
            }
            break;

        default:
            break;
    }
    return trans_limit;
}

// to calculate all amount of same days
unsigned int calculate_amounts_same_days(unsigned int to_calcu_index,char who) {

    if(who=='t') {
        struct node* current_user_info = search(root,to_calcu_index);
        struct info current_user_data = current_user_info->data;

        unsigned int total_amount_for_same_day = 0;

        int record_counter = space_array[to_calcu_index-1]-11;
        int index_counter = 0;

        char amount_array[10];
        char day_char_array[3];
        for (int i = record_counter-1; i >=0 ; --i) {
            if(current_user_data.trc[i].note[0] == 'f'){
                int current_record_counter = charCounting(current_user_data.trc[i].note);
                for (int j = 0; j < current_record_counter; ++j) {
                    if(current_user_data.trc[i].note[j] == '$'){
                        break;
                    }
                    index_counter++;
                }
                int quantity_of_amount= 0;
                for (int j = index_counter; j < current_record_counter; ++j) {
                    if(current_user_data.trc[i].note[j] == '-'){
                        break;
                    }
                    quantity_of_amount++;
                }

                index_counter++;
                for (int j = 0; j < quantity_of_amount-1; ++j) {
                    amount_array[j] = current_user_data.trc[i].note[index_counter];
                    index_counter++;
                }

                unsigned int current_record_amount = char_to_unsigned_int(amount_array);

                //to get day of current record
                for (int j = index_counter; j < current_record_counter; ++j) {
                    if(current_user_data.trc[i].note[j] == '!'){
                        break;
                    }
                    index_counter++;
                }

                if(current_user_data.trc[i].note[index_counter+5] == '/'){
                    day_char_array[0] = '0';
                }else{
                    day_char_array[0] = current_user_data.trc[i].note[index_counter+5];

                }
                day_char_array[1] = current_user_data.trc[i].note[index_counter+6];

                unsigned int current_record_day = char_to_unsigned_int(day_char_array);

                if(current_record_day != current_day_to_transfer){
                    break;
                }
                total_amount_for_same_day += current_record_amount;

                index_counter = 0;
            }

        }

        return total_amount_for_same_day;
    }else{
        struct node* current_user_info = search(root,to_calcu_index);
        struct info current_user_data = current_user_info->data;

        unsigned int total_amount_for_same_day = 0;

        int record_counter = space_array[to_calcu_index-1]-11;
        int index_counter = 0;

        char amount_array[10];
        char day_char_array[3];
        for (int i = record_counter-1; i >=0 ; --i) {
            if(current_user_data.trc[i].note[0] != 'f' ) {
                int current_record_counter = charCounting(current_user_data.trc[i].note);
                for (int j = 0; j < current_record_counter; ++j) {
                    if(current_user_data.trc[i].note[j] == '$'){
                        break;
                    }
                    index_counter++;
                }
                int quantity_of_amount= 0;
                for (int j = index_counter; j < current_record_counter; ++j) {
                    if(current_user_data.trc[i].note[j] == '-'){
                        break;
                    }
                    quantity_of_amount++;
                }

                index_counter++;
                for (int j = 0; j < quantity_of_amount-1; ++j) {
                    amount_array[j] = current_user_data.trc[i].note[index_counter];
                    index_counter++;
                }

                unsigned int current_record_amount = char_to_unsigned_int(amount_array);

                //to get day of current record
                for (int j = index_counter; j < current_record_counter; ++j) {
                    if(current_user_data.trc[i].note[j] == '!'){
                        break;
                    }
                    index_counter++;
                }

                if(current_user_data.trc[i].note[index_counter+5] == '/'){
                    day_char_array[0] = '0';
                }else{
                    day_char_array[0] = current_user_data.trc[i].note[index_counter+5];

                }
                day_char_array[1] = current_user_data.trc[i].note[index_counter+6];

                unsigned int current_record_day = char_to_unsigned_int(day_char_array);

                if(current_record_day != current_day_to_transfer){
                    break;
                }
                total_amount_for_same_day += current_record_amount;

                index_counter = 0;
            }

        }

        return total_amount_for_same_day;
    }
}

void get_time(){
    FILE* fptr = fopen("time.txt", "w");
    if(fptr == NULL) {
        printf("Error at opening time.txt\n");
    }else{
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        fprintf(fptr,"%s", asctime(tm));
    }
    fclose(fptr);

    FILE *fptr2 = fopen("time.txt", "r");
    if(fptr2== NULL){
        printf("Error at reading time.txt");
    }else{
        char c = fgetc(fptr2);
        int index = 0;
        int time_space_counter = 0;
        while (!feof(fptr2)){
            if(c == ' '){
                time_space_counter++;
                if(time_space_counter == 1){
                    current_time_array[index] = '!';
                    c = fgetc(fptr2);
                    index++;
                }else if(time_space_counter == 4){
                    current_time_array[index] = '@';
                    c= fgetc(fptr2);
                    index++;
                }else{
                    current_time_array[index] = '/';
                    c= fgetc(fptr2);
                    index++;
                }

            } else{
                current_time_array[index] = c;
                c= fgetc(fptr2);
                index++;
            }
        }

    }
    fclose(fptr2);
}


void integer_to_char(unsigned int value) {
    FILE *fptr = fopen("int_to_char.txt", "w");
    if(fptr == NULL) {
        printf("error at integer_to_char function\n");
    }else{
        fprintf(fptr,"%c%u",'v',value);
    }
    fclose(fptr);
    FILE *fptr2 = fopen("int_to_char.txt", "r");
    if(fptr2 == NULL) {
        printf("Error at integer_to_char function\n");
    }
    fscanf(fptr2, "%s", &integer_to_char_array[0]);
    fclose(fptr2);
}

//****************************************************************** main-end  *******************************************************************************

#define DIPLEVEL1_FINAL_PROJECT_BANK_H

#endif //DIPLEVEL1_FINAL_PROJECT_BANK_H
