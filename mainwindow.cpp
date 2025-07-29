#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadBooksFromFile();
    updateBookListWidget();
}

MainWindow::~MainWindow() {
    saveBooksToFile();
    delete ui;
}

void MainWindow::on_addButton_clicked() {
    QString title = ui->titleEdit->text().trimmed();
    QString author = ui->authorEdit->text().trimmed();

    if (title.isEmpty() || author.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите название и автора.");
        return;
    }

    bookList.append({title, author});
    updateBookListWidget();

    ui->titleEdit->clear();
    ui->authorEdit->clear();
}

void MainWindow::on_searchEdit_textChanged(const QString &text) {
    ui->bookListWidget->clear();

    QString filter = text.trimmed().toLower();

    for (const Book &book : bookList) {
        if (book.title.toLower().contains(filter)) {
            ui->bookListWidget->addItem(book.title + " — " + book.author);
        }
    }
}


void MainWindow::on_deleteButton_clicked() {
    int row = ui->bookListWidget->currentRow();
    if (row >= 0 && row < bookList.size()) {
        bookList.removeAt(row);
        updateBookListWidget();
    }
}

void MainWindow::updateBookListWidget() {
    ui->bookListWidget->clear();
    for (const Book &book : bookList) {
        ui->bookListWidget->addItem(book.title + " — " + book.author);
    }
}

void MainWindow::loadBooksFromFile() {
    QFile file("books.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split("||");
        if (parts.size() == 2) {
            bookList.append({parts[0], parts[1]});
        }
    }
    file.close();
}

void MainWindow::saveBooksToFile() {
    QFile file("books.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const Book &book : bookList) {
        out << book.title << "||" << book.author << "\n";
    }
    file.close();
}
