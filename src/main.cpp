#include "InvertedIndex.h"
#include "ConverterJSON.h"
#include "SearchEngine.h"
#include "callermain.h"
#include "gui.h"


using namespace std;


int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    CallerMainWindow window(nullptr);
    Ui::MainWindow caller;
    caller.setupUi(&window);
    window.textEdit = caller.textEdit;
    window.button1 = caller.pushButton;
    window.button2 = caller.pushButton_2;
    window.browser = caller.textBrowser;
    ConverterJSON conv;
    vector<vector<Entry>> result;
    InvertedIndex in;
    in.UpdateDocumentBase(conv.GetTextDocuments("json/config.json"));
    SearchServer s(in);
    window.setWindowTitle(QString::fromStdString(conv.engineName + " Ver. " + conv.engineVersion));
   // window.label->setText(QString::fromStdString(conv.engineName + " " + conv.engineVersion));
    QObject::connect(window.button1, &QPushButton::clicked, [&s, &conv, &window]{
        window.browser->clear();
        s.config.putAnswers(s.search(conv.GetRequests("json/requests.json")));
        window.browser->setText(QString::fromStdString(s.stringResult));
    });

    QObject::connect(window.button2, &QPushButton::clicked, [&s, &conv, &window]{
       window.browser->clear();
       std::vector<std::string> searchTemp;
       searchTemp.clear();
       searchTemp.push_back(window.textEdit->toPlainText().toStdString());
       s.config.putAnswers(s.search(searchTemp));
       window.browser->setText(QString::fromStdString(s.stringResult));
    });

    window.show();
    return QApplication::exec();
}
