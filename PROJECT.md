<span style="color:yellow"> жёлтый </span> цвет - класс  
<span style="color:green"> зеленый </span> цвет - public  
<span style="color:blue"> синий </span> цвет - protected  
<span style="color:red"> красный </span> цвет - private

# Вспомогательные графические классы

## <span style="color:yellow"> Windows_wrapper </span>
### Класс-обертка, вызывающий различные окна. Так же совершает работу с базой данных через класс Database_levels. Все окна содержат указатель на Windows_wrapper, из которого они были вызваны
### 1. <span style="color:green"> Database_levels db_levels </span>
### Объект для работы с базой данных
### 2. <span style="color:green"> void open_generate_window() </span>
### Открывает окно генерации уровня
### 3. <span style="color:green"> void open_choose_window(Size btn_label) </span>
### Принимает размер уровня и открывает окно выбора уровня (в зависмости от размера уровны)
### 4. <span style="color:green"> void open_play_window(Size size, const std::string& level_title, Level_button& btn) </span>
### Принимает размер уровня, название уровня и ссылку на кнопку уровня. Открывает игровое окно
### 5. <span style="color:green"> void open_rules_window() </span>
### Открывает окно правил
### 6. <span style="color:red"> Указатели на различные окна </span>

## <span style="color:yellow"> Window_with_back : Graph_lib::Window </span>
### Класс, от которого наследуются все окна программы. Содержит единственную кнопку, возвращающую пользователя на предыдущее окно.
### 1. <span style="color:green"> void wait_for_button() </span>
### Функция для отслеживания нажатия на кнопку "back"
### 2. <span style="color:blue"> bool button_pushed </span>
### Нажата ли кнопка
### 3. <span style="color:red"> Graph_lib::Button back_button </span>
### Кнопка "back"
### 4. <span style="color:red"> static void cb_back (Graph_lib::Address, Graph_lib::Address) </span>
### Callback для кнопкаи back_button; вызывает back()
### 5. <span style="color:red"> void back() </span>
### Изменяет состояние кнопки

## <span style="color:yellow"> Size_button : Graph_lib::Button </span>
### Кнопка размера уровня. Содержит размер уровня
### 1. <span style="color:green"> Size level_size() </span>
### Возвращает размер уровня
### 2. <span style="color:red"> Size _level_size </span>
### Размер уровня

## <span style="color:yellow"> Level_button: Graph_lib::Button </span>
### Кнопка уровня. 
### 1. <span style="color:green"> void change_color(bool is_finished) </span>
### Изменяет цвет кнопки в зависимости от завершенности уровня

## <span style="color:yellow"> Option_button: Graph_lib::Button </span>
### Кнопка опции. От этого класса наследуются три: кнопка заполнения, кнопка крестика и кнопка инвертации 
### 1. <span style="color:green"> virtual void change_state() </span>
### Изменяет состояние кнопки на обратное текущему
### 2. <span style="color:green"> bool active() </span>
### Возвращает состояние кнопки - активная или неактивная
### 3. <span style="color:blue"> void set_color() </span>
### Изменяет цвет кнопки в зависимости от состояния
### 4.1 <span style="color:blue"> Graph_lib::Color default_color </span>
### 4.2 <span style="color:blue"> Graph_lib::Color active_color </span>
### Цвет неактивной и активной кнопки соответственно
### 5. <span style="color:blue"> std::unique_ptr<Graph_lib::Shape> mark </span>
### Указатель на фигуру, которая будет отображаться на кнопке
### 6. <span style="color:red"> bool _active </span>
### Состояние кнопки

## <span style="color:yellow"> Fill_button : public Option_button </span>
### Кнопка заполнения
## <span style="color:yellow"> Cross_button : public Option_button </span>
### Кнопка крестика
## <span style="color:yellow"> Invert_button : public Option_button </span>
### Кнопка инвертации. Переопределяет attach базового класса.
### 1. <span style="color:red"> std::unique_ptr<Graph_lib::Label_widget> label_widget </span>
### Указатель на Label_widget с текстом "invert: "

## <span style="color:yellow"> Heart : Graph_lib::Widget </span>
### Обертка для fltk виджета Fl_Box, содержащего в себе изображение
### 1. <span style="color:green"> void clean_pointer() </span>
### Переопределяет метод clean_pointer() базового класса. Освобождает память, выделенную для изображения
### 2. <span style="color:green"> void change(bool fill) </span>
### Изменяет состояние изображения
### 3. <span style="color:green"> bool is_filled() </span>
### Возвращает текущее состояние изображения
### 4.1 <span style="color:red"> const std::string fill_heart = "resources/heart.png" </span>
### 4.2 <span style="color:red"> const std::string empty_heart = "resources/empty_heart.png" </span>
### Путь к картинке с заполненным и незаполненным сердцем
### 5. <span style="color:red"> Graph_lib::Image* img </span>
### Указатель на изображение
### 6. <span style="color:red"> bool filled </span>
### Состояние изображения

