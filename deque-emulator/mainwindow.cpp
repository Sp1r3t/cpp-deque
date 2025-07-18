#include "mainwindow.h"
#include "algo.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <algorithm>
#include <string>
#include <deque>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , gen(std::random_device{}())
    , deque_model_()
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ApplyModel();
    ApplyIterator();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetRandomGen(const std::mt19937& random_gen) {
    gen = random_gen;
}

void MainWindow::ApplyModel() {
    ui->list_widget->clear();

    for (size_t idx = 0; idx < deque_model_.items.size(); ++idx) {
        ui->list_widget->addItem(QString::number(idx) + ": " + QString::fromStdString(deque_model_.items[idx]));
    }

    ui->list_widget->addItem("end");
    ui->txt_size->setText(QString::number(deque_model_.items.size()));
}

void MainWindow::ApplyIterator() {
    if (deque_model_.items.empty()) {
        ui->list_widget->setCurrentRow(0);
        ui->txt_elem_content->clear();
        ui->btn_edit->setEnabled(false);
        ui->btn_pop_back->setEnabled(false);
        ui->btn_erase->setEnabled(false);
        ui->btn_inc_iterator->setEnabled(false);
        ui->btn_dec_iterator->setEnabled(false);
        ui->btn_pop_front->setEnabled(false);
        return;
    }

    if (deque_model_.iterator == deque_model_.items.end()) {
        ui->list_widget->setCurrentRow(static_cast<int>(deque_model_.items.size()));
        ui->txt_elem_content->clear();
        ui->btn_edit->setEnabled(false);
        ui->btn_erase->setEnabled(false);
        ui->btn_inc_iterator->setEnabled(false);
    } else {
        int index = std::distance(deque_model_.items.begin(), deque_model_.iterator);
        ui->list_widget->setCurrentRow(index);
        ui->txt_elem_content->setText(QString::fromStdString(*deque_model_.iterator));
        ui->btn_edit->setEnabled(true);
        ui->btn_erase->setEnabled(true);
        ui->btn_inc_iterator->setEnabled(true);
    }

    ui->btn_pop_front->setEnabled(true);
    ui->btn_pop_back->setEnabled(true);
    ui->btn_dec_iterator->setEnabled(deque_model_.iterator != deque_model_.items.begin());
}

void MainWindow::on_btn_pop_back_clicked() {
    if (!deque_model_.items.empty()) {
        deque_model_.items.pop_back();
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
        ApplyIterator();
    }
}

