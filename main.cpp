#include <windows.h>
#include <iostream>
#include <vector>
#include <array>
#include <sstream>

#include "CImg.h"

using namespace cimg_library;

CImg<double>& resizeImage(CImg<double>& image, int new_width=100)
{
    int width = image._width;
    int height = image._height;
    double ratio = (double)height / width;
    auto new_height = new_width * ratio;
    return image.resize(new_width, static_cast<int>(new_height));
}

CImg<double>& convertToGrayscale(CImg<double>& image)
{
    cimg_forXY(image, x, y)
    {
        double CLinear{ image(x, y, 0, 0)*0.2126 + image(x, y, 0, 1)*0.7152 + image(x, y, 0, 2)*0.0722 };

        image(x, y, 0, 0) = CLinear;
        image(x, y, 0, 1) = CLinear;
        image(x, y, 0, 2) = CLinear;
    }

    return image;
}

auto pixelsToASCII(CImg<double>& image, const std::vector<char>& asciiChars)
{
    std::string characters;
    cimg_forY(image, y)
    {
        cimg_forX(image, x)
        {
            auto pixel{ image(x, y, 0, 0) };

            if (pixel < 25)
                characters.push_back(asciiChars[10]);
            else
                characters.push_back(asciiChars[static_cast<std::size_t>(248/pixel)]);

            characters.push_back(' ');
        }
        characters.push_back('\n');
    }
    return characters;
}

int main(int argc, char *argv[]) {
    std::vector<char> asciiChars { '@', '#', 'S', '%', '?', '*', '+', ';', ':', ',', '.' };

    if (argc < 2)
        std::cout << "No file was entered.\n";
    else
    {
        std::string path { _getcwd(nullptr, 1000) };

        path.push_back('/');
        path.append(argv[1]);

        CImg<double> image(path.c_str());

        try
        {
            std::istringstream strm( argv[2] );
            int value;
            strm >> value;
            std::cout << pixelsToASCII(convertToGrayscale(resizeImage(image, value)), asciiChars);
        }
        catch (std::logic_error& err)
        {
            std::cout << pixelsToASCII(convertToGrayscale(resizeImage(image)), asciiChars);
        }
    }

    return 0;
}