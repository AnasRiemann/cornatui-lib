
#define CORNATUI_DISABLE_WIN32
#define CORNATUI_DISABLE_RANG_DOT_HPP

#include "cornatui.hpp"


namespace output
{
static const std::vector<std::string> list
{
    "Color",
    "Text effects test",  
    "More [ e.g : animation , Translate , RGB , etc... ]",
    "INFO"
};

void color_list();
void border_test();
void animation_test();
void font_test();
void start_screen();

void rgb_test();
void translate_test();




namespace Info
{
 void informations_about_cornatui();
 void show_license();
 void show_compatibility();
 void error_message_info();
 void info();
}


}




int main()
{
std::string option;

output::start_screen();

tui::display_cursor(true);


while(true)
{

tui::cls();
std::cout<<tui::str::fg_color(ans::get_random_number(134, 255),ans::get_random_number(100, 255),ans::get_random_number(210,255));


tui::br();



tui::Text header = {"C++ Text User Interface Library"};



std::cout<<tui::str::create_page(header.content(),output::list);


std::cin>>option;
tui::fg_color(0);
if(option=="1"){output::color_list();}
else if(option=="2"){output::font_test();}
else if(option=="3"){output::animation_test();output::rgb_test();output::translate_test();}
else if(option=="4"){output::Info::info();}
else if(tui::check_break_keywords(option)){break;}

}


    return 0;
}








