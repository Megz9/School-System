#include "model.h"

model * model::mModel = nullptr;

// QSqlDatabase mDatabase;

bool model::executeQuery(QSqlQuery query){
    bool success = true;
    if(!query.exec()){
        success = false;
    }
    return success;
}
void model::createTables(){
    if(!mDatabase.tables().contains(QLatin1String("employees"))){
        executeQuery(QSqlQuery("CREATE TABLE employees ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "first_name TEXT,"
                               "last_name TEXT,"
                               "email TEXT UNIQUE,"
                               "password TEXT,"
                               "gender BOOL,"
                               "age INTEGER"
                               ");"));
    }
    if(!mDatabase.tables().contains(QLatin1String("students"))){
        executeQuery(QSqlQuery("CREATE TABLE students ("
                               "student_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "employee_id INTEGER,"
                               "registered_course TEXT,"
                               "FOREIGN KEY (employee_id) REFERENCES employees(id) ON DELETE CASCADE"
                               ");"));
    }

    if(!mDatabase.tables().contains(QLatin1String("teachers"))){
        executeQuery(QSqlQuery("CREATE TABLE teachers ("
                               "teacher_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "employee_id INTEGER,"
                               "course TEXT,"
                               "background TEXT,"
                               "address TEXT,"
                               "FOREIGN KEY (employee_id) REFERENCES employees(id) ON DELETE CASCADE"
                               ");"));
    }
    //insert admin
    insertPerson("Administrator","Account","admin","admin","male",23);
}


model* model::getInstance(const QString& _dbPath){
    if(mModel == nullptr){
        mModel = new model(_dbPath);
    }
    return mModel;

}

model::model(const QString& _dbPath){
    const QString DRIVER("QSQLITE");
    if(QSqlDatabase::isDriverAvailable(DRIVER)){
        mDatabase = QSqlDatabase::addDatabase(DRIVER);
        mDatabase.setDatabaseName(_dbPath);
        if(!mDatabase.open()){
            qWarning() << "ERROR: " << mDatabase.lastError().text();
        }else{
            createTables();
        }
    }
}
bool authenticateUser(QString _email, QString _password){
    QSqlQuery authQuery;
    authQuery.prepare("SELECT email from employees WHERE email = (:_email) AND password = (:_password)");
    authQuery.bindValue(":email", _email);
    authQuery.bindValue(":password", _password);

    if(authQuery.exec()){
        if(authQuery.next()){
            return true;
        }
    }
    return false;
}
bool model::insertPerson(QString firstName, QString lastName, QString email, QString password,QString gender, qint16 age){
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO employees (first_name, last_name, email, password, gender, age)"
                  "VALUES (:firstname, :lastname, :email, :password, :gender, :age);");
    query.bindValue(":firstname", firstName);
    query.bindValue(":lastname", lastName);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.bindValue(":gender", gender);
    query.bindValue(":age", age);
    try {
        success = executeQuery(query);
    } catch (std::runtime_error e){
        qWarning() << "ERROR: " << mDatabase.lastError().text();
    }
    return success;
}

bool model::insertStudent(QString firstName, QString lastName, QString email, QString password, QString gender, qint16 age, QString registeredCourse){
    bool success = insertPerson(firstName, lastName, email, password, gender, age);
    QSqlQuery query;
    try {
        success = executeQuery(query);
        if(success){
            int employeeId = query.lastInsertId().toInt();
            QSqlQuery studentQuery;
            studentQuery.prepare("INSERT INTO students (employee_id, registered_course) "
                                 "VALUES (:employee_id, :registered_course);");
            studentQuery.bindValue(":employee_id", employeeId);
            studentQuery.bindValue(":registered_course", registeredCourse);
            success = executeQuery(studentQuery);
        }
    } catch (std::runtime_error e){
        qWarning() << "ERROR: " << mDatabase.lastError().text();
    }
    return success;
}
bool model::insertTeacher(QString firstName, QString lastName, QString email, QString password, QString gender, qint16 age, QString course, QString background, QString address){
    bool success = insertPerson(firstName, lastName, email, password, gender, age);
    QSqlQuery query;
    query.prepare("INSERT INTO employees (first_name, last_name, email, password, gender, age)"
                  "VALUES (:firstname, :lastname, :email, :password, :gender, :age);");
    query.bindValue(":firstname", firstName);
    query.bindValue(":lastname", lastName);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.bindValue(":gender", gender);
    query.bindValue(":age", age);


    try {
        success = executeQuery(query);
        if (success) {
            // Get the last inserted employee ID
            int employeeId = query.lastInsertId().toInt();

            // Insert teacher-specific data into teachers table
            QSqlQuery teacherQuery;
            teacherQuery.prepare("INSERT INTO teachers (employee_id, course, background, address) "
                                 "VALUES (:employee_id, :course, :background, :address);");
            teacherQuery.bindValue(":employee_id", employeeId);
            teacherQuery.bindValue(":course", course);
            teacherQuery.bindValue(":background", background);
            teacherQuery.bindValue(":address", address);
            success = executeQuery(teacherQuery);
        }
    } catch (std::runtime_error e){
        qWarning() << "ERROR: " << mDatabase.lastError().text();
    }
    return success;
}
QString mGetName(QString email){
    QSqlQuery query;
    query.prepare("SELECT first_name FROM employees WHERE email = (:email)");
    query.bindValue(":email", email);

    if (query.exec() && query.next()) {
        return query.value(0).toString();  // Return the first name
    }
    return QString();
}
