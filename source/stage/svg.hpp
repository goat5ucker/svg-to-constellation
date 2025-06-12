#pragma once

            std::vector<gvec_2d> out_dots;
            std::vector<gvec_u2ll> out_indx;

using namespace tinyxml2;

//                                                           ,d     
//                                                           88     
//          ,adPPYba,             ,adPPYba,   88       88  MM88MMM  
//          I8[    ""  aaaaaaaa  a8"     "8a  88       88    88     
//           `"Y8ba,   """"""""  8b       d8  88       88    88     
//          aa    ]8I            "8a,   ,a8"  "8a,   ,a88    88,    
//          `"YbbdP"'             `"YbbdP"'    `"YbbdP'Y8    "Y888  
            // читай как sh!t-out (задумывалось как sub-out)
                // тут просто под-функции для out_from_path

struct d_tkn_tmplt {
    char cmd;
    std::vector<double> digts; 
};
std::vector<d_tkn_tmplt> buf_d_tokens; // НЕ ЗАБЫВАЙ ОЧИЩАТЬ БУФЕР ТОКЕНОВ

/// @brief токенизирует  d_string, в который ты передаёшь
/// @param d_strng - строка с параметрами элемента d из path
void path_d_token_extractor(std::string d_strng)
{

    size_t _counter = 0;
    size_t _d_size = d_strng.size();
    bool second_dot = false;

    while (_counter < _d_size)
    {
            // пропуск пробелов
        while (_counter < _d_size
            && std::isspace(static_cast<unsigned char>(d_strng[_counter])))
                { _counter++; }
            // если дошли до конца данных - прервать чтение
        if (_counter >= _d_size) break;

            // если символом оказалась не буква - то вывалиться в ошибку на!уй
        if (!(std::isalpha(static_cast<unsigned char>(d_strng[_counter]))))
        {
            std::cout << "  --I WAS WAITING A COMMAND IN SYMBOL NUMBER " << _counter << ", DUMPING THE WHOLE STRING: '" << d_strng << "'" << std::endl;
            break;
        }

            // заспавнил новый буферный токен
        d_tkn_tmplt _token_buf;
            // записываем команду в токенбуфер и обновляем счётчик
        _token_buf.cmd = d_strng[_counter];
        _counter++;

        // на этом этапе отработаны возможные ошибки и проблемы при парсинге данных,
            // делаю чтение и запись чисел в заспавненный _токен_буфер
        while (_counter < _d_size)
        {
                // игнорирование пробелов и запятых
            while (_counter < _d_size
                && (std::isspace(static_cast<unsigned char>(d_strng[_counter]))
                || d_strng[_counter] == ','))
                    { _counter++; }
                // break'аем, если счётчик перевалил за размер d_strng (ака _d_size)
            if (_counter >= _d_size) break;

                // если читаемый символ является буквой - то break'нуть цикл
            if (std::isalpha(static_cast<unsigned char>(d_strng[_counter]))) break;

                // считать номер символа в d_strng[_counter], где начинается число
            size_t _num_start = _counter;

                // число может начинаться с '-' или с '+' или с '.' или с цифры. если это так - то просто обновляем счётчик
            if (d_strng[_counter] == '-'
                || d_strng[_counter] == '+'
                || d_strng[_counter] == '.'
                || std::isdigit(static_cast<unsigned char>(d_strng[_counter]))
                )
            {
                    // употребление в буфер первого символа начинается с обновления счётчика
                _counter++;

                    // обновление счётчика заканчивается тогда,
                        // когда читаемый символ не является цифрой или точкой
                            //
                            // эти шизофреники блять (как и я, впринципе) сделали так, что число можнт начинаться с точки.
                            // я не мог понять, почему у меня при чтении некоторых аттрибутов не достаёт одного или двух чисел, а оно вон оно что... ё-п-р-с-т...
                            //
                            // пока что я не сделал обработку этой зло!бучей второй точки, это оставлю деду, он доест...
                            //
                
                bool found_dot = false;
                while ( _counter < _d_size
                        && (std::isdigit(static_cast<unsigned char>(d_strng[_counter]))
                            || d_strng[_counter] == '.' )
                      )
                {
                    // break-аем цикл, если обнаружили вторую точку (потому что в числе может быть только одна точка)
                    if(d_strng[_counter] == '.' && found_dot)
                        break;
                    if(d_strng[_counter] == '.')
                        found_dot = true;
                    _counter++;
                }

                    // больше буферов богу буферов -
                    // используя значения _counter и _num_start считываем цифру в буфер _buf_double!
                std::string _buf_double = d_strng.substr(_num_start, _counter - _num_start);
                    // пробуем транслировать значение _buf_double в буфер токена
                try
                {
                    double val = std::stod(_buf_double);
                    _token_buf.digts.push_back(val);
                }
                    // и обрабатываем ошибку, если каким-то образом в коде есть баг и в buf_double залетел нелегальный символ
                catch (...)
                {
                    std::cout << "  --IT'S NOT A DIGIT IN COL. NO '" << _counter << "', INNIT?:  '" << _buf_double << "'\n";
                    break;
                }
            }   // заканчиваем считывать число.
            else
            {
                // при непрописанном символе просто начинаем заново искать число или букву
                _counter++;
            }
        }
            // пушбэк полученного значения в токены!
        buf_d_tokens.push_back(_token_buf);
    } // на этом моменте или заново шуршим d_string, или выходим, если счётчик перевалил за свой предел
}

    /// @brief возвращает true, если была прописана команда 'z'/'Z'. в остальных случаях - возвращает false;
