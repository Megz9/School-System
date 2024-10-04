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
                               "type TEXT,"
                               "email TEXT UNIQUE,"
                               "password TEXT,"
                               "gender TEXT,"
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
    insertPerson("Administrator","Account","admin","admin","male",23,"admin");
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
bool model::authenticateUser(QString _email, QString _password){
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
bool model::insertPerson(QString firstName, QString lastName, QString email, QString password,QString gender, qint16 age, QString type="admin"){
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO employees (first_name, last_name, email, password, gender, age, type)"
                  "VALUES (:firstname, :lastname, :email, :password, :gender, :age, :type);");
    query.bindValue(":firstname", firstName);
    query.bindValue(":lastname", lastName);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.bindValue(":gender", gender);
    query.bindValue(":age", age);
    query.bindValue(":type", type);
    try {
        success = executeQuery(query);
    } catch (std::runtime_error e){
        qWarning() << "ERROR: " << mDatabase.lastError().text();
    }
    return success;
}

bool model::insertStudent(QString firstName, QString lastName, QString email, QString password, QString gender, qint16 age, QString registeredCourse){
    bool success = insertPerson(firstName, lastName, email, password, gender, age,"student");
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
    bool success = insertPerson(firstName, lastName, email, password, gender, age,"teacher");
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

bool model::deletePerson(QString email) {
    QSqlQuery query;
    query.prepare("DELETE FROM employees WHERE email = (:email)");
    query.bindValue(":email", email);
    return executeQuery(query);
}

bool model::modifyPerson(QString email, QString firstName, QString lastName, QString password, QString gender, qint16 age) {
    QSqlQuery query;
    query.prepare("UPDATE employees SET first_name = :first_name, last_name = :last_name, password = :password, gender = :gender, age = :age WHERE email = :email");
    query.bindValue(":first_name", firstName);
    query.bindValue(":last_name", lastName);
    query.bindValue(":password", password);
    query.bindValue(":gender", gender);
    query.bindValue(":age", age);
    query.bindValue(":email", email);
    return executeQuery(query);
}

// bool model::addSubject(QString subjectName) {
//     QSqlQuery query;
//     query.prepare("INSERT INTO subjects (name) VALUES (:name)");
//     query.bindValue(":name", subjectName);
//     return executeQuery(query);
// }

QList<QMap<QString, QString>> model::getAssignedStudents(QString course) {
    QSqlQuery query;
    query.prepare("SELECT students.student_id, employees.first_name, employees.last_name, students.registered_course FROM students INNER JOIN employees ON students.employee_id = employees.id WHERE students.registered_course = (:course)");
    query.bindValue(":course", course);
    query.exec();

    QList<QMap<QString, QString>> studentList;
    while (query.next()) {
        QMap<QString, QString> student;
        student["student_id"] = query.value(0).toString();
        student["first_name"] = query.value(1).toString();
        student["last_name"] = query.value(2).toString();
        student["registered_course"] = query.value(3).toString();
        studentList.append(student);
    }
    return studentList;
}

bool model::registerForCourse(QString email, QString course) {
    QSqlQuery query;
    query.prepare("UPDATE students SET registered_course = :course WHERE employee_id = (SELECT id FROM employees WHERE email = :email)");
    query.bindValue(":course", course);
    query.bindValue(":email", email);
    return executeQuery(query);
}

QString model::mGetName(QString email){
    QSqlQuery query;
    query.prepare("SELECT first_name FROM employees WHERE email = (:email)");
    query.bindValue(":email", email);

    if (query.exec() && query.next()) {
        return query.value(0).toString();  // Return the first name
    }
    return QString();
}


QString model::mGetType(QString email){
    QSqlQuery query;
    query.prepare("SELECT type FROM employees WHERE email = (:email)");
    query.bindValue(":email", email);

    if (query.exec() && query.next()) {
        return query.value(0).toString();  // Return the type
    }
    return QString();
}
