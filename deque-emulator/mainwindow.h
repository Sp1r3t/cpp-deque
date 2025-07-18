#pragma once

#include <QMainWindow>
#include <QStringListModel>
#include <QListWidgetItem>
#include <random>

#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

static std::deque<std::string> tea {
    "Чай Лунцзин",
    "Эрл Грей",
    "Сенча",
    "Пуэр",
    "Дарджилинг",
    "Ассам",
    "Матча",
    "Ганпаудер",
    "Оолонг",
    "Лапсанг Сушонг"
};

static std::deque<std::string> cakes {
    "Красный бархат",
    "Наполеон",
    "Медовик",
    "Тирамису",
    "Прага",
    "Чизкейк",
    "Захер",
    "Эстерхази",
    "Морковный торт",
    "Чёрный лес",
};

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetRandomGen(const std::mt19937& random_gen);

private slots:

    void on_btn_clear_clicked();
    void on_btn_push_front_clicked();
    void on_btn_push_back_clicked();
    void on_btn_pop_back_clicked();
    void on_btn_pop_front_clicked();
    void on_btn_insert_clicked();
    void on_btn_erase_clicked();
    void on_btn_begin_clicked();
    void on_btn_end_clicked();
    void on_btn_dec_iterator_clicked();
    void on_btn_inc_iterator_clicked();
    void on_list_widget_currentRowChanged(int currentRow);
    void on_btn_tea_clicked();
    void on_btn_cakes_clicked();
    void on_btn_merge_sort_clicked();
    void on_btn_merge_sOrT_clicked();
    void on_btn_lower_clicked();
    void on_btn_upper_clicked();
    void on_btn_edit_clicked();
    void on_btn_shuffle_clicked();
    void on_btn_unique_clicked();
    void on_btn_resize_clicked();
    void on_btn_min_el_clicked();
    void on_btn_max_el_clicked();
    void on_btn_find_clicked();
    void on_btn_count_clicked();
    void on_btn_reverse_clicked();

private:

    void ApplyModel();
    void ApplyIterator();

private:
    std::mt19937 gen;
    Model deque_model_;
    Ui::MainWindow *ui;
};
