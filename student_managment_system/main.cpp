#include <iostream>    // for input/output operation
#include <string.h>    // for string operation
#include <fstream>     // for file operation
#include <sys/stat.h>  // for creating a directory in linux [ubuntu]

#define MAXCOURSE 7

using namespace std;
short noOfCourse;

struct Student{
    string Name;
    long IDNo;
    short Year;
    string Department;
    string College;
    string Program;
    Student *next;
};

struct RegStud{
    string Name;
    long IDNo;
    short Year;
    string Department;
    string College;
    string Program;
    struct course{
        string cname;
        short  ects;
        short  crdhr;
        double final;
    }course[MAXCOURSE];
    struct grade{
        double grade;
    }grade[MAXCOURSE];
    double GPA;
    short  totalCourse;
    RegStud *next;
};

RegStud *Head = NULL;
Student *head = NULL;
Student *student_info();
Student *edit(Student *t);
RegStud *reg_info();
RegStud * editor(RegStud *t);

/*
 * Compare two string for search
 *      and check whether they are
 *          equal or not
 * */

int stringCompare(string str1, string str2){
    int i=0,flag=0;

    while(str1[i]!='\0' && str2[i]!='\0'){
        if(str1[i]!=str2[i]){
            flag=1;
            break;
        }
        i++;
    }

    return flag == 0 && str1[i] == '\0' && str2[i] == '\0';

}

/* Compare two string for sorting in
 *   Name , Program  and Department
 *      in ascending order
 * */

int stringCompare2(string str1, string str2){
    int i=0,flag=0;

    while(str1[i]!='\0' && str2[i]!='\0'){
        if(str1[i] < str2[i]){
            flag=1;
            break;
        }
        i++;
    }

    return flag == 0 && str1[i] == '\0' && str2[i] == '\0';

}

// Create a working directory for storing the file from the memory
void dircreator() {
    char path[]="/home/develope/Student Managment System";
    mkdir(path,777); // create a directory in the specified path with read,write and execute mode for linux [ubuntu]
    //mkdir(path); to create a directory in windows
}

// Prototypes for saving data to file and for backup and restore data

void save_enroll_data();
void save_reg_data();
void backup_enroll_data();
void backup_reg_dat();
void restore_enroll_dat();
void restore_reg_dat();
void clear_enroll_data();
void clear_reg_data();

// Prototype for enrolling functions

void enroll_at_first();
void enroll_at_last();
void enroll_at_nth();

// Prototype for removing a Student from Enroll List

void delete_at_first();
void delete_at_last();
void delete_at_nth();
void delete_by_id();

// Prototype for editing a student

void edit_student();

// Prototype for sorting functions

void sort_by_id();
void sort_by_name();
void sort_by_year();
void sort_by_college();
void sort_by_department();

// Prototype for searching functions

void search_id();
void search_name();
void search_dep();
void search_prog();
void search_coll();

// Prototype for printing the list and printing the sorted list

void print_list();
void print_sort_id();
void print_sort_dep();
void print_sort_colle();
void print_sort_year();

// Prototype for registering a student for a course

void register_at_first();
void register_at_last();
void register_at_nth();
void register_by_gpa();

// Prototype for deleting a student from the registered list

void delete_reg_first();
void delete_reg_last();
void delete_reg_nth();

// Prototype for searching a register list by id and name only

void search_reg_id();
void search_reg_name();

// Prototype for sorting the register list

void sort_reg_by_id();
void sort_reg_by_name();

// Prototype for editing a student in the register list

void edit_reg_student();

// Prototype for printing the register list

void print_reg_list();
void print_reg_list_with_gpa();

// Prototype for grade converter

void get_GPA(RegStud *t);

// Prototypes for the menus
void MainMenu();
void BuildDatabase();
void Build_Enroll_Database();
void Build_Register();
void Build_Register_GPA();
void View_Database();
void Search_Database();
void Search_Enroll_Database();
void Search_Reg_Database();
void Edit_Database();
void edit_enroll_database();
void Edit_Reg_Database();
void delete_reg_by_id();
void Sort_Database();
void sort_enroll_database();
void sort_reg_database();
void backup_or_restore_database();

int main(){
    dircreator();
    MainMenu();
    return 0;
}

// Main menu of the program

void MainMenu(){

    short choice;
    cout << "\n\n\n\n";
    cout << "\t\t\t[!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[:::::::*****:::::  Student          ::::::::::::]\n"
            "\t\t\t[::::::*     :::::      Management   ::::::::::::]\n"
            "\t\t\t[:::::::`****,::::        System     ::::::::::::]\n"
            "\t\t\t[:::::::     *::::~~~~~~~~~~~~~~~~~~~::::::::::::]\n"
            "\t\t\t[:::::::*****:::::    Main Menu      ::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]"<< endl;
    cout << "\n\n";
    cout << "\t\t\t\t  [ 1. ] Build   Database " << endl;
    cout << "\t\t\t\t  [ 2. ] View    Database " << endl;
    cout << "\t\t\t\t  [ 3. ] Search  Database" << endl;
    cout << "\t\t\t\t  [ 4. ] Modify  Database " << endl;
    cout << "\t\t\t\t  [ 5. ] Sort    Database " << endl;
    cout << "\t\t\t\t  [ 6. ] Backup/Restore Database " << endl;
    cout << "\t\t\t\t  [ 7. ] Exit " << endl;
    cout << " \n\t\t\t\t Your Choice : ";
    cin >> choice;

    if (choice == 1)
        BuildDatabase();
    else if (choice == 2)
        View_Database();
    else if (choice == 3)
        Search_Database();
    else if (choice == 4)
        Edit_Database();
    else if (choice == 5)
        Sort_Database();
    else if (choice == 6 )
        backup_or_restore_database();
    else if (choice == 7 )
        exit(0);
    else{
        cout << "Enter a valid choice please " << endl;
        MainMenu();
    }
}

// menu for backup , restore and saving the current database from memory to the file

void backup_or_restore_database() {
    short choice;
    cout << "\n\n\n\n";
    cout << "\t\t\t[!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[:::::::*****:::::  Student          ::::::::::::]\n"
            "\t\t\t[::::::*     :::::      Management   ::::::::::::]\n"
            "\t\t\t[:::::::`****,::::        System     ::::::::::::]\n"
            "\t\t\t[:::::::     *::::~~~~~~~~~~~~~~~~~~~::::::::::::]\n"
            "\t\t\t[:::::::*****:::::   Backup/Restore  ::::::::::::]\n"
            "\t\t\t[:::::::::::::::::       Menu        ::::::::::::]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]"<< endl;
    cout << "\n\n";
    cout << "\t\t\t\t  [ 1. ] Save Current  Enroll    Database " << endl;
    cout << "\t\t\t\t  [ 2. ] Save Current  Register  Database " << endl;
    cout << "\t\t\t\t  [ 3. ] Backup  Enroll    Database " << endl;
    cout << "\t\t\t\t  [ 4. ] Backup  Register  Database " << endl;
    cout << "\t\t\t\t  [ 5. ] Restore Register  Database " << endl;
    cout << "\t\t\t\t  [ 6. ] Restore Enroll    Database " << endl;
    cout << "\t\t\t\t  [ 7. ] Clear   Enroll    Database " << endl;
    cout << "\t\t\t\t  [ 8. ] Clear   Register  Database " << endl;
    cout << "\t\t\t\t  [ 9. ] Go Back " << endl;
    cout << "\t\t\t\t  [ 10.] Exit " << endl;
    cout << " \n\t\t\t\t Your Choice : ";
    cin >> choice;
    if (choice == 1)
        save_enroll_data();
    else if(choice ==2 )
        save_reg_data();
    else if (choice == 3)
        backup_enroll_data();
    else if (choice == 4)
        backup_reg_dat();
    else if (choice == 5)
        restore_reg_dat();
    else if (choice == 6)
        restore_enroll_dat();
    else if (choice == 7)
        clear_enroll_data();
    else if (choice == 8)
        clear_reg_data();
    else if(choice == 9)
        MainMenu();
    else {
        cout << "Please enter a valid choice  "<< endl;
        backup_or_restore_database();
    }
}

// menu for sorting the database

