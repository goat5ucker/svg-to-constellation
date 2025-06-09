#pragma once



            std::vector<gvec_2f> out_dots;
            float alignment_factor = 5;



void run(std::vector<gvec_2d> in_dots)
{
    std::cout << "starting to align dots with max coord value of "
                << alignment_factor << "..." << std::endl;
    
    double max_recorded_in = in_dots[0].x;

    // вычисление максимального значения на входе
    for (int i = 0; i < in_dots.size(); i++)
    {  
        max_recorded_in = std::max(max_recorded_in, std::abs(in_dots[i].x));
        max_recorded_in = std::max(max_recorded_in, std::abs(in_dots[i].y));
    }

    // вычисление подгоночного делителя
    float alignment_divider = (float)max_recorded_in / alignment_factor;
    std::cout << "alignment divider: " << alignment_divider << " , found max value in input data: " << max_recorded_in << std::endl;
    // подгонка значений
    for (int i = 0; i < in_dots.size(); i++)
    {
        out_dots.push_back({
            (float)in_dots[i].x / alignment_divider,
            (float)in_dots[i].y / alignment_divider
        });
    }

    std::cout << "the coordinates were aligned;" << std::endl;
}