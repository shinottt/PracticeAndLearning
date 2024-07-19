/*
猜数字
*/

#include<iostream>
#include<random>

#define MIN_ 1
#define MAX_ 100

int main(){
    //获取硬件噪声产生随机数
    std::random_device rd;
    //范围内均匀分布随机数
    std::uniform_int_distribution<int> dist(MIN_, MAX_);

    for(;;){
        std::cout << "Guess the number between " << MIN_ << " and " << MAX_ << std::endl;
        int num = dist(rd);
        for(;;){
            int guess;
            std::cout << "Enter your guess: ";
            std::cin >> guess;
            if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number." << std::endl;
                continue;
            }
            if(guess == num){std::cout<<"you win"<<std::endl;break;}
            if(guess > num){std::cout<<"too high"<<std::endl;}
            if(guess < num){std::cout<<"too low"<<std::endl;}
        }

    }

    return 0;
}