void Sort_Database() {

    short choice;
    cout << "\n\n\n\n";
    cout << "\t\t\t[!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[:::::::*****:::::  Student          ::::::::::::]\n"
            "\t\t\t[::::::*     :::::      Management   ::::::::::::]\n"
            "\t\t\t[:::::::`****,::::        System     ::::::::::::]\n"
            "\t\t\t[:::::::     *::::~~~~~~~~~~~~~~~~~~~::::::::::::]\n"
            "\t\t\t[:::::::*****:::::    Sort Menu      ::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[~~~~~~~~~~~~~~~~~~  SORT  DATABASE  ~~~~~~~~~~~~]"<< endl;
    cout << "\n\n";
    cout << "\t\t\t\t  [ 1. ] Sort Enroll   Database          " << endl;
    cout << "\t\t\t\t  [ 2. ] Sort Register Database          " << endl;
    cout << "\t\t\t\t  [ 3. ] Go Back                         " << endl;
    cout << "\t\t\t\t  [ 4. ] Exit " << endl;
    cout << " \n\t\t\t\t Your Choice : ";
    cin >> choice;
    if(choice == 1)
        sort_enroll_database();
    else if (choice == 2)
        sort_reg_database();
    else if (choice == 3)
        MainMenu();
    else if (choice == 4)
        exit(0);
    else {
        cout << "Enter a valid choice please " << endl;
        Sort_Database();
    }
}

// menu for the register database

void sort_reg_database() {
    short choice;
    cout << "\n\n\n\n";
    cout << "\t\t\t[!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[:::::::*****:::::  Student          ::::::::::::]\n"
            "\t\t\t[::::::*     :::::      Management   ::::::::::::]\n"
            "\t\t\t[:::::::`****,::::        System     ::::::::::::]\n"
            "\t\t\t[:::::::     *::::~~~~~~~~~~~~~~~~~~~::::::::::::]\n"
            "\t\t\t[:::::::*****:::::    Sort Menu      ::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[~~~~~~~~~~~~~~~ SORT REGISTER DATABASE ~~~~~~~~~]"<< endl;
    cout << "\n\n";
    cout << "\t\t\t\t  [ 1. ] Sort Register  Database by ID     " << endl;
    cout << "\t\t\t\t  [ 2. ] Sort Register  Database by Name   " << endl;
    cout << "\t\t\t\t  [ 3. ] Go Back                            " << endl;
    cout << "\t\t\t\t  [ 4. ] Exit " << endl;
    cout << " \n\t\t\t\t Your Choice : ";
    cin >> choice;
    if (choice == 1)
        sort_reg_by_id();
    else if (choice == 2)
        sort_reg_by_name();
    else if (choice == 3)
        Sort_Database();
    else if (choice == 4)
        exit(0);
    else {
        cout << "Enter a valid choice please " << endl;
        sort_reg_database();
    }
}

// menu for sorting the current enroll databse

void sort_enroll_database() {

    short choice;
    cout << "\n\n\n\n";
    cout << "\t\t\t[!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[:::::::*****:::::  Student          ::::::::::::]\n"
            "\t\t\t[::::::*     :::::      Management   ::::::::::::]\n"
            "\t\t\t[:::::::`****,::::        System     ::::::::::::]\n"
            "\t\t\t[:::::::     *::::~~~~~~~~~~~~~~~~~~~::::::::::::]\n"
            "\t\t\t[:::::::*****:::::    Sort Menu      ::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[~~~~~~~~~~~~~~  SORT ENROLL DATABASE  ~~~~~~~~~~]"<< endl;
    cout << "\n\n";
    cout << "\t\t\t\t  [ 1. ] Sort Enroll   Database by ID         " << endl;
    cout << "\t\t\t\t  [ 2. ] Sort Register Database by Name       " << endl;
    cout << "\t\t\t\t  [ 3. ] Sort Register Database by Year       " << endl;
    cout << "\t\t\t\t  [ 4. ] Sort Register Database by Department " << endl;
    cout << "\t\t\t\t  [ 5. ] Sort Register Database by College    " << endl;
    cout << "\t\t\t\t  [ 6. ] Go Back                         " << endl;
    cout << "\t\t\t\t  [ 7. ] Exit " << endl;
    cout << " \n\t\t\t\t Your Choice : ";
    cin >> choice;
    if (choice == 1){
        sort_by_id();
        print_sort_id();
    }else if (choice == 2){
        sort_by_name();
        print_list();
    }else if (choice == 3){
        sort_by_year();
        print_sort_year();
    }else if (choice == 4){
        sort_by_department();
        print_sort_dep();
    }else if (choice == 5){
        sort_by_college();
        print_sort_colle();
    }else if (choice == 6){
        Sort_Database();
    }else if (choice == 7){
        exit(0);

    }
    else {
        cout << "Enter a valid choice please " << endl;
        Sort_Database();
    }

}

// menu for editing the current database

void Edit_Database() {

    short choice;
    cout << "\n\n\n\n";
    cout << "\t\t\t[!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[:::::::*****:::::  Student          ::::::::::::]\n"
            "\t\t\t[::::::*     :::::      Management   ::::::::::::]\n"
            "\t\t\t[:::::::`****,::::        System     ::::::::::::]\n"
            "\t\t\t[:::::::     *::::~~~~~~~~~~~~~~~~~~~::::::::::::]\n"
            "\t\t\t[:::::::*****:::::    Edit Menu      ::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[~~~~~~~~~~~~~~~~~   EDIT DATABASE   ~~~~~~~~~~~~]"<< endl;
    cout << "\n\n";
    cout << "\t\t\t\t  [ 1. ] Edit  Enroll   Database          " << endl;
    cout << "\t\t\t\t  [ 2. ] Edit  Register Database          " << endl;
    cout << "\t\t\t\t  [ 3. ] Go Back                         " << endl;
    cout << "\t\t\t\t  [ 4. ] Exit " << endl;
    cout << " \n\t\t\t\t Your Choice : ";
    cin >> choice;
    if (choice == 1)
        edit_enroll_database();
    else if (choice == 2)
        Edit_Reg_Database();
    else if (choice == 3)
        MainMenu();
    else if (choice == 4)
        exit(0);
    else {
        cout << "Enter a valid choice please " << endl;
        Edit_Database();
    }
}

// menu for editing the current register database

void Edit_Reg_Database() {

    short choice;
    cout << "\n\n\n\n";
    cout << "\t\t\t[!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[:::::::*****:::::  Student          ::::::::::::]\n"
            "\t\t\t[::::::*     :::::      Management   ::::::::::::]\n"
            "\t\t\t[:::::::`****,::::        System     ::::::::::::]\n"
            "\t\t\t[:::::::     *::::~~~~~~~~~~~~~~~~~~~::::::::::::]\n"
            "\t\t\t[:::::::*****:::::    Edit Menu      ::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[~~~~~~~~~~~~  EDIT REGISTER DATABASE ~~~~~~~~~~~]"<< endl;
    cout << "\n\n";
    cout << "\t\t\t\t  [ 1. ] Edit   Single Student          " << endl;
    cout << "\t\t\t\t  [ 2. ] Remove First  Student           " << endl;
    cout << "\t\t\t\t  [ 3. ] Remove Last   Student           " << endl;
    cout << "\t\t\t\t  [ 4. ] Remove nth    Student           " << endl;
    cout << "\t\t\t\t  [ 5. ] Remove Student by ID            " << endl;
    cout << "\t\t\t\t  [ 6. ] Go Back                         " << endl;
    cout << "\t\t\t\t  [ 7. ] Exit " << endl;
    cout << " \n\t\t\t\t Your Choice : ";
    cin >> choice;
    if (choice == 1)
        edit_reg_student();
    else if (choice == 2)
        delete_reg_first();
    else if  (choice == 3)
        delete_reg_last();
    else if (choice == 4)
        delete_reg_nth();
    else if (choice == 5)
        delete_reg_by_id();
    else if (choice == 6)
        Edit_Database();
    else if (choice == 7)
        exit(0);
    else {
        cout << "Enter a valid choice please " << endl;
        Edit_Reg_Database();
    }
}

// delete a student of the given id

void delete_reg_by_id() {
system("clear");
    long id;
    short flag = 0;
    cout << "Enter id to delete : ";
    cin >> id;
    RegStud *current = Head;
    if ( current == NULL){
        cout << "There are no item in the list " << endl;
        return;
    }else{
        RegStud *temp = Head;
        temp = temp ->next;
        while(temp != NULL){
            if (temp ->IDNo == id){
                current->next = temp->next;
                delete temp;
                flag = 1;
            }
            temp = temp->next;
            current = current->next;
        }
        if (flag == 0){
            cout << "ID not found in the list " << endl;
            return;
        }
    }
    Edit_Reg_Database();
}

