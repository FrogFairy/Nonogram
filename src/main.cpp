#include "main_window.h"
#include "generate_level.h"
#include "create_level.h"

#include <iostream>
#include <vector>
#include <fstream>


void save_input_file(Fl_File_Chooser *w, void *userdata)
{
    std::cout << "File selected:" << w->value() << std::endl;
}


int main()
{
    // Main_window win{Graph_lib::Point{400, 100}, 700, 700, "window"};
    // Generate_level_window win{Graph_lib::Point{400, 100}, 700, 700, "window"};
    std::vector<std::vector<int>> matrix = create_matrix_level(30, 30, "resources/heart.png");
    std::ofstream out{"black_pixels.txt"};
    out << "[";
    for (int j = 0; j < matrix.size(); ++j)
    {
        out << "[";
        for (int i = 0; i < matrix[0].size(); ++i)
        {
            if (matrix[j][i]) out << "[255, 255, 255]";
            else out << "[0, 0, 0]";
            if (i != matrix[0].size() - 1) out << ", ";
        }
        out << "]";
        if (j != matrix.size() - 1) out << ", ";
    }
    out << "]";
    // return Graph_lib::gui_main();

    // Fl_File_Chooser *fc = new Fl_File_Chooser(".", "Image Files (*.{jpg,png})", 0, "Image");
    // fc->callback(save_input_file);
    // fc->show();
    // return Graph_lib::gui_main();
}