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


#include <berryStarter.h>
#include <Poco/Util/MapConfiguration.h>

#include <QApplication>

int main(int argc, char** argv)
{
  // Create a QApplication instance first
  QApplication myApp(argc, argv);
  myApp.setApplicationName("NICATest_ProjectAppName");
  myApp.setOrganizationName("DKFZ, Medical and Biological Informatics");

  // These paths replace the .ini file and are tailored for installation
  // packages created with CPack. If a .ini file is presented, it will
  // overwrite the settings in MapConfiguration
  Poco::Path basePath(argv[0]);
  basePath.setFileName("");
  
  Poco::Path provFile(basePath);
  provFile.setFileName("NICATest_ProjectAppName.provisioning");

  Poco::Util::MapConfiguration* sbConfig(new Poco::Util::MapConfiguration());
  sbConfig->setString(berry::Platform::ARG_PROVISIONING, provFile.toString());
  sbConfig->setString(berry::Platform::ARG_APPLICATION, "org.mitk.qt.extapplication");
  return berry::Starter::Run(argc, argv, sbConfig);
}
