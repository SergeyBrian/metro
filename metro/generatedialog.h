#ifndef GENERATEDIALOG_H
#define GENERATEDIALOG_H

#include <QDialog>

#include "ui_generatedialog.h"

namespace Ui {
    class GenerateDialog;
}

class GenerateDialog : public QDialog {
Q_OBJECT

public:
    explicit GenerateDialog(QWidget *parent = nullptr);

    int getBranchesCount() const;

    int getStationsCount() const;

    int getBranchThreshold() const;

    QString getSeed();

    ~GenerateDialog();

private slots:

    void on_stationsSpinBox_valueChanged(int arg1);

    void on_branchesSpinBox_valueChanged(int arg1);

    void on_buttonBox_accepted();

private:
    Ui::GenerateDialog *ui;

    int branchesCount;
    int stationsCount;
    int branchThreshold;
    QString seed;
};

#endif // GENERATEDIALOG_H