## <span style="color:yellow"> Game_button : Graph_lib::Button </span>
### Игровая кнопка (на поле).
### 1. <span style="color:green"> void change_button(Level::Cell_state state) </span>
### Изменяет состояние кнопки
### 2. <span style="color:green"> void init_mark() </span>
### Отрисовывает необходимую фигуру на кнопке, в зависимости от ее состояния
### 3. <span style="color:red"> Graph_lib::Shape* mark </span>
### Указатель на фигуру, которая должна отрисоваться на кнопке

## <span style="color:yellow"> Choice_box : Graph_lib::Widget </span>
### Выпадающий список

## <span style="color:yellow"> File_chooser_box : Graph_lib::Widget </span>
### Виджет для выбора файла. В конструкторе принимает кроме стандартных аргументов label для кнопки, возможные расширения файлов, callback для окна (в него передается путь к выбранному файлу) и callback для кнопки.
### 1.1 <span style="color:green"> Button btn </span>
### 1.2 <span style="color:green"> Out_box out_box </span>
### 1.3 <span style="color:green"> Rectangle err_rectangle </span>
### Кнопка, поле для вывода пути к файлу и прямоугольник, отображающийся при ошибке
### 2. <span style="color:green"> Fl_File_Chooser* chooser </span>
### Указатель на fltk виджет - окно с выбором файла
### 3. <span style="color:green"> choose_file() </span>
### Callback для chooser. В нем путь к файлу записывается в out_box и вызывается callback для окна, в котором находится виджет.
### 4. <span style="color:green"> enum State </span>
### Состояние виджета - OK или ERR
### 5. <span style="color:green"> change_state(State state) </span>
### Изменяет цвет err_rectangle

## <span style="color:yellow"> Label_widget : Graph_lib::Widget </span>
### Обертка для fltk виджета - Fl_Box. Отображает надпись

## <span style="color:yellow"> Scrollable_Menu : Widget </span>
### Обертка для fltk виджета - Fl_Scroll


<br></br>
# Графические классы

## <span style="color:yellow"> Main_window : Graph_lib::Window </span>
![Alt text](./image_for_project/main.png?raw=true "Title")
###  1. <span style="color:red"> Graph_lib::Menu main_widget </span>
###  Меню с кнопками размеров уровней

###  2. <span style="color:red"> Graph_lib::Button generate_button </span>
### Кнопка для открытия окна генерации уровня

###  3. <span style="color:red"> std::vector<Size_button> size_buttons </span>
### Вектор кнопок с размерами уровней

###  3.1 <span style="color:red"> static void cb_go_to_level(Graph_lib::Address, Graph_lib::Address) </span>
###  3.2 <span style="color:red"> void go_to_level(Size btn_label); </span>
### Callback для кнопок с уровнями определенного размера. go_to_level принимает размер уровня

###  4.1 <span style="color:red"> static void cb_create_level(Graph_lib::Address, Graph_lib::Address) </span>
###  4.2 <span style="color:red">  void create_level() </span>
### Callback для кнопки генерации уровня.

<br></br>
## <span style="color:yellow"> Choose_level_window : Window_with_back </span>
![Alt text](./image_for_project/choose.png?raw=true "Title")
###  1. <span style="color:red"> Size size </span>
### Размер уровней

###  2. <span style="color:red"> Graph_lib::Menu level_widget </span>
### Меню с кнопками уровней

###  3.1 <span style="color:red"> std::vector<Level> levels </span>
###  3.2 <span style="color:red"> Graph_lib::Vector_ref<Level_button*> level_buttons </span>
### Вектор уровней и кнопок уровней

###  4.1 <span style="color:red"> static void cb_start_level(Graph_lib::Address, Graph_lib::Address) </span>
###  4.2 <span style="color:red"> void start_level(const std::string& title, Level_button& btn) </span>
### Callback для перехода к игровому окну определенного уровня

<br></br>
## <span style="color:yellow"> Generate_level_window : Window_with_back </span>
![Alt text](./image_for_project/generate.png?raw=true "Title")
###  1.1 <span style="color:red"> std::string filename </span>
###  1.2 <span style="color:red"> Size level_size </span>
###  1.3 <span style="color:red"> std::string str_level_name </span>
### Информация об уровне: путь к файлу с изображением, размер уровня, название уровня. В эти поля сохранятся данные пользователя