namespace output 
{



void color_list()
{

 std::ostringstream os16,os256;
 tui::fg_color(0);
 tui::cls();
 
  
 tui::br();
 tui::hr(100,"=",1);

 tui::create_border("normal colors & bright colors [ 1 , 16 ]");
 tui::br();
 for(size_t i=0;i<16;i++)
 {
   os16 <<   tui::str::fg_color(i+1)<<" #"<<std::setfill('0')<<std::setw(2)<<i+1;
   if((i+1)%8==0&&(i+1)!=16){os16 <<"\n";}
 }
 std::cout<<os16.str();
 tui::br();
 tui::fg_color(0);


 tui::create_border("[ 17 , 256 ] colors");
 tui::br();
 for(size_t k=16;k<256;k++)
 {
    os256 << tui::str::fg_color(k+1) << "  #"<<std::setfill('0')<<std::setw(3)<<k+1;
    if((k+1)%16==0&&(k+1)!=256){os256 <<"\n";}
 }
 std::cout<<os256.str();
 tui::fg_color(0);
 tui::br();

 tui::hr(100,"=",2);

tui::pause();


 std::ostringstream osBg16,osBg256;
 tui::bg_color(0);
 tui::cls();
 
  
 tui::br();
 tui::hr(100,"=",1);

 tui::create_border("normal Bg colors & bright colors [ 1 , 16 ]");
 tui::br();
 for(size_t i=0;i<16;i++)
 {
   osBg16 <<   tui::str::bg_color(i+1)<<" #"<<std::setfill('0')<<std::setw(2)<<i+1;
   if((i+1)%8==0&&(i+1)!=16){osBg16 <<"\n";}
 }
 std::cout<<osBg16.str();
 tui::br();
 tui::bg_color(0);


 tui::create_border("[ 17 , 256 ] Bg colors");
 tui::br();
 for(size_t k=16;k<256;k++)
 {
    osBg256 << tui::str::bg_color(k+1) << "  #"<<std::setfill('0')<<std::setw(3)<<k+1;
    if((k+1)%16==0&&(k+1)!=256){osBg256 <<"\n";}
 }
 std::cout<<osBg256.str();
 tui::bg_color(0);
 tui::br();

 tui::hr(100,"=",2);

tui::pause();


return;
}



void border_test()
{
    tui::cls();
    tui::br();
    tui::create_border("Border Test ");

    tui::hr(80, "=" , 1);
   
    tui::create_border("single", tui::Border::single);
    tui::create_border("bold"  , tui::Border::bold);
    tui::create_border("star"  , tui::Border::star);
    tui::create_border("hash"  , tui::Border::hash);
    tui::create_border("cross" , tui::Border::cross);
    tui::create_border("wave"  , tui::Border::wave);

    tui::hr(80, "=", 2);
    tui::pause();
}


void animation_test()
{
    tui::cls();
    tui::br();
    tui::create_border("Animation Test");

    tui::hr(80, "=",2);
    std::string message = " # This is an animation test";
    tui::Text animatedText = {message};

    animatedText.write(50);
    tui::br(2);
    animatedText.write_colorful(50, 1, 255);
    tui::br();
    tui::hr(80, "=", 2);
    tui::pause();
}

void font_test()
{

tui::cls();

tui::create_border("text effects test", tui::Border::bold);

tui::hr(80, "=", 2);
tui::Text message = {"I Love Conratui Library"};



std::vector<std::string> font
{
    message.content(),
    message.color(5),
    message.lowercase(),
    message.uppercase(),
    message.bold(),
    message.dim(),
    message.italic(),
    message.underline(),
    message.blink(),
    message.reversed(),
    message.bg_colorful(),
    message.crossed(),
    message.double_underline(),
    message.curly_underline(),
    message.overline(),
    message.reverse(),
    message.colorful(50, 220)
};

std::vector<std::string> msg
{

    "always works         -> normal text       :",
    "always works         -> colored text      :",
    "always works         -> lowercase text    :",
    "always works         -> uppercase text    :",
    "widely supported     -> bold text         :",
    "widely supported     -> dim text          :",
    "most terminals       -> italic text       :",
    "widely supported     -> underline text    :",
    "widely supported     -> blink text        :",
    "widely supported     -> reversed bg text  :",
    "widely supported     -> bg_colorful text  :",
    "widely supported     -> crossed out text  :",
    "inconsistent support -> double underline  :",
    "modern terms only    -> curly underline   :",
    "limited support      -> overline text     :",
    "always works         -> reversed text     :",
    "always works         -> colorful text     :"

};

for (size_t i = 0; i < msg.size(); i++) { msg.at(i) = msg.at(i) + " " + font.at(i); }




tui::create_unordered_list(msg);

tui::hr(80, "=", 2);

tui::pause();

border_test();

}



void rgb_test()
{
    tui::cls();
    tui::br();
    tui::create_border("True RGB Test", tui::Border::bold);
    tui::hr(80, "=", 2);

    for (int i = 0; i < 256; i += 8)
    {
        std::cout << tui::str::fg_color(255 - i, i, 128)
                   << tui::str::bg_color(i, 40, 255 - i)
                   << " ## ";
        if ((i + 8) % 64 == 0&&(i + 8)!=256)tui::br();
    }

    tui::fg_color(0);
    tui::br();
    tui::hr(80, "=", 2);
    tui::pause();
}

void translate_test()
{
    tui::cls();
    tui::br();
    tui::create_border("Translate Test", tui::Border::bold);
    tui::hr(80, "=" , 2);
    std::cout<<"Normal Text";
    std::cout << tui::str::translate("Padding Method\nLine Two", 10, 2, tui::Method::padding);
    tui::br();
    std::cout << tui::str::translate("ANSI Method\nLine Two", 20, 2, tui::Method::ansi);

    tui::br();
    tui::hr(80, "=", 2);
    tui::pause();
}

void start_screen()
{

tui::display_cursor(false);



for(int i =0 ; i<50;i++)
{
tui::font_style(1);

tui::cls();
std::ostringstream os,os1;
os<<"Developed By  A n a s R i e m a n n , Loading -> [ "<<std::setfill('0')<<std::setw(3)<<2*(i+1)<<"% : 100% ]";

tui::Text var = {os.str()};   


tui::br();

os1<<tui::str::create_page(os.str(),output::list);

std::cout<<tui::Text(os1.str()).colorful();



tui::delay_ms(100-1.9*i);

}



}



namespace Info
{

constexpr const char *Name       = "cornatui";
constexpr const char *NameOrigin = "C++ ornament text user interface";
constexpr const char *Version    = "0.0.2";  
constexpr const char *Author     = "Anas Riemann";
constexpr const char *Repository = "https://github.com/AnasRiemann/cornatui-lib"; 
constexpr const char *License    = "MIT";


inline const std::string MIT_LICENSE_Content = R"LICENSE(
 MIT License