void path_d_instructions_interpreter(const char _instr, std::vector<double> coords, bool* found_line, gvec_2d* _init_point)
{
    const char instr = tolower(_instr);
    gvec_2d _buf_coords;
    unsigned int offset = 0;
    bool nothing_left = false;
    // std::cout << "  " << _instr << ": \n";

read:
    switch (instr)
    {
    case 'h':
        {
            _buf_coords = {coords[offset], 0};
            if(isupper(_instr))
                _buf_coords = {_buf_coords.x, out_dots.back().y};
            if (coords.size() > (offset + 1)) 
            {
                offset += 1;
                goto write;
            }
            break;
        }
    case 'v':
        {
            _buf_coords = {0, coords[offset]};
            if (isupper(_instr))
                _buf_coords = {out_dots.back().x, _buf_coords.y};
            if (coords.size() > (offset + 1)) 
            {
                offset += 1;
                goto write;
            }
            break;
        }
    case 't':
    case 'l':
    case 'm':
        {
            _buf_coords = {coords[offset],coords[offset + 1]};
            if (coords.size() > (offset + 3)) 
            {
                offset += 2;
                goto write;
            }
            break;
        }
    case 'q':
    case 's':
        {
            _buf_coords = {coords[offset+2],coords[offset + 3]};
            if (coords.size() > (offset + 7)) 
            {
                offset += 4;
                goto write;
            }
            break;
        }
    case 'c':
        {
            _buf_coords = {coords[offset+4],coords[offset + 5]};
            if (coords.size() > (offset + 11)) 
            {
                offset += 6;
                goto write;
            }
            break;
        }
    case 'a':
        {
            _buf_coords = {coords[offset+5],coords[offset+6]};
            if(coords.size() > (offset + 13))
            {
                offset += 7;
                goto write;
            }
            break;
        }
    case 'z':
        {
            _buf_coords = *_init_point;
            if(coords.size() > (offset+1))
                goto write;
            break;
        }

    default:
        std::cout << "    --I CAN'T WORK WITH INSTRUCTION '" << instr << "', IGNORING..." << std::endl; 
    }

    nothing_left = true;    // по задумке - эта инструкция пропустится, если ещё останутся координаты для обработки.
                            // в свитч-кейсе выше есть директивы 'goto write;', которые вызываются, если в векторе остаются элементы;

write:
    bool _is_relative = !isupper(_instr);
    if(_is_relative && *found_line)
    {
        // std::cout << "    relative: " << _buf_coords.x << " / " << _buf_coords.y << std::endl;
        _buf_coords = _buf_coords + out_dots.back();
        // std::cout << "        rel-to-abs: '";
    }
    else
        // std::cout << "    absolute  : '";

    out_dots.push_back(_buf_coords);
    // std::cout << _buf_coords.x << "' / '" << _buf_coords.y << "'\n";

    if(*found_line)
        out_indx.push_back({(unsigned long long)out_dots.size()-2, (unsigned long long)out_dots.size() - 1});
    else
        *found_line = true;
    if(instr == 'z')
        *found_line = false;
    if(instr == 'm')
        *_init_point = _buf_coords;

    if(!nothing_left) goto read;

    return;
}

//                                      ,d     
//                                      88     
//           ,adPPYba,   88       88  MM88MMM  
//          a8"     "8a  88       88    88     
//          8b       d8  88       88    88     
//          "8a,   ,a8"  "8a,   ,a88    88,    
//           `"YbbdP"'    `"YbbdP'Y8    "Y888  



