/*
*   Copy single file from source to destination
*   
*   Usage: file_copy(source_file, destination_file)
*
*   # Auto create folder if it does not exist 
*   # If destination file already exists, ask user to overwrite or rename destination file
*/


#include<fstream>
#include<string>
#include<iostream>
#include<filesystem>


void check_file_exists(std::string& file_name){
    if(std::filesystem::exists(file_name)){
        std::cout << "File already exists, overwrite or rename destination file? (o/r)" << std::endl;
        std::cout << ">>";
        char c;
        std::cin >> c;
        while(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid option (o/r)." << std::endl;
            std::cin >> c;
        }
        if(c == 'o' || c == 'O'){
            std::cout << "Overwriting file " << file_name << std::endl;
        }
        if(c == 'r' || c == 'R'){
            std::cout << "Enter new name for file. Old file "<< file_name << "will be kept." << std::endl;
            std::cout << ">>";
            std::string new_name;
            std::cin >> new_name;
            file_name = new_name;
            // check if new name already exists
            check_file_exists(file_name);
        }
    }
}


int file_copy(const std::string src_file, std::string dst_file){
    std::fstream src(src_file, std::ios::in | std::ios::binary);
    if(!src.is_open()){
        std::cout << "Error: Could not open file " << src_file << std::endl;
        return 0;
    }
    // check if destination file already exists
    check_file_exists(dst_file);

    std::fstream dst(dst_file, std::ios::out | std::ios::binary);
    if(!dst.is_open()){
        // create the destination folder if it does not exist
        int pos_slash = dst_file.find_last_of('/');
        if(pos_slash == std::string::npos){
            std::cout << "Error: Could not create file " << dst_file << std::endl;
            return 0;
        }
        std::string dst_folder = dst_file.substr(0, pos_slash);
        if(!std::filesystem::exists(dst_folder)){
            std::filesystem::create_directories(dst_folder);
        }
        dst.open(dst_file, std::ios::out | std::ios::binary);
        if(!dst.is_open()){
            std::cout << "Error: Could not create file " << dst_file << std::endl;
            return 0;
        }
    }
    char buffer;
    uintmax_t size = 0;
    while(src.get(buffer)){
        dst.write(&buffer, sizeof(buffer));
        size++;
    }
    src.close();
    dst.close();
    std::cout << "File " << src_file << " has been copied to " << dst_file << " with size of " << size << " bytes." << std::endl;
    return 1;
}


int main(){

    file_copy("test.png","copy_files/test-copy.png");
    return 0;

}


