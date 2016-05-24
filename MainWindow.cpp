#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <stdint.h>
#include <QDebug>
#include <QTimer>
#include "opencv2/opencv.hpp"

#ifdef _WIN32
#ifdef QT_NO_DEBUG
#pragma comment(lib, "opencv_core2413.lib")
#pragma comment(lib, "opencv_highgui2413.lib")
#else
#pragma comment(lib, "opencv_core2413d.lib")
#pragma comment(lib, "opencv_highgui2413d.lib")
#endif
#endif

struct MainWindow::Private {
	cv::VideoCapture cap;
	QTimer timer;
};

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	pv = new Private();
	ui->setupUi(this);

	pv->cap.open(0);

	connect(&pv->timer, SIGNAL(timeout()), this, SLOT(doCapture()));
	pv->timer.setInterval(0);
	pv->timer.start();
}

MainWindow::~MainWindow()
{
	pv->cap.release();
	delete pv;
	delete ui;
}

void MainWindow::doCapture()
{
	if (pv->cap.isOpened()) {
		cv::Mat frame;
		pv->cap.read(frame);
		if (frame.dims == 2 && frame.channels() == 3) {
			int w = frame.cols;
			int h = frame.rows;
			setFixedSize(w, h);
			ui->widget->setFixedSize(w, h);
			QImage image(w, h, QImage::Format_ARGB32);
			for (int i = 0; i < h; i++) {
				uint8_t *src = frame.ptr(i);
				QRgb *dst = (QRgb *)image.scanLine(i);
				for (int j = 0; j < w; j++) {
					dst[j] = qRgb(src[2], src[1], src[0]);
					src += 3;
				}
			}
			ui->widget->setImage(image);
		}
	}
}
