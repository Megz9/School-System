#include "controller.h"

controller::controller(MainWindow* view, model* xModel){
    dmodel =xModel;
    dview = view;
    mRegisterSignals();

}

void controller::mRegisterSignals()
{
    //TODO:: connect login attempt and add new user attempts to slots
    connect(dview->loginButton, &QPushButton::clicked,this, &controller::mAttemptLoginAndRedirect);
    connect(dview->studentsButton, &QPushButton::clicked, this, &controller::mAttemptAddingStudent);
    connect(dview->teachersButton, &QPushButton::clicked, this, &controller::mAttemptAddingTeacher);
    //     connect(subjectsButton, &QPushButton::clicked, this, &MainWindow::loadSubjectsData);
}

void controller::mAttemptLoginAndRedirect()
{
    //TODO:: Implement this function
    if(dmodel->authenticateUser(dview->mGetInputLoginEmail(),dview->mGetInputLoginPassword())){
        QString type = dmodel->mGetType(dview->mGetInputLoginEmail());
        QString Fname = dmodel->mGetName(dview->mGetInputLoginEmail());
        if(type == "student"){
            dview->mShowStudentFrame(dview->mGetInputLoginEmail(),Fname);
        }else if(type == "teacher"){
            dview->mShowTeacherFrame(dview->mGetInputLoginEmail(),Fname);
        }else if(type == "admin"){
            dview->mLoadAdminGui();
        }

    }else{
        dview->mShowLoginState(false);
    }

}

void controller::mAttemptAddingStudent()
{
    //TODO:: Implement this function
    if(!dmodel  || !dview)
        return;
    QString Email = dview->mGetInputRegisterEmail();
    QString Password = dview->mGetInputRegisterPassword();
    QString Fname = dview->mGetInputRegisterFirstName();
    QString Lname = dview->mGetInputRegisterLastName();
    qint16 Age = dview->mGetInputRegisterAge();
    QString Gender = dview->mGetInputRegisterGender();
    QString Course = dview->mGetInputRegisterRegisteredCourse();

    bool success = dmodel->insertStudent(Fname, Lname,Email,Password,Gender,Age,Course);

    // dview->mLoadStudentsGui()
    dview->mShowInsertState(success);
}

void controller::mAttemptAddingTeacher()
{
    //TODO:: Implement this function
    if(!dmodel  || !dview)
        return;
    QString Email = dview->mGetInputRegisterEmail();
    QString Password = dview->mGetInputRegisterPassword();
    QString Fname = dview->mGetInputRegisterFirstName();
    QString Lname = dview->mGetInputRegisterLastName();
    qint16 Age = dview->mGetInputRegisterAge();
    QString Gender = dview->mGetInputRegisterGender();
    QString Course = dview->mGetInputRegisterTeacherCourse();
    QString Address = dview->mGetInputRegisterAddress();
    QString Background = dview->mGetInputRegisterBackground();

    bool success = dmodel->insertTeacher(Fname, Lname,Email,Password,Gender,Age,Course,Background,Address);

    // dview->mLoadTeachersGui()
    dview->mShowInsertState(success);
}

// void controller::mAttemptDeletePerson() {
//     QString email = dview->mGetDeleteEmail();
//     bool success = dmodel->deletePerson(email);
//     dview->mShowDeleteState(success);
// }

// void controller::mAttemptModifyPerson() {
//     QString email = dview->mGetInputModifyEmail();
//     QString firstName = dview->mGetInputModifyFirstName();
//     QString lastName = dview->mGetInputModifyLastName();
//     QString password = dview->mGetInputModifyPassword();
//     QString gender = dview->mGetInputModifyGender();
//     qint16 age = dview->mGetInputModifyAge();

//     bool success = dmodel->modifyPerson(email, firstName, lastName, password, gender, age);
//     dview->mShowModifyState(success);
// }
// void controller::mViewAssignedStudents() {
//     QString course = dmodel->getTeacherCourse(dview->mGetLoggedInEmail());
//     QList<QMap<QString, QString>> students = dmodel->getAssignedStudents(course);
//     dview->mLoadStudentsGui(students);
// }

// void controller::mAttemptRegisterCourse() {
//     QString course = dview->mGetInputCourse();
//     QString email = dview->mGetLoggedInEmail();
//     bool success = dmodel->registerForCourse(email, course);
//     dview->mShowRegisterCourseState(success);
// }

// void controller::mAttemptAddSubject() {
//     QString subjectName = dview->mGetInputSubjectName();
//     bool success = dmodel->addSubject(subjectName);
//     dview->mShowAddSubjectState(success);
// }
