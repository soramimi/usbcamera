#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QImage>

class ImageWidget : public QWidget
{
	Q_OBJECT
private:
	QImage image_;
	QImage image_scaled_;
public:
	explicit ImageWidget(QWidget *parent = 0);

	void setImage(QImage const &image);

	QImage getImage() const
	{
		return image_;
	}

signals:

public slots:

	// QWidget interface
protected:
	void paintEvent(QPaintEvent *);
};

#endif // IMAGEWIDGET_H
