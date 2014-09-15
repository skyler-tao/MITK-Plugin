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


// Blueberry
#include <berryISelectionService.h>
#include <berryIWorkbenchWindow.h>

// Qmitk
#include "QmitkNicaTestView.h"

// Qt
#include <QMessageBox>

//vtk
#include <vtkTransform.h>


const std::string QmitkNicaTestView::VIEW_ID = "org.mitk.views.nicatest_view_name";

QmitkNicaTestView::QmitkNicaTestView()
: QmitkAbstractView()
, m_InputNode(NULL)
{
  m_TranslateSliderPos[0] = 0;
  m_TranslateSliderPos[1] = 0;
  m_TranslateSliderPos[2] = 0;

  m_RotateSliderPos[0] = 0;
  m_RotateSliderPos[1] = 0;
  m_RotateSliderPos[2] = 0;

  m_ScaleSliderPos[0] = 0;
  m_ScaleSliderPos[1] = 0;
  m_ScaleSliderPos[2] = 0;

  translationParams = new int[3];
  rotationParams = new int[3];
  scalingParams = new int[3];

}
QmitkNicaTestView::~QmitkNicaTestView()
{

}

void QmitkNicaTestView::SetFocus()
{
  /*m_Controls.buttonPerformImageProcessing->setFocus();*/
}

void QmitkNicaTestView::CreateQtPartControl( QWidget *parent )
{
  // create GUI widgets from the Qt Designer's .ui file
  m_Controls.setupUi( parent );

  connect( this, SIGNAL(OnSelectionChanged(berry::IWorkbenchPart::Pointer /*source*/,
	  const QList<mitk::DataNode::Pointer>& )), this, SLOT(ImageSelected(const mitk::DataNode*)));

  connect( m_Controls.TranslationXSlider,SIGNAL(valueChanged(int)), m_Controls.TranslationXSpin, SLOT(setValue(int)));
  connect( m_Controls.TranslationXSpin,SIGNAL(valueChanged(int)), m_Controls.TranslationXSlider, SLOT(setValue(int)));
  connect( m_Controls.TranslationYSlider,SIGNAL(valueChanged(int)), m_Controls.TranslationYSpin, SLOT(setValue(int)));
  connect( m_Controls.TranslationYSpin,SIGNAL(valueChanged(int)), m_Controls.TranslationYSlider, SLOT(setValue(int)));
  connect( m_Controls.TranslationZSlider,SIGNAL(valueChanged(int)), m_Controls.TranslationZSpin, SLOT(setValue(int)));
  connect( m_Controls.TranslationZSpin,SIGNAL(valueChanged(int)), m_Controls.TranslationZSlider, SLOT(setValue(int)));

  //Translation通过代码完成QSlider和QSpin的连接，Rotation和Scaling通过QT Designer完成


  //connect( m_Controls.buttonPerformImageProcessing, SIGNAL(clicked()), this, SLOT(DoImageProcessing()) );
  connect( m_Controls.TranslationXSlider,SIGNAL(valueChanged(int)), this, SLOT(xTrans_valueChanged(int)));
  connect( m_Controls.TranslationYSlider,SIGNAL(valueChanged(int)), this, SLOT(yTrans_valueChanged(int)));
  connect( m_Controls.TranslationZSlider,SIGNAL(valueChanged(int)), this, SLOT(zTrans_valueChanged(int)));
  connect(m_Controls.RotationXSlider, SIGNAL(valueChanged(int)), this, SLOT(xRot_valueChanged(int)));
  connect(m_Controls.RotationYSlider, SIGNAL(valueChanged(int)), this, SLOT(yRot_valueChanged(int)));
  connect(m_Controls.RotationZSlider, SIGNAL(valueChanged(int)), this, SLOT(zRot_valueChanged(int)));
  connect(m_Controls.ScalingXSlider, SIGNAL(valueChanged(int)), this, SLOT(xScale_valueChanged(int)));
  connect(m_Controls.ScalingYSlider, SIGNAL(valueChanged(int)), this, SLOT(yScale_valueChanged(int)));
  connect(m_Controls.ScalingZSlider, SIGNAL(valueChanged(int)), this, SLOT(zScale_valueChanged(int)));
 /* m_Controls.m_ImageSelectedLabel->hide();*/
  
}
void QmitkNicaTestView::ImageSelected(const mitk::DataNode* inputImage)
{
	//if(inputImage == 0 || inputImage->GetData() == 0 )
	//	return;
	//m_InputNode = inputImage;
}
void QmitkNicaTestView::OnSelectionChanged( berry::IWorkbenchPart::Pointer /*source*/,
                                             const QList<mitk::DataNode::Pointer>& nodes )
{

	this->m_InputNode = 0;
	
  
  // iterate all selected objects, adjust warning visibility
 // foreach( mitk::DataNode::Pointer node, nodes )
 // {
 //   if( node.IsNotNull() && dynamic_cast<mitk::Image*>(node->GetData()) )
 //   {
 //     m_Controls.labelWarning->setVisible( false );
 //     m_Controls.buttonPerformImageProcessing->setEnabled( true );
	//  //m_InputNode = nodes;
	//  //std::string inputName = node->GetName();
	//  //m_Controls.m_ImageSelectedLabel->setText(QString(inputName.c_str()));

 //    return;
	///*  break;*/
 //   }

 // }
	for(int i = 0; i<nodes.size();++i)
	{
		if(dynamic_cast<mitk::Image*>(nodes.at(i)->GetData()))
		{
			this->m_InputNode = nodes.at(i);
			this->m_Controls.labelWarning->setVisible( false );
			//this->m_Controls.buttonPerformImageProcessing->setEnabled( true );

			QString nodeLabel = "None selected";
            if(this->m_InputNode.IsNotNull())
	            nodeLabel = QString::fromStdString(this->m_InputNode->GetName());
            this->m_Controls.m_ImageSelectedLabel->setText(nodeLabel);
			return;
		}
	}

  m_Controls.labelWarning->setVisible( true );
  //m_Controls.buttonPerformImageProcessing->setEnabled( false );

}


