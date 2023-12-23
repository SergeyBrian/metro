#include "generatedialog.h"

GenerateDialog::GenerateDialog(QWidget *parent)
        : QDialog(parent), ui(new Ui::GenerateDialog) {
    ui->setupUi(this);

}

GenerateDialog::~GenerateDialog() {
    delete ui;
}

void GenerateDialog::on_stationsSpinBox_valueChanged(int arg1) {
    ui->branchesSpinBox->setMaximum(arg1);
}


void GenerateDialog::on_branchesSpinBox_valueChanged(int arg1) {
}


void GenerateDialog::on_buttonBox_accepted() {
    stationsCount = ui->stationsSpinBox->value();
    branchesCount = ui->branchesSpinBox->value();
    seed = ui->seedLineEdit->text();
}

int GenerateDialog::getBranchesCount() const {
    return branchesCount;
}

int GenerateDialog::getStationsCount() const {
    return stationsCount;
}

QString GenerateDialog::getSeed() {
    return seed;
}