// menu for editing the enroll database

void edit_enroll_database() {

    short choice;
    cout << "\n\n\n\n";
    cout << "\t\t\t[!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[:::::::*****:::::  Student          ::::::::::::]\n"
            "\t\t\t[::::::*     :::::      Management   ::::::::::::]\n"
            "\t\t\t[:::::::`****,::::        System     ::::::::::::]\n"
            "\t\t\t[:::::::     *::::~~~~~~~~~~~~~~~~~~~::::::::::::]\n"
            "\t\t\t[:::::::*****:::::    Edit Menu      ::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[~~~~~~~~~~~~~~~ EDIT ENROLL DATABASE ~~~~~~~~~~~]"<< endl;
    cout << "\n\n";
    cout << "\t\t\t\t  [ 1. ] Edit   Single Student          " << endl;
    cout << "\t\t\t\t  [ 2. ] Remove First  Student           " << endl;
    cout << "\t\t\t\t  [ 3. ] Remove Last   Student           " << endl;
    cout << "\t\t\t\t  [ 4. ] Remove nth    Student           " << endl;
    cout << "\t\t\t\t  [ 5. ] Remove Student by ID            " << endl;
    cout << "\t\t\t\t  [ 6. ] Go Back                         " << endl;
    cout << "\t\t\t\t  [ 7. ] Exit " << endl;
    cout << " \n\t\t\t\t Your Choice : ";
    cin >> choice;
    if(choice == 1)
        edit_student();
    else if (choice == 2)
        delete_at_first();
    else if (choice == 3)
        delete_at_last();
    else if (choice == 4)
        delete_at_nth();
    else if (choice == 5)
        delete_by_id();
    else if (choice == 6)
        Edit_Database();
    else if (choice == 7)
        exit(0);
    else {
        cout << "Enter a valid choice please " << endl;
        edit_enroll_database();
    }
}

// menu for seaching the current database from the memory

void Search_Database() {
    short choice;
    cout << "\n\n\n\n";
    cout << "\t\t\t[!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[:::::::*****:::::  Student          ::::::::::::]\n"
            "\t\t\t[::::::*     :::::      Management   ::::::::::::]\n"
            "\t\t\t[:::::::`****,::::        System     ::::::::::::]\n"
            "\t\t\t[:::::::     *::::~~~~~~~~~~~~~~~~~~~::::::::::::]\n"
            "\t\t\t[:::::::*****:::::    Search Menu    ::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[~~~~~~~~~~~~~~~~~ SEARCH  DATABASE  ~~~~~~~~~~~~]"<< endl;
    cout << "\n\n";
    cout << "\t\t\t\t  [ 1. ] Search  Enroll   Database          " << endl;
    cout << "\t\t\t\t  [ 2. ] Search  Register Database          " << endl;
    cout << "\t\t\t\t  [ 3. ] Go Back                         " << endl;
    cout << "\t\t\t\t  [ 4. ] Exit " << endl;
    cout << " \n\t\t\t\t Your Choice : ";
    cin >> choice;
    if (choice == 1)
        Search_Enroll_Database();
    else if (choice == 2)
        Search_Reg_Database();
    else if (choice == 3)
        MainMenu();
    else if (choice == 4)
        exit(0);
    else {
        cout << "Enter a valid choice please " << endl;
        Search_Database();
    }
}

// menu for searching the register database

void Search_Reg_Database() {

    short choice;
    cout << "\n\n\n\n";
    cout << "\t\t\t[!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[:::::::*****:::::  Student          ::::::::::::]\n"
            "\t\t\t[::::::*     :::::      Management   ::::::::::::]\n"
            "\t\t\t[:::::::`****,::::        System     ::::::::::::]\n"
            "\t\t\t[:::::::     *::::~~~~~~~~~~~~~~~~~~~::::::::::::]\n"
            "\t\t\t[:::::::*****:::::    Search Menu    ::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[~~~~~~~~~~~~~~~ SEARCH REGISTER DATABASE ~~~~~~~]"<< endl;
    cout << "\n\n";
    cout << "\t\t\t\t  [ 1. ] Search  Register   Database by ID         " << endl;
    cout << "\t\t\t\t  [ 2. ] Search  Register   Database by Name       " << endl;
    cout << "\t\t\t\t  [ 3. ] Go Back                         " << endl;
    cout << "\t\t\t\t  [ 4. ] Exit " << endl;
    cout << " \n\t\t\t\t Your Choice : ";
    cin >> choice;
    if (choice == 1)
        search_reg_id();
    else if (choice == 2)
        search_reg_name();
    else if (choice == 3)
        Search_Database();
    else if (choice == 4)
        exit(0);
    else {
        cout << "Enter a valid choice please " << endl;
        Search_Reg_Database();
    }
}

// menu for searching the enroll database

void Search_Enroll_Database() {
system("clear");
    short choice;
    cout << "\n\n\n\n";
    cout << "\t\t\t[!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[:::::::*****:::::  Student          ::::::::::::]\n"
            "\t\t\t[::::::*     :::::      Management   ::::::::::::]\n"
            "\t\t\t[:::::::`****,::::        System     ::::::::::::]\n"
            "\t\t\t[:::::::     *::::~~~~~~~~~~~~~~~~~~~::::::::::::]\n"
            "\t\t\t[:::::::*****:::::    Search Menu    ::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[~~~~~~~~~~~~~  SEARCH ENROLL DATABASE ~~~~~~~~~~]"<< endl;
    cout << "\n\n";
    cout << "\t\t\t\t  [ 1. ] Search Enroll   Database by ID          " << endl;
    cout << "\t\t\t\t  [ 2. ] Search Enroll   Database by Name        " << endl;
    cout << "\t\t\t\t  [ 3. ] Search Enroll   Database by Department  " << endl;
    cout << "\t\t\t\t  [ 4. ] Search Enroll   Database by College     " << endl;
    cout << "\t\t\t\t  [ 5. ] Search Enroll   Database by Prpgram     " << endl;
    cout << "\t\t\t\t  [ 6. ] Go Back                         " << endl;
    cout << "\t\t\t\t  [ 5. ] Exit " << endl;
    cout << " \n\t\t\t\t Your Choice : ";
    cin >> choice;
    if (choice == 1)
        search_id();
    else if (choice ==2 )
        search_name();
    else if (choice == 3)
        search_dep();
    else if (choice == 4)
        search_coll();
    else if (choice == 5)
        search_prog();
    else if (choice == 6)
        Search_Database();
    else if (choice == 7)
        exit(0);
    else {
        cout << "Enter a valid choice please " << endl;
        Search_Enroll_Database();
    }

}

// menu for viewing the current database from the memory

void View_Database() {
    short choice;
    cout << "\n\n\n\n";
    cout << "\t\t\t[!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[:::::::*****:::::  Student          ::::::::::::]\n"
            "\t\t\t[::::::*     :::::      Management   ::::::::::::]\n"
            "\t\t\t[:::::::`****,::::        System     ::::::::::::]\n"
            "\t\t\t[:::::::     *::::~~~~~~~~~~~~~~~~~~~::::::::::::]\n"
            "\t\t\t[:::::::*****:::::    View Menu      ::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[~~~~~~~~~~~~~~~~~~  VIEW  DATABASE  ~~~~~~~~~~~~]"<< endl;
    cout << "\n\n";
    cout << "\t\t\t\t  [ 1. ] View Enroll   Database          " << endl;
    cout << "\t\t\t\t  [ 2. ] View Register Database          " << endl;
    cout << "\t\t\t\t  [ 3. ] View Register Database with GPA " << endl;
    cout << "\t\t\t\t  [ 4. ] Go Back                         " << endl;
    cout << "\t\t\t\t  [ 5. ] Exit " << endl;
    cout << " \n\t\t\t\t Your Choice : ";
    cin >> choice;
    if(choice == 1)
        print_list();
    else if (choice == 2)
        print_reg_list();
    else if (choice == 3)
        print_reg_list_with_gpa();
    else if (choice == 4)
        MainMenu();
    else if (choice == 5 )
        exit(0);
    else {
        cout << "Enter a valid choice please " << endl;
        View_Database();
    }
}

