#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SoftwareApplication.h"
#include <qpushbutton.h>

#include "Controller.h"
#include "Domain.h"
#include "Observer.h"

class SoftwareApplication : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    SoftwareApplication(Controller& controller, User user, QWidget *parent = Q_NULLPTR);

private:
    Ui::SoftwareApplicationClass ui;

    Controller& controller;
    User user;

    QPushButton* removeButton;
    QPushButton* addButton;
    QPushButton* resolveButton;
    QLineEdit* descrLineEdit;

    void populateIssues();
    int getSelected();
    Issue getSelectedIssue();
    void connections();

    void removeIssue();
    void addIssue();
    void resolveIssue();

    void checkClicked(QListWidgetItem* item);

public:
    void update() override { this->populateIssues(); }
};
