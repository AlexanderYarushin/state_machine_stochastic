#include <QCoreApplication>
#include <ctime>
#include <QTextStream>
#include <QTextCodec>
#include <QTime>

#include "lib.cpp"

void log(const QString text){
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM 866"));
    QTextStream cout(stdout);
    cout << text;
}

static std::vector<QString> arrayInput{
    {"Пойти на экзамен"},                            //1
    {"Попытаться сесть вперед"},                     //2
    {"Попытаться сесть назад"},                      //3
    {"Попытаться достать шпаргалку"},                //4
    {"Попытаться списать"},                          //5
    {"Пойти отвечать по билету"},                    //6
    {"При ответе попытаться подглядеть в телефоне"}, //7
    {"Попросить преподавателя о тройке"},            //8
    {"Закончить ответ"},                             //9
    {"Выйти из аудитории"},                             //9
};

static std::vector<QString> arrayCondition{
    {"Начало"},                             //1
    {"Прибытие на экзамен"},                //2
    {"Усаживание на переднюю парту"},       //3
    {"Усаживание на последнюю парту"},      //4
    {"Доставание шпаргалки"},               //5
    {"Списывание"},                         //6
    {"Ответ по билету"},                    //7
    {"Подглядывание в телефон"},            //8
    {"Упрашивание преподавателя о тройке"}, //9
    {"Экзамен сдан"},                       //10
    {"Экзамен не сдан"}                     //11
};

static std::vector<std::vector<std::vector<double>>> jumpTable {
    {{2,1},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0},{10,0},{11,0}},          //1
    {{1,0},{3,0.7},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0},{10,0},{11,0}},        //2
    {{1,0},{4,0.3},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0},{10,0},{11,0}},        //3
    {{1,0},{2,0},{5,0.2},{5,0.3},{5,0},{6,0},{7,0},{8,0},{9,0},{10,0},{11,0}},      //4
    {{1,0},{2,0},{3,0},{4,0},{6,0.9},{6,0},{7,0},{8,0},{9,0},{10,0},{11,0}},        //5
    {{1,0},{2,0},{7,0.8},{7,0.7},{5,0},{7,0.9},{7,0},{7,0},{7,0},{10,0},{11,0}},    //6
    {{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{8,0.1},{8,0},{9,0},{10,0},{11,0}},        //7
    {{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{9,0.6},{9,0.2},{9,0},{10,0},{11,0}},      //8
    {{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{10,0.9},{10,0.3},{10,0.9},{0,0},{0,0}}, //9
    {{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{7,0},{8,0},{1,1},{1,1}},          //10
};

static QTextStream cin(stdin);

void jump(unsigned index){
    srand(time(nullptr));
    double rnd = (rand() % 100);
    rnd /= 100;
    int select = 0, currentSelect = 0;
    unsigned newCondition;
    std::vector<double> selectArray;
    std::vector<double> probability;

    log("Текущее состояние: "+arrayCondition[index]+"\n");
    log("Действия:\n");

    for(unsigned i = 0; i < jumpTable.size(); ++i){
        if((index+1) != jumpTable[i][index][0]) {
            log(QString::number(select+1) + ". " + arrayInput[i]+ " / P = " + QString::number(jumpTable[i][index][1]) + "\n");
            select++;
            selectArray.push_back(jumpTable[i][index][0]);
            probability.push_back(jumpTable[i][index][1]);
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

    if(newCondition == 9) if(rnd > 0.5) newCondition = 10;

    if(probability[currentSelect-1] > rnd){

        log("\nПереход из состояния \""+arrayCondition[index]+"\" в состояние \""+arrayCondition[newCondition]+"\"\n\n");

        log("------------------------------\n\n");

        jump(newCondition);
    }else{
        log("\nПереход из состояния \""+arrayCondition[index]+"\" в состояние \""+arrayCondition[newCondition]+" не удался\"\n\n");
        jump(index);
    }
}




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    jump(0);
    return a.exec();
}




















