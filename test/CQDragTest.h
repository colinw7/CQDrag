#include <QWidget>

class CQDrag;
class CQDragCancel;

class CQDragTest : public QWidget {
  Q_OBJECT

 public:
  CQDragTest();

  void test();

 private:
  CQDrag       *drag1_;
  CQDrag       *drag2_;
  CQDragCancel *cancelDrag_;
};

class CQDragCancel : public QObject {
  Q_OBJECT

 public:
  CQDragCancel(QWidget *w, const QPoint &pos) :
   w_(w), pos_(pos), timer_(0) {
  }

 public slots:
  void cancelDragStart();
  void cancelDragEnd();
  void cancelDrag();

 private:
  QWidget *w_;
  QPoint   pos_;
  QTimer  *timer_;
};
