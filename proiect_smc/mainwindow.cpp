#include "mainwindow.h"
#include <string>
#include <regex>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.username->setPlaceholderText("username");
    ui.password->setPlaceholderText("password");
    ui.firstName->setPlaceholderText("first name");
    ui.lastName->setPlaceholderText("last name");

    ui.username_2->setPlaceholderText("username");
    ui.password_2->setPlaceholderText("password");
}

void MainWindow::on_SignUpBtn_clicked()
{
    //Connecting to MySql Database
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("Library.db");

    if (database.open())
    {

        QString username = ui.username->text();
        QString password = ui.password->text();
        QString first_name = ui.firstName->text();
        QString last_name = ui.lastName->text();


        QSqlQuery qry;

        std::regex regexUsername("([A-Z]|[a-z])((-|\\.|@|\\w)*)");
        bool correctUsername = false, usernameLength = false;
        std::string usernameTest = username.toStdString();

        if (std::regex_match(usernameTest, regexUsername))
            correctUsername = true;
        else
            QMessageBox::warning(this, "Username", "Invalid Username!\nThe username must start with a letter and must contain only alphanumeric characters, \"_ \",  \"- \",  \". \" or  \"@ \"");

        if (usernameTest.size() >= 6)
            usernameLength = true;
        else
            QMessageBox::warning(this, "Username", "Invalid Username!\nThe username must contain only alphanumeric characters, \"_ \",  \"- \",  \". \" or \"@\"");

        std::regex regexPassword("(?=.*\\d)(?=.*[a-z])(?=.*[A-Z])");
        bool correctPassword = false, passwordLength = false;
        std::string passwordTest = password.toStdString();

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

        if (correctUsername == true && usernameLength == true && passwordLength == true)
        {

            qry.prepare("INSERT INTO users (username, password, first_name, last_name)"
                "VALUES (:username, :password, :first_name, :last_name)");
            qry.bindValue(":username", username);
            qry.bindValue(":password", password);
            qry.bindValue(":first_name", first_name);
            qry.bindValue(":last_name", last_name);



            if (qry.exec()) {
                QMessageBox::information(this, "Insertion", "Account Created Succesfully!");
                this->close();
                Account dialog(username, password);
                dialog.setModal(true);
                dialog.exec();
            }
            else {
                QMessageBox::warning(this, "Insertion", "Data is not inserted");

            }
        }

    }
    else
    {
        QMessageBox::warning(this, "Conection", "Database not connected");
    }
}

void MainWindow::on_LogInBtn_clicked()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Library.db");

    QString username = ui.username_2->text();
    QString password = ui.password_2->text();

    if (db.open())
    {
        QSqlQuery query;
        query.prepare(QString("SELECT * FROM users WHERE username = :username AND password = :password"));
        query.bindValue(":username", username);
        query.bindValue(":password", password);
        bool ok = false;

        if (!query.exec())
        {
            QMessageBox::warning(this, "Failed", "Query Failed to Execute");
        }
        else
        {

            while (query.next())
            {
                ok = true;
                QMessageBox::information(this, "Succes", "Log In Success");
                this->close();
                Account dialog(username, password);
                dialog.setModal(true);
                dialog.exec();
            }
        }
        if (ok == false)
            QMessageBox::warning(this, "Log In Failed", "Incorrect username or password!");

    }
    else
    {
        QMessageBox::warning(this, "Connection", "Database not connected");
    }

}
