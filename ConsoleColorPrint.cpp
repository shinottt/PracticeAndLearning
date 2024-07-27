#include<iostream>

/*
使用ANSI转义序列设置终端输出文字的颜色
\033[显示方式;前景色;背景色m
显示方式：0（默认）、1（高亮）、3（斜体）、4（下划线）、7（反显）、8（不可见）、9（中间一条横线）
前景色：30（黑色）、31（红色）、32（绿色）、33（黄色）、34（蓝色）、35（洋红色）、36（青色）、37（白色）
背景色：40（黑色）、41（红色）、42（绿色）、43（黄色）、44（蓝色）、45（洋红色）、46（青色）、47（白色）
\033[0m 关闭颜色设置
*/

int main(){
    std::cout << "\033[31m" << "This is a red text on yellow background" << "\033[0m" << std::endl;
    std::cout << "\033[32m" << "This is a green text on blue background" << "\033[0m" << std::endl;
    std::cout << "\033[33m" << "This is a yellow text on green background" << "\033[0m" << std::endl;
    std::cout << "\033[34m" << "This is a blue text on red background" << "\033[0m" << std::endl;
    std::cout << "\033[35m" << "This is a magenta text on black background" << "\033[0m" << std::endl;
    std::cout << "\033[36m" << "This is a cyan text on red background" << "\033[0m" << std::endl;
    std::cout << "\033[37m" << "This is a white text on black background" << "\033[0m" << std::endl;
    std::cout<<std::endl;
    std::cout<<"\033[1m"<<"This is a highlighted text"<<"\033[0m"<<std::endl;
    std::cout<<"\033[3m"<<"This is a italicized text"<<"\033[0m"<<std::endl;
    std::cout<<"\033[4m"<<"This is a underlined text"<<"\033[0m"<<std::endl;
    std::cout<<"\033[8m"<<"This is a invisible text"<<"\033[0m"<<std::endl;
    std::cout<<"\033[7m"<<"This is a reverse display text"<<"\033[0m"<<std::endl;
    std::cout<<"\033[9m"<<"This is a strikethrough text"<<"\033[0m"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"\033[41m"<<"This is a red background"<<"\033[0m"<<std::endl;
    std::cout<<"\033[42m"<<"This is a green background"<<"\033[0m"<<std::endl;
    std::cout<<"\033[43m"<<"This is a yellow background"<<"\033[0m"<<std::endl;
    std::cout<<"\033[44m"<<"This is a blue background"<<"\033[0m"<<std::endl;
    std::cout<<"\033[45m"<<"This is a magenta background"<<"\033[0m"<<std::endl;
    std::cout<<"\033[46m"<<"This is a cyan background"<<"\033[0m"<<std::endl;
    std::cout<<"\033[47m"<<"This is a white background"<<"\033[0m"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"\033[1;3;4;9;31;47m"<<"This is a red text on white background with highlight, italic, underline and strikethrough style"<<"\033[0m"<<std::endl;

    return 0;
}