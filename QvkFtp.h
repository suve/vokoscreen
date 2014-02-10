#ifndef QVKFTP_H
#define QVKFTP_H

#include <QDialog> 
#include <QLineEdit>
#include <QFtp>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QDesktopServices>
#include <QDebug>

class QvkFtp: public QDialog
{
    Q_OBJECT
    
public:
    QvkFtp();
    virtual ~QvkFtp();
    
    
signals:

    
private slots:
  void getLocalFile();
  void uploadLocalFile();
  void myStateChanged( int state );
  void myDestroyed();


private:
    QLineEdit *fileLineEdit;
    QLineEdit *userLineEdit;
    QLineEdit *passLineEdit;
    QLineEdit *serverLineEdit;
    QLineEdit *dirLineEdit;
    QFtp *ftp;

  
protected:  

};

#endif
