/*
*   Pack and unpack files in one package
*
*   Usage:  pack_file(package_name, file_name1, file_name2,..., file_nameN)
*           unpack_file(package_name)   
*
*   # Auto create folder if not exists
*   # Check if package already exists   
*   # Overwrite or skip existing file
*   
*/



#include<fstream>
#include<string>
#include<iostream>
#include<vector>
#include<cstring>
#include<filesystem>        //C++17


class file_header{
public:
    uintmax_t file_size = 0;
    char file_name[256]{'\0'};

    file_header()=default;
};


template<typename T>
void get_file_names(std::vector<std::string>& file_name_vec, T&& file_name){
    file_name_vec.emplace_back(file_name);
}

template<typename T, typename... Args>
void get_file_names(std::vector<std::string>& file_name_vec, T&& file_name, Args&&... args){
    file_name_vec.emplace_back(file_name);
    get_file_names(file_name_vec, args...);
}

template<typename T = std::string, typename... Args>
int pack_file(std::string package_name, Args&&... args){
    std::vector<std::string> file_name_vec;
    get_file_names(file_name_vec, args...);

    // check if package already exists
    if(std::filesystem::exists(package_name)){
        std::cout << "Package " << package_name << " already exists, overwrite or stop? (o/s): " << std::endl;
        std::cout<<">>";
        char c;
        std::cin >> c;
        while(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid option (o/s)." << std::endl;
            std::cout<<">>";
            std::cin >> c;
        }
        if(c == 'o' || c == 'O'){
            std::cout << "Overwriting package " << package_name << std::endl;
        }
        if(c =='s' || c == 'S'){
            std::cout << "Stopping packing process for package " << package_name << std::endl;
            return 1;
        }
    }
    std::fstream package_file(package_name.c_str(), std::ios::out | std::ios::binary);
    if(!package_file){
        std::cout << "Error: package file " << package_name << " not found." << std::endl;
        return 0;
    }

    for(int i = 0; i < file_name_vec.size(); ++i){
        std::fstream file(file_name_vec[i].c_str(), std::ios::in | std::ios::binary);
        if(!file){
            std::cout << "Error: file " << file_name_vec[i] << " not found." << std::endl;
            return 0;
        }
        file_header header;
        strcpy(header.file_name, file_name_vec[i].c_str());
        // get file size
        file.seekg(0, std::ios::end);
        header.file_size = file.tellg();
        file.seekg(0, std::ios::beg);
        package_file.write(reinterpret_cast<const char*>(&header), sizeof(header));
        char c;
        while(file.get(c)){
            package_file.write(&c, sizeof(char));
        }
        file.close();
        std::cout<< "File " << file_name_vec[i] << " packed " << "with size of " << header.file_size << " bytes." << std::endl;
    }
    package_file.close();
    std::cout << "Package " << package_name << " created successfully "<< "with size of " << std::filesystem::file_size(package_name) << " bytes." << std::endl;
    return 1;
}




int unpack_file(std::string package_name){
    std::fstream package_file(package_name.c_str(), std::ios::in | std::ios::binary);
    if(!package_file){
        std::cout << "Error: package file " << package_name << " not found." << std::endl;
        return 0;
    }

    while(package_file.peek() != EOF){
        file_header header;
        package_file.read(reinterpret_cast<char*>(&header), sizeof(header));
        std::filesystem::path file_path = header.file_name;
        // check if file already exists
        if(std::filesystem::exists(file_path)){
            std::cout<< "File " << header.file_name << " already exists, overwrite or skip? (o/s): " << std::endl;
            std::cout<<">>";
            char c;
            std::cin >> c;
            while(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a valid option (o/r)." << std::endl;
                std::cout<<">>";
                std::cin >> c;
            }
            if(c == 'o' || c == 'O'){
                std::cout << "Overwriting file " << header.file_name << std::endl;
            }
            if(c =='s' || c == 'S'){
                std::cout << "Skipping file " << header.file_name << std::endl;
                package_file.seekg(header.file_size, std::ios::cur);
                std::cout << "Skipping file " << header.file_name << " with size of " << header.file_size << " bytes." << std::endl;
                continue;
            }
        }

        std::fstream file(header.file_name, std::ios::out | std::ios::binary);
        if(!file){
            // create folder if not exists
            std::string folder(header.file_name);
            int pos_slash = folder.find_last_of('/');
            if(pos_slash == std::string::npos){
                std::cout<<"Error: Could not create the file "<<header.file_name<<std::endl;
                return 0;
            }
            std::string dst_folder = folder.substr(0, pos_slash);
            if(!std::filesystem::exists(dst_folder)){
                std::filesystem::create_directories(dst_folder);
            }
            file.open(header.file_name, std::ios::out | std::ios::binary);
            if(!file){
                std::cout<<"Error: Could not create the file "<<header.file_name<<std::endl;
                return 0;
            }
        }

        for(int i = 0; i < header.file_size; ++i){
            char c;
            package_file.read(&c, sizeof(char));
            file.write(&c, sizeof(char));
        }
        file.close();
        std::cout<< "File " << header.file_name << " unpacked " << "with size of " << header.file_size << " bytes." << std::endl;
    }
    package_file.close();
    std::cout << "Package " << package_name << " unpacked successfully " << "with size of " << std::filesystem::file_size(package_name) << " bytes." << std::endl;
    return 1;
}





int main(){
    
    if(!pack_file("package.pack", "file/file_1.png", "file/file_2.png")){
        std::cout << "Error: package creation failed." << std::endl;
    }
    
    if(!unpack_file("package.pack")){
        std::cout << "Error: package unpacking failed." << std::endl;
    }
    

    return 0;
}