//void QmitkNicaTestView::DoImageProcessing()
//{
//  QList<mitk::DataNode::Pointer> nodes = this->GetDataManagerSelection();
//  if (nodes.empty()) return;
//
//  mitk::DataNode* node = nodes.front();
//
//  if (!node)
//  {
//    // Nothing selected. Inform the user and return
//    QMessageBox::information( NULL, "Template", "Please load and select an image before starting image processing.");
//    return;
//  }
//
//  // here we have a valid mitk::DataNode
//
//  // a node itself is not very useful, we need its data item (the image)
//  mitk::BaseData* data = node->GetData();
//  if (data)
//  {
//    // test if this data item is an image or not (could also be a surface or something totally different)
//    mitk::Image* image = dynamic_cast<mitk::Image*>( data );
//    if (image)
//    {
//      std::stringstream message;
//      std::string name;
//      message << "Performing image processing for image ";
//      if (node->GetName(name))
//      {
//        // a property called "name" was found for this DataNode
//        message << "'" << name << "'";
//      }
//      message << ".";
//      MITK_INFO << message.str();
//
//      // actually do something here...
//
//    }
//  }
//}


void QmitkNicaTestView::xTrans_valueChanged( int v )
{
	if(m_InputNode.IsNotNull())
	{
		translationParams[0] = v;
		translationParams[1] = m_Controls.TranslationYSlider->value();
		translationParams[2] = m_Controls.TranslationZSlider->value();
		Translate(translationParams);
	}
}
void QmitkNicaTestView::yTrans_valueChanged( int v )
{
	if(m_InputNode.IsNotNull())
	{
		translationParams[1] = v;
		translationParams[0] = m_Controls.TranslationXSlider->value();
		translationParams[2] = m_Controls.TranslationZSlider->value();
		Translate(translationParams);
	}
}
void QmitkNicaTestView::zTrans_valueChanged( int v )
{
	if(m_InputNode.IsNotNull())
	{
		translationParams[2] = v;
		translationParams[0] = m_Controls.TranslationXSlider->value();
		translationParams[1] = m_Controls.TranslationYSlider->value();
		Translate(translationParams);
	}
}

void QmitkNicaTestView::xRot_valueChanged( int v )
{
  if (m_InputNode.IsNotNull())
  {
    rotationParams[0]=v;
    rotationParams[1]=m_Controls.RotationYSlider->value();
    rotationParams[2]=m_Controls.RotationZSlider->value();
    Rotate(rotationParams);
  }
  //else
  //{
  //  InputImageChanged();
  //}
}

void QmitkNicaTestView::yRot_valueChanged( int v )
{
  if (m_InputNode.IsNotNull())
  {
    rotationParams[0]=m_Controls.RotationXSlider->value();
    rotationParams[1]=v;
    rotationParams[2]=m_Controls.RotationZSlider->value();
    Rotate(rotationParams);
  }
  //else
  //{
  //  InputImageChanged();
  //}
}

void QmitkNicaTestView::zRot_valueChanged( int v )
{
  if (m_InputNode.IsNotNull())
  {
    rotationParams[0]=m_Controls.RotationXSlider->value();
    rotationParams[1]=m_Controls.RotationYSlider->value();
    rotationParams[2]=v;
    Rotate(rotationParams);
  }
  //else
  //{
  //  InputImageChanged();
  //}
}

