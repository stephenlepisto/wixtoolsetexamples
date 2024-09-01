# WiX Toolset Examples
by Stephen P. Lepisto

### Copyright (c) 2024 Stephen P. Lepisto
### Licensed under the MIT License.  See LICENSE.md for details.


# Overview
This repository contains a single Visual Studio 2022 solution with seven projects.
Six of the projects are WiX-based installer/setup projects and the last project
is the payload installed by the setup projects.  Five setup projects are examples
of the five template types provided by the `WiX.Toolset.ui.wixext`
extension for the WiX application.  The sixth setup project provides two typical
customizations to one of the templates.  The five template types are:
1. Advanced
2. FeatureTree
3. InstallDir
4. Minimal
5. Mondo

The WiX Toolset documentation (start here: https://wixtoolset.org/docs/intro/)
explains these but, for me, the documentation lacks some clear examples of how
to use each template and how to implement custom features in those templates.
That is what these example setup projects attempt to cover in more detail.

## WiX in Brief
WiX is a relatively thin wrapper around the Microsoft Installer technology that
results in .MSI files, the core install package for Windows.  The Microsoft
Installer is a complex web of relational databases that connects a wide variety
of elements that control installation/update/repair/removal of even the most
complex product.  In fact, the Microsoft Installer grew out of the effort for
delivering Microsoft Office in the early 2000's, with its numerous products,
each with dozens of optional features.

However, creating a .MSI file directly of even a small size can be a daunting
task and is easily a full-time job for any product that has even just a few
components.  The WiX Toolset helps create robust and useful install packages in
a fraction of the time without needing to work directly with any databases.

WiX accomplishes this by using XML to describe the components, features, and
various dialog boxes used in a .MSI file in XML.  At a high level, there is a
`<Package>` tag that contains one or more `<Feature>` tags and each feature
contains one or more `<Component>` tags.  A `<Component>` tag contains
`<File>`, `<Shortcut>`, and `<RegistryValue>` tags that describe individual
files.  And the `<Directory>` and `<StandardDirectory>` tags describe the
directory layout of the installed product.

There is much, much more to WiX than that, such as "Burn Bundles", which support
install packages that contain multiple install packages (for example, to support
installing dependencies).  These setup project examples do _not_ cover such
bundles or custom Bootstrapper Applications (the user interface that drives the
installation).  See https://wixtoolset.org/docs/tools/burn/ to start learning
about Burn Bundles.

## In This Repository
The five template types provided by WiX should have sufficient functionality for
most install packages with just a little effort.  The examples here show various
ways to install an application with an optional set of documentation.  All the
examples accomplish the same thing: Install the `(Really) Simple App` along with
a `README.txt` file in a `Docs/` sub-directory (representing the optional
"documentation").  Each example presents to the user different levels of control
over the install process.  The `Minimal` example has no control (a "one-button
install") while the `Mondo` example has maximum control.  All the setup projects
here support silent install and uninstall for automated systems (it's built
into WiX).

The files in each of the setup projects have lots of comments to point out
interesting features.

# How to Build

## Minimum Requirements

1. Windows 10 or later

   _Note: Developed on Windows 10_

2. Visual Studio 2022
   
   *Note: any edition; this project was developed on the Community Edition*

   Visual Studio Extensions:
   - "HeatWave for VS2022" Extension (for WiX v4 project templates)
 
3. Git for Windows
   
   Download from https://gitforwindows.org/

4. WiX.Toolset.ui.wixext NuGet package version 5.0.1

   This is automatically installed when the `wixtoolsetexamples` solution is
   first loaded into Visual Studio on a system without the WiX extension
   already installed.
   
5. WiX.Toolset.SDK NuGet package
   
   The `WiX.Toolset.ui.wixext` depends on this and is automatically installed
   when that extension is installed.


## Building the Code
1. Open a Windows Command Prompt and create a directory where to download the
   WiX Toolset Examples repository.   For example:
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cmd}
   cd %HOMEPATH%
   md work
   cd work
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Change "`%HOMEPATH%`" to a more preferred root folder, if desired.
2. Use git to get the example source code from GitHub.com:
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cmd}
   git https://github.com/stephenlepisto/wixtoolsetexamples.git
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
3. Start Visual Studio 2022, select the option to load an existing solution,
   then navigate to where the wixtoolsetexamples were downloaded and load the 
   `wixtoolsetexamples.sln` solution file.