// menu for build the database

void BuildDatabase() {

    short choice;
    cout << "\n\n\n\n";
    cout << "\t\t\t[!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[:::::::*****:::::  Student          ::::::::::::]\n"
            "\t\t\t[::::::*     :::::      Management   ::::::::::::]\n"
            "\t\t\t[:::::::`****,::::        System     ::::::::::::]\n"
            "\t\t\t[:::::::     *::::~~~~~~~~~~~~~~~~~~~::::::::::::]\n"
            "\t\t\t[:::::::*****:::::    Build Menu      ::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[~~~~~~~~~~~~~~~~~  BUILD DATABASE   ~~~~~~~~~~~~]"<< endl;
    cout << "\n\n";
    cout << "\t\t\t\t  [ 1. ] Build Enroll     Database " << endl;
    cout << "\t\t\t\t  [ 2. ] Build Register   Database[with out GPA ] " << endl;
    cout << "\t\t\t\t  [ 3. ] Build Register   Database[with GPA ]   " << endl;
    cout << "\t\t\t\t  [ 4. ] Go Back                                " << endl;
    cout << "\t\t\t\t  [ 5. ] Exit " << endl;
    cout << " \n\t\t\t\t Your Choice : ";
    cin >> choice;
    if (choice == 1)
        Build_Enroll_Database();
    else if (choice == 2)
        Build_Register();
    else if (choice == 3)
        Build_Register_GPA();
    else if (choice == 4)
        MainMenu();
    else if (choice == 5)
        exit(0);
    else {
        cout << "Enter a valid choice please " << endl;
        BuildDatabase();
    }
}

//  call the register info then build the register database

void Build_Register_GPA() {
    register_by_gpa();
    BuildDatabase();
}

// menu for building the register list

void Build_Register() {

    short choice;
    cout << "\n\n\n\n";
    cout << "\t\t\t[!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[:::::::*****:::::  Student          ::::::::::::]\n"
            "\t\t\t[::::::*     :::::      Management   ::::::::::::]\n"
            "\t\t\t[:::::::`****,::::        System     ::::::::::::]\n"
            "\t\t\t[:::::::     *::::~~~~~~~~~~~~~~~~~~~::::::::::::]\n"
            "\t\t\t[:::::::*****:::::  Register Menu    ::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[~~~~~~~~~~~~~ BUILD REGISTER DATABASE ~~~~~~~~~~~~]"<< endl;
    cout << "\n\n";
    cout << "\t\t\t\t  [ 1. ] Build Register   Database Forward         " << endl;
    cout << "\t\t\t\t  [ 2. ] Build Register   Database Backward        " << endl;
    cout << "\t\t\t\t  [ 3. ] Build Register   Database at nth position " << endl;
    cout << "\t\t\t\t  [ 4. ] Go Back                                " << endl;
    cout << "\t\t\t\t  [ 5. ] Exit " << endl;
    cout << " \n\t\t\t\t Your Choice : ";
    cin >> choice;
    if(choice ==1 )
        register_at_last();
    else if (choice == 2)
        register_at_first();
    else if (choice == 3)
        register_at_nth();
    else if (choice == 4)
        BuildDatabase();
    else if (choice == 5)
        exit(0);
    else {
        cout << "Enter a valid choice please " << endl;
        Build_Register();
    }
}

// menu for building the enroll database

void Build_Enroll_Database() {

    short choice;
    cout << "\n\n\n\n";
    cout << "\t\t\t[!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[:::::::*****:::::  Student          ::::::::::::]\n"
            "\t\t\t[::::::*     :::::      Management   ::::::::::::]\n"
            "\t\t\t[:::::::`****,::::        System     ::::::::::::]\n"
            "\t\t\t[:::::::     *::::~~~~~~~~~~~~~~~~~~~::::::::::::]\n"
            "\t\t\t[:::::::*****:::::    Build Menu     ::::::::::::]\n"
            "\t\t\t[:::::::::::::::::                   ::::::::::::]\n"
            "\t\t\t[::::::::::::::::::::::::::::::::::::::::::::::::]\n"
            "\t\t\t[~~~~~~~~~~~~~ BUILD ENROLL DATABASE ~~~~~~~~~~~~]"<< endl;
    cout << "\n\n";
    cout << "\t\t\t\t  [ 1. ] Build Enroll Database Forward         " << endl;
    cout << "\t\t\t\t  [ 2. ] Build Enroll Database Backward        " << endl;
    cout << "\t\t\t\t  [ 3. ] Build Enroll Database at nth position " << endl;
    cout << "\t\t\t\t  [ 4. ] Go Back                                " << endl;
    cout << "\t\t\t\t  [ 5. ] Exit " << endl;
    cout << " \n\t\t\t\t Your Choice : ";
    cin >> choice;
    if (choice == 1)
        enroll_at_last();
    else if (choice == 2)
        enroll_at_first();
    else if (choice == 3)
        enroll_at_nth();
    else if (choice == 4)
        BuildDatabase();
    else if (choice == 5)
        exit(0);
    else {
        cout << "Enter a valid choice please " << endl;
        Build_Enroll_Database();
    }

}

// get the information of the student to be enrolled

Student * student_info(){
    Student *temp = new Student();

    cout << "Student Name : ";
    cin >> temp->Name;
    cout << "Student Department : ";
    cin >> temp->Department;
    cout << "Student Program :  ";
    cin >> temp->Program;
    cout << "Student College : ";
    cin >> temp->College;
    cout << "Student ID : ";
    cin >> temp->IDNo;
    cout << "Student Year : ";
    cin >> temp->Year;

    return temp;
}

// get the information of the student to be register for a course

RegStud * reg_info(){
    RegStud *temp = new RegStud();

    cout << "Student Name : ";
    cin >> temp->Name;
    cout << "Student Department : ";
    cin >> temp->Department;
    cout << "Student Program :  ";
    cin >> temp->Program;
    cout << "Student College : ";
    cin >> temp->College;
    cout << "Student ID : ";
    cin >> temp->IDNo;
    cout << "Student Year : ";
    cin >> temp->Year;
    cout << "How many courses does this student take (must be less than 7) ";
    cin >>noOfCourse;
    temp->totalCourse = noOfCourse;
    if(noOfCourse < 7){
    for (int i = 0; i < noOfCourse ; ++i) {
        cout << "Enter the " << i+1 << "course "<<endl;
        cout << "Course Name : ";
        cin >> temp->course[i].cname;
        cout << "Course ECTS : ";
        cin >> temp->course[i].ects;
        cout << "Course Credit Hour : ";
        cin >> temp->course[i].crdhr;
        cout << "Student Registered for the course " << endl;
        cout << endl;
        }
    }
    return temp;
}

// enroll as student at the first of the list (backward building)

void enroll_at_first(){
    Student* info = student_info();
    if (head == NULL){
        head = info;
        info->next = NULL;
    }else {
        info->next = head;
        head = info;
    }
    Build_Enroll_Database();
}

// enroll a student at the last of the list (forward building)

void enroll_at_last(){
    Student *info = student_info();
    Student *temp = head;
    if ( head == NULL){
        head = info;
    }else {
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = info;
        info->next = NULL;
    }
    Build_Enroll_Database();
}

// enroll a student at the given position of the current list

void enroll_at_nth(){
    Student *info = student_info();
    Student *current = head;
    Student *temp = head;
    int pos , total = 0 ;
    Student *counter = head;
    while(counter != NULL){
        counter = counter->next;
        total++;
    }
    cout << "You currently have " << total << " number of nodes in the list " << endl;
    cout << "Enter the position you want to insert " ;
    cin >> pos ;
    if (head == NULL){
        head = info;
        info->next = NULL;
    }if (pos > total){
        cout << "Plese enter a valid number "<< endl;
        return;
    }else if ( pos < 0){
        cout << "Please enter a valid number "<< endl;
        return;
    }else if (pos == total){
        enroll_at_last();
    }else {
        for ( int i = 1 ; i <= pos ; i++){
            current = current->next;
            temp = temp->next;
        }
        current->next = info;
        info->next = temp;
    }
    Build_Enroll_Database();
}

// sort the enroll list by id

