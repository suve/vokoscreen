#include "QvkDbus.h"
#include "vokoscreenqvkdbus_adaptor.h"
#include "QvkAllLoaded.h"

QvkDbus::QvkDbus()
{
}


QvkDbus::QvkDbus( Ui_screencast value )
{
    myUi = value;
    
    new GuiAdaptor( this );
    QDBusConnection dbusConnection = QDBusConnection::sessionBus();
    dbusConnection.registerObject("/gui", this);
    dbusConnection.registerService("org.vokoscreen.screencast");
}


QvkDbus::~QvkDbus()
{  
}


QString QvkDbus::showAllMethods()
{
    QStringList functions;
    for (int n = 0; n < staticMetaObject.methodCount(); n++) {

        functions.append(QString::fromLocal8Bit(staticMetaObject.method(n).name() ) );

        int index = functions.indexOf("destroyed");
        functions.removeAt( index );

        index = functions.indexOf("objectNameChanged");
        functions.removeAt( index );

        index = functions.indexOf("deleteLater");
        functions.removeAt( index );

        index = functions.indexOf("_q_reregisterTimers");
        functions.removeAt( index );

        int value = staticMetaObject.method(n).parameterCount();

        if ( ( value == 1 ) and ( !functions.empty() ) )
        {
           functions.replace( functions.count()-1, QString::fromLocal8Bit( staticMetaObject.method(n).name()).append( " int" ) );
        }
    }

    functions.sort( Qt::CaseInsensitive );

    QString string = functions.join( ", " );

    return string;
}


QString QvkDbus::isVokoscreenLoaded()
{
    if ( cameraLoaded == true )
        return "0";
    else
        return "1";
}

QString QvkDbus::Tab( QString value )
{

    if ( value.toInt() < myUi.tabWidget->count() )
    {
      myUi.tabWidget->setCurrentIndex( value.toInt() - 1 );
      return "0";
    }
    else
    {
      return "1";
    }
}

QString QvkDbus::startrecord()
{
   if ( myUi.recordButton->isEnabled() == true )
   {
     myUi.recordButton->click();
     return "0";
   }
   else
   {
     return "1";
   }
}


QString QvkDbus::stoprecord()
{
   if ( myUi.StopButton->isEnabled() == true )
   {
     myUi.StopButton->click();
     return "0";
   }
   else
   {
     return "1";
   }
}


QString QvkDbus::FullScreen()
{
    if ( ( myUi.FullScreenRadioButton->isEnabled() == true ) and ( myUi.FullScreenRadioButton->isChecked() == false ) )
    {
      myUi.FullScreenRadioButton->click();
      return "0";
    }
    else
    {
      return "1";
    }
}


QString QvkDbus::Window()
{
   if ( ( myUi.WindowRadioButton->isEnabled() == true ) and ( myUi.WindowRadioButton->isChecked() == false ) )
   {
     myUi.WindowRadioButton->click();
     return "0";
   }
   else
   {
     return "1";
   }
}



QString QvkDbus::Area()
{
   if ( ( myUi.AreaRadioButton->isEnabled() == true ) and ( myUi.AreaRadioButton->isChecked() == false ) )
   {
     myUi.AreaRadioButton->click();
     return "0";
   }
   else
   {
     return "1";
   }
}


QString QvkDbus::AreaReset()
{
   if ( myUi.areaResetButton->isEnabled() == true )
   {
      myUi.areaResetButton->click();
      return "0";
   }
   else
   {
      return "1";
   }
}

QString QvkDbus::MagnifierOn()
{
   if ( ( myUi.MagnifierCheckBox->isEnabled() == true ) and ( myUi.MagnifierCheckBox->checkState() == Qt::Unchecked ) )
   {
      myUi.MagnifierCheckBox->click();
      return "0";
   }
   else
   {
      return "1";
   }
}

QString QvkDbus::MagnifierOff()
{
   if ( ( myUi.MagnifierCheckBox->isEnabled() == true ) and ( myUi.MagnifierCheckBox->checkState() == Qt::Checked ) )
   {
      myUi.MagnifierCheckBox->click();
      return "0";
   }
   else
   {
      return "1";
   }
}

QString QvkDbus::AudioOn()
{
   if ( ( myUi.AudioOnOffCheckbox->isEnabled() == true ) and ( myUi.AudioOnOffCheckbox->checkState() == Qt::Unchecked ) )
   {
       myUi.AudioOnOffCheckbox->click();
       return "0";
   }
   else
   {
       return "1";
   }
}


QString QvkDbus::AudioOff()
{
   if ( ( myUi.AudioOnOffCheckbox->isEnabled() == true ) and ( myUi.AudioOnOffCheckbox->checkState() == Qt::Checked ) )
   {
       myUi.AudioOnOffCheckbox->click();
       return "0";
   }
   else
   {
       return "1";
   }
}


QString QvkDbus::CameraOn()
{
    if ( ( myUi.webcamCheckBox->isEnabled() == true ) and ( myUi.webcamCheckBox->checkState() == Qt::Unchecked ) )
    {
        myUi.webcamCheckBox->click();
        return "0";
    }
    else
    {
        return "1";
    }
}


QString QvkDbus::CameraOff()
{
    if ( ( myUi.webcamCheckBox->isEnabled() == true ) and  ( myUi.webcamCheckBox->checkState() == Qt::Checked ) )
    {
        myUi.webcamCheckBox->click();
        return "0";
    }
    else
    {
        return "1";
    }
}

QString QvkDbus::CameraAllNames()
{
    if ( myUi.webcamComboBox->isEnabled() == true )
    {
        QStringList stringList;
        for ( int i = 0; i < myUi.webcamComboBox->count(); i++  )
        {
            stringList <<  myUi.webcamComboBox->itemText( i );
        }
        QString string = stringList.join( ", " );
        return string;
    }
    else
    {
        return "1";
    }
}

QString QvkDbus::CameraCount()
{
    return  QString::number( myUi.webcamComboBox->count() );
}

QString QvkDbus::CameraSetIndex( QString value )
{
    if ( myUi.webcamComboBox->isEnabled() == true )
    {
        if ( ( value.toInt() > 0 ) and ( value.toInt() <= myUi.webcamComboBox->count() ) )
        {
            myUi.webcamComboBox->setCurrentIndex( value.toInt()-1 );
            return "0";
        }
        else
        {
            return "1";
        }
    }
    else
    {
        return "1";
    }
}

QString QvkDbus::CameraResolutions()
{
    QStringList stringList;
    for ( int i = 0; i < myUi.resolutionComboBox->count(); i++  )
    {
        stringList <<  myUi.resolutionComboBox->itemText( i );
    }
    QString string = stringList.join( ", " );
    return string;
}

QString QvkDbus::CountDown( QString value )
{
    myUi.CountdownSpinBox->setValue( value.toInt() );
    return "0";
}

void QvkDbus::quit()
{
    emit close();
}
