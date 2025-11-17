#pragma once
#include <QtWidgets/QtWidgets>

#include "GeneratedFiles/ui_binexport_class.h"
#include "all_include.h"




class BinExportClass : public QWidget {
	Q_OBJECT

public:
	BinExportClass(QWidget * parent = Q_NULLPTR);
	~BinExportClass();

private:
	Ui::BinExportClass ui;

	private slots:
	/**
	* \brief \n Определяет функцию выполняющую бинарный экспорт в файл ...
	*/
	void binary_export();
	/**
	* \brief \n Определяет функцию выполняющую текстовый экспорт в файл ...
	*/
	void text_export();
	/**
	* \brief \n Определяет функцию выполняющую экспорт статистики в текстовый файл ...
	*/
	void statistic_export();

	
};
