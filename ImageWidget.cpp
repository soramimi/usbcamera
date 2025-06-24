#include "ImageWidget.h"

#include <QPainter>

ImageWidget::ImageWidget(QWidget *parent)
	: QWidget(parent)
{

}

void ImageWidget::setImage(const QImage &image)
{
	image_ = image;
	update();
}

void ImageWidget::paintEvent(QPaintEvent *)
{
	QRect r(rect());
	int w = image_.width();
	int h = image_.height();
	w = 1280;
	h = 720;
	if (w * r.height() > h * r.width() ) {
		h = r.width() * h / w;
		w = r.width();
	} else {
		w = r.height() * w / h;
		h = r.height();
	}
	qDebug() << w << h;
	int x = (r.width() - w) / 2;
	int y = (r.height() - h) / 2;
	QPainter pr(this);
	pr.drawImage(x, y, image_.scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

}
