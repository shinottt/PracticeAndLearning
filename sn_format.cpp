/*
sn_format.cpp - A simple format function for C++
*/
#include<vector>
#include<string>
#include<string_view>
#include<sstream>
#include<iostream>

template<typename T>
void GetString(std::vector<std::string>& str_vec, T&& t){
    std::ostringstream oss;
    oss << t;
    str_vec.push_back(oss.str());
}

template<typename T, typename... Args>
void GetString(std::vector<std::string>& str_vec, T&& t, Args&&... args){
    std::ostringstream oss;
    oss << t;
    str_vec.push_back(oss.str());
    GetString(str_vec, args...);
}

//format string

std::string sn_format(std::string_view fmt){
    return fmt.data();
}

template<typename... Args>
std::string sn_format(std::string_view fmt, Args&&... args){
    size_t args_index = 0;

    std::vector<std::string> str_vec;
    GetString(str_vec, args...);

    std::ostringstream oss;
    for(auto it = fmt.begin(); it != fmt.end(); ++it){
        if(*it == '{'){
            if(*(it+1) == '}'){
                if(args_index >= str_vec.size()){
                    printf("Error: Not enough arguments for format string\n");
                    exit(1);
                }
                oss << str_vec[args_index];
                ++args_index;
                ++it;
            }
        } else{
            oss << *it;
        }
    }
    return oss.str();
} 


int main(){

    std::cout<< sn_format("Hello, {}! year: {}", "world", 2024)<<std::endl;
    std::cout<< sn_format("hello")<<std::endl;
    return 0;
}

