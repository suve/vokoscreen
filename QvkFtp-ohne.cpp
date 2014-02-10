
#include "QvkFtp.h"


QvkFtp::QvkFtp()
{
  setGeometry( 500, 200, 600, 500 );
  
  QLabel *userLabel = new QLabel( this );
  userLabel->setGeometry( 100, 50, 100, 30 );
  userLabel->setText( "User" );
  userLabel->show();
  
  userLineEdit = new QLineEdit( this );
  userLineEdit->setGeometry( 200, 50, 200, 30 );
  userLineEdit->show();
  
  QLabel *passLabel = new QLabel( this );
  passLabel->setGeometry( 100, 100, 100, 30 );
  passLabel->setText( "Password" );
  passLabel->show();

  passLineEdit = new QLineEdit( this );
  passLineEdit->setGeometry( 200, 100, 200, 30 );
  passLineEdit->show();
  
  QLabel *serverLabel = new QLabel( this );
  serverLabel->setGeometry( 100, 150, 100, 30 );
  serverLabel->setText( "Server" );
  serverLabel->show();

  serverLineEdit = new QLineEdit( this );
  serverLineEdit->setGeometry( 200, 150, 200, 30 );
  serverLineEdit->show();
  
  QLabel *dirLabel = new QLabel( this );
  dirLabel->setGeometry( 100, 200, 100, 30 );
  dirLabel->setText( "Directory" );
  dirLabel->show();
  
  dirLineEdit = new QLineEdit( this );
  dirLineEdit->setGeometry( 200, 200, 200, 30 );
  dirLineEdit->show();
  
  fileLineEdit = new QLineEdit( this );
  fileLineEdit->setGeometry( 100, 250, 300, 30 );
  fileLineEdit->show();
  
  QPushButton *pushButton = new QPushButton( this );
  pushButton->setGeometry( 400, 250, 100, 30 );
  pushButton->setText( "File..." );
  pushButton->show();
  connect( pushButton, SIGNAL( clicked() ), SLOT( getLocalFile() ) );

  QPushButton *uploadButton = new QPushButton( this );
  uploadButton->setGeometry( 100, 300, 400, 30 );
  uploadButton->setText( "Upload" );
  connect( uploadButton, SIGNAL( clicked() ), SLOT( uploadLocalFile() ) );

  // Wird aufgerufen wenn Fenster geschloßen wird
  connect( this, SIGNAL( finished( int ) ), SLOT( myDestroyed() ) );

  ftp = new QFtp( this );
  connect( ftp, SIGNAL( stateChanged( int ) ), SLOT( myStateChanged( int ) ) );

}

QvkFtp::~QvkFtp()
{
}


void QvkFtp::getLocalFile()
{
  QString videoFile = QFileDialog::getOpenFileName ( this, 
						    "Open Directory",
						     QDesktopServices::storageLocation( QDesktopServices::MoviesLocation ),
						     "*.*" );
						     
  fileLineEdit->setText( videoFile );
  
}


void QvkFtp::uploadLocalFile()
{
  
  ftp->connectToHost( serverLineEdit->text() );
  ftp->login( userLineEdit->text(), passLineEdit->text() );
  
  ftp->cd( dirLineEdit->text() );
  
  QFile dataFile( fileLineEdit->text() );
  dataFile.open( QIODevice::ReadOnly );
  
  QByteArray content = dataFile.readAll();
  
  QFileInfo fileInfo( dataFile.fileName() );
  ftp->put( content, fileInfo.fileName() );
  
}


void QvkFtp::myStateChanged( int state )
{
  if ( state == QFtp::Unconnected )
  {
    qDebug() << "[vokoscreen] There is no connection to the host";
  }

  if ( state == QFtp::Connected )
  {
    qDebug() << "[vokoscreen] Connection to the host has been achieved";
  }
  
  if ( state == QFtp::LoggedIn )
  {
    qDebug() << "[vokoscreen] Connection and user login have been achieved";
  }
}

// Wird aufgerufen wenn Fenster geschloßen wird
void QvkFtp::myDestroyed()
{
  qDebug() << "[vokoscreen] close ftp connection";
  ftp->close();
}




