#ifndef CQDrag_H
#define CQDrag_H

#include <QWidget>

class QMimeData;

class CQDrag : public QWidget {
  Q_OBJECT

 public:
  CQDrag(QWidget *parent=0);

  void paintEvent(QPaintEvent *);

  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *);

  void dragEnterEvent(QDragEnterEvent *event);
  void dragMoveEvent(QDragMoveEvent *event);
  void dropEvent(QDropEvent *event);

  bool dragValid(const QMimeData *m) const;

 signals:
  void dragStart();
  void dragEnd();

 private:
  QPoint pressPos_;
  bool   pressed_;
  int    count_;
};

#endif
