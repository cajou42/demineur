#pragma once
#include <QLabel>
#include <QPushButton>
class Cases:QPushButton
{
	Q_OBJECT

public :
	Cases();
	~Cases();
	void markcase(QMouseEvent* event);

private :
	QPushButton* button;
	QLabel* labels;
};

