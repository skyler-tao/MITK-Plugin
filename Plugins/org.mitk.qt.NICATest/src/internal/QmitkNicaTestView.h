/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Language:  C++
Date:      $Date$
Version:   $Revision$ 
 
Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/


#ifndef QmitkNicaTestView_h
#define QmitkNicaTestView_h

#include <berryISelectionListener.h>

#include <QmitkAbstractView.h>

#include "ui_QmitkNicaTestViewControls.h"


/*!
  \brief QmitkNicaTestView

  \warning  This class is not yet documented. Use "git blame" and ask the author to provide basic documentation.

  \sa QmitkFunctionality
  \ingroup ${plugin_target}_internal
*/
class QmitkNicaTestView : public QmitkAbstractView
{  
  // this is needed for all Qt objects that should have a Qt meta-object
  // (everything that derives from QObject and wants to have signal/slots)
  Q_OBJECT
  
  public:  

    static const std::string VIEW_ID;

	QmitkNicaTestView();
	virtual ~QmitkNicaTestView();
    virtual void CreateQtPartControl(QWidget *parent);


  protected slots:
  
    /// \brief Called when the user clicks the GUI button
    //void DoImageProcessing();
	void Translate(int* translateVector);
	void Rotate(int* rotateVector);
	void Scale(int* scaleVector);
    void xTrans_valueChanged( int v );
	void yTrans_valueChanged( int v );
	void zTrans_valueChanged( int v );
	void xRot_valueChanged( int v );
	void yRot_valueChanged( int v );
	void zRot_valueChanged( int v );
    void xScale_valueChanged( int v );
	void yScale_valueChanged( int v );
	void zScale_valueChanged( int v );
	void ImageSelected(const mitk::DataNode* inputImage);

  protected:
  
    virtual void SetFocus();

    /// \brief called by QmitkFunctionality when DataManager's selection has changed
    virtual void OnSelectionChanged( berry::IWorkbenchPart::Pointer source,
                                     const QList<mitk::DataNode::Pointer>& nodes );


    Ui::QmitkNicaTestViewControls m_Controls;
	mitk::DataNode::Pointer m_InputNode;
	int * translationParams;
	int * rotationParams;
    int * scalingParams;
	int m_TranslateSliderPos[3];
	int m_RotateSliderPos[3];
    int m_ScaleSliderPos[3];

};

#endif // QmitkNicaTestView_h