bool out_from_line(XMLElement* element)
{
    bool found = false;     // по сути, он должен возвращать true, если он нашёл как минимум две точки.
    found = true;           // но я пишу этот код в 5 утра и мне пока что дичайше лень и это прописывать...
    std::vector<const char*> attr_names = {"x1","y1","x2","y2"};
    
    out_dots.push_back
        ({
        element->FindAttribute(attr_names[0])->DoubleValue(),
        element->FindAttribute(attr_names[1])->DoubleValue()
        });
    out_dots.push_back
        ({
        element->FindAttribute(attr_names[2])->DoubleValue(),
        element->FindAttribute(attr_names[3])->DoubleValue()
        });
    out_indx.push_back
        ({
            (unsigned long long)out_dots.size() - 2,
            (unsigned long long)out_dots.size() - 1
        });
    // std::cout << "    dotNo" << out_indx[out_indx.size() - 1].a << "-dotNo" << out_indx[out_indx.size() - 1].b << ": x: '";
    // std::cout  << out_dots[out_dots.size() - 2 ].x << "' y: '" << out_dots[out_dots.size() - 2 ].y << "' / x: '";
    // std::cout << out_dots.back().x << "' y: '" << out_dots.back().y << std::endl;

    return found;
}

bool out_from_polyline(XMLElement* element)
{
    bool found = false;

    std::istringstream iss((std::string)element->FindAttribute("points")->Value());  // поток символов, из которого будут извлекаться координаты точек
    std::string pair;  // буффер под не-раз-парсенную координату (используется while-ом)
    while (iss >> pair)
    {
        std::istringstream pair_iss(pair);
        std::string x_str, y_str;
        if (std::getline(pair_iss, x_str, ',') && std::getline(pair_iss, y_str))
        {
            gvec_2d v; // буффер под координату
            try        // попробовать буфферизировать текущую точку и внести её в вектор точек
            {
                v.x = std::stod(x_str);
                v.y = std::stod(y_str);
                out_dots.push_back(v);  // пушбэк в вектор точек!
            }
            catch (const std::invalid_argument& err)
            {
                std::cerr << "  --ERROR WHILE PARSING POLYLINE: '" << pair << "' (" << err.what() << ")" << std::endl;
            }

            if(!found)
                found = true;       // нашёл связь минимум между двумя точками!
            else
            {
                // добавляю индекс в вектор индексов
                out_indx.push_back({ (unsigned long long)out_dots.size() - 2, (unsigned long long)out_dots.size() - 1 });
                // вывожу добавленные индекс и точку:
                // std::cout << "    dotNo" << out_indx[out_indx.size() - 1].a << "-dotNo" << out_indx[out_indx.size() - 1].b << ": x: '";
                // std::cout  << out_dots[out_dots.size() - 2 ].x << "' y: '" << out_dots[out_dots.size() - 2 ].y << "' / x: '";
                // std::cout << out_dots.back().x << "' y: '" << out_dots.back().y << std::endl;
            }
        }
    }
    return found;
}
                                                    
bool out_from_path(XMLElement* element)
{
    bool found = false;     // буалеан для обработки соединений с линиями;
    
    if(element->FindAttribute("d") == NULL)
        return false;

    std::string wtf = element->FindAttribute("d")->Value();
        // перевожу аттрибут d в рабочий вектьтор buf_d_tokens
    path_d_token_extractor(wtf);

    gvec_2d _init_point = {0.f,0.f};

    for (int i = 0; i < buf_d_tokens.size(); i++)
    {
        path_d_instructions_interpreter(buf_d_tokens[i].cmd,
                                        buf_d_tokens[i].digts,
                                        &found, &_init_point);
        found = false;
    }

    buf_d_tokens.clear();

    return true;
}

//         88                                             88  88              
//         88                                             88  88              
//         88                                             88  88              
//         88,dPPYba,   ,adPPYYba,  8b,dPPYba,    ,adPPYb,88  88   ,adPPYba,  
//         88P'    "8a  ""     `Y8  88P'   `"8a  a8"    `Y88  88  a8P_____88  
//         88       88  ,adPPPPP88  88       88  8b       88  88  8PP"""""""  
//         88       88  88,    ,88  88       88  "8a,   ,d88  88  "8b,   ,aa  
//         88       88  `"8bbdP"Y8  88       88   `"8bbdP"Y8  88   `"Ybbd8"'  

void handle_line_element(XMLElement* line)
{   
    std::cout << "line: " << std::endl;
    if(!out_from_line(line))
    {   std::cout << "    coord attribute is empty, ignoring..." << std::endl; }
    else
    {   std::cout << "    found data in 'line';" << std::endl;    }
}

