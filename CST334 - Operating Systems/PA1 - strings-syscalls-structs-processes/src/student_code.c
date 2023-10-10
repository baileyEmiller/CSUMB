//
// Created by Sam Ogden on 8/28/23.
//

#include "student_code.h"


/***********
 * Strings *
 ***********/

/**
 * This function takes in a c-string and returns it's length.  It **does not** use the strlen(...) function in string.h
 * @param str The string that we will be finding the length of.  It will be null terminated
 * @return The lenght of the inpurt string
 */
int get_str_length(char* str) {
    // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
    int count = 0;
    while(str[count] != '\0'){
       count++;
    }
    return count;
}

/**
 * Returns a pointer to a copy of the original string.  It **does not** use strcpy or any related function (but may use strlen)
 * @param str An input string that is null terminated
 * @return a new char* that copies the input string str
 */
char* copy_str(char* str) {
    // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
    int len = get_str_length(str);
    char* newstr = (char*)malloc(len + 1);
    int count = 0;
    while(str[count] != '\0'){
	newstr[count] = str[count];
	count++;
    }
    newstr[count] = '\0';
    return newstr;
}

/**
 * Truncates a string to a the given length, not including the null terminator.  If the given length is longer than the original string the original string is returned unchanged.
 * @param str A null-terminated input string
 * @param new_length The length of the output string.
 */
void truncate_string(char* str, int new_length) {
    // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
    if(get_str_length(str) < new_length){
      return;
    }
    str[new_length] = '\0';
}

/**
 * Converts a given string, str, to all uppercase letters
 * @param str A null-terminated input string
 */
void to_uppercase(char* str) {
   int i = 0;
   while(str[i] != '\0'){
      if(str[i] >= 'a' && str[i] <= 'z'){
         str[i] -= 32;
      }
      i++;
   } 
}

/**
 * Converts a given string, str, to all lowercase letters
 * @param str A null-terminated input string
 */
void to_lowercase(char* str) {
    int i = 0;
    while(str[i] != '\0'){
       if(str[i] >= 'A' && str[i] <= 'Z'){
          str[i] += 32;
       }
       i++;
    }
}

/**
 * Finds the index of the first usage of a target character, starting from 0.  If it doesn't exist return -1
 * @param str A null-terminated input string
 * @param target A character to find in string
 * @return The index of the first usage of the target character in the string
 */
int find_first_index(char* str, char target) {
    // Note: You cannot use any functions in string.h for this function!  Doing so will result in a score of 0
    char* newstr = copy_str(str);
    if(target >= 'a' && target <= 'z'){
	to_lowercase(newstr);
    }else{
	to_uppercase(newstr);
    }
    int i = 0;
    while(newstr[i] != '\0'){
	if(newstr[i] == target){
           return i;
	}
	i++;
    }
    return -1;
}

/**
 * Finds the index of the last usage of a target character, starting from 0.  If it doesn't exist return -1
 * @param str A null-terminated input string
 * @param target A character to find in string
 * @return The index of the last usage of the target character in the string
 */
int find_last_index(char* str, char target) {
    char* newstr = copy_str(str);
    if(target >= 'a' && target <= 'z'){
       to_lowercase(newstr);
    }else{
       to_uppercase(newstr);
    }
    int i = 0;
    int last = -1;
    while(newstr[i] != '\0'){
       if(newstr[i] == target){
          last = i;
       }
       i++;
    }
    return last;
}


/**************
 * Structures *
 **************/
/**
 * Create a new person object and return the object
 * @param first_name The first name of the new person as a null-terminated string
 * @param last_name The last name of the new person as a null-terminated string
 * @param age The age of the person as an int
 * @return A Person struct containing the new person
 */;

Person person_make_new(char* first_name, char* last_name, int age) {
    struct Person new_person;

    for(int i = 0; last_name[i] != '\0'; i++){
	new_person.last_name[i] = last_name[i];
    }
    new_person.last_name[get_str_length(last_name)] = '\0';
    for(int i = 0; first_name[i] != '\0'; i++){
       new_person.first_name[i] = first_name[i];
    }
    new_person.first_name[get_str_length(first_name)] = '\0';
    new_person.age = age;
    return new_person;
}
/**
 * Return a string containing the full name and age of the person in the format "First Last (age)"
 * @param person The person to get the relevant string for
 * @return A string containing the name of the person
 */