void MainWindow::on_btn_push_back_clicked() {
    deque_model_.items.push_back(ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_btn_clear_clicked() {
    deque_model_.items.clear();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_btn_insert_clicked() {
    deque_model_.items.insert(deque_model_.iterator, ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_btn_erase_clicked() {
    if (deque_model_.iterator != deque_model_.items.end()) {
        deque_model_.items.erase(deque_model_.iterator);
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
        ApplyIterator();
    }
}

void MainWindow::on_btn_edit_clicked() {
    if (deque_model_.iterator != deque_model_.items.end()) {
        int index = std::distance(deque_model_.items.begin(), deque_model_.iterator);
        *deque_model_.iterator = ui->txt_elem_content->text().toStdString();
        ApplyModel();
        deque_model_.iterator = deque_model_.items.begin() + index;
        ApplyIterator();
    }
}

void MainWindow::on_btn_merge_sort_clicked() {
    if (deque_model_.items.empty()) {
        return;
    }

    auto comparator = [](const std::string &a, const std::string &b) {
        return a < b;
    };

    deque_model_.items = MergeSort<>(deque_model_.items, comparator);
    deque_model_.iterator = deque_model_.items.begin();

    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_btn_merge_sOrT_clicked() {
    if (deque_model_.items.empty()) {
        return;
    }

    auto comparator = [](const std::string &a, const std::string &b) {
        return QString::fromStdString(a).compare(QString::fromStdString(b), Qt::CaseInsensitive) < 0;
    };

    deque_model_.items = MergeSort(deque_model_.items, comparator);
    deque_model_.iterator = deque_model_.items.begin();

    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_btn_shuffle_clicked() {
    int current_index;

    if (deque_model_.iterator != deque_model_.items.end()) {
        current_index = std::distance(deque_model_.items.begin(), deque_model_.iterator);
    } else {
        current_index = -1;
    }

    std::shuffle(deque_model_.items.begin(), deque_model_.items.end(), gen);

    ApplyModel();

    if (current_index >= 0) {
        deque_model_.iterator = deque_model_.items.begin() + current_index;
    } else {
        deque_model_.iterator = deque_model_.items.end();
    }

    ApplyIterator();
}

void MainWindow::on_btn_unique_clicked() {
    if (std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        auto last = std::unique(deque_model_.items.begin(), deque_model_.items.end());
        deque_model_.items.erase(last, deque_model_.items.end());
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
        ApplyIterator();
    }
}

void MainWindow::on_list_widget_currentRowChanged(int currentRow) {
    if (currentRow < 0) {
        return;
    }

    if (currentRow < static_cast<int>(deque_model_.items.size())) {
        deque_model_.iterator = deque_model_.items.begin() + currentRow;
    } else {
        deque_model_.iterator = deque_model_.items.end();
    }
    ApplyIterator();
}

void MainWindow::on_btn_dec_iterator_clicked() {
    if (deque_model_.iterator != deque_model_.items.begin()) {
        --deque_model_.iterator;
        ApplyIterator();
    }
}

void MainWindow::on_btn_inc_iterator_clicked() {
    if (deque_model_.iterator != deque_model_.items.end()) {
        ++deque_model_.iterator;
        ApplyIterator();
    }
}

void MainWindow::on_btn_begin_clicked() {
    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}

void MainWindow::on_btn_end_clicked() {
    deque_model_.iterator = deque_model_.items.end();
    ApplyIterator();
}

void MainWindow::on_btn_resize_clicked() {
    bool ok;
    int new_size = ui->txt_size->text().toInt(&ok);
    if (ok && new_size >= 0) {
        deque_model_.items.resize(new_size);
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
        ApplyIterator();
    }
}

void MainWindow::on_btn_min_el_clicked() {
    if (!deque_model_.items.empty()) {
        deque_model_.iterator = std::min_element(deque_model_.items.begin(), deque_model_.items.end());
        ApplyIterator();
    }
}

void MainWindow::on_btn_max_el_clicked() {
    if (!deque_model_.items.empty()) {
        deque_model_.iterator = std::max_element(deque_model_.items.begin(), deque_model_.items.end());
        ApplyIterator();
    }
}

void MainWindow::on_btn_find_clicked() {
    if (!deque_model_.items.empty()) {
        auto it = std::find(deque_model_.items.begin(), deque_model_.items.end(), ui->txt_elem_content->text().toStdString());
        deque_model_.iterator = it;
        ApplyIterator();
    }
}

void MainWindow::on_btn_count_clicked() {
    auto count = std::count(deque_model_.items.begin(), deque_model_.items.end(), ui->le_count->text().toStdString());
    ui->lbl_count->setText(QString::number(count));
}

void MainWindow::on_btn_tea_clicked() {
    deque_model_.items = tea;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
}


void MainWindow::on_btn_cakes_clicked() {
    deque_model_.items = cakes;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_btn_lower_clicked() {
    if (std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        deque_model_.iterator = std::lower_bound(deque_model_.items.begin(), deque_model_.items.end(), ui->txt_elem_content->text().toStdString());
        ApplyIterator();
    }
}


void MainWindow::on_btn_upper_clicked() {
    if (std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        deque_model_.iterator = std::upper_bound(deque_model_.items.begin(), deque_model_.items.end(), ui->txt_elem_content->text().toStdString());
        ApplyIterator();
    }
}


void MainWindow::on_btn_push_front_clicked() {
    deque_model_.items.push_front(ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
}


void MainWindow::on_btn_pop_front_clicked() {
    deque_model_.items.pop_front();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
}

void MainWindow::on_btn_reverse_clicked() {
    int current_index;

    if (deque_model_.iterator != deque_model_.items.end()) {
        current_index = std::distance(deque_model_.items.begin(), deque_model_.iterator);
    } else {
        current_index = -1;
    }

    std::reverse(deque_model_.items.begin(), deque_model_.items.end());

    ApplyModel();

    if (current_index >= 0) {
        deque_model_.iterator = deque_model_.items.begin() + current_index;
    } else {
        deque_model_.iterator = deque_model_.items.end();
    }

    ApplyIterator();
}