void sort_by_id(){
        Student  *r;
        Student *student = new Student();
        for (Student *i = head ; i->next != NULL ; i = i->next){
            for(Student *j = head ; j->next != NULL; j = j->next){
                r = j->next;
                if (j->IDNo > r->IDNo){
                    student->IDNo = j->IDNo;
                    student->Name = j->Name;
                    student->Department = j->Department;
                    student->College = j->College;
                    student->Program = j->Program;
                    student->Year = j->Year;
                    j->Name = r->Name;
                    j->Year = r->Year;
                    j->College = r->College;
                    j->Department = r->Department;
                    j->Program = r->Program;
                    j->IDNo = r->IDNo;
                    r->IDNo =student->IDNo;
                    r->Name = student->Name;
                    r->Department = student->Department;
                    r->College = student->College;
                    r->Program = student->Program;
                    r->Year = student->Year;
                }
            }
        }
    delete student;
}

// sort the enroll list by year

void sort_by_year(){
    Student  *r;
    Student *student = new Student();
    for (Student *i = head ; i->next != NULL ; i = i->next){
        for(Student *j = head ; j->next != NULL; j = j->next){
            r = j->next;
            if (j->Year > r->Year){
                student->IDNo = j->IDNo;
                student->Name = j->Name;
                student->Department = j->Department;
                student->College = j->College;
                student->Program = j->Program;
                student->Year = j->Year;
                j->Name = r->Name;
                j->Year = r->Year;
                j->College = r->College;
                j->Department = r->Department;
                j->Program = r->Program;
                j->IDNo = r->IDNo;
                r->IDNo =student->IDNo;
                r->Name = student->Name;
                r->Department = student->Department;
                r->College = student->College;
                r->Program = student->Program;
                r->Year = student->Year;
            }
        }
    }
    delete student;
}

// sort the enroll list by name

void sort_by_name(){
    Student  *r;
    Student *student = new Student();
    for (Student *i = head ; i->next != NULL ; i = i->next){
        for(Student *j = head ; j->next != NULL; j = j->next){
            r = j->next;
            if (stringCompare2(j->Name,r->Name) != 0){
                student->IDNo = j->IDNo;
                student->Name = j->Name;
                student->Department = j->Department;
                student->College = j->College;
                student->Program = j->Program;
                student->Year = j->Year;
                j->Name = r->Name;
                j->Year = r->Year;
                j->College = r->College;
                j->Department = r->Department;
                j->Program = r->Program;
                j->IDNo = r->IDNo;
                r->IDNo =student->IDNo;
                r->Name = student->Name;
                r->Department = student->Department;
                r->College = student->College;
                r->Program = student->Program;
                r->Year = student->Year;
            }
        }
    }
    delete student;
}

// sort the enroll list by department

void sort_by_department(){
    Student  *r;
    Student *student = new Student();
    for (Student *i = head ; i->next != NULL ; i = i->next){
        for(Student *j = head ; j->next != NULL; j = j->next){
            r = j->next;
            if (stringCompare2(j->Department,r->Department) != 0){
                student->IDNo = j->IDNo;
                student->Name = j->Name;
                student->Department = j->Department;
                student->College = j->College;
                student->Program = j->Program;
                student->Year = j->Year;
                j->Name = r->Name;
                j->Year = r->Year;
                j->College = r->College;
                j->Department = r->Department;
                j->Program = r->Program;
                j->IDNo = r->IDNo;
                r->IDNo =student->IDNo;
                r->Name = student->Name;
                r->Department = student->Department;
                r->College = student->College;
                r->Program = student->Program;
                r->Year = student->Year;
            }
        }
    }
    delete student;
}

// sort the enroll list by college

void sort_by_college(){
    Student  *r;
    Student *student = new Student();
    for (Student *i = head ; i->next != NULL ; i = i->next){
        for(Student *j = head ; j->next != NULL; j = j->next){
            r = j->next;
            if (stringCompare2(j->College,r->College) != 0){
                student->IDNo = j->IDNo;
                student->Name = j->Name;
                student->Department = j->Department;
                student->College = j->College;
                student->Program = j->Program;
                student->Year = j->Year;
                j->Name = r->Name;
                j->Year = r->Year;
                j->College = r->College;
                j->Department = r->Department;
                j->Program = r->Program;
                j->IDNo = r->IDNo;
                r->IDNo =student->IDNo;
                r->Name = student->Name;
                r->Department = student->Department;
                r->College = student->College;
                r->Program = student->Program;
                r->Year = student->Year;
            }
        }
    }
    delete student;
}

//Print list by name first

void print_list(){
    Student *temp = head;
    if (head == NULL){
        cout << "List is emtpy " << endl;
    }else {
        cout << " The current list is " << endl;
        while ( temp->next != NULL){
            cout << endl;
            cout << " Name         : " << temp->Name << endl;
            cout << " ID           : " << temp->IDNo << endl;
            cout << " Department   : " << temp->Department << endl;
            cout << " Year         : " << temp->Year << endl;
            cout << " College      : " << temp->College << endl;
            cout << " Program      : " << temp->Program << endl;
            temp = temp->next;
        }
    }
    View_Database();
}

//Print list by id first

void print_sort_id(){
    Student *temp = head;
    if (head == NULL){
        cout << "List is emtpy " << endl;
    }else {
        cout << " The current list is " << endl;
        while ( temp != NULL){
            cout << endl;
            cout << " ID           : " << temp->IDNo << endl;
            cout << " Name         : " << temp->Name << endl;
            cout << " Department   : " << temp->Department << endl;
            cout << " Year         : " << temp->Year << endl;
            cout << " College      : " << temp->College << endl;
            cout << " Program      : " << temp->Program << endl;
            temp = temp->next;
        }
    }
    sort_enroll_database();
}

//Print list by year first

void print_sort_year(){
    Student *temp = head;
    if (head == NULL){
        cout << "List is emtpy " << endl;
    }else {
        cout << " The current list is " << endl;
        while ( temp != NULL){
            cout << endl;
            cout << " Year         : " << temp->Year << endl;
            cout << " Name         : " << temp->Name << endl;
            cout << " ID           : " << temp->IDNo << endl;
            cout << " Department   : " << temp->Department << endl;
            cout << " College      : " << temp->College << endl;
            cout << " Program      : " << temp->Program << endl;
            temp = temp->next;
        }
    }
    sort_enroll_database();
}

// Print list by department first

void print_sort_dep(){
    Student *temp = head;
    if (head == NULL){
        cout << "List is emtpy " << endl;
    }else {
        cout << " The current list is " << endl;
        while ( temp != NULL){
            cout << endl;
            cout << " Department   : " << temp->Department << endl;
            cout << " Name         : " << temp->Name << endl;
            cout << " ID           : " << temp->IDNo << endl;
            cout << " Year         : " << temp->Year << endl;
            cout << " College      : " << temp->College << endl;
            cout << " Program      : " << temp->Program << endl;
            temp = temp->next;
        }
    }
    sort_enroll_database();
}

// Print list by college first

void print_sort_colle(){
    Student *temp = head;
    if (head == NULL){
        cout << "List is emtpy " << endl;
    }else {
        cout << " The current list is " << endl;
        while ( temp != NULL){
            cout << endl;
            cout << " College      : " << temp->College << endl;
            cout << " Name         : " << temp->Name << endl;
            cout << " ID           : " << temp->IDNo << endl;
            cout << " Year         : " << temp->Year << endl;
            cout << " Department   : " << temp->Department << endl;
            cout << " Program      : " << temp->Program << endl;
            temp = temp->next;
        }
    }
    sort_enroll_database();
}

// delete the first node form the list

void delete_at_first(){
    Student *temp = head;
    if ( temp == NULL){
        cout << "Nothing to delete lis is already emtp! "<< endl;
    }
    else {
        Student *old = temp;
        head = old->next;
        delete old;
    }
    edit_enroll_database();
}

// delete the last node from the list

void delete_at_last(){
    Student *temp = head;
    if(temp == NULL){
        cout << "List is empty! " << endl;
        return;
    }
    else {
        Student *old = temp;
        old = old->next;
        while ( old-> next != NULL){
            old = old ->next;
            temp = temp->next;
        }
        delete old;
        temp->next = NULL;
    }
    edit_enroll_database();
}

// delete the nth node form the list

