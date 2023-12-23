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
    branchThreshold = ui->branchThresholdSpinBox->value();
    minDistance = ui->minDistanceSpinBox->value();
    seed = ui->seedLineEdit->text();
}

metro::Params GenerateDialog::getParams() const {
    return {
            .branch_count = branchesCount,
            .stations_count = stationsCount,
            .branch_threshold = branchThreshold,
            .min_distance = minDistance,
    };
}

