#include "modulemanagerwidget.h"
#include "ui_modulemanagerwidget.h"

ModuleManagerWidget::ModuleManagerWidget(QWidget *videoWidget, QWidget *parent) :
    QWidget(parent), ui(new Ui::ModuleManagerWidget), videoWidget((VideoGallery*)videoWidget)
{
    ui->setupUi(this);
    new QVBoxLayout(ui->settingsBox);
    currentSettingsWidget = NULL;
    fileName = "/media/disk/Downloads/Dexter.S05E03.HDTV.XviD-2HD/dexter.s05e03.hdtv.xvid-2hd.avi";
    processor = NULL;
    modules = new QList<Module*>();

    possibleModules.append("Dummy Module");
    possibleModules.append("Background removal");

    ui->modulesBox->addItems(possibleModules);
    QStringListModel* model = new QStringListModel(ui->modulesList);
    ui->modulesList->setModel(model);
    selectedModule=NULL;
    connect(ui->modulesList->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(showSettings(QItemSelection,QItemSelection)));
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

    if(!processor) {
        processor = new ImageProcessor(fileName, modules, this);
        processor->setModuleList(modules);
    }

    if(!processor->isRunning()) {
        processor->start();
    }


}

void ModuleManagerWidget::on_stopButton_clicked()
{
    if(processor->isRunning()){
        processor->stop();
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

        processor->chModList();
        m->setVideo(false);
        videoWidget->layout()->removeWidget(m->getVideoWidget());
        modules->removeAt(sel);
        if(currentSettingsWidget == m->getSettingsWidget()) {
            ui->settingsBox->layout()->removeWidget(currentSettingsWidget);
            currentSettingsWidget = NULL;
        }
        delete m;
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

        ui->settingsBox->layout()->addWidget(m->getSettingsWidget());
        ui->settingsBox->layout()->update();
        currentSettingsWidget = m->getSettingsWidget();
        currentSettingsWidget->show();

    }
}