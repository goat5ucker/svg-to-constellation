#pragma once

/// @brief vector with two DOUBLE: x,y
struct gvec_2d
{
    double x;
    double y;

    gvec_2d operator + (gvec_2d inp)
    {
        x += inp.x;
        y += inp.y;
        return {x,y};
    }
};

/// @brief vector with two FLOAT: x,y
struct gvec_2f
{
    float x;
    float y;
};

/// @brief vector with two UNSIGNED INT: a,b
struct gvec_u2ll
{
    unsigned long long a;
    unsigned long long b;
};

namespace dirs
{
    std::string in_path = "..\\files\\input";
    std::string out_path = "..\\files";
}

namespace utils
{
        std::string filename_extractor(std::string filepath)
    {
        std::string filename;
        char scan_buf;
        int name_start = 0;
        int name_end = (int)filepath.size() - 4;
        for(int i=0; i < filepath.size(); i++ )
        {
            scan_buf = filepath[i];
            if(scan_buf == '\\') name_start = i + 1;
        }
        for(int i = name_start; i < name_end; i++)
            filename.push_back(filepath[i]);
        return filename;
    }
}