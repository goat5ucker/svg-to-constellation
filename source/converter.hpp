#pragma once
#include "utils.hpp"


namespace converter
{
    namespace stage
    {

        namespace svg
        {
            // std::vector<gvec_2d> out_dots;
            // std::vector<gvec_u2i> out_indx;
            #include "stage/svg.hpp"
        }
        namespace align
        {
            // std::vector<gvec_2f> out_dots;
            #include "stage/align.hpp"
        }
        namespace write
        {
            #include "stage/write.hpp"
        }

        void flush_ ()
        {
            svg::out_dots.clear();
            svg::out_indx.clear();
            align::out_dots.clear();
        }
    }
    
    int main(std::string filepath_in)
    {
        stage::svg::run(filepath_in);
        std::cout << "\n----------\n" << std::endl;

        std::cout << "dots and indexes were read successfully;" << std::endl;
        // std::cout <<  "here's the coordinates of dots:\n";
        // for(int i = 0; i < stage::svg::out_dots.size(); i++)
        // {
        //     std::cout << i << ":  x: '" << stage::svg::out_dots[i].x << "' y: '" << stage::svg::out_dots[i].y << "'" << std::endl;
        // }
        // std::cout << "\nhere's the indexes:\n";
        // for(int i = 0; i < stage::svg::out_indx.size(); i++)
        // {
        //     std::cout << i << ":  a: '" << stage::svg::out_indx[i].a << "' b: '" << stage::svg::out_indx[i].b << "'" << std::endl;
        // }
        std::cout << "\n----------\n" << std::endl;

        stage::align::run(stage::svg::out_dots);

        std::cout << "\n----------\n" << std::endl;

        stage::write::run(utils::filename_extractor(filepath_in), stage::align::out_dots, stage::svg::out_indx);

        stage::flush_();
        std::cout << "\nconverter finished working with '" << utils::filename_extractor(filepath_in) << "';\n";
        std::cout << "\n---------------------------------------------------------------------------\n" << std::endl;
        return 1;
    }
}