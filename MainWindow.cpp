#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <stdint.h>
#include <QDebug>
#include <QTimer>
#include <QFileDialog>
#include <QClipboard>
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

// solution 1: use cv::VideoCapture
class Capture1 {
private:
	cv::VideoCapture cap;
public:
	void open()
	{
		close();
		cap.open(0);
	}
	void close()
	{
		cap.release();
	}
	bool isOpened() const
	{
		return cap.isOpened();
	}
	QImage capture()
	{
		if (isOpened()) {
			cv::Mat frame;
			cap.read(frame);
			if (frame.dims == 2 && frame.channels() == 3) {
				int w = frame.cols;
				int h = frame.rows;
				QImage image(w, h, QImage::Format_RGB32);
				for (int i = 0; i < h; i++) {
					uint8_t const *src = frame.ptr(i);
					QRgb *dst = (QRgb *)image.scanLine(i);
					for (int j = 0; j < w; j++) {
						dst[j] = qRgb(src[2], src[1], src[0]);
						src += 3;
					}
				}
				return image;
			}
		}
		return QImage();
	}
};

// solution 2: use CvCapture
#if 0
class Capture2 {
private:
	CvCapture *cap = nullptr;
public:
	void open()
	{
		close();
		cap = cvCreateCameraCapture(0);
	}
	void close()
	{
		if (isOpened()) {
			cvReleaseCapture(&cap);
			cap = nullptr;
		}
	}
	bool isOpened() const
	{
		return cap != nullptr;
	}
	QImage capture()
	{
		if (isOpened()) {
			cvQueryFrame(cap);
			IplImage *iplimage = cvQueryFrame(cap);
			int w = iplimage->width;
			int h = iplimage->height;
			QImage image(w, h, QImage::Format_RGB32);
			for (int i = 0; i < h; i++) {
				uint8_t const *src = (uint8_t const *)iplimage->imageData + i * w * 3;
				QRgb *dst = (QRgb *)image.scanLine(i);
				for (int j = 0; j < w; j++) {
					dst[j] = qRgb(src[2], src[1], src[0]);
					src += 3;
				}
			}
			return image;
		}
		return QImage();
	}
};
#endif

struct MainWindow::Private {
	Capture1 cap;
//	Capture2 cap;
	QTimer timer;
};

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	pv = new Private();
	ui->setupUi(this);

	pv->cap.open();

	connect(&pv->timer, SIGNAL(timeout()), this, SLOT(doCapture()));
	pv->timer.setInterval(0);
	pv->timer.start();
}

MainWindow::~MainWindow()
{
	pv->cap.close();
	delete pv;
	delete ui;
}

void MainWindow::doCapture()
{
	QImage image = pv->cap.capture();
	int w = image.width();
	int h = image.height();
	if (w > 0 && h > 0) {
		setFixedSize(w, h);
		ui->widget->setFixedSize(w, h);
		ui->widget->setImage(image);
	}
}

void MainWindow::on_action_file_save_as_triggered()
{
	QString path = QFileDialog::getSaveFileName(this, tr("Save as"), QString(), "JPEG files (*.jpg);;PNG files (*.png)");
	if (path.isEmpty()) return;

	QImage image = ui->widget->getImage();
	image.save(path);
}

void MainWindow::on_action_edit_copy_triggered()
{
	QImage image = ui->widget->getImage();
	qApp->clipboard()->setImage(image);
}
