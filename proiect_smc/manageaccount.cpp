#include "manageaccount.h"
#include"account.h"
#include<qinputdialog.h>
#include"mainwindow.h"
#include <regex>
#include<QDialog>
ManageAccount::ManageAccount(const QString& username, const QString& password, QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    this->username = username;
    this->password = password;
}

ManageAccount::~ManageAccount()
{
}

void ManageAccount::on_backBtn_clicked()
{
    this->close();
    Account dialog(username, password);
    dialog.setModal(true);
    dialog.exec();
}

void ManageAccount::on_deleteBtn_clicked()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Library.db");

    if (db.open())
    {
        QSqlQuery query, qry;
        QString insertedPassword = QInputDialog::getText(this, "Deleting account", "Insert your password");
        query.prepare(QString("SELECT password FROM users WHERE password = :password"));
        query.bindValue(":password", insertedPassword);
        if (insertedPassword == password)
        {
            query.prepare(QString("DELETE FROM users WHERE username = :username AND password = :password;"));
            query.bindValue(":username", username);
            query.bindValue(":password", password);

            if (!query.exec())
            {
                QMessageBox::warning(this, "Failed", "Query Failed to Execute");
            }
            else
            {
                QMessageBox::information(this, "Succes", "Deleted Account");
                this->close();
                MainWindow w;
                w.show();
            }
        }
        else
        {
            QMessageBox::warning(this, "Failed", "Wrong password");
        }
    }
    else
    {
        QMessageBox::warning(this, "Connection", "Database not connected");
    }
}

void ManageAccount::on_changeBtn_clicked()
{
    QString newPassword = QInputDialog::getText(this, "New Password", "Add New Password");

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Library.db");

    if (db.open())
    {
        QSqlQuery query;
        std::regex regexPassword("(?=.*\\d)(?=.*[a-z])(?=.*[A-Z])");
        bool correctPassword = false, passwordLength = false;
        std::string passwordTest = newPassword.toStdString();

        if (std::regex_search(passwordTest, regexPassword))
            correctPassword = true;
        else
            QMessageBox::warning(this, "Password", "Invalid Password!\nThe password must contain at least an uppercase letter, a lowercase letter and a digit!");
        if (correctPassword == true)
        {
            if (passwordTest.size() < 8)
                QMessageBox::warning(this, "Password", "Password too weak!");
            else if (passwordTest.size() >= 8 && passwordTest.size() < 12)
            {
                QMessageBox::information(this, "Password", "Medium password");
                passwordLength = true;
            }
            else
            {
                QMessageBox::information(this, "Password", "Strong password");
                passwordLength = true;
            }
        }

        if (passwordLength == true)
        {
            query.prepare(QString("UPDATE users SET password = :newPassword WHERE username = :username;"));
            query.bindValue(":username", username);
            query.bindValue(":newPassword", newPassword);

            if (!query.exec())
            {
                QMessageBox::warning(this, "Failed", "Query Failed to Execute");
            }
            else
            {
                password = newPassword;
                QMessageBox::information(this, "Succes", "Password Modified");
                this->close();
                Account dialog(username, password);
                dialog.setModal(true);
                dialog.exec();
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "Connection", "Database not connected");
    }
}