void handle_polyline_element(XMLElement* polyline)
{
    std::cout << "polyline: " << std::endl;
    if(!out_from_polyline(polyline))
    {   std::cout << "    coord attribute is empty, ignoring..." << std::endl; }
    else
    {   std::cout << "    нашёл данные в аттрибуте \'polyline\'; записал;" << std::endl;    }
}

void handle_path_element(XMLElement* path)
{
    std::cout << "path: " << std::endl;
    if(!out_from_path(path))
    {   std::cout << "    coord attribute is empty, ignoring..." << std::endl; }
    else
    {   std::cout << "    found data in 'path';" << std::endl;    }

}

            //  ,adPPYb,d8  
            // a8"    `Y88  
            // 8b       88  
            // "8a,   ,d88  
            //  `"YbbdP"Y8  
            //  aa,    ,88  
            //   "Y8bbdP"   

void handle_g(XMLElement * group)
{
    std::cout << "g: " << std::endl;
    std::vector<XMLElement*> buf_childs;
    for (tinyxml2::XMLElement* child = group->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
    {   buf_childs.push_back(child);    }
    int readcounter = 0;
    for(int i = 0; i < buf_childs.size(); i++)
    {
        const char* name = buf_childs[i]->Name();
        if (strcmp(name, "path") == 0)          handle_path_element(buf_childs[i]);
        else if(strcmp(name, "line") == 0)      handle_line_element(buf_childs[i]);
        else if(strcmp(name, "polyline") == 0)  handle_polyline_element(buf_childs[i]);
        else if(strcmp(name, "g") == 0)  {std::cout << "--nested "; handle_g(buf_childs[i]);}
        else std::cout << "I WON'T PARSE ELEMENT '" << name << "' IN LINE No. " << buf_childs[i]->GetLineNum() << std::endl;
    }
    if (buf_childs.size() == 0)
    {
        std::cout << "  --nochild" << std::endl;
    }
}

void handle_svg(XMLElement * group)
{
    std::cout << "svg: " << std::endl;
    std::vector<XMLElement*> buf_childs;
    for (tinyxml2::XMLElement* child = group->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
    {   buf_childs.push_back(child);    }
    int readcounter = 0;
    for(int i = 0; i < buf_childs.size(); i++)
    {
        const char* name = buf_childs[i]->Name();
        if (strcmp(name, "path") == 0)          handle_path_element(buf_childs[i]);
        else if(strcmp(name, "line") == 0)      handle_line_element(buf_childs[i]);
        else if(strcmp(name, "polyline") == 0)  handle_polyline_element(buf_childs[i]);
        else if(strcmp(name, "g") == 0)         handle_g(buf_childs[i]);
        else std::cout << name << " in line No. " << buf_childs[i]->GetLineNum() << " there is " << name << ": can't take it, ignoring..." << std::endl;
    }
    if (buf_childs.size() == 0)
    {
        std::cout << "  --nochild" << std::endl;
    }
}

//          8b,dPPYba,  88       88  8b,dPPYba,   8b,dPPYba,    ,adPPYba,  8b,dPPYba,  
//          88P'   "Y8  88       88  88P'   `"8a  88P'   `"8a  a8P_____88  88P'   "Y8  
//          88          88       88  88       88  88       88  8PP"""""""  88          
//          88          "8a,   ,a88  88       88  88       88  "8b,   ,aa  88          
//          88           `"YbbdP'Y8  88       88  88       88   `"Ybbd8"'  88          

void run(std::string filepath)
{
    tinyxml2::XMLDocument svg_file;
    
    if(!(svg_file.LoadFile(filepath.c_str())))
    {
        std::cout << "tinyxml2 opened the file for reading..." << std::endl;
        XMLElement* element_svg = svg_file.FirstChildElement("svg");

        handle_svg(element_svg);
    }
}

//                                             88  88           88                 ad88              
//                                             ""  ""           ""                d8"                
//                                                                                88                 
//          ,adPPYYba,  ,adPPYba,   ,adPPYba,  88  88           88  8b,dPPYba,  MM88MMM  ,adPPYba,   
//          ""     `Y8  I8[    ""  a8"     ""  88  88           88  88P'   `"8a   88    a8"     "8a  
//          ,adPPPPP88   `"Y8ba,   8b          88  88           88  88       88   88    8b       d8  
//          88,    ,88  aa    ]8I  "8a,   ,aa  88  88           88  88       88   88    "8a,   ,a8"  
//          `"8bbdP"Y8  `"YbbdP"'   `"Ybbd8"'  88  88           88  88       88   88     `"YbbdP"'  
//
// generated via     https://patorjk.com/software/taag/#p=display&f=Univers