void delete_at_nth(){

    Student *current = head;
    Student *temp = head;
    temp = temp->next;
    int pos , total = 0 ;
    Student *counter = head;
    while(counter != NULL){
        counter = counter->next;
        total++;
    }
    delete counter;// Temporary pointer just to count the number of nodes in the list
    cout << "You currently have " << total << " number of nodes in the list " << endl;
    cout << "Enter the position you want to insert " ;
    cin >> pos ;
    if (head == NULL){
       cout << "Nothing to delete. List is already empty " << endl;
    }if (pos > total){
        cout << "Plese enter a valid number "<< endl;
        return;
    }else if ( pos < 0){
        cout << "Please enter a valid number "<< endl;
        return;
    }else if (pos == total){
        enroll_at_last();
    }else {
        for ( int i = 1 ; i <= pos ; i++){
            current = current->next;
            temp = temp->next;
        }
        current->next = temp->next;
        delete temp;
    }
    edit_enroll_database();
}

// delete the node by the given id number

void delete_by_id(){
    long id;
    short flag = 0;
    cout << "Enter id to delete : ";
    cin >> id;
    Student *current = head;
    if ( current == NULL){
        cout << "There are no item in the list " << endl;
        return;
    }else{
        Student *temp = head;
        temp = temp ->next;
        while(temp != NULL){
            if (temp ->IDNo == id){
                current->next = temp->next;
                delete temp;
                flag = 1;
            }
            temp = temp->next;
            current = current->next;
        }
        if (flag == 0){
            cout << "ID not found in the list " << endl;
            return;
        }
    }
    edit_enroll_database();
}

// search the enroll list by id

void search_id(){
    long id;
    int flag = 0;
    Student *temp = head;
    cout << "Enter id ";
    cin >> id;
    if (temp == NULL){
        cout << "There are no items in the list "<< endl;
        return;
    }else {
        while (temp->next != NULL){
            if ( temp->IDNo == id){
                cout << " Name         : " << temp->Name << endl;
                cout << " ID           : " << temp->IDNo << endl;
                cout << " Department   : " << temp->Department << endl;
                cout << " Year         : " << temp->Year << endl;
                cout << " College      : " << temp->College << endl;
                cout << " Program      : " << temp->Program << endl;
                flag = 1;
            }
            temp = temp->next;
        }
        if (flag == 0 ){
            cout << "Item not found " << endl;
        }
    }
    Search_Enroll_Database();
}

// search the enroll list by id

void search_name(){
    int flag = 0;
    string name;
    Student *temp = head;
    cout << "Enter Name ";
    cin >> name;
    if (temp == NULL){
        cout << "There are no items in the list "<< endl;
        return;
    }else {
        while (temp != NULL){
            if ( stringCompare(temp->Name,name) == 0){
                cout << " Name         : " << temp->Name << endl;
                cout << " ID           : " << temp->IDNo << endl;
                cout << " Department   : " << temp->Department << endl;
                cout << " Year         : " << temp->Year << endl;
                cout << " College      : " << temp->College << endl;
                cout << " Program      : " << temp->Program << endl;
                flag = 1;
            }
            temp = temp->next;
        }
        if (flag == 0 ){
            cout << "Student is not enrolled in the list. " << endl;
        }
    }
    Search_Enroll_Database();
}

// search the enroll list by department

void search_dep(){
    int flag = 0;
    string dep;
    Student *temp = head;
    cout << "Enter Department ";
    cin >> dep;
    if (temp == NULL){
        cout << "There are no items in the list "<< endl;
    }else {
        while (temp->next != NULL){
            if ( stringCompare(temp->Department,dep) != 0){
                while ((stringCompare(temp->Department,dep) != 0) && temp->next != NULL){
                cout << endl;
                cout << " Name         : " << temp->Name << endl;
                cout << " ID           : " << temp->IDNo << endl;
                cout << " Department   : " << temp->Department << endl;
                cout << " Year         : " << temp->Year << endl;
                cout << " College      : " << temp->College << endl;
                cout << " Program      : " << temp->Program << endl;
                    temp = temp->next;
                }
                flag = 1;
            }
            temp = temp->next;
        }
        if (flag == 0 ){
            cout << "Currently there are no Student enrolled in the "<< dep << " Department."<< endl;
        }
    }
    Search_Enroll_Database();
}

// search the enroll list by program

void search_prog(){
    int flag = 0;
    string prog;
    Student *temp = head;
    cout << "Enter Department ";
    cin >> prog;
    if (temp == NULL){
        cout << "There are no items in the list "<< endl;
        return;
    }else {
        while (temp->next != NULL){
            if ( stringCompare(temp->Program,prog) != 0){
                while ((stringCompare(temp->Program,prog) == 0) && temp->next != NULL){
                    cout << " Name         : " << temp->Name << endl;
                    cout << " ID           : " << temp->IDNo << endl;
                    cout << " Department   : " << temp->Department << endl;
                    cout << " Year         : " << temp->Year << endl;
                    cout << " College      : " << temp->College << endl;
                    cout << " Program      : " << temp->Program << endl;
                    temp = temp->next;
                }
                flag = 1;
            }
            temp = temp->next;
        }
        if (flag == 0 ){
            cout << "Currently there are no Student enrolled in the "<< prog << " Program."<< endl;
            return;
        }
    }
    Search_Enroll_Database();
}

// search the enroll list by college

void search_coll(){
    int flag = 0;
    string coll;
    Student *temp = head;
    cout << "Enter Department ";
    cin >> coll;
    if (temp == NULL){
        cout << "There are no items in the list "<< endl;
        return;
    }else {
        while (temp->next != NULL){
            if (stringCompare(temp->College, coll) != 0){
                while ((stringCompare(temp->College,coll) != 0) && temp->next != NULL){
                    cout << " Name         : " << temp->Name << endl;
                    cout << " ID           : " << temp->IDNo << endl;
                    cout << " Department   : " << temp->Department << endl;
                    cout << " Year         : " << temp->Year << endl;
                    cout << " College      : " << temp->College << endl;
                    cout << " Program      : " << temp->Program << endl;
                    temp = temp->next;
                }
                flag = 1;
            }
            temp = temp->next;
        }
        if (flag == 0 ){
            cout << "Currently there are no Student enrolled in the " << coll << " college." << endl;
        }
    }
    Search_Enroll_Database();
}

// edit the info of a single student form the enroll list

void edit_student(){
    long id;
    int flag = -1;
    Student *temp = head;
    cout << "Enter ID of the student you want to edit ";
    cin >> id;
    if (temp == NULL){
        cout << "There are no items in the list "<< endl;
    }else {
        while (temp != NULL){
            if ( temp->IDNo == id){
                edit(temp);
                flag = 1;
                break;
            }
            temp = temp->next;
            flag = 0;
        }
        if (flag == 0){
             cout << " SORRY ! " << endl;
             cout << "The student is not enrolled in the list " << endl;
         }
    }
    edit_enroll_database();
}

// function to enter the new details of the student

Student * edit(Student *t){
    cout << "Enter the new details " << endl;
    Student *tempo = student_info();
    t->Name = tempo->Name;
    t->IDNo = tempo->IDNo;
    t->Department = tempo->Department;
    t->College = tempo->College;
    t->Year = tempo->Year;
    t->Program = tempo->Program;
    return tempo;
}

// function to enter the new detail of the student to the current register list

RegStud * editor(RegStud *t){
    cout << "Enter the new details " << endl;
    RegStud *tempo = reg_info();
    t->Name = tempo->Name;
    t->IDNo = tempo->IDNo;
    t->Department = tempo->Department;
    t->College = tempo->College;
    t->Year = tempo->Year;
    t->Program = tempo->Program;
    for (int i = 0; i < tempo->totalCourse; ++i) {
        t->course[i].cname = tempo->course[i].cname;
        t->course[i].ects = tempo->course[i].ects;
        t->course[i].crdhr = tempo->course[i].crdhr;
    }
    return tempo;
}

// register a student at the first of the list (backward building)

void register_at_first(){
    RegStud* info = reg_info();
    if (Head == NULL){
        Head = info;
        info->next = NULL;
    }else {
        info->next = Head;
        Head = info;
    }
    Build_Register();
}

// register a student at the last of the list (forward building)

void register_at_last(){
    RegStud *info = reg_info();
    RegStud *temp = Head;
    if ( Head == NULL){
        Head = info;
    }else {
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = info;
        info->next = NULL;
    }
    Build_Register();
}

// register a student to the list by the given position of the current list

