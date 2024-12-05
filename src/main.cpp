#include "wrapper.h"

#include <iostream>
#include <vector>


int main()
{
    // auto vec = create_matrix_level(30, 30, "resources/heart.png");
    // std::vector<std::vector<int>> vec1 {std::vector<int>{30}};
    // for (int i = 0; i < 30; ++i)
    // {
    //     for (int j = 0; j < 30; ++j)
    //     {
    //         vec1[i].push_back(1);
    //     }
    // }
    // auto vec2 = vec;
    // std::cout << check_click(vec1, vec) << check_click(vec2, vec);
    Windows_wrapper win{Graph_lib::Point{400, 100}, 700, 700, "window"};
    return Graph_lib::gui_main();
    // Level level{"hamster level", "30x30", create_matrix_level(30, 30, "resources/hamster.jpg")};
    // Level level1{"heart level", "30x30", create_matrix_level(30, 30, "resources/heart.png")};
    // Level level2{"heart1 level", "30x30", create_matrix_level(30, 30, "resources/heart.png")};
    // Database_levels db_levels{};
    // Database_levels::Response res = db_levels.add_level(level);
    // Database_levels::Response res1 = db_levels.add_level(level1);
    // Database_levels::Response res2 = db_levels.add_level(level2);
    // // if (res == Database_levels::Response::ALREADY_EXISTS)
    // //     std::cout << "cool!" << std::endl;
    // // Level hamster_level = db_levels.get_level("hamster level", "30x30");
    // // std::cout << hamster_level.title << " " << hamster_level.size << " " << hamster_level.hearts_count << " " << hamster_level.finished << std::endl;
    // std::cout << db_levels.get_new_id("30x30") << std::endl;
    return 0;
}