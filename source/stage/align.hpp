#pragma once



            std::vector<gvec_2f> out_dots;
            float alignment_factor = 1.5;



void run(std::vector<gvec_2d> in_dots)
{
    std::cout << "shifting dots to positive coordinates..." << std::endl;

    // offset values used firstly to calculate the off-center offset of whole fed image
    // then offset.x is used to write the found maximum value of all of the coordinates
    // and offset.y is used as alignment divider (to limit maximum value of dots according to alignment factor)
    gvec_2d offset;
    offset = {in_dots[0].x, in_dots[0].y};
    // brushing all the coordinates to find the image's offset
    // ( just take the minimums of X and Y coordinates )
    for (int i = 1; i < in_dots.size(); i++)
    {
        offset.x = std::min(in_dots[i].x, offset.x);
        offset.y = std::min(in_dots[i].y, offset.y);
    }
    std::cout << "calculated offset:: for X: " << offset.x << " , for y: " << offset.y << std::endl; 
    // buffer for mid-program calculations
    std::vector<gvec_2d> preout_dots;
    // pulling all the dots from in_dots and, patching with offset's values, writing 'em to preout_dots
    for (int i = 0; i < in_dots.size(); i++)
    {
        preout_dots.push_back({  (in_dots[i].x - offset.x) , (in_dots[i].y - offset.y)  });
    }
    std::cout << "calculating the resizing factor..." << std::endl;
    // writing to offset.x the absolute maximum coordinate found across all of the preout_dots
    for (int i = 0; i < preout_dots.size(); i++)
    {
        offset.x = std::max(offset.x, preout_dots[i].x);
        offset.x = std::max(offset.x, preout_dots[i].y);
    }
    std::cout << "found maximum of coordinates: " << offset.x;
    // alignment divider is calculated pretty easily. trivia about it is in the comment at the bottom of this header 
    offset.y = offset.x / (alignment_factor * 2 );
    // just a silly check
    if(offset.y <= 0)
        return;
    std::cout << " , calculated the divider: " << offset.y << std::endl;
    std::cout << "alignment of dots - NOW;" << std::endl;
    for(int i = 0; i < preout_dots.size(); i++)
    {
        preout_dots[i].x = preout_dots[i].x / ( offset.y );
        preout_dots[i].y = preout_dots[i].y / ( offset.y );
        // out_dots.push_back({(float)preout_dots[i].x, (float)preout_dots[i].y});
    }   
    // resetting offsets for the next step
    offset = {0.f,0.f};

    // brushing all the pre-out dots to find maximum values on both axis
    for(int i = 0; i < preout_dots.size(); i++)
    {
        offset.x = std::max(offset.x, preout_dots[i].x);
        offset.y = std::max(offset.y, preout_dots[i].y);
    }
    std::cout << "calculated current offsets, for x: " << offset.x << " , y: " << offset.y << std::endl;
    std::cout << "writing aligned data to buffers..." << std::endl;
    for(int i = 0; i < preout_dots.size(); i++)
    {   // push backing the dots to a buffer 
        out_dots.push_back( { (float)(preout_dots[i].x - (offset.x / 2) ), (float)(preout_dots[i].y - (offset.y / 2) ) } );
    }

}

// trivia about alignment divider, aka re-using of offset.y
/*
    on the input we have value that is greater than alignment factor.
        it is deliberately aligned to have absolute values.
    we need to divide the input value on alignment divider, so it won't be greater than (alignment factor) * 2, aka (desired maximum value) * 2
                    (which is also multiplied by 2, as the following step is to center out the values).
    so the formula should look like this:
        in_coord / (dividr / 2) = out_coord
    we know the in_coord, we know that out_coord should not be greater than ((alignment factor) * 2), so the formula to calculate it would be:
        (dividr / 2) = in_coord / (alignment_factor * 2)
            or
            dividr = (in_coord / (alignment_factor * 2)) * 2
                or
                dividr = in_coord * 4 / alignment_factor
*/