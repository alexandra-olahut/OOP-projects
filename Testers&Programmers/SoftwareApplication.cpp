#include "SoftwareApplication.h"
#include "Exception.h"

#include <qlineedit.h>
#include <qgridlayout.h>
#include <qmessagebox.h>

SoftwareApplication::SoftwareApplication(Controller& controller, User user, QWidget *parent)
    : QMainWindow(parent), controller(controller), user(user)
{
    ui.setupUi(this);

    this->removeButton = new QPushButton{ "Remove" };
    this->addButton = new QPushButton{ "Add" };
    this->resolveButton = new QPushButton{ "Resolve" };
    this->descrLineEdit = new QLineEdit{};

    this->ui.verticalLayout->addWidget(this->removeButton);
    if (user.getType() == "tester")
    {
        QGridLayout* addLayout = new QGridLayout{};
        addLayout->addWidget(this->descrLineEdit, 0, 0);
        addLayout->addWidget(this->addButton, 0, 1);
        this->ui.verticalLayout->addLayout(addLayout);
    }
    else
    {
        this->ui.verticalLayout->addWidget(this->resolveButton);
    }

    this->setWindowTitle(QString::fromStdString(user.getName() + " - " + user.getType()));
    this->populateIssues();
    this->connections();

}

void SoftwareApplication::populateIssues()
{
    this->ui.issues_listWidget->clear();
    std::vector<Issue> issues = this->controller.getIssuesSorted();

    for (auto issue : issues)
    {
        this->ui.issues_listWidget->addItem(QString::fromStdString(issue.toString()));
    }
}

int SoftwareApplication::getSelected()
{
    QModelIndexList selected_indexes = this->ui.issues_listWidget->selectionModel()->selectedIndexes();
    int selected_index = selected_indexes.at(0).row();
    return selected_index;
}

Issue SoftwareApplication::getSelectedIssue()
{
    int index = getSelected();
    return this->controller.getIssuesSorted()[index];
}

void SoftwareApplication::connections()
{
    QObject::connect(this->removeButton, &QPushButton::clicked, this, &SoftwareApplication::removeIssue);
    QObject::connect(this->addButton, &QPushButton::clicked, this, &SoftwareApplication::addIssue);
    QObject::connect(this->resolveButton, &QPushButton::clicked, this, &SoftwareApplication::resolveIssue);

    QObject::connect(this->ui.issues_listWidget, &QListWidget::itemClicked, this, &SoftwareApplication::checkClicked);
}

void SoftwareApplication::removeIssue()
{
    Issue issue = getSelectedIssue();

    if (issue.getStatus() == "open")
    {
        QMessageBox::critical(this, "Error", "Issue must be resolved");
        return;
    }

    this->controller.removeIssue(issue);
}

void SoftwareApplication::addIssue()
{
    if (this->descrLineEdit->text().isEmpty())
    {
        QMessageBox::critical(this, "Error", "Please provide description");
        return;
    }
    std::string descr = this->descrLineEdit->text().toStdString();
    try
    {
        this->controller.addIssue(descr, this->user.getName());
    }
    catch (Exceptions& ex)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(ex.get_message()));
    }
}

void SoftwareApplication::resolveIssue()
{
    Issue issue = getSelectedIssue();
    this->controller.resolveIssue(issue, this->user.getName());
}

void SoftwareApplication::checkClicked(QListWidgetItem* item)
{
    Issue issue = getSelectedIssue();
    //if (issue.getStatus() == "open")
    //    this->removeButton->setDisabled(true);
    //else
    //    this->removeButton->setDisabled(false);

    if (issue.getStatus() == "open")
        this->resolveButton->setDisabled(false);
    else
        this->resolveButton->setDisabled(true);
}
