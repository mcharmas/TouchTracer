#include "modulemanagerwidget.h"
#include "ui_modulemanagerwidget.h"

ModuleManagerWidget::ModuleManagerWidget(QWidget *videoWidget, QWidget *parent) :
    QWidget(parent), ui(new Ui::ModuleManagerWidget), videoWidget((VideoGallery*)videoWidget)
{
    ui->setupUi(this);
    new QVBoxLayout(ui->settingsBox);
    currentSettingsWidget = NULL;
    fileName = "";
    //fileName = "/home/orbit/stol-szajze-wideo/zfiltrem-2B-1palec-odrywanie.avi";
    //fileName = "/home/orbit/stol-szajze-wideo/bezfiltra-2A-1palec.avi";
    //fileName = "/home/orbit/stol-szajze-wideo/bezfiltra-3A-wiele-palcow.avi";
    //fileName = "/home/orbit/stol-szajze-wideo/bezfiltra-2B-1palec-odrywanie.avi";

    processor = NULL;
    modules = new QList<Module*>();

    possibleModules.append("Dummy Module");
    possibleModules.append("Background removal");
    possibleModules.append("Filters");
    possibleModules.append("Tracking");

    ui->modulesBox->addItems(possibleModules);
    QStringListModel* model = new QStringListModel(ui->modulesList);
    ui->modulesList->setModel(model);
    selectedModule=NULL;
    connect(ui->modulesList->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(showSettings(QItemSelection,QItemSelection)));
}

void ModuleManagerWidget::openFile(QString fileName)
{
    on_stopButton_clicked();
    this->fileName = fileName;
}

ModuleManagerWidget::~ModuleManagerWidget()
{
    delete ui;
    if(processor)
    {
        processor->stop();
        delete processor;
    }

    foreach(Module *m, *modules)
    {
        delete m;
    }
}

void ModuleManagerWidget::on_startButton_clicked()
{
    if(fileName=="")
    {
        QMessageBox::information(this, tr("No file opened."), tr("No video file has been opened."), QMessageBox::Ok);
        return;
    }

    if(!processor) {
        processor = new ImageProcessor(fileName, modules, this);
        processor->setModuleList(modules);
        connect(processor, SIGNAL(fpsUpdated(int)), this, SLOT(showFps(int)));
        connect(processor, SIGNAL(dpsUpdated(int)), this, SLOT(showDps(int)));
    }

    if(!processor->isRunning()) {
        processor->start();
    }


}

void ModuleManagerWidget::on_stopButton_clicked()
{
    if(processor && processor->isRunning()){
        processor->stop();
        disconnect(processor, SIGNAL(fpsUpdated(int)));
        disconnect(processor, SIGNAL(dpsUpdated(int)));
        delete processor;
        processor = NULL;
    }

}

void ModuleManagerWidget::on_addModuleButton_clicked()
{
    QString moduleName = ui->modulesBox->currentText();
    qDebug() << moduleName;
    Module* m = NULL;
    if(moduleName == "Dummy Module") {
        m = new ModuleVideo();
    } else if(moduleName == "Background removal") {
        m = new ModuleBackground();
    } else if(moduleName == "Filters") {
        m = new ModuleFilters();
    } else if(moduleName == "Tracking") {
        m = new ModuleTracking();
    }

    connect(m, SIGNAL(videoStopped(QWidget*)), videoWidget, SLOT(unRegisterWidget(QWidget*)));
    videoWidget->registerNewWidget(m->getVideoWidget());

    if(processor)
        processor->chModList();

    modules->append(m);

    if(processor)
    {
        processor->stopChModList();
        processor->setModuleList(modules);
    }
    updateList();
}

void ModuleManagerWidget::updateList()
{
    QStringListModel *model = (QStringListModel *)ui->modulesList->model();
    QStringList list;
    foreach(Module *m, *modules)
    {
        list << m->getName();
    }
    model->setStringList(list);
}

void ModuleManagerWidget::on_removeModuleButton_clicked()
{
    if(!ui->modulesList->selectionModel()->selectedRows().isEmpty())
    {
        int sel = ui->modulesList->selectionModel()->currentIndex().row();
        Module *m = modules->at(sel);

        if(m == selectedModule) {
            selectedModule = NULL;
        }

        if(processor)
            processor->chModList();

        m->setVideo(false);
        videoWidget->layout()->removeWidget(m->getVideoWidget());
        modules->removeAt(sel);
        if(currentSettingsWidget == m->getSettingsWidget()) {
            ui->settingsBox->layout()->removeWidget(currentSettingsWidget);
            currentSettingsWidget = NULL;
        }
        delete m;

        if(processor)
            processor->stopChModList();

        updateList();
    }
}

void ModuleManagerWidget::showSettings(QItemSelection,QItemSelection)
{
    if(!ui->modulesList->selectionModel()->selectedRows().isEmpty())
    {
        int sel = ui->modulesList->selectionModel()->currentIndex().row();
        Module *m = modules->at(sel);        

        if (selectedModule) {
            ((VideoWidget*)(selectedModule->getVideoWidget()))->setSelected(true);
        }
        selectedModule = m;
        ((VideoWidget*)(m->getVideoWidget()))->setSelected(false);

        if(currentSettingsWidget){
            currentSettingsWidget->hide();
            ui->settingsBox->layout()->removeWidget(currentSettingsWidget);
        }

        if(m->getSettingsWidget()) {
            ui->settingsBox->layout()->addWidget(m->getSettingsWidget());
            ui->settingsBox->layout()->update();
            currentSettingsWidget = m->getSettingsWidget();
            currentSettingsWidget->show();
        }

    }
}

void ModuleManagerWidget::showFps(int x)
{
    ui->fpsLabel->setText(QString::number(x));
}

void ModuleManagerWidget::showDps(int x)
{
    ui->dpsLabel->setText(QString::number(x));
}
