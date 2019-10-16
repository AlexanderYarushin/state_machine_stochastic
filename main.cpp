#include <QCoreApplication>
#include <ctime>
#include <QTextStream>
#include <QTextCodec>

#include "lib.cpp"

void log(const QString text){
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM 866"));
    QTextStream cout(stdout);
    cout << text;
}

static std::vector<std::vector<QString>> arrayInputOutput  = {
    {"Пойти на экзамен",""},                            //1
    {"Попытаться сесть вперед",""},                     //2
    {"Попытаться сесть назад",""},                      //3
    {"Попытаться достать шпаргалку",""},                //4
    {"Попытаться списать",""},                          //5
    {"Пойти отвечать по билету",""},                    //6
    {"При ответе попытаться подглядеть в телефоне",""}, //7
    {"Попросить преподавателя о тройке",""},            //8
    {"Закончить ответ",""},                             //9
};

static std::vector<QString> arrayCondition = {
    {"Начало"},                             //1
    {"Прибытие на экзамен"},                //2
    {"Усаживание на переднюю парту"},       //3
    {"Усаживание на последнюю парту"},      //4
    {"Доставание шпаргалки"},               //5
    {"Списывание"},                         //6
    {"Ответ по билету"},                    //6
    {"Подглядывание в телефон"},            //7
    {"Упрашивание преподавателя о тройке"}, //8
    {"Экзамен сдан"},                       //9
    {"Экзамен не сдан"}                     //10
};

static std::vector<std::vector<std::vector<float>>> jumpTable = {
    {{2,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},  //1
    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},  //2
    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},  //3
    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},  //4
    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},  //5
    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},  //6
    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},  //7
    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},  //8
    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},  //9
};

static QTextStream cin(stdin);

void jump(unsigned index){
    int select = 0, currentSelect = 0;
    unsigned newCondition;
    std::vector<float> selectArray;

    log("Текущее состояние: "+arrayCondition[index]+"\n");
    log("Действия:\n");

    for(unsigned i = 0; i < jumpTable.size(); ++i){
        if(jumpTable[i][index][0] != 0) {
            log(QString::number(select+1) + ". " + arrayInputOutput[i][0]+"\n");
            select++;
            selectArray.push_back(jumpTable[i][index][0]);
        }
    }
    repeatEnter:
    log("Выберите действие: ");
    cin >> currentSelect;

    if(currentSelect < 1 || currentSelect > select){
        log("Неверные входные данные\n");
        goto repeatEnter;
    }

    newCondition = selectArray[currentSelect-1]-1;

    log("\nПереход из состояния \""+arrayCondition[index]+"\" в состояние \""+arrayCondition[newCondition]+"\"\n\n");

    log("------------------------------\n\n");
    jump(newCondition);
}




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    jump(0);
    return a.exec();
}




















