#include "account.h"

Account::Account(const QString& username, const QString& password, QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->username = username;
	this->password = password;
}

void Account::on_mybooksBtn_clicked()
{
	this->close();
	BorrowedBooks dialog(username, password);
	dialog.setModal(true);
	dialog.exec();
}

Account::~Account()
{

}

void Account::on_borrowBtn_clicked()
{
	this->close();
	Borrow dialog(username, password);
	dialog.setModal(true);
	dialog.exec();
}


void Account::on_SignOutBtn_clicked()
{
		this->close();
}

void Account::on_manageBtn_clicked()
{
	this->close();
	ManageAccount dialog(username, password);
	dialog.setModal(true);
	dialog.exec();
}