void register_at_nth(){
    RegStud *info = reg_info();
    RegStud *current = Head;
    RegStud *temp = Head;
    int pos , total = 0;
    RegStud *counter = Head;
    while(counter != NULL){
        counter = counter->next;
        total++;
    }
    cout << "You currently have " << total << " number of nodes in the list " << endl;
    cout << "Enter the position you want to insert " ;
    cin >> pos ;
    if (Head == NULL){
        Head = info;
        info->next = NULL;
    }if (pos > total){
        cout << "Plese enter a valid number "<< endl;
        return;
    }else if ( pos < 0){
        cout << "Please enter a valid number "<< endl;
        return;
    }else if (pos == total){
        enroll_at_last();
    }else {
        for ( int i = 1 ; i <= pos ; i++){
            current = current->next;
            temp = temp->next;
        }
        current->next = info;
        info->next = temp;
    }
    Build_Register();
}

// register a student by gpa

void register_by_gpa(){
    RegStud *info = reg_info();
    RegStud *temp = Head;
    if ( Head == NULL){
        Head = info;
    }else {
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = info;
        info->next = NULL;
    }
    get_GPA(info);
}

// delete the first student from the current register list

void delete_reg_first(){
    RegStud *temp = Head;
    if ( temp == NULL){
        cout << "Nothing to delete list is already emtp! "<< endl;
    }
    else {
        RegStud *old = temp;
        Head = old->next;
        delete old;
    }
    Edit_Reg_Database();
}

// delete the last student form the register list

void delete_reg_last(){
    RegStud *temp = Head;
    if(temp == NULL){
        cout << "List is empty! " << endl;
        return;
    }
    else {
        RegStud *old = temp;
        old = old->next;
        while ( old-> next != NULL){
            old = old ->next;
            temp = temp->next;
        }
        delete old;
        temp->next = NULL;
    }
    Edit_Reg_Database();
}

// delete a student form the register list the given position of the current list(which is on memory)

void delete_reg_nth(){
    RegStud *current = Head;
    RegStud *temp = Head;
    temp = temp->next;
    int pos , total = 0 ;
    RegStud *counter = Head;
    while(counter != NULL){
        counter = counter->next;
        total++;
    }
    delete counter;// Temporary pointer just to count the number of nodes in the list
    cout << "You currently have " << total << " number of nodes in the list " << endl;
    cout << "Enter the position you want to insert " ;
    cin >> pos ;
    if (head == NULL){
        cout << "Nothing to delete. List is already empty " << endl;
    }if (pos > total){
        cout << "Plese enter a valid number "<< endl;
        return;
    }else if ( pos < 0){
        cout << "Please enter a valid number "<< endl;
        return;
    }else if (pos == total){
        enroll_at_last();
    }else {
        for ( int i = 1 ; i <= pos ; i++){
            current = current->next;
            temp = temp->next;
        }
        current->next = temp->next;
        delete temp;
    }
    Edit_Reg_Database();
}

// search the register list by id

void search_reg_id(){
    long id;
    int flag = 0;
    RegStud *temp = Head;
    cout << "Enter id ";
    cin >> id;
    if (temp == NULL){
        cout << "There are no items in the list "<< endl;
        return;
    }else {
        while (temp->next != NULL){
            if ( temp->IDNo == id){
                cout << "STUDENT FOUND " << endl << endl;
                cout << " Name         : " << temp->Name << endl;
                cout << " ID           : " << temp->IDNo << endl;
                cout << " Department   : " << temp->Department << endl;
                cout << " Year         : " << temp->Year << endl;
                cout << " College      : " << temp->College << endl;
                cout << " Program      : " << temp->Program << endl;
                cout << " List of courses that this student takes " << endl;
                for (int i = 0; i < noOfCourse; ++i) {
                    cout << "Course " << i+1 << endl;
                    cout << "Course Name : " << temp->course[i].cname << endl;
                    cout << "Course ECTS   : " << temp->course[i].ects << endl;
                    cout << "Course Creadit Hour " << temp->course[i].crdhr << endl;
                }
                flag = 1;
            }
            temp = temp->next;
        }
        if (flag == 0 ){
            cout << "Item not found " << endl;
            return;
        }
    }
    Search_Reg_Database();
}

// search the register list by name using stringCompare(string , string) function

void search_reg_name(){
    int flag = 0;
    string name;
    RegStud *temp = Head;
    cout << "Enter Name ";
    cin >> name;
    if (temp == NULL){
        cout << "There are no items in the list "<< endl;
        return;
    }else {
        while (temp->next != NULL){
            if ( stringCompare(temp->Name,name) != 0){
                cout << "STUDENT FOUND " << endl << endl;
                cout << " Name         : " << temp->Name << endl;
                cout << " ID           : " << temp->IDNo << endl;
                cout << " Department   : " << temp->Department << endl;
                cout << " Year         : " << temp->Year << endl;
                cout << " College      : " << temp->College << endl;
                cout << " Program      : " << temp->Program << endl;
            for (int i = 0; i < noOfCourse; ++i) {
                cout << "Course  " << i+1 << endl;
                cout << "Course Name   : " << temp->course[i].cname << endl;
                cout << "Course ECTS   : " << temp->course[i].ects << endl;
                cout << "Creadit Hour  : " << temp->course[i].crdhr << endl;
                }
                flag = 1;
            }
            temp = temp->next;
        }
        if (flag == 0 ){
            cout << "Student is not registered in the list. " << endl;
        }
    }
    Search_Reg_Database();
}

// sor the register data by id

void sort_reg_by_id(){
   RegStud  *r;
    RegStud *student = new RegStud();
    for (RegStud *i = Head ; i->next != NULL ; i = i->next){
        for(RegStud *j = Head ; j->next != NULL; j = j->next){
            r = j->next;
            if (j->IDNo > r->IDNo){
                student->IDNo = j->IDNo;
                student->Name = j->Name;
                student->Department = j->Department;
                student->College = j->College;
                student->Program = j->Program;
                student->Year = j->Year;
                j->Name = r->Name;
                j->Year = r->Year;
                j->College = r->College;
                j->Department = r->Department;
                j->Program = r->Program;
                j->IDNo = r->IDNo;
                r->IDNo =student->IDNo;
                r->Name = student->Name;
                r->Department = student->Department;
                r->College = student->College;
                r->Program = student->Program;
                r->Year = student->Year;
            }
        }
    }
    delete student;
    sort_reg_database();
}

// sort the register list by name base on the stringCompare2(string, string) function

void sort_reg_by_name(){
    RegStud  *r;
    RegStud *student = new RegStud();
    for (RegStud *i = Head ; i->next != NULL ; i = i->next){
        for(RegStud *j = Head ; j->next != NULL; j = j->next){
            r = j->next;
            if (stringCompare2(j->Name,r->Name) != 0){
                student->IDNo = j->IDNo;
                student->Name = j->Name;
                student->Department = j->Department;
                student->College = j->College;
                student->Program = j->Program;
                student->Year = j->Year;
                j->Name = r->Name;
                j->Year = r->Year;
                j->College = r->College;
                j->Department = r->Department;
                j->Program = r->Program;
                j->IDNo = r->IDNo;
                r->IDNo =student->IDNo;
                r->Name = student->Name;
                r->Department = student->Department;
                r->College = student->College;
                r->Program = student->Program;
                r->Year = student->Year;
            }
        }
    }
    delete student;
    sort_reg_database();
}

// edit a single student form the register database

void edit_reg_student(){
    long id;
    int flag = -1;
    RegStud *temp = Head;
    cout << "Enter ID of the student you want to edit ";
    cin >> id;
    if (temp == NULL){
        cout << "There are no items in the list "<< endl;
    }else {
        while (temp != NULL){
            if ( temp->IDNo == id){
                editor(temp);
                flag = 1;
                break;
            }
            temp = temp->next;
            flag = 0;
        }
        if (flag == 0){
            cout << " SORRY ! " << endl;
            cout << "The student is not enrolled in the list " << endl;
        }
    }
    Edit_Reg_Database();
}

// print the register dat without the gpa