4. From the Visual Studio menu, select `Build` > `Batch Build...` to open the
   Batch Build dialog box.
5. Click the `Select All` button then click the `Build` button.
6. The resulting installation files appear in
   `build\setup\<Platform>\<Configuration>\en-US\`, like this:
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cmd}
   SimpleAppSetup-adv.msi
   SimpleAppSetup-cus.msi
   SimpleAppSetup-fea.msi
   SimpleAppSetup-ins.msi
   SimpleAppSetup-min.msi
   SimpleAppSetup-mon.msi
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Where `<Platform>` is "x86" or "x64" and `<Configuration>` is "Debug" or
   "Release".  For example, `build\x64\Debug\en-US\`.

   The suffixes on the base filename indicate the type of install process
   contained within.

   | Abbreviation | Description                 |
   | ------------ | --------------------------- |
   | `adv`        | Advanced template           |
   | `cus`        | InstallTree Custom template |
   | `fea`        | FeatureTree template        |
   | `ins`        | InstallTree template        |
   | `min`        | Minimal template            |
   | `mon`        | Mondo template              |

# The WiX Toolset Examples
The first project in the wixtoolsetexamples solution is the `SimpleApp` project.
This is a C++ console application that prints "Hello World!".  It has separate
documentation consisting of a single `README.txt` file.  The documentation is
considered optional.  Two shortcuts are added to the Start menu in a folder,
where one shortcut runs the program while the other shortcut uninstalls the
application.

The remaining six projects are the various WiX install projects built around
the five WiX Toolset Install Type Templates (as described below) plus one setup
project that contains two customizations (also described below).  The goal of
each install project is to install the SimpleApp application and the (optional)
associated documentation file.  Building everything builds a 32-bit application
with a 32-bit installer, a 64-bit application with a 64-bit installer, in a
Debug and Release configuration of each, for a total of 24 install files.

It is possible to install the 32-bit and 64-bit versions side-by-side, although
the applications will end up in different locations unless overridden by the
user.

It is _not_ possible to install the Debug and Release versions side-by-side as
the application files will step on each other.

All of the installers, except Minimal, supports changing what is installed
(well, only the documentation is optional so that can be added or removed
separately) by running the installer again.  All installers support the Repair
option.  And, of course, all installers support the Remove option.

All installers support a silent install and uninstall.  To see the command line
options, run the installer from the command line with the `/?` switch.

## To Install SimpleApp
There are three ways to launch the installer file:
1. Open Windows Explorer, navigate to the folder containing the installer file
   (for example, `%HOMEPATH%\work\wixtoolsetexamples\build\setup\x64\Release\en-US\`)
   and either double-click on the file (for example, `SimpleAppSetup-min.msi`)
   or right-click on the file and select __Install__
2. From a Command Prompt, navigate to the folder containing the installer file,
   type the name of the installer file, and press Enter (you can also just
   enter the full path to the installer file).  For example:
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   cd %HOMEPATH%\work\wixtoolsetexamples\build\setup\x64\Release\en-US\
   SimpleAppSetup-min.msi
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
3. From a Command Prompt, run the msiexec program with the path to the installer
   file as the argument.  For example:
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   msiexec %HOMEPATH%\work\wixtoolsetexamples\build\setup\x64\Release\en-US\SimpleAppSetup-min.msi
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## To Uninstall SimpleApp
There are three basic ways to uninstall SimpleApp after it is installed.
1. Right-click on the Windows Start icon and select _Apps and Features_, then
   type "SimpleApp" in the search box, click on the found entry and click the
   _Uninstall_ button.
2. Open the Start menu and find the `SimpleApp` folder icon, open it, and select
   the, for example, `SimpleApp-min-64bit uninstall` to launch the shortcut.
   Click The "Yes" button to uninstall.
3. Run the installer file (see the __To Install SimpleApp__ section), click the
   Next button, click the Remove button, and click the Remove button (again),
   and finally, click the Finish button to close the installer.

# The WiX Install Type Templates
_WiXUI dialog library documentation: https://wixtoolset.org/docs/tools/wixext/wixui/_

Running an install file created by WiX provides several variations on the
installation process that all follow the Windows Wizard format (one or more
pages that are moved through with a "Next" button).  The five templates
described below provide a variety of installation experiences that should cover
most use cases for installing a product.

Note that with WiX, it is possible to customize every dialog box and to add
custom actions, if desired.  The usual process is to take an existing template
and then tweak it for the desired use case.  See the **Customized Installer**
section below for a simple example of doing this.

By replacing the WiX Standard Bootstrapper Application extension (which supports
a customizable Wizard-style interface), a completely custom user interface can
be created but that is way beyond the scope of these examples and requires
detailed knowledge of how the Microsoft Installer technology works. See
https://wixtoolset.org/docs/tools/burn/wixstdba/ for a little more about
replacing the standard WiX Standard Bootstrapper Application extension.

## Advanced Template
__IMPORTANT! Based on the comments in the WixUI_Advanced.wxs template file,
the Advanced template is subject to changes in the future that are likely to be
incompatible with the current form.  However, this warning has been in the code
since March of 2014 so either the warning was never removed/updated or the
hinted-at changes have never materialized.__

Provides a one-click installer with the following pages:
1. End User License Agreement (EULA) Page with Advanced button and Install button
2. Clicking the Advanced button provides the following pages:
   1. Installation Scope page (per-user or per-machine)
   2. Selecting per-user then the Next button jumps to the Product Features list
   3. Selecting per-machine then the Next button shows
      1. Destination Folder (Install Directory) page
      2. Clicking the Next button jumps to the Project Features list
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
1. Welcome page combined with the EULA and the Install button
2. Clicking the Install button shows the Installation Process page and then
3. The Exit page
 
## Mondo Template
Provides a one-click installer with the following pages:
1. Welcome page with Next button
2. EULA page with Next button
3. Setup Type page with Typical, Custom, and Complete buttons
   1. Selecting Typical jumps to Ready to Install page
   2. Selecting Custom jumps to a Product Feature list, with option to change
      the Destination Folder, and the Next button
      1. Selecting Next jumps to the Ready to Install page
   3. Selecting Complete jumps to the Ready to Install page
4. Ready to Install page with Install button
5. Clicking the Install button shows the Installation Process page and then
6. The Exit page

The Typical setup type installs only those features that are considered
required, while the Complete setup type installs all features even if they are
considered optional.

# Customized Installer
This installer (`SimpleAppSetup-cus`) is a copy of the InstallDir installer but
with the following customizations:
1. A checkbox is added to the `ExitDialog` (the "Exit" page) that, when checked,
   causes the application to be launched when the Finish button is clicked.
2. A checkbox is added to the `VerifyReadyDlg` ("Ready to Install" page) that,
   when checked, causes a shortcut to the application to be added to the user's
   desktop during installation.

## ExitDialog Checkbox
The first customization takes advantage of an optional checkbox that is already
part of the `ExitDialog`.  By defining the text for the checkbox (by setting the
property `WIXUI_EXITDIALOGOPTIONALCHECKBOXTEXT`), the checkbox is shown.  A
custom action is attached to the Finish button to trigger the launch of the
application when the installer exits.

## Desktop Shortcut Checkbox
The second customization requires adding a new checkbox and that requires
modifying an existing dialog box to create a new dialog box with a new ID.  And
that, in turn, requires modifying the parent installer template (in this case,
`WixUI_InstallDir`) to use the new dialog box.  And that requires giving the
template a new ID as well.

Download the `VerifyReadyDlg.wxs` and `WixUI_InstallDir.wxs` files from the WiX
Toolset source (in this case, v5.0.1 of the WiX Toolset at
https://github.com/wixtoolset/wix/blob/v5.0.1/src/ext/UI/wixlib) and move them
into the `SimpleAppSetup-cus/` directory.  Alter the dialog ID and template ID
for each and then make changes to the dialog and template.  Finally, modify
`Package.wxs` to refer to the new WixUI_InstallDir template.  This has already
been done for this project.

The desktop shortcut has been added as a separate component so that it can be
conditionally included if the new checkbox is selected when the installer is
run (an individual `<Shortcut>` tag cannot be made conditional so it is wrapped
in a `<Component>` tag that can be made conditional).  If the desktop shortcut
is installed, it will be automatically uninstalled when the application is
uninstalled.