###  2. <span style="color:red"> std::vector<Size> sizes </span>
### Вектор размеров для Choice_box

###  3.1 <span style="color:red"> Graph_lib::Choice_box size_box </span>
###  3.2 <span style="color:red"> Graph_lib::File_chooser_box image_chooser </span>
###  3.3 <span style="color:red"> Graph_lib::In_box level_name </span>
### Виджеты для введения данных об уровне

###  4 <span style="color:red"> static void cb_choose_file(Graph_lib::Address, Graph_lib::Address) </span>
### Callback для кнопки выбора файла. Вызывает метод, открывающий fltk виджет с выбором файла 
###  5 <span style="color:red"> static void save_image(Graph_lib::Window *own, const std::string&) </span>
### Callback для File_Chooser_Box. Сохраняет в поле filename путь к изображению
###  6.1 <span style="color:red"> static void cb_save_button(Graph_lib::Address, Graph_lib::Address addr) </span>
###  6.2 <span style="color:red"> void save_button() </span>
### Callback для кнопки "Save". Добавляет новый уровень в базу данных или сообщает пользователю об ошибке

<br></br>
## <span style="color:yellow"> Rules_window : Window_with_back </span>
![Alt text](./image_for_project/rules.png?raw=true "Title")
###  1.1 <span style="color:red"> Graph_lib::Text rt </span>
###  1.2 <span style="color:red"> Graph_lib::Image rules </span>
### Текст и изображение с правилами

<br></br>
## <span style="color:yellow"> Graph_board : Graph_lib::Widget </span>

###  1. <span style="color:green"> Level restart() </span>
### Перезапускает logic_board, изменяет состояние кнопок. Возвращает измененный level
###  2.1 <span style="color:green"> void init_buttons() </span>
###  2.2 <span style="color:green"> void init_digits() </span>
### Инициализирует игровые кнопки и цифры
###  3. <span style="color:green"> void get_hint() </span>
### Callback для клика на подсказку
###  4. <span style="color:green"> Level invert_digits() </span>
### Callback для клика на инвертацию
###  5. <span style="color:red"> void change_previous() </span>
### Изменяет состояние последнего клика (если предыдущим ходом была нажата подсказка или пользователь ошибся)
###  6.1 <span style="color:red"> void change_buttons(bool state) </span>
###  6.2 <span style="color:red"> void change_digits(Position pos) </span>
### Изменяет состояние кнопок и цифр
###  7. <span style="color:red"> void set_digit_color(Graph_lib::Text& text, Graph_lib::Color color) </span>
### Устанавливает цифре определенный цвет
###  8. <span style="color:red"> void block_buttons(bool state) </span>
### Блокирует/разблокирует все кнопки
###  9.1 <span style="color:red"> Position mistake {} </span>
###  9.2 <span style="color:red"> Position hint {} </span>
### Позиция клетки, на которую пользователь выставил неверное значение и позиция клетки, на которую была поставлена подсказка
###  10. <span style="color:red"> bool blocked </span>
### Состояние поля - заблокированно или нет

<br></br>
## <span style="color:yellow"> Play_window : Window_with_back </span>
![Alt text](./image_for_project/play.png?raw=true "Title")
###  1. <span style="color:green"> Методы для обновления уровня в бд </span>
###  2 <span style="color:red"> Callback для кнопок и сами кнопки </span>
###  3. <span style="color:red"> std::vector<Heart> hearts_img </span>
###  Вектор сердечек
###  4. <span style="color:red"> Level::Cell_state button_option </span>
### Текущая выбранная опция: заполнение или крестик

<br></br>
# Вспомогательные логические классы
## <span style="color:yellow"> Size </span>
### Размер. Содержит два поля - width и height
## <span style="color:yellow"> Position </span>
### Позиция в векторе. Содержит два поля - x и y и метод empty()
## <span style="color:yellow"> Interval </span>
### Интервал. Содержит два поля - start и end и метод empty()
## <span style="color:yellow"> Position_interval </span>
### Интервал в строке или столбце. Содержит два поля - pos: индекс столбца или строки и Interval interval: сам интервал

