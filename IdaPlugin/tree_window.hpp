#pragma once
#include <QtWidgets/QtWidgets>
#include "ui_tree_window.h"

class TreeWindow : public QWidget {
	Q_OBJECT

public:
	TreeWindow(QWidget * parent = Q_NULLPTR);
	~TreeWindow();

private:
	Ui::TreeWindow ui;
};
