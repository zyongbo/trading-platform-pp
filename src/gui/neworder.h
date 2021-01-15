#ifndef NEWORDER_H
#define NEWORDER_H

#include "../components/trading_order.h"

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QVariant>
#include <QWidget>

#include "../components/stock.h"

namespace Ui {
class NewOrder;
}

class NewOrder : public QWidget {
  Q_OBJECT

 public:
  explicit NewOrder(QWidget *parent = nullptr);
  ~NewOrder();

  void write(TradingOrder &trading_order) const;
  void updateWatchlistStocks(QVector<Stock *> watchlistStocks);

 signals:
  void newOrderCreated(TradingOrder *newOrder);

 private slots:
  void on_orderPushButton_released();
  void on_cancelPushButton_pressed();

 private:
  Ui::NewOrder *ui;
  void setDefault();

  QVector<Stock *> watchlistStocks;
};

#endif // NEWORDER_H