void print_reg_list(){
    RegStud *temp = Head;
    if (head == NULL){
        cout << "List is emtpy " << endl;
    }else {
        cout << " The current list is " << endl;
        while ( temp != NULL){
            cout << endl;
            cout << " Name         : " << temp->Name << endl;
            cout << " ID           : " << temp->IDNo << endl;
            cout << " Department   : " << temp->Department << endl;
            cout << " Year         : " << temp->Year << endl;
            cout << " College      : " << temp->College << endl;
            cout << " Program      : " << temp->Program << endl;
        for (int i = 0; i < temp->totalCourse ; ++i) {
            cout << "Course  " << i+1 << endl;
            cout << "Course Name   : " << temp->course[i].cname << endl;
            cout << "Course ECTS   : " << temp->course[i].ects << endl;
            cout << "Creadit Hour  : " << temp->course[i].crdhr << endl;
            }
            temp = temp->next;
        }
    }
    View_Database();
}

// print the register data with the gpa of each student

void print_reg_list_with_gpa(){
    RegStud *temp = Head;
    if (head == NULL){
        cout << "List is emtpy " << endl;
    }else {
        cout << " The current list is " << endl;
        while ( temp != NULL){
            cout << endl;
            cout << " Name         : " << temp->Name << endl;
            cout << " ID           : " << temp->IDNo << endl;
            cout << " Department   : " << temp->Department << endl;
            cout << " Year         : " << temp->Year << endl;
            cout << " College      : " << temp->College << endl;
            cout << " Program      : " << temp->Program << endl;
            cout << " Student is currently taking in " << temp->totalCourse << " number of courses."<< endl;
            for (int i = 0; i < temp->totalCourse ; ++i) {
            cout << "Course  " << i+1 << endl;
            cout << "Course Name   : " << temp->course[i].cname << endl;
            cout << "Course ECTS   : " << temp->course[i].ects << endl;
            cout << "Creadit Hour  : " << temp->course[i].crdhr << endl;
            }
            cout << "Student GPA   : " << temp->GPA << endl;
            temp = temp->next;
        }
    }
    View_Database();
}

// get the gpa of the specified student(passed as a parameter )

void get_GPA(RegStud *t){
    RegStud *current = Head;
    cout << "Getting GPA for student " << t->Name << endl;
    if (t != NULL){
    for (int j = 0; j < t->totalCourse; ++j) {
        cout << "Course " << j << endl;
        cout << "Course Name : " << t->course[j].cname << endl;
        cout << "Course Final mark : " ;
        cin >> t->course[j].final ;
        }
    }
    while (t != NULL ){
        for (int i = 0; i < t->totalCourse; ++i) {
            if (t->course[i].final >=90){
                t->grade[i].grade = 4.0; // A+
            }else if (83 <= t->course[i].final <90){
                t->grade[i].grade = 4.0; // A
            }else if( 80 <= t->course[i].final < 83 ){
                t->grade[i].grade = 3.75; // A-
            }else if ( 75 <= t->course[i].final < 80){
                t->grade[i].grade = 3.5; // B+
            }else if ( 68 <= t->course[i].final < 75){
                t->grade[i].grade = 3.0; // B
            }else if ( 65 <= t->course[i].final < 68){
                t->grade[i].grade = 2.75;   // B+
            } else if ( 60 <= t->course[i].final < 68){
                t->grade[i].grade = 2.5;    // C+
            }else if ( 50 <= t->course[i].final < 60){
                t->grade[i].grade = 2.0;    // C
            } else if ( 45 <= t->course[i].final < 50){
                t->grade[i].grade = 1.75;  // C-
            } else if ( 40 <= t->course[i].final < 45 ){
                t->grade[i].grade = 1.0 ; // D
            }else if ( 30 <= t->course[i].final < 40){
                t->grade[i].grade = 0; // Fx
            }else if ( t->course[i].final < 30 ){
                t->grade[i].grade = 0;   // F
            }
        }
        t = t->next;
    }
    while (current != NULL){
        double gpa = 0;
        double sum = 0;
        short overall = 0;
        for (int i = 0; i < current->totalCourse; ++i) {
            overall = overall + current->course[i].ects;
            sum = sum + (current->course[i].ects * current->grade[i].grade);
            gpa = sum/overall;
            current->GPA = gpa;
        }
        current = current->next;
    }
}

// save the current enroll data from memory to the files

void save_enroll_data(){
    Student *temp = head;
    sort_by_name();
    ofstream writetofile("/home/develope/Student Managment System/EnrollData.txt",ios::app);
    while (temp->next != NULL){
        writetofile << endl;
        writetofile << " Name         : " << temp->Name << endl;
        writetofile << " ID           : " << temp->IDNo << endl;
        writetofile << " Department   : " << temp->Department << endl;
        writetofile << " Year         : " << temp->Year << endl;
        writetofile << " College      : " << temp->College << endl;
        writetofile << " Program      : " << temp->Program << endl;
        temp = temp->next;
    }
    backup_or_restore_database();
}

// save the current register data form memory to the file

void save_reg_data(){
    sort_reg_by_name();
    RegStud *temp = new RegStud();
    ofstream writeFile("/home/develope/Student Managment System/RegData.txt",ios::app);
    while (temp->next != NULL){
    writeFile << endl;
    writeFile << " Name         : " << temp->Name << endl;
    writeFile << " ID           : " << temp->IDNo << endl;
    writeFile << " Department   : " << temp->Department << endl;
    writeFile << " Year         : " << temp->Year << endl;
    writeFile << " College      : " << temp->College << endl;
    writeFile << " Program      : " << temp->Program << endl;
    for (int i = 0; i < temp->totalCourse ; ++i) {
        writeFile << "Course  " << i+1 << endl;
        writeFile << "Course Name   : " << temp->course[i].cname << endl;
        writeFile << "Course ECTS   : " << temp->course[i].ects << endl;
        writeFile << "Creadit Hour  : " << temp->course[i].crdhr << endl;
    }
    temp = temp->next;
    }
    backup_or_restore_database();
}

// backup the current enroll database

void backup_enroll_data(){
    char ch;
    ifstream currefile;
    ofstream backupfile;
    backupfile.open("/home/develope/Student Managment System/EnrollData[BACKUP].txt",ios::app);
    currefile.open("/home/develope/Student Managment System/EnrollData.txt");
    currefile.get(ch);
    while(!currefile.eof())
    {
        backupfile.put(ch);
        currefile.get(ch);
    }
    currefile.close();
    backupfile.close();
    cout<<"\t\tBackup Complete "<<endl;
    backup_or_restore_database();
}

// backup the current register database

void backup_reg_dat(){
    char ch;
    ifstream currefile;
    ofstream backupfile;
    backupfile.open("/home/develope/Railway Managment System/RegData[BACKUP].txt",ios::app);
    currefile.open("/home/develope/Railway Managment System/RegData.txt");
    currefile.get(ch);
    while(!currefile.eof())
    {
        backupfile.put(ch);
        currefile.get(ch);
    }
    currefile.close();
    backupfile.close();
    cout<<"\t\tBackup Complete "<<endl;
    backup_or_restore_database();
}

// restore the enroll backup files to the current database

void restore_enroll_dat(){
    char ch;
    ifstream resfile;
    ofstream rfile;
    resfile.open("/home/develope/Student Managment System/EnrollData[BACKUP]");
    rfile.open("/home/develope/Student Managment System/EnrollData.txt",ios::ate);
    resfile.get(ch);
    while(resfile)
    {
        rfile.put(ch);
        resfile.get(ch);
    }
    resfile.close();
    rfile.close();

    cout<<"\t\tRestore Complete "<<endl;
    backup_or_restore_database();
}

//restore the register backup file to the current database

void restore_reg_dat(){
    char ch;
    ifstream resfile;
    ofstream rfile;
    resfile.open("/home/develope/Student Managment System/RegData[BACKUP]");
    rfile.open("/home/develope/Student Managment System/RegData.txt",ios::ate);
    resfile.get(ch);
    while(resfile)
    {
        rfile.put(ch);
        resfile.get(ch);
    }
    resfile.close();
    rfile.close();

    cout<<"\t\tRestore Complete "<<endl;
    backup_or_restore_database();
}

// clear the enroll data that is in the working directory of the current database

void clear_enroll_data(){
    ofstream clearfile("/home/develope/Student Managment System/EnrollData.txt",ios::trunc);
    clearfile.close();
    cout<<"\t\t Enroll Database cleared " <<endl;
    backup_or_restore_database();
}

// clear the register data that in the working directory of the current database

void clear_reg_data(){
    ofstream clearfile("/home/develope/Student Managment System/RegData.txt",ios::trunc);
    clearfile.close();
    cout<<"Register Database cleared " <<endl;
    backup_or_restore_database();
}

