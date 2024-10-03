#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "model.h"
#include "viewFrames.h"
class controller : public QObject
{
    Q_OBJECT
public:
    controller(MainWindow* view, model* xModel);
private:
    MainWindow* dview;
    model* dmodel;
private slots:
    void mAttemptLoginAndRedirect();
    void mAttemptAddingEmployee();
    void mRegisterSignals();
};

#endif // CONTROLLER_H