char* person_to_string(Person person) {
    // hint: sprintf
    char* mystr = (char*)malloc(get_str_length(person.first_name)+get_str_length(person.last_name)+7);
    int i = 0;
    while(person.first_name[i] != '\0'){
       mystr[i] = person.first_name[i];
       i++;
    }
    mystr[i] = ' ';
    i++;
    int k = 0;
    while(person.last_name[k] != '\0'){
       mystr[i] = person.last_name[k];
       i++;
       k++;
    }

    mystr[i] = ' ';
    i++;
    mystr[i] = '(';
    i++;
    mystr[i] = (person.age / 10) + 48;
    i++;
    mystr[i] = (person.age % 10) + 48;
    i++;
    mystr[i] = ')';
    i++;
    mystr[i] = '\0';
    return mystr;
}

/**
 * A function to create a new empty group
 * @param group_name A null-terminuated string to name the new group
 * @return A new Group struct
 */
Group group_make_new(char* group_name) {
   struct Group new_group;
   new_group.group_name = (char*)malloc(50);
   int temp = 0;
   for(int i = 0; group_name[i] != '\0'; i++){
      new_group.group_name[i] = group_name[i];
      temp++;
   }   
   new_group.group_name[temp] = '\0';
   new_group.num_members = 0;
   return new_group;
}

/**
 * A function to find the total number of people in the group
 * @param group A Group struct that contains some number of people
 * @return The number of users in the group
 */
int num_people_in_group(Group group) {
    return group.num_members;
}
/**
 * Get the number of free spaces remaining in the group
 * @param group A Group struct that contains some number of people
 * @return The number of free spaces in the group
 */
int free_spaces_in_group(Group group) {
    return 50-group.num_members;
}

/**
 * Add a person to the group if possible and return the total number of free space in the group. Otherwise return -1.
 * @param group A group struct that contains some number of people
 * @param person_to_add The person to add to the group
 * @return The number of free spaces after add the new person, -1 if the group was already full
 */
int add_person(Group* group, Person* person_to_add) {
	//todo, this isn't passing
	if(free_spaces_in_group(*group) <= 0){
	  return -1;
	}
	int present = 0;
	for(int i = 0; i < num_people_in_group(*group); i++){
		if(person_to_add == group->group_members[i]){
			present = 1;
		}
	}
	if(present == 0){
   		 group->group_members[group->num_members] = person_to_add;
    		group->num_members++;
	}
    return free_spaces_in_group(*group);
}

/**
 * Remove a person from the group if they are in the group, otherwise return -1
 * @param group A Group struct that contains some number of people
 * @param person_to_remove A person to remove from the group
 * @return The number of people remaining in the group, -1 if the person was not in the group
 */
int remove_person(Group* group, Person* person_to_remove) {
    int found = 0;
    for(int i = 0; i < group->num_members; i++){
	if(group->group_members[i] == person_to_remove){
	  found = 1;
	  group->num_members--;
	}
	if(found > 0){
		group->group_members[i] = group->group_members[i+1];
	}
    }

    if(found > 0){
	return group->num_members;
    }
    return -1;
}

/*************
 * Processes *
 *************/
/**
 * Fork off a process and return the child's PID *from the child process*
 * @return the PID of the child process
 */
int fork_and_return_child() {
    // todo
    /*
     * Question:
     * Is this even possible?
     * If it is then make it so, if it isn't then write a quick paragraph telling me why it isn't possible using the ideas of `fork(...)` discussed in class
     * Write this up here instead of code and ignore the failing unit-test -- I'll grade based on this answer instead.
     */
    pid_t forked_pid;
    forked_pid = fork();
    if(forked_pid < 0){
       exit(EXIT_FAILURE);
    } else if(forked_pid == 0){  //return of fork is 0 if we are in child
       return getpid();
    }else{
       exit(EXIT_SUCCESS);
    }
}

/**
 * Fork off a process and return the child's PID *from the parent process*
 * @return the PID of the child process
 */
int fork_and_return_parent() {
    pid_t forked_pid;
    forked_pid = fork();
    if(forked_pid <  0){
       exit(EXIT_FAILURE);
    }else if(forked_pid == 0){
       exit(EXIT_SUCCESS);
    }else{
    return forked_pid;
    }
}

