#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
private:
	struct Private;
	Private *pv;
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:

	void doCapture();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
