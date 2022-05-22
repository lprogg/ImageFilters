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

auto blue_filter() {
    auto temp_blue_channel = blue_channel + 50;

    temp_blue_channel > 255 ? blue_channel = 255 : blue_channel = temp_blue_channel;
}

auto sepia_filter() {
    auto temp_red_channel =
                                    0.393 * red_channel +
                                    0.769 * green_channel +
                                    0.189 * blue_channel;

    auto temp_green_channel = 
                                        0.349 * red_channel +
                                        0.686 * green_channel +
                                        0.168 * blue_channel;

    auto temp_blue_channel =
                                    0.272 * red_channel +
                                    0.534 * green_channel +
                                    0.131 * blue_channel;

    temp_red_channel > 255 ? red_channel = 255 : red_channel = temp_red_channel;
    temp_green_channel > 255 ? green_channel = 255 : green_channel = temp_green_channel;
    temp_blue_channel > 255 ? blue_channel = 255 : blue_channel = temp_blue_channel;
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

        new_image << red_channel << " " << green_channel << " " << blue_channel << std::endl;
    }

    image.close();
    new_image.close();
}