 Copyright (c) 2026 Anas Riemann

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
)LICENSE";



inline void informations_about_cornatui()
{
    tui::cls();
    tui::br();

    tui::fg_color(4);
    tui::create_border("About Cornatui", tui::Border::bold);

    tui::hr(80, "=", 2);

    tui::fg_color(13);
    std::cout << "  cornatui is a lightweight, header-only C++ library for building";
    tui::br();
    std::cout << "  retro text UIs in the terminal : colors, borders, animated text";
    tui::br();
    std::cout << "  and simple menus.";
    tui::br(2);


    tui::fg_color(13);
    std::cout << "  # Name origin : ";
    tui::fg_color(11);
    std::cout << Name << " = " << NameOrigin;

    tui::br();

    tui::fg_color(4);
    tui::hr(80, "-", 2);

    tui::fg_color(13);
    std::cout << "  # Name        : ";
    tui::fg_color(11);
    std::cout << Name;
    tui::br();
    tui::fg_color(13);
    std::cout << "  # Version     : ";
    tui::fg_color(11);
    std::cout << Version;
    tui::br();
    tui::fg_color(13);
    std::cout << "  # Author      : ";
    tui::fg_color(11);
    std::cout << Author;
    tui::br();
    tui::fg_color(13);
    std::cout << "  # Repository  : ";
    tui::fg_color(11);
    std::cout << Repository;
    tui::br();
    tui::fg_color(13);
    std::cout << "  # License     : ";
    tui::fg_color(11);
    std::cout << License;
    tui::br();
    tui::fg_color(13);
    std::cout << "  # Build date  : ";
    tui::fg_color(11);
    std::cout << __DATE__ << "  " << __TIME__;
    tui::br();
    tui::fg_color(13);
    std::cout << "  # Language    : ";
    tui::fg_color(11);
    std::cout << "C++" << " version " << __cplusplus << " .";
    tui::br();
    tui::fg_color(4);
    tui::hr(80, "-", 2);
    tui::fg_color(13);
    std::cout << "  # Dependencies : cornatui_math_ans.hpp .";
    tui::br();
    tui::fg_color(4);
    tui::hr(80, "=", 2);
    tui::fg_color(0);
    tui::pause();
}


inline void show_license()
{
    tui::cls();
    tui::fg_color(13);

    std::cout<<
    tui::str::translate
    (
    tui::Text::merge
    (
    {
    tui::str::border("MIT License Content", tui::Border::bold),
    tui::str::hr(80, "=", 1),
    MIT_LICENSE_Content,
    tui::str::hr(80, "=", 2) 
    }
    ),
    2,
    1,
    tui::Method::ansi
    );

    tui::pause();
}




















inline void show_compatibility()
{
    tui::cls();
    tui::br();
    tui::fg_color(4);
    tui::create_border("System Compatibility", tui::Border::bold);

    tui::hr(80, "=", 2);

    tui::fg_color(13);
    std::cout << "  [+] Supported Operating Systems";
    tui::br(2);
    tui::fg_color(11);
    std::cout << "  - Windows 10+  ( Best : Windows Terminal )";
    tui::br();
    std::cout << "  - Linux        ( GNOME Terminal , Konsole recommended )";
    tui::br();
    std::cout << "  - macOS 10.14+ ( iTerm2 recommended )";
    tui::br();

    tui::fg_color(4);
    tui::hr(80, "-", 2);
    tui::fg_color(13);
    std::cout << "  [+] Color Support";
    tui::br(2);
    tui::fg_color(11);
    std::cout << " - 16 named colors     : always available";
    tui::br();
    std::cout << " - 256-color palette   : most modern terminals";
    tui::br();
    std::cout << " - True RGB color      : Windows Terminal, Linux, macOS";
    tui::br();

    tui::fg_color(4);
    tui::hr(80, "-", 2);
    tui::fg_color(13);
    std::cout << "  [+] Known Limitations";
    tui::br(2);
    tui::fg_color(11);
    std::cout << " - tui::Text keeps ASCII characters only ( no UTF-8 content yet )";
    tui::br();
    std::cout << " - tui::cls() ( clears scrollback too ) doesn't work in every terminal";
    tui::br();
    std::cout << " - Blink / curly underline may be ignored on older terminals";
    tui::br();

    tui::fg_color(4);
    tui::hr(80, "-", 2);
    tui::fg_color(13);
    std::cout << "  [+] Report issues";
    tui::br(2);
    tui::fg_color(11);
    std::cout << " - issues : " << "https://github.com/AnasRiemann/cornatui-lib/issues";

    tui::br();
    tui::fg_color(4);
    tui::hr(80, "=", 2);
    tui::pause();
}

inline void error_message_info()
{
    tui::fg_color(2);
    tui::br();
    std::cout << "  [!] Invalid choice, please try again.";
    tui::br();
    tui::fg_color(0);
    tui::delay_ms(600);
}

inline void info()
{
    const std::vector<std::string> selectInfoList =
    {
        "About  cornatui",
        "About LICENSE",
        "Compatibility & Supported Terminals"
    };

    std::string select;
    while (true)
    {
        tui::cls();
        tui::fg_color(14);
        tui::create_page("INFO", selectInfoList);

        std::cin >> select;
        select = tui::Text(select).lowercase();

        if (select == "1" || select == "a" || select == "i" || select == "info")
        {
            informations_about_cornatui(); continue;
        }
        else if (select == "2" || select == "b" || select == "ii" || select == "license")
        {
            show_license(); continue;
        }
        else if (select == "3" || select == "c" || select == "iii" || select == "compatibility")
        {
            show_compatibility(); continue;
        }
        else if (tui::check_break_keywords(select)) { break; }
        else { error_message_info(); }
    }
}

} // namespace Info



}