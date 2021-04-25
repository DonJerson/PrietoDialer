#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->stackedWidget);
    ui->velocidadBox->setValue(6);
        if(this->logged){
            ui->stackedWidget->setCurrentIndex(1);
        }else{
            ui->stackedWidget->setCurrentIndex(0);
        }
        QFile file("/Users/jersonmendez/Desktop/Referencia/leads.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
               return;

           QTextStream in(&file);
           QString line = "";
           while (!line.isNull()) {
               cantidadLeads = cantidadLeads+1;
               line = in.readLine();
               if(line.length()>0){
                   myLeads.push_back(line);
               }

           }
        for(int j=0; j<(int)(myLeads.size()); ++j) {
            ui->queueTable->clear();
            ui->queueTable->insertRow(j);
            ui->queueTable->setItem(j,0, new QTableWidgetItem(myLeads[j]));

            qDebug()<<myLeads[j];
            qDebug()<<j;
        }

        ui->cantidadNumeros->setText(QString::number(myLeads.size()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loginButton_clicked()
{
    logged = !logged;
    ui->stackedWidget->setCurrentIndex(1);
    CURL *curl;
      CURLcode res;

      /* In windows, this will init the winsock stuff */
      curl_global_init(CURL_GLOBAL_ALL);

      /* get a curl handle */
      curl = curl_easy_init();
      if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
           just as well be a https:// URL if that is what should receive the
           data. */
        curl_easy_setopt(curl, CURLOPT_URL, "https://google.com");
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
          fprintf(stderr, "curl_easy_perform() failed: %s\n",
                  curl_easy_strerror(res));
        qDebug()<<"bobo "<<res;
        /* always cleanup */
        curl_easy_cleanup(curl);
      }
      curl_global_cleanup();

}

void MainWindow::on_userField_textChanged(const QString &arg1)
{
    userName=arg1;
//    ui->testLabel->setText(arg1);
}

void MainWindow::on_loadButton_clicked()
{
    QFile file("/Users/jersonmendez/Desktop/Referencia/leads.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
           return;
     QByteArray ba = leadsLoader.toLocal8Bit();
     const char *c_str2 = ba.data();
    file.write(c_str2, leadsLoader.size());        // write to stderr
    file.close();

    cantidadLeads=0;
    myLeads.clear();
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
           return;

       QTextStream in(&file);
       QString line = "";
       while (!line.isNull()) {
           line = in.readLine();
           if(line.length()>0){
               myLeads.push_back(line);
           }

       }
       ui->queueTable->setRowCount(0);
       for(int j=0; j<(int)(myLeads.size()); ++j) {
   //        ui->queueTable->clear();
            cantidadLeads = cantidadLeads+1;
           ui->queueTable->insertRow(j);
           ui->queueTable->setItem(j,0, new QTableWidgetItem(myLeads[j]));

   //        qDebug()<<myLeads[j];
   //        qDebug()<<j;
       }
    ui->numbersLoader->setPlainText("");
}


void MainWindow::on_numbersLoader_textChanged()
{
     leadsLoader="\n"+ui->numbersLoader->toPlainText();

}

void MainWindow::on_deleteAllButton_clicked()
{

    QFile file("/Users/jersonmendez/Desktop/Referencia/leads.txt");

     if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
            return;
    cantidadLeads=0;
    ui->queueTable->setRowCount(0);
    file.write("");
    file.resize(0);
    file.close();
}

void MainWindow::on_powerButton_clicked()
{
    power=!power;
    if(power){
        ui->powerButton->setText("Pausar");
        ui->dialingStatus->setText("Marcando...");
    }else{
        ui->dialingStatus->setText("Pausado");
         ui->powerButton->setText("Marcar");
    }
}