/**
 * Fork a process and then call exec to run the program
 * @param program_to_call Name of the program to call
 * @param arguments Arguments to pass to the program we're calling
 * @param errno Error code if necessary.  Set to 0 for success, 1 for failure to fork, 2 for failure to exec
 * @return Exit code of the program run via the exec call (hint: look for *status)
 */
int make_exec_call(char* program_to_call, char** arguments, int* errno) {
    pid_t forked_pid;
    forked_pid = fork();

    if(forked_pid < 0){
	*errno = 1;
	exit(EXIT_FAILURE);
    } 
    
    if(forked_pid == 0){ //in child
	int exec = execvp(program_to_call, arguments);
	if(exec < 0){
		*errno = 2;
		exit(EXIT_FAILURE);
	}

    }
    if(forked_pid > 0){
	int status;
	waitpid(forked_pid, &status, 0);
	return status;
    }
    return -1;
}

/****************
 * System Calls *
 ****************/

/**
 * Open a file to read using the `open(...)` call in C
 * @param path_to_file The null terminated path to the file to open
 * @return A FILE point object
 */
// hint: https://stackoverflow.com/a/1658517
    // Note: You cannot use `fopen()` for this assignment.  Instead you must use `open(...)` and `fdopen(...)`
FILE* open_file_to_read(char* path_to_file) {
    int file_number = open(path_to_file, O_RDONLY | O_CREAT, 555);
    if(file_number < 0){
	perror("open read");
	return NULL;
    }
    FILE* file = fdopen(file_number, "r");
    if(file == NULL){
	perror("fdopen read");
	close(file_number);
	return NULL;
    }
    return file;
}

/**
 * Open a file to write using the `open(...)` call in C
 * @param path_to_file The null terminated path to the file to open
 * @return A FILE point object
 */
FILE* open_file_to_write(char* path_to_file) {
    int file_number = open(path_to_file, O_WRONLY | O_CREAT | O_TRUNC, 333);
    if(file_number < 0){
       perror("open write");
       return NULL;
    }
    FILE* file = fdopen(file_number, "w");
    if(file == NULL){
       perror("fdopen write");
       close(file_number);
       return NULL;
    }
    return file;
}

/**
 * Open a file to read or write using the `open(...)` call in C
 * @param path_to_file The null terminated path to the file to open
 * @return A FILE point object
 */
FILE* open_file_to_readwrite(char* path_to_file) {
    int file_number = open(path_to_file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if(file_number < 0){
	perror("open readwrite");
        return NULL;
    }
    FILE* file = fdopen(file_number, "a+");
    if(file == NULL){
	perror("fdopen readwrite");
	close(file_number);
	return NULL;
    }
    return file;
}

/**
 * Given a FID, write the given string to the fid using the `write(...)` system call
 * @param str A null-terminuated string
 * @param fid A FILE file descriptor
 */
void write_str_to_fid(char* str, FILE* f) {
    int file_number = fileno(f);
    if(file_number < 0){
	perror("open write_str_to_fid");
	return;
    }
    
    write(file_number, str, get_str_length(str));
    

    // hint: https://linuxhint.com/write-system-call-c/
    // Note: You cannot use `fopen()` for this assignment.  Instead you must use `open(...)` and `fdopen(...)`
    // Failure to do so will result in a 0 for this function!
}

/**
 * Given a file descriptor, read a newline-terminated string from a file
 * @param f A FILE file descriptor
 * @param max_chars Maximum characters to read
 * @return
 */
char* read_str_from_fid(FILE* f, int max_chars) {
    int file_number = fileno(f);
    if(file_number < 0){
	perror("open read_str");
	return NULL;
    }
    char* new = (char*)malloc(max_chars+1);
    read(file_number, new, max_chars);
    return new;
}

/**
 * Given a file descriptor, close the FID
 * @param f The file descriptor to close using the `close(...)` system call
 */
void close_fid(FILE* f) {
    int file_number = fileno(f);
    close(file_number);
    free(f);
    // Note: You cannot use `fopen()` for this assignment.  Instead you must use `open(...)` and `fdopen(...)`
    // Failure to do so will result in a 0 for this function!
}