void QmitkNicaTestView::xScale_valueChanged( int v )
{
  if (m_InputNode.IsNotNull())
  {
    scalingParams[0]=v;
    scalingParams[1]=m_Controls.ScalingYSlider->value();
    scalingParams[2]=m_Controls.ScalingZSlider->value();
    Scale(scalingParams);
  }
  //else
  //{
  //  InputImageChanged();
  //}
}

void QmitkNicaTestView::yScale_valueChanged( int v )
{
  if (m_InputNode.IsNotNull())
  {
    scalingParams[0]=m_Controls.ScalingXSlider->value();
    scalingParams[1]=v;
    scalingParams[2]=m_Controls.ScalingZSlider->value();
    Scale(scalingParams);
  }
  //else
  //{
  //  InputImageChanged();
  //}
}

void QmitkNicaTestView::zScale_valueChanged( int v )
{
  if (m_InputNode.IsNotNull())
  {
    scalingParams[0]=m_Controls.ScalingXSlider->value();
    scalingParams[1]=m_Controls.ScalingYSlider->value();
    scalingParams[2]=v;
    Scale(scalingParams);
  }
  //else
  //{
  //  InputImageChanged();
  //}
}
void QmitkNicaTestView::Translate(int *translateVector)
{
	if(m_InputNode.IsNotNull())
	{
		mitk::Vector3D translateVec;

		translateVec[0] = translateVector[0] - m_TranslateSliderPos[0];
		translateVec[1] = translateVector[1] - m_TranslateSliderPos[1];
        translateVec[2] = translateVector[2] - m_TranslateSliderPos[2];

		m_TranslateSliderPos[0] = translateVector[0];
        m_TranslateSliderPos[1] = translateVector[1];
        m_TranslateSliderPos[2] = translateVector[2];
		
		vtkMatrix4x4* translationMatrix = vtkMatrix4x4::New();
        translationMatrix->Identity();
		double (*transMatrix)[4] = translationMatrix->Element;

        transMatrix[0][3] = -translateVec[0];
		transMatrix[1][3] = -translateVec[1];
		transMatrix[2][3] = -translateVec[2];

		translationMatrix->Invert();

		m_InputNode->GetData()->GetGeometry()->Compose(translationMatrix);
		m_InputNode->GetData()->Modified();
		mitk::DataStorage::SetOfObjects::ConstPointer children = this->GetDataStorage()->GetDerivations(m_InputNode);
		unsigned long size;
		size = children->Size();
		mitk::DataNode::Pointer childNode;
		for(unsigned long i = 0; i < size; ++i)
		{
			childNode = children->GetElement(i);
			childNode->GetData()->GetGeometry()->Compose( translationMatrix );
			childNode->GetData()->Modified();
		}
		mitk::RenderingManager::GetInstance()->RequestUpdateAll();
	}
}
void QmitkNicaTestView::Rotate(int* rotateVector)
{
  if (m_InputNode.IsNotNull())
  {
    mitk::Vector3D rotateVec;

    rotateVec[0] = rotateVector[0] - m_RotateSliderPos[0];
    rotateVec[1] = rotateVector[1] - m_RotateSliderPos[1];
    rotateVec[2] = rotateVector[2] - m_RotateSliderPos[2];

    m_RotateSliderPos[0] = rotateVector[0];
    m_RotateSliderPos[1] = rotateVector[1];
    m_RotateSliderPos[2] = rotateVector[2];

    vtkMatrix4x4* rotationMatrix = vtkMatrix4x4::New();
    vtkMatrix4x4* translationMatrix = vtkMatrix4x4::New();
    rotationMatrix->Identity();
    translationMatrix->Identity();

    double (*rotMatrix)[4] = rotationMatrix->Element;
    double (*transMatrix)[4] = translationMatrix->Element;

    mitk::Point3D centerBB = m_InputNode->GetData()->GetGeometry()->GetCenter();

    transMatrix[0][3] = centerBB[0];
    transMatrix[1][3] = centerBB[1];
    transMatrix[2][3] = centerBB[2];

    translationMatrix->Invert();

    m_InputNode->GetData()->GetGeometry()->Compose( translationMatrix );
    mitk::DataStorage::SetOfObjects::ConstPointer children = this->GetDataStorage()->GetDerivations(m_InputNode);
    unsigned long size;
    size = children->Size();
    mitk::DataNode::Pointer childNode;
    for (unsigned long i = 0; i < size; ++i)
    {
      childNode = children->GetElement(i);
      childNode->GetData()->GetGeometry()->Compose( translationMatrix );
      childNode->GetData()->Modified();
    }

    double radianX = rotateVec[0] * vnl_math::pi / 180;
    double radianY = rotateVec[1] * vnl_math::pi / 180;
    double radianZ = rotateVec[2] * vnl_math::pi / 180;

    if ( rotateVec[0] != 0 )
    {
      rotMatrix[1][1] = cos( radianX );
      rotMatrix[1][2] = -sin( radianX );
      rotMatrix[2][1] = sin( radianX );
      rotMatrix[2][2] = cos( radianX );
    }
    else if ( rotateVec[1] != 0 )
    {
      rotMatrix[0][0] = cos( radianY );
      rotMatrix[0][2] = sin( radianY );
      rotMatrix[2][0] = -sin( radianY );
      rotMatrix[2][2] = cos( radianY );
    }
    else if ( rotateVec[2] != 0 )
    {
      rotMatrix[0][0] = cos( radianZ );
      rotMatrix[0][1] = -sin( radianZ );
      rotMatrix[1][0] = sin( radianZ );
      rotMatrix[1][1] = cos( radianZ );
    }

    m_InputNode->GetData()->GetGeometry()->Compose( rotationMatrix );
    for (unsigned long i = 0; i < size; ++i)
    {
      childNode = children->GetElement(i);
      childNode->GetData()->GetGeometry()->Compose( rotationMatrix );
      childNode->GetData()->Modified();
    }

    translationMatrix->Invert();

    m_InputNode->GetData()->GetGeometry()->Compose( translationMatrix );
    for (unsigned long i = 0; i < size; ++i)
    {
      childNode = children->GetElement(i);
      childNode->GetData()->GetGeometry()->Compose( rotationMatrix );
      childNode->GetData()->Modified();
    }
    m_InputNode->GetData()->Modified();
 /*   m_RedoGeometryList.clear();*/
    mitk::RenderingManager::GetInstance()->RequestUpdateAll();
  }
}

