#pragma once



            std::vector<gvec_2f> out_dots;
            float alignment_factor = 1.5;



void run(std::vector<gvec_2d> in_dots)
{

    std::cout << "shifting dots to positive coordinates..." << std::endl;

    gvec_2d offset;
    offset = {in_dots[0].x, in_dots[0].y};
    for (int i = 1; i < in_dots.size(); i++)
    {
        offset.x = std::min(in_dots[i].x, offset.x);
        offset.y = std::min(in_dots[i].y, offset.y);
    }
    std::cout << "calculated offset:: for X: " << offset.x << " , for y: " << offset.y << std::endl; 
    std::vector<gvec_2d> preout_dots;
    for (int i = 0; i < in_dots.size(); i++)
    {
        preout_dots.push_back({  (in_dots[i].x - offset.x) , (in_dots[i].y - offset.y)  });
    }
    std::cout << "calculating the resizing factor..." << std::endl;
    for (int i = 0; i < preout_dots.size(); i++)
    {
        offset.x = std::max(offset.x, preout_dots[i].x);
        offset.x = std::max(offset.x, preout_dots[i].y);
    }
    std::cout << "found maximum of coordinates: " << offset.x;
    offset.y = offset.x / alignment_factor;
    if(offset.y <= 0)
        return;
    std::cout << " , calculated the divider: " << offset.y << std::endl;
    std::cout << "alignment of dots - NOW;" << std::endl;
    for(int i = 0; i < preout_dots.size(); i++)
    {
        preout_dots[i].x /= offset.y; ;
        preout_dots[i].y /= offset.y;;
        out_dots.push_back({ ( (float)preout_dots[i].x - (alignment_factor / 2) ), ( (float)preout_dots[i].y - (alignment_factor / 2) ) });
    }
    
}