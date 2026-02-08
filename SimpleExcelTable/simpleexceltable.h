#ifndef SIMPLEEXCELTABLE_H
#define SIMPLEEXCELTABLE_H

#include <QTableWidget>
#include <QUndoStack>

class SimpleExcelTable : public QTableWidget {
  Q_OBJECT
 public:
  explicit SimpleExcelTable(QWidget *parent = 0);
  ~SimpleExcelTable();

 public slots:
  void undo();   // 撤销
  void redo();   // 重组
  void copy();   // 复制
  void paste();  // 粘贴
  void del();    // 删除

 protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void paintEvent(QPaintEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

 private:
  void pasteData(int startRow, int startCol, const QString &clipboardText);
  // 判断当前鼠标位置是否在拖拉范围内
  bool isInHandleArea(const QModelIndex &index, const QPoint &pos) const;
  void updateFillPreview(const QModelIndex &endIndex);
  void performFill();
  QVector<QString> generateFillSeries(const QString &base, int count) const;

 private:
  QUndoStack *m_undoStack = nullptr;

  /// 拖动填充
  bool m_draging = false;  // 是否正在拖动
  QModelIndex m_startIndex;
  bool m_isCopyMode = false;  // 按ctrl键为复制模式
  bool m_isProcessingUndoRedo = false;
  enum DragDirection {
    NoDirection,
    RightHorizontal,
    LeftHorizontal,
    UpVertical,
    DownVertical
  };
  DragDirection m_dragDirection = NoDirection;

 public slots:
};

#endif  // SIMPLEEXCELTABLE_H
