#ifndef MODEL_H
#define MODEL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QFile>
#include <QDebug>
class model
{
private:
    QSqlDatabase mDatabase;
    model(const QString& _dbPath);
    static model* mModel;
    void createTables();
    bool executeQuery(QSqlQuery query);
public:
    static model* getInstance(const QString& _dbPath);
    bool authenticateUser(QString _email, QString _password);
    bool insertStudent(QString firstName, QString lastName, QString email, QString password, QString gender, qint16 age, QString registeredCourse);
    bool insertTeacher(QString firstName, QString lastName, QString email, QString password, QString gender, qint16 age, QString course, QString background, QString address);
    bool insertPerson(QString firstName, QString lastName, QString email, QString password,QString gender, qint16 age );

    QString mGetName(QString email);
};

#endif // MODEL_H
