#include "viewframes.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{


    mCreateGui();
}
void MainWindow::mCreateGui(){
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QLabel *emailLabel = new QLabel("Email:",this);
    QLineEdit *emailInput = new QLineEdit(this);
    QLabel *passwordLabel = new QLabel("Password:",this);
    QLineEdit *passwordInput = new QLineEdit(this);
    //passwordInput->setEchoMode(QLineEdit::Password); // Hide password input

    QPushButton *loginButton = new QPushButton("Login",this);

    mainLayout->addWidget(emailLabel);
    mainLayout->addWidget(emailInput);
    mainLayout->addWidget(passwordLabel);
    mainLayout->addWidget(passwordInput);
    mainLayout->addWidget(loginButton);

    setCentralWidget(centralWidget);
}
MainWindow::~MainWindow()
{
}
