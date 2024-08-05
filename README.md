# WiX Toolset Examples
by Stephen P. Lepisto

### Copyright (c) 2024 Stephen P. Lepisto
### Licensed under the MIT License.  See LICENSE.md for details.


# Overview
This repository contains a single Visual Studio 2022 solution with six projects.
Five of the projects are WiX-based installer/setup projects and the sixth
project is the payload installed by the setup projects.  The five setup projects
are examples of the five template types provided by the WiX Toolset extension
for Visual Studio.  Namely:
1. Advanced
2. FeatureTree
3. InstallDir
4. Minimal
5. Mondo

These examples do _not_ show any customized dialog boxes and they do _not_ show
the use of custom actions (I have never needed those in my use cases).  However,
WiX Toolset does support customized dialog boxes and custom actions.  The WiX
Toolset documentation covers those two topics fairly well.

WiX is a relatively thin wrapper around the Windows Installer technology that
results in .MSI files.  The Windows Installer is a complex web of a relational
database that connects a wide variety of elements that control installation of
even the most complex product.  In fact, the Windows Installer grew out of the
effort of delivering Microsoft Office in the early 2000's.

However, creating a .MSI file of even a small size can be a daunting task and
is easily a full-time job for any product that has just a few components.  The
WiX toolset aims to make creating robust and useful install packages in a
fraction of the time without needing to create any databases.  Well, at least
not needing to directly create any databases.

WiX accomplishes this by using XML to describe the components, features, and
various dialog boxes used in a .MSI file in XML.  At a high level, there is a
\<Package> tag that contains one or more \<Feature> tags and each feature
contains one or more \<Component> tags.  A \<Component> tag contains \<File>,
\<Shortcut>, and \<RegistryValue> tags that describe individual files.  And the
\<Directory> tag describes the directory layout of the installed product.

There is much, much more to WiX than that.  The five template types provided by
WiX should have sufficient functionality for most install packages with just a
little effort.  The examples show various ways to install an application with
an optional set of documentation.  All the examples accomplish the same thing:
Install the (Really) Simple App along with a README.txt file in a Docs/
sub-directory (representing the optional "documentation").  Each example
provides different levels of control for the user over the install process.
The Minimal example has no control while the Mondo example has maximum control.

# How to Build

## Minimum Requirements

Note: These examples are for Windows only.

1. Windows 10 or later

   Developed on Windows 10.

2. Visual Studio 2022
   
   any edition; this project was developed on the Community Edition.

3. Git for Windows
   
   Download from https://gitforwindows.org/

4. WiX.Toolset.ui.wixext NuGet package

   This will be automatically installed when the wixtoolsetexamples solution is
   first loaded into Visual Studio on a system without the WiX extension
   already installed.
   
5. WiX.Toolset.SDK NuGet package
   
   The WiX.Toolset.ui.wixext depends on this and is automatically installed
   when that extension is installed.


## Building the Code
1. Open a Windows Command Prompt and create a directory where to download the
   WiX Toolset Examples repository.   For example:
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cmd}
   cd %HOMEPATH%
   md work
   cd work
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
2. Use git to get the examples from GitHub.com:
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cmd}
   git https://github.com/stephenlepisto/wixtoolsetexamples.git
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
3. Start Visual Studio 2022, select the option to load an existing solution,
   then navigate to where the wixtoolsetexamples were downloaded and load the 
   wixtoolsetexamples.sln solution file.
4. From the Visual Studio menu, select `Build` > `Batch Build...` to open the
   Batch Build dialog box.
