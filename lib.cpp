#include <QTextStream>
#include <QTextCodec>
void log(const QString text){
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM 866"));
    QTextStream cout(stdout);
    cout << text;
}
