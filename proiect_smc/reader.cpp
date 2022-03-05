#include "reader.h"

Reader::Reader(const QString& username, const QString& password, QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->username = username;
	this->password = password;
}

Reader::~Reader()
{
}

void Reader::on_returnBtn_clicked()
{
	this->close();
	BorrowedBooks dialog(username,password);
	dialog.setModal(true);
	dialog.exec();
}