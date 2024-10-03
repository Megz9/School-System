#ifndef VIEWFRAMES_H
#define VIEWFRAMES_H

#include <QMainWindow>

// QT_BEGIN_NAMESPACE
// namespace Ui { class MainWindow; }
// QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString mGetInputLoginEmail();
    QString mGetInputLoginPassword();
    QString mGetInputRegisterEmail();
    QString mGetInputRegisterFirstName();
    QString mGetInputRegisterLastName();
    QString mGetInputRegisterPassword();
    int     mGetInputRegisterAge();
    bool    mGetInputRegisterGender();
    QString mGetInputRegisterAddress();
    QString mGetInputRegisterRegisteredCourse();
    QString mGetInputRegisterTeacherCourse();
    QString mGetInputRegisterBackground();
    void mShowStudentFrame(QString email, QString firstName);
    void mShowTeacherFrame(QString email, QString firstName);
    void mShowInsertState(bool state);//register
    void mShowLoginState(bool state);
    // void mLoadUsersGui(QMap<QString,QString> xEmployees);

// private slots:
//     void on_LoginButton_clicked();

//     void on_LogoutPB_clicked();

//     void on_AddUserPB_clicked();

private:
//     // Ui::MainWindow * ui;
    // QString dCurrentUserEmail;

    void mCreateGui();

// signals:
//     void LoginAttempt();
//     void AddNewUserAttempt();
};

#endif // VIEWFRAMES_H