void QmitkNicaTestView::Scale(int* scaleVector)
{
  if (m_InputNode.IsNotNull())
  {
    mitk::Vector3D scaleVec;

    scaleVec[0] = scaleVector[0] - m_ScaleSliderPos[0];
    scaleVec[1] = scaleVector[1] - m_ScaleSliderPos[1];
    scaleVec[2] = scaleVector[2] - m_ScaleSliderPos[2];

    m_ScaleSliderPos[0] = scaleVector[0];
    m_ScaleSliderPos[1] = scaleVector[1];
    m_ScaleSliderPos[2] = scaleVector[2];

    vtkMatrix4x4* scalingMatrix = vtkMatrix4x4::New();
    scalingMatrix->Identity();

    double (*scaleMatrix)[4] = scalingMatrix->Element;

    if (scaleVec[0] >= 0)
    {
      for(int i = 0; i<scaleVec[0]; i++)
      {
        scaleMatrix[0][0] *= 0.95;
      }
    }
    else
    {
      for(int i = 0; i<-scaleVec[0]; i++)
      {
        scaleMatrix[0][0] *= 1/0.95;
      }
    }

    if (scaleVec[1] >= 0)
    {
      for(int i = 0; i<scaleVec[1]; i++)
      {
        scaleMatrix[1][1] *= 0.95;
      }
    }
    else
    {
      for(int i = 0; i<-scaleVec[1]; i++)
      {
        scaleMatrix[1][1] *= 1/0.95;
      }
    }

    if (scaleVec[2] >= 0)
    {
      for(int i = 0; i<scaleVec[2]; i++)
      {
        scaleMatrix[2][2] *= 0.95;
      }
    }
    else
    {
      for(int i = 0; i<-scaleVec[2]; i++)
      {
        scaleMatrix[2][2] *= 1/0.95;
      }
    }

    scalingMatrix->Invert();

    m_InputNode->GetData()->GetGeometry()->Compose( scalingMatrix );
    m_InputNode->GetData()->Modified();
    mitk::DataStorage::SetOfObjects::ConstPointer children = this->GetDataStorage()->GetDerivations(m_InputNode);
    unsigned long size;
    size = children->Size();
    mitk::DataNode::Pointer childNode;
    for (unsigned long i = 0; i < size; ++i)
    {
      childNode = children->GetElement(i);
      childNode->GetData()->GetGeometry()->Compose( scalingMatrix );
      childNode->GetData()->Modified();
    }
    //m_RedoGeometryList.clear();

    mitk::RenderingManager::GetInstance()->RequestUpdateAll();
  }
}