#include <iostream>
#include <string>
#include <fstream>

#define MAX_USERS 5
#define MAX_FILES 7

using namespace std;

void print_matrix(string arr[MAX_USERS][MAX_FILES]);
bool hasChar(string s, char c);

int main(){
    string arr[MAX_USERS][MAX_FILES]; //array of array of strings represent the matrix
    for(int i = 0; i < MAX_USERS; i++){
        for(int k = 0; k < MAX_FILES; k++){
            arr[i][k] = "*"; //set equal to * for no perms
        }
    }
    fstream file;
    cout << "Enter file name (! for sample): ";
    string response;
    cin >> response;
    if(response == "!"){
        file.open("input-acm-entries.txt");
    }else{
        file.open(response);
        response.clear();
    }
    while(getline(file, response)){
        int tempUsr = response[4] - 'A'; //converting user into index of user
        int tempFile = response[10] - '1';
        if(arr[tempUsr][tempFile] == "*"){
            arr[tempUsr][tempFile] = "";
        }
        arr[tempUsr][tempFile] += response[12];
    }

    response.clear();
    file.close();

    while(response != "0"){ //exit choice
        cout << "\nWhat would you like to do?\n\t0: Exit\n\t1: Update ACM entries\n\t2: Issue requests\n\t3: Print matrix\n";
        cin >> response;
        if(response == "0"){
            break;
        }else if (response == "1"){ //update choice
            cout << "Enter file name (! for example)\n";
            response.clear();
            cin >> response;
            if(response != "!"){
                file.open(response);
            }else{
                file.open("sample-update-acm-entries.txt");
            }
            response.clear();
            while(getline(file, response)){
                cout << response << ": ";
                int tempUsr = response[8]-'A';
                int tempFile = response[14] - '1';
                if(response[0] == 'a'){
                    if(hasChar(arr[tempUsr][tempFile], response[16])){ //person already has that permission for that file
                        cout << "Invalid Update. Permission Already Exists.\n";
                        continue;
                    }
                    if(arr[tempUsr][tempFile] == "*"){
                        arr[tempUsr][tempFile] = "";
                    }
                    arr[tempUsr][tempFile] += response[16];
                }else if(response[0] == 'r'){
                    tempUsr = response[11] - 'A';
                    tempFile = response[17] - '1';
                    if(!hasChar(arr[tempUsr][tempFile], response[19])){ //no permission to remove
                        cout << "Invalid Update. Entry Not Found.\n";
                        continue;
                    }
                    for(int i = 0; i < arr[tempUsr][tempFile].length(); i++){
                        if(arr[tempUsr][tempFile][i] == response[19]){
                            if(i = arr[tempUsr][tempFile].length()-1){
                                arr[tempUsr][tempFile][i] = ' ';
                            }else{
                                arr[tempUsr][tempFile][i] = arr[tempUsr][tempFile][i+1];
                            }
                        }
                    }
                }
                cout << "Successfully Updated.\n";
            }
            file.close();
            response.clear();
        }else if(response == "2"){ //request choice
            cout << "Enter file name (! for example)\n";
            response.clear();
            cin >> response;
            if(response != "!"){
                file.open(response);
            }else{
                file.open("sample-requests.txt");
            }

            response.clear();
            while(getline(file, response)){
                int tempUsr = response[4]-'A';
                int tempFile = response[10] - '1';
                if(hasChar(arr[tempUsr][tempFile], response[12])){
                    cout << "PERMIT\n";
                }else{
                    cout << "DENY\n";
                    continue;
                }
            }

            file.close();
            response.clear();
        }else if(response == "3"){
            print_matrix(arr);
        }else{
            cout << "Invalid choice\n";
        }
    }
    return 0;
}

void print_matrix(string arr[MAX_USERS][MAX_FILES]){
    for(int i = 0; i < MAX_USERS; i++){
        char temp = i+65;
        cout << "User " << temp << ": ";
        for(int k = 0; k < MAX_FILES; k++){
            cout << arr[i][k] << "\t\t";
        }
        cout << endl;
    }
}

bool hasChar(string s, char c){
    for(int i = 0; i < s.length(); i++){
        if(s[i] == c){
            return true;
        }
    }
    return false;
}