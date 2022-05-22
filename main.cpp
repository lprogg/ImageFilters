#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

auto parameters = std::vector<std::string>(4, "");

auto &type = parameters.at(0);
auto &width = parameters.at(1);
auto &height = parameters.at(2);
auto &RGB = parameters.at(3);

std::string
            red,
            green,
            blue;

int
    red_channel,
    green_channel,
    blue_channel;

double
        temporary_red_channel,
        temporary_green_channel,
        temporary_blue_channel;

auto check_temporary_red_channel() {
    temporary_red_channel > 255 ? red_channel = 255 : red_channel = temporary_red_channel;
}

auto check_temporary_green_channel() {
    temporary_green_channel > 255 ? green_channel = 255 : green_channel = temporary_green_channel;
}

auto check_temporary_blue_channel() {
    temporary_blue_channel > 255 ? blue_channel = 255 : blue_channel = temporary_blue_channel;
}

auto check_all_temporary_channels() {
    check_temporary_red_channel();
    check_temporary_green_channel();
    check_temporary_blue_channel();
}

auto blue_filter() {
    temporary_blue_channel = blue_channel + 50;

    check_temporary_blue_channel();
}

auto sepia_filter() {
    temporary_red_channel =
                            0.393 * red_channel +
                            0.769 * green_channel +
                            0.189 * blue_channel;

    temporary_green_channel = 
                                0.349 * red_channel +
                                0.686 * green_channel +
                                0.168 * blue_channel;

    temporary_blue_channel =
                            0.272 * red_channel +
                            0.534 * green_channel +
                            0.131 * blue_channel;

    check_all_temporary_channels();
}

auto grayscale_filter() {
    temporary_red_channel = temporary_green_channel = temporary_blue_channel =
                                                                                0.299 * red_channel +
                                                                                0.587 * green_channel +
                                                                                0.114 * blue_channel;
    
    check_all_temporary_channels();
}

int main() {
    std::ifstream image;
    std::ofstream new_image;

    image.open("");
    new_image.open("new_image.ppm");
                
    for_each_n(parameters.begin(), parameters.size(), [&](auto &item) {
        image >> item;
    });

    new_image << type << std::endl;
    new_image << width << " " << height<< std::endl;
    new_image << RGB << std::endl;

    while (!image.eof()) {
        image >> red;
        image >> green;
        image >> blue;

        std::stringstream red_stream(red);
        std::stringstream green_stream(green);
        std::stringstream blue_stream(blue);

        red_stream >> red_channel;
        green_stream >> green_channel;
        blue_stream >> blue_channel;

        blue_filter();

        new_image << red_channel << " " << green_channel << " " << blue_channel << std::endl;
    }

    image.close();
    new_image.close();
}