5. Click the `Select All` button then click the `Build` button.
6. The resulting installation files appear in
   `build\setup\<Platform>\<Configuration>\en-US\`, like this:
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cmd}
   SimpleAppSetup-adv.msi
   SimpleAppSetup-fea.msi
   SimpleAppSetup-ins.msi
   SimpleAppSetup-min.msi
   SimpleAppSetup-mon.msi
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   The suffices on the main filename indicate the type of install process
   contained within.

   | Abbreviation | Description          |
   | ------------ | -------------------- |
   | `adv`        | Advanced template    |
   | `fea`        | FeatureTree template |
   | `ins`        | InstallTree template |
   | `min`        | Minimal template     |
   | `mon`        | Mondo template       |

# The WiX Toolset Examples
The first project in the wixtoolsetexamples solution is the SimpleApp project.
This is a C++ console application that prints "Hello World!".  It has separate
documentation consisting of a single README.txt file.  The documentation is
considered optional.  Shortcuts are added to the Start menu in a folder, where
one shortcut runs the program while the other shortcut uninstalls the
application.

The remaining five projects are the various WiX install projects built around
the five WiX Toolset Install Type Templates as described below.  The goal of
each install project is to install the SimpleApp application and the (optional)
associated documentation file.  Building everything builds a 32-bit application
with a 32-bit installer, a 64-bit application with a 64-bit installer, in a
Debug and Release configuration of each, for a total of 20 install files.

It is possible to install the 32-bit and 64-bit versions side-by-side, although
the applications will end up in different locations unless overridden by the
user.

It is _not_ possible to install the Debug and Release versions side-by-side as
the application files will step on each other.

All of the installers, except Minimal, supports changing what is installed
(well, only the documentation is optional so that can be added or removed
separately) by running the installer again.  All installers support the Repair
option.  And, of course, all installer support the Remove option.

All installers support a silent install and uninstall.  To see the command line
options, run the installer from the command line with the `/?` switch.

# The WiX Install Type Templates
Running an install file created by WiX provides several variations on the
installation process.  The five templates described below provide a variety of
installation experiences that should cover most use cases for installing a
product.

Note that with WiX, it is possible to customize every dialog box and to add
custom actions, if desired.  The usual process is to take an existing template
and then tweak it for the desired use case.  The Wix Toolset Examples presented
here do _not_ show that level of customization nor the use of custom actions.

## Advanced Template
__IMPORTANT! Based on the comments in the WixUI_Advanced.wxs template file,
the Advanced template is subject to changes in the future that are likely to be
incompatible with the current form.  However, this warning has been in the code
since March of 2014 so either the warning was never updated or the promised
changes have never materialized.__

Provides a one-click installer with the following pages:
1. EULA Page with Advanced button and Install button
2. Clicking the Advanced button provides the following pages:
   1. Installation Scope page (per-user or per-machine)
   2. Selecting per-user then Next jumps to the Product Features list
   3. Selecting per-machine then Next shows
      1. Destination Folder (Install Directory) page
   4. Product Features list with Install button
3. Clicking the Install button shows the Installation Process page and then
4. The Exit page

## FeatureTree Template
Provides an installer with the following pages:
1. Welcome page with Next button
2. EULA page with Next button
3. Product Feature List with option to change the Destination Folder with Next button
4. Ready to Install page with Install button
5. Clicking the Install button shows the Installation Process page and then
6. The Exit page
 
## InstallDir Template
Provides an installer with the following pages:
1. Welcome page with Next button
2. EULA page with Next button
3. Destination Folder (Install Directory) page with Next button
4. Ready to Install page with Install button
5. Clicking the Install button shows the Installation Process page and then
6. The Exit page
 
## Minimal Template
Provides a one-click installer with the following pages:
1. Welcome page combined with EULA with Install button
2. Clicking the Install button shows the Installation Process page and then
3. The Exit page
 
## Mondo Template
Provides a one-click installer with the following pages:
1. Welcome page with Next button
2. EULA page with Next button
3. Setup Type page with Typical, Custom, and Complete buttons
   1. Selecting Typical jumps to Ready to Install page
   2. Selecting Custom jumps to a Product Feature list with option to change
      the Destination Folder with Next button
      1. Selecting Next jumps to the Ready to Install page
   3. Selecting Complete jumps to the Ready to Install page
4. Ready to Install page with Install button
5. Clicking the Install button shows the Installation Process page and then
6. The Exit page

The Typical setup type installs only those features that are considered
required, while the Complete setup type installs all features even if they are
considered optional.
