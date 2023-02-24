#include <QMainWindow>
#include <QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QLabel>

class CallerMainWindow : public QMainWindow {
Q_OBJECT

public:
    CallerMainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
    }
    QTextEdit *textEdit = nullptr;
    QPushButton *button1 = nullptr;
    QPushButton *button2 = nullptr;
    QTextBrowser *browser = nullptr;
    QLabel *label = nullptr;
};
