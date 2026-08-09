
#include "cornatui.hpp"

void show_color_list();
void show_colorful_text_test();

void show_border_test()
{
    tui::cls();
    tui::br(2);
    tui::create_border("Border Test ");
    tui::br();
    tui::hr(80, "=", 2 );
   
    tui::create_border("single", tui::border::single);
    tui::create_border("bold"  , tui::border::bold);
    tui::create_border("star"  , tui::border::star);
    tui::create_border("hash"  , tui::border::hash);
    tui::create_border("cross" , tui::border::cross);
    tui::br();
    tui::hr(80, "=", 2);
    tui::pause();
};

void show_animation_test()
{
    tui::cls();
    tui::br(2);
    tui::create_border("Animation Test");
    tui::br();
    tui::hr(80, "=",2);
    std::string message = "This is an animation test\n";
    tui::Text animatedText = {message};
    animatedText.write(50);
    animatedText.write_colorful(50, 1, 255);
    tui::br();
    tui::hr(80, "=", 2);
    tui::pause();
}


int main()
{

std::string option;



for(int i =0 ; i<25;i++)
{
tui::cls();
std::ostringstream os;
os<<"Developed By  A n a s R i e m a n n , Loading -> [ "<<std::setfill('0')<<std::setw(3)<<4*(i+1)<<"% : 100% ]";

tui::Text var = {os.str()};   

tui::display_cursor(false);
tui::br(2);

std::cout<<tui::Text(tui::Text(var.border(tui::border::cross)).colorful()).bold();
os.clear();
tui::delay_ms(64);

}


while(true)
{



tui::cls();
tui::br();



tui::Text header = {"C++ Text User Interface Library"};
std::vector<std::string>list{"Colour","colorful text","border","animation","Text effects test"};
tui::create_page(header.content(),list);


std::cin>>option;

if(option=="1"){show_color_list();}
else if(option=="2"){show_colorful_text_test();}
else if(option=="3"){show_border_test();}
else if(option=="4"){show_animation_test();}
else if(option=="5")
{

tui::cls();
tui::br(2);
tui::create_border("text effects test", tui::border::bold);
tui::br();
tui::hr(80, "=", 2);
tui::Text message = {"I  love  C++  programming language"};
std::cout<<"normal text    : "<<message.content()<<"\n\n";
std::cout<<"colored text   : "<<message.color(5)<<"\n\n";
std::cout<<"lowercase text : "<<message.lowercase()<<"\n\n";
std::cout<<"uppercase text : "<<message.uppercase()<<"\n\n";
std::cout<<"bold text      : "<<message.bold()<<"\n\n";
std::cout<<"blink text     : "<<message.blink()<<"\n\n";
std::cout<<"italic text    : "<<message.italic()<<"\n\n";
std::cout<<"reversed text  : "<<message.reverse()<<"\n";
std::cout<<tui::Text("border text : I  love  C++  programming language").border()<<"\n";
std::cout<<"colorful text  : "<<message.colorful(50,220)<<"\n\n";


tui::hr(80, "=", 2);
tui::pause();
}
else if(tui::check_break_keywords(option)){break;}







}


    return 0;
}



void show_color_list()
{

 std::ostringstream os16,os256;
 tui::fg_color(0);
 tui::cls();
 
  
 tui::br();
 tui::hr(100,"=",1);

 tui::create_border("normal colours & bright colours [ 1 , 16 ]");
 tui::br();
 for(size_t i=0;i<16;i++)
 {
   os16 <<   tui::str::fg_color(i+1)<<" #"<<std::setfill('0')<<std::setw(2)<<i+1;
   if((i+1)%8==0&&(i+1)!=16){os16 <<"\n";}
 }
 std::cout<<os16.str();
 tui::br();
 tui::fg_color(0);


 tui::create_border("[ 17 , 256 ] color");
 tui::br();
 for(size_t k=16;k<256;k++)
 {
    os256 << tui::str::fg_color(k+1) << "  #"<<std::setfill('0')<<std::setw(3)<<k+1;
    if((k+1)%16==0&&(k+1)!=256){os256 <<"\n";}
 }
 std::cout<<os256.str();
 tui::fg_color(0);
 tui::br(2);

 tui::hr(100,"=",2);

tui::pause();
return;
}


inline void show_colorful_text_test()
{
    tui::cls();
    tui::br(2);
    tui::create_border("Colorful Text Test ");
    tui::br();
    tui::hr(80, "=", 2);
    std::string message = " #  This is a colorful text  # ";


    for (int i = 0; i < 16; ++i)
     {
        tui::Text colorfulText = {message};

        std::cout <<  colorfulText.colorful( 0, 255);
        if((i+1)%2==0) tui::br(2);
    }
     tui::br();
     tui::hr(80, "=", 2);
       tui::pause();
}