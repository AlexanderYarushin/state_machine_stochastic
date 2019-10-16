#include <QCoreApplication>

#include "lib.cpp"

static std::vector<std::vector<QString>> arrayInputOutput  = {
    {"Пойти на экзамен",""},
    {"Попытаться сесть вперед",""},
    {"Попытаться сесть назад",""},
};

static std::vector<QString> arrayCondition = {
    {"Начало"},
    {"Прибытие на экзамен"},                            //1
    {"Усаживание на переднюю парту"},                    //2
    {"Усаживание на последнюю парту"},                    //3
    {"Доставание шпаргалки"},            //4
    {"Списывание"},                    //5
    {"Ответ по билету"},                    //6
    {"Подглядывание в телефон"},            //7
    {"Упрашивание преподавателя о тройке"},
    {"Экзамен сдан"},
    {"Экзамен не сдан"}
};

static std::vector<std::vector<unsigned>> jumpTable = {
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  //1
    {0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  //2
    {0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  //3
    {0,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
    {0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0},  //5
    {0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0},  //6
    {0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0},  //7
    {0,0,0,0,0,11,0,0,0,0,0,0,0,0,0,0,0}, //8
    {0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0},  //9
    {0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0},  //10
    {0,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0}, //11
    {0,0,0,0,0,0,0,0,11,0,0,0,0,0,0,0,0}, //12
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},  //13
    {0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0}, //14
    {0,0,0,0,0,0,0,0,0,0,13,0,0,0,0,0,0}, //15
    {0,0,0,0,0,0,0,0,0,0,14,0,0,0,0,0,0}, //16
    {0,0,0,0,0,0,0,0,0,0,0,11,0,0,0,0,0}, //17
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,0}, //18
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11}, //19
    {0,0,0,0,0,0,0,0,0,0,0,0,16,0,0,0,0}, //20
    {0,0,0,0,0,0,0,0,0,0,0,0,0,15,0,0,0}, //21
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,0,0}, //22
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},  //23
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},  //24
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},  //25
};

static QTextStream cin(stdin);

void jump(unsigned index){
    int select = 0, currentSelect = 0;
    unsigned newCondition;
    std::vector<unsigned> selectArray;
    std::vector<unsigned> outputArray;

    log("Текущее состояние: "+arrayCondition[index]+"\n");
    log("Действия:\n");

    for(unsigned i = 0; i < jumpTable.size(); ++i){
        if(jumpTable[i][index] != 0) {
            log(QString::number(select+1) + ". " + arrayInputOutput[i][0]+"\n");
            select++;
            selectArray.push_back(jumpTable[i][index]);
            outputArray.push_back(i);
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

    log("\nПереход из состояния \""+arrayCondition[index]+"\" в состояние \""+arrayCondition[newCondition]+"\"\n");
    if(arrayInputOutput[outputArray[currentSelect-1]][1].length() > 0)
        log("Выходные данные: "+arrayInputOutput[outputArray[currentSelect-1]][1]+"\n\n");
    else
        log("\n");

    log("------------------------------\n\n");
    jump(newCondition);
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    jump(0);
    return a.exec();
}




















