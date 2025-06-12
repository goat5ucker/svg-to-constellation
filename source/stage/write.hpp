#pragma once


void run(std::string filename, std::vector<gvec_2f> in_dots, std::vector<gvec_u2ll> in_indxs)
{
    if(in_dots.size() < 2) return;

        // задаю путь выходного файла
    std::string filepath = dirs::out_path + "\\" + filename + ".constellation.txt";
    std::cout << "writing the converted data in " << filepath << std::endl;

    std::ofstream file_out(filepath);
    file_out << "Constellation " << filename << "(\n";
    file_out << "{ // coords \n" << "    { " << std::fixed << std::setprecision(5)
                                << in_dots[0].x << ", " << in_dots[0].y << ", 0. }";
    for(int i = 1; i < in_dots.size(); i++)
    {
        file_out << ",\n    { " << in_dots[i].x << ", " << in_dots[i].y << ", 0. }";
    }
    file_out << "\n},\n{ // indexes \n" << "    { " << std::fixed << std::setprecision(5)
                                 << in_indxs[0].a << ", " << in_indxs[0].b << " }";
    for(int i = 1; i < in_indxs.size(); i++)
    {
        file_out << ",\n    { " << in_indxs[i].a << ", " << in_indxs[i].b << " }";
    }
    file_out << "\n}\n);";
    file_out.close();
    std::cout << "finished writing.. . :D" << std::endl;
}