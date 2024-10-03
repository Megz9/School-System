#include "controller.h"

controller::controller(MainWindow* view, model* xModel){
    dmodel =xModel;
    dview = view;
    mRegisterSignals();

}

void controller::mRegisterSignals()
{
    //TODO:: connect login attempt and add new user attempts to slots
}

void controller::mAttemptLoginAndRedirect()
{
    //TODO:: Implement this function
}

void controller::mAttemptAddingEmployee()
{
    //TODO:: Implement this function
}
