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

	void on_action_file_save_as_triggered();

	void on_action_edit_copy_triggered();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
