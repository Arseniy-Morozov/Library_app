#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Book {
    QString title;
    QString author;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_searchEdit_textChanged(const QString &text);

private:
    Ui::MainWindow *ui;
    QList<Book> bookList;

    void loadBooksFromFile();
    void saveBooksToFile();
    void updateBookListWidget();
};

#endif // MAINWINDOW_H