<br></br>
# Логические классы
## <span style="color:yellow"> Database_levels </span>
![Alt text](./image_for_project/db.png?raw=true "Title")
## Класс, работающий с базой данных
###  1. <span style="color:green"> concept LevelConcept </span>
### Концепт, позволяющий работать только с типами Level::Needful и Level::Cell_state
###  2. <span style="color:green"> enum Response </span>
### enum для ответа базы данных. Три состояния: OK, FAIL и ALREADY_EXISTS (для уровня)
### 3. <span style="color:green"> Методы для работы с бд: добавление уровня, получение уровня по названию и размеру, получение всех уровней с определенным размером, обновление некоторых полей бд </span>
### 4. <span style="color:green"> int get_new_id(Size size) </span>
### Возвращает следующий за последним id уровня (необходимо при генерации уровня, если пользователь не ввел никакого названия)
### 5. <span style="color:red"> Callback для sqlite3 </span>
### 6.1 <span style="color:red"> 
    template<LevelConcept T>
    std::string vector_to_string(std::vector<std::vector<T>> vec) const </span>
### 6.2 <span style="color:red"> static std::string positions_to_string(std::vector<Position>& vec) const </span>
### Методы для преобразования векторов в строки
### 7.1 <span style="color:red"> 
    template<LevelConcept T>
    static std::vector<std::vector<T>> string_to_vector(const std::string& str) </span>
### 7.2 <span style="color:red"> static std::vector<Position> string_to_positions(const std::string& str) </span>
### Методы для преобразования строк в векторы

## <span style="color:yellow"> Level </span>
## Класс, содержащий информацию об уровне
###  1. <span style="color:green"> enum Needful </span>
### enum для значений в корректном массиве. Значения: FILLED_VAL и CROSS_VAL.
###  2. <span style="color:green"> enum Cell_state </span>
### enum для значений в пользовательском массиве. Состояния: EMPTY, CROSS, FILLED, HINT_CROSS, HINT_FILLED, MISTAKE_CROSS, MISTAKE_FILLED
### 3. <span style="color:green"> Методы, обновляющие поля уровня </span>
### 4. <span style="color:green"> restart() </span>
### Перезапускает уровень
### 5. <span style="color:green"> init() </span>
### Инициализирует пользовательский массив EMPTY и массив с пустыми клетками - позициями всех клеток поля
### 6 <span style="color:red"> 
    std::vector<std::vector<Needful>> create_matrix_level(Size size, const std::string& filename) const </span>
### Генерация матрицы уровня на основе изображения

## <span style="color:yellow"> Nonogram_logic </span>
## Класс, содержащий логику работы с игровой доской
###  1. <span style="color:green"> enum Response </span>
### enum для состояния поля. Значения: OK, MISTAKE и FINISH.
###  2. <span style="color:green"> void set_cell(Position pos, Level::Cell_state val) </span>
### Метод, устанавливающий значение в опеределнную клетку пользовательской матрицы
###  3. <span style="color:green"> void change_cell(Position pos, Level::Cell_state val) </span>
### Метод, изменяющий значение в опеределнную клетку пользовательской матрицы
###  4. <span style="color:green"> std::vector<Position> changed_digits(Position pos, Level::Needful state) </span>
### Метод, возвращающий, какие цифры были изменены при нажатии на клетку с позицией pos
###  5. <span style="color:green"> void invert()  </span>
### Метод, инвентирующий поле
###  6.1 <span style="color:red"> Position row_changed(Position pos, Level::Cell_state needful_value, Level::Cell_state opposed_value, Level::Needful state) </span>
###  6.2 <span style="color:red"> Position col_changed(Position pos, Level::Cell_state needful_value, Level::Cell_state opposed_value, Level::Needful state) </span>
### Методы, возвращающие позиции измененных цифр в строке и столбце

###  7.1 <span style="color:red"> void fill_row_digits() </span>
###  7.2 <span style="color:red"> void fill_col_digits() </span>
### Методы, заполняющие цифры, отображающиеся слева и сверху поля

###  8.1 <span style="color:red"> void init_hidden_rows() </span>
###  8.2 <span style="color:red"> void init_hidden_cols() </span>
### Методы, инициализирующие скрытые цифры (то есть те, которые пользователь уже использовал)

###  9.1 <span style="color:red"> void load_hidden_rows() </span>
###  9.2 <span style="color:red"> void load_hidden_cols() </span>
### Методы, подгружающие скрытые цифры из буфера (при инвертации уровня)

## <span style="color:yellow"> Prompter </span>
## Класс, создающий подсказки для пользователя
###  1. <span style="color:green"> Position get_hint() </span>
### Получение подсказки (в случайной пустой клетке)
###  2. <span style="color:green"> void after_hint(Position pos) </span>
### Метод, преобразующий клетку с подсказкой в обычную клетку
###  3. <span style="color:red"> Nonogram_logic* logic_board </span>
### Указатель на Nonogram_logic, к которому будет применятся подсказка