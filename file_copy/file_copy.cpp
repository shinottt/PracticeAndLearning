/*
*   Copy the file from source to destination
*   Can not copy file if the destination folder does not exist
*
*/


#include<cstddef>
#include<fstream>
#include<string>
#include<iostream>


void file_copy(const std::string src_file, const std::string dst_file){
    std::fstream src(src_file, std::ios::in | std::ios::binary);
    if(!src.is_open()){
        std::cout << "Error: Could not open file " << src_file << std::endl;
        return;
    }
    std::fstream dst(dst_file, std::ios::out | std::ios::binary);
    if(!dst.is_open()){
        std::cout << "Error: Could not open file " << dst_file << std::endl;
        return;
    }
    char buffer;
    size_t size = 0;
    while(src.get(buffer)){
        dst.write(&buffer, sizeof(buffer));
        size++;
    }
    src.close();
    dst.close();
    std::cout << "File " << src_file << " has been copied to " << dst_file << " with size of " << size << " bytes." << std::endl;
}


int main(){

    file_copy("test.png","test-copy.png");
    return 0;

}


