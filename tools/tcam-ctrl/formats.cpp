
#include "formats.h"

#include <iostream>
#include <iomanip>

void list_formats (const std::vector<VideoFormatDescription>& available_formats)
{
    std::cout << "Available format settings:" << std::endl;
    for (const VideoFormatDescription& f : available_formats)
    {
        auto desc = f.getStruct();

        std::cout << "Format: " << desc.description << " - Fourcc(" << desc.fourcc << ")" << std::endl;
        for (const auto& s : f.getResolutionsFramesrates())
        {
            std::cout << "\tResolution: " << s.resolution.width << "x" << s.resolution.height << std::endl;
            for (const auto& fps : s.fps)
            {
                std::cout << "\t\t" << std::setw(8) << std::fixed << std::setprecision(4)<< fps << " fps" << std::endl;
            }
        }
        std::cout << std::endl;
    }
}


void print_active_format (const VideoFormat& format)
{
    std::cout << "Active format:\n"
              << "Format: \t" << tcam_fourcc_to_description(format.getFourcc())
              << "\nResolution: \t" << format.getSize().width << "x" << format.getSize().height
              << "\nFramerate: \t" << format.getFramerate() << "\n" << std::endl;
}


bool set_active_format (CaptureDevice& g, const std::string& new_format)
{
    VideoFormat v;

    bool ret = v.fromString(new_format);

    if (ret)
    {
        return g.setVideoFormat(v);
    }
    else
    {
        std::cout << "Invalid string description!" << std::endl;
    }
    return false